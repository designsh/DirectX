#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() :
	TransformData_{},
	Parent_(nullptr)	
{
}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::AttachTransform(GameEngineTransform* _Transform)
{
	// 현재 내가 어떠한 부모에 속해있다면
	if (nullptr != Parent_)
	{
		// 현재 속해있는 부모에게 나를 자신의 자식에서
		// 제거해주기를 요청한다.
		Parent_->DetachChildTransform(this);
	}

	// 부모가 존재하지않다면
	Parent_ = _Transform;
	_Transform->Childs_.push_back(this);
}

void GameEngineTransform::DetachChildTransform(GameEngineTransform* _Transform)
{
	// 자식이 자신을 해제해주기를 요청했으므로
	// 자식목록에서 해당 자식을 제거
	static std::vector<GameEngineTransform*>::iterator StartIter = Childs_.begin();
	static std::vector<GameEngineTransform*>::iterator EndIter = Childs_.end();
	for (; StartIter != EndIter; )
	{
		if (*StartIter != _Transform)
		{
			++StartIter;
			continue;
		}

		StartIter = Childs_.erase(StartIter);
	}
}

TransformData& GameEngineTransform::GetTransformData()
{
	return TransformData_;
}

void GameEngineTransform::AllChildCalculationScaling()
{
	// 부모의 크기가 변경되어 해당 함수가 호출되었다는 의미이며,
	// 해당 부모가 가지는 모든 자식들은 부모의 크기변화로 인해
	// 모든 자식들은 각각의 월드크기 변화 및 월드위치 변화가 일어난다.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	// 부모의 회전이 변경되어 해당 함수가 호출되었다는 의미이며,
	// 해당 부모가 가지는 모든 자식들은 부모의 회전변화로 인해
	// 모든 자식들은 각각의 월드회전 변화 및 월드위치 변화가 일어난다.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	// 부모의 위치가 변경되어 해당 함수가 호출되었다는 의미이며,
	// 해당 부모가 가지는 모든 자식들은 부모의 회전변화로 인해
	// 모든 자식들은 각각의 월드위치 변화가 일어난다.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();
		Child->AllChildCalculationPosition();
	}
}

void GameEngineTransform::CalculationLocalScaling()
{
	// 자신의 로컬크기 = 자신의 월드크기 / 부모의 월드크기
	TransformData_.vLocalScaling_ = TransformData_.vWorldScaling_ / Parent_->TransformData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	// 자신의 월드크기 = 부모의 월드크기 * 자신의 로컬크기
	TransformData_.vWorldScaling_ = Parent_->TransformData_.vWorldScaling_ * TransformData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	// 자신의 로컬회전 = 자신의 월드회전 - 부모의 월드회전
	TransformData_.vLocalRotation_ = TransformData_.vWorldRotation_ - Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	// 자신의 월드회전 = 부모의 월드회전 + 자신의 로컬회전
	TransformData_.vWorldRotation_ = Parent_->TransformData_.vWorldRotation_ + TransformData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// 자전 : 회전 * 이동
	// 공전 : 이동 * 회전(공전은 자전의 역순계산)

	// 자신의 로컬위치를 계산하여 아무런 영향을 받지않고 위치만을 영향받은 로컬위치를 계산하고,
	float4 LocalPosition = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;

	// 로컬위치를 통해서 부모의 월드회전의 역벡터를 통하여 회전을 적용하고
	LocalPosition.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);

	// 부모의 크기를 영향받은 최종적인 위치를 계산한다.
	// 단, 부모의 크기가 0이면 0을나누는거므로 터진다.
	LocalPosition /= Parent_->TransformData_.vWorldScaling_;

	// 최종적인 부모의 크기/회전/위치를 영향받은 나의 로컬위치를 계산한다.
	TransformData_.vLocalPosition_ = LocalPosition;
}

void GameEngineTransform::CalculationWorldPosition()
{
	// 자신의 로컬위치를 가져와서
	float4 CalWorldPos = TransformData_.vLocalPosition_;

	// 크기를 증가시키고
	CalWorldPos *= Parent_->TransformData_.vWorldScaling_;

	// 회전을 시키고
	CalWorldPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);

	// 부모의 위치로 이동한다.
	CalWorldPos += Parent_->TransformData_.vWorldPosition_;

	// 이를 자신의 월드위치로 계산
	TransformData_.vWorldPosition_ = CalWorldPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	// 로컬크기 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드크기 = 자신의 로컬크기
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationScaling();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vLocalScaling_ = _Value;

	// 부모의 영향을 받는 자신의 월드크기를 계산
	CalculationWorldScaling();

	// 자식이 존재한다면 자식을 모두 계산
	AllChildCalculationScaling();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	// 월드크기 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드크기 = 자신의 로컬크기
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationScaling();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vWorldScaling_ = _Value;

	// 부모의 영향을 받는 자신의 로컬크기를 계산
	CalculationLocalScaling();

	// 자식이 존재한다면 자식을 모두 계산
	AllChildCalculationScaling();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::SetLocalRotationDegree(const float4& _Value)
{
	// 로컬회전 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드회전 = 자신의 로컬회전
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationRotation();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vLocalRotation_ = _Value;

	// 부모의 영향을 받는 월드회전을 계산
	CalculationWorldRotation();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationRotation();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::SetWorldRotationDegree(const float4& _Value)
{
	// 월드회전 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드회전 = 자신의 로컬회전
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationRotation();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vWorldRotation_ = _Value;

	// 부모의 영향을 받는 로컬회전을 계산
	CalculationLocalRotation();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationRotation();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	// 로컬위치 벡터를 수신했을 경우

	// 부모가 존재하지않는다면
	if (nullptr == Parent_)
	{
		// 자신의 월드위치 = 자신의 로컬위치
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;

		// 자식이 존재한다면 모두 계산
		AllChildCalculationPosition();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vLocalPosition_ = _Value;

	// 부모의 영향을 받는 월드위치을 계산
	CalculationWorldPosition();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationPosition();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	// 월드위치 벡터를 수신했을 경우

	// 부모가 존재하지않는다면
	if (nullptr == Parent_)
	{
		// 자신의 월드위치 = 자신의 로컬위치
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;

		// 자식이 존재한다면 모두 계산
		AllChildCalculationPosition();

		// 즉시 행렬에 적용
		TransformUpdate();

		return;
	}

	// 부모가 존재한다면
	TransformData_.vWorldPosition_ = _Value;

	// 부모의 영향을 받는 로컬위치을 계산
	CalculationLocalPosition();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationPosition();

	// 즉시 행렬에 적용
	TransformUpdate();
}

void GameEngineTransform::AddLocalDeltaTimeRotation(const float4& _Value)
{
	SetLocalRotationDegree(TransformData_.vLocalRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
}

void GameEngineTransform::AddWorldDeltaTimeRotation(const float4& _Value)
{
	SetWorldRotationDegree(TransformData_.vWorldRotation_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
}

void GameEngineTransform::SetLocalDeltaTimeMove(const float4& _Value)
{
	SetLocalPosition(TransformData_.vLocalPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
}

void GameEngineTransform::SetWorldDeltaTimeMove(const float4& _Value)
{
	SetWorldPosition(TransformData_.vWorldPosition_ + _Value * GameEngineTime::GetInst().GetDeltaTime());
}

void GameEngineTransform::AddLocalRotationDegreeX(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.x += _Value;
	SetLocalRotationDegree(Local);
}
void GameEngineTransform::AddWorldRotationDegreeX(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.x += _Value;
	SetWorldRotationDegree(Local);
}

void GameEngineTransform::AddLocalRotationDegreeY(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.y += _Value;
	SetLocalRotationDegree(Local);
}

void GameEngineTransform::AddWorldRotationDegreeY(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.y += _Value;
	SetWorldRotationDegree(Local);
}

void GameEngineTransform::AddLocalRotationDegreeZ(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.z += _Value;
	SetLocalRotationDegree(Local);
}
void GameEngineTransform::AddWorldRotationDegreeZ(const float _Value)
{
	float4 Local = TransformData_.vLocalRotation_;
	Local.z += _Value;
	SetWorldRotationDegree(Local);
}

void GameEngineTransform::SetLocalMove(const float4& _Value)
{
	SetLocalPosition(TransformData_.vLocalPosition_ + _Value);
}

void GameEngineTransform::SetWorldMove(const float4& _Value)
{
	SetWorldPosition(TransformData_.vWorldPosition_ + _Value);
}

void GameEngineTransform::SetLocalZOrder(float _Value)
{
	TransformData_.vLocalPosition_.z = _Value;
	SetLocalPosition(TransformData_.vLocalPosition_);
}

void GameEngineTransform::SetWorldZOrder(float _Value)
{
	TransformData_.vWorldPosition_.z = _Value;
	SetWorldPosition(TransformData_.vWorldPosition_);
}

void GameEngineTransform::Copy(const GameEngineTransform& _Other)
{
	TransformData_ = _Other.TransformData_;
	ColData_ = _Other.ColData_;
	Parent_ = _Other.Parent_;
	Childs_ = _Other.Childs_;

	// 복사 후 자식들까지 모두 계산 후
	AllChildCalculationScaling();
	AllChildCalculationRotation();
	AllChildCalculationPosition();

	// 업데이트
	TransformUpdate();
}

float4 GameEngineTransform::GetLocalScaling() const
{
	return TransformData_.vLocalScaling_;
}

float4 GameEngineTransform::GetWorldScaling() const
{
	return TransformData_.vWorldScaling_;
}

float4 GameEngineTransform::GetLocalRotation() const
{
	return TransformData_.vLocalRotation_;
}

float4 GameEngineTransform::GetWorldRotation() const
{
	return TransformData_.vWorldRotation_;
}

float4 GameEngineTransform::GetLocalPosition() const
{
	return TransformData_.vLocalPosition_;
}

float4 GameEngineTransform::GetWorldPosition() const
{
	return TransformData_.vWorldPosition_;
}

float4 GameEngineTransform::GetWorldForwardVector() const
{
	return TransformData_.WorldWorld_.vz.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalForwardVector() const
{
	return TransformData_.LocalWorld_.vz.NormalizeReturn3D();
}

float4 GameEngineTransform::GetWorldRightVector() const
{
	return TransformData_.WorldWorld_.vx.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalRightVector() const
{
	return TransformData_.LocalWorld_.vx.NormalizeReturn3D();
}

float4 GameEngineTransform::GetWorldUpVector() const
{
	return TransformData_.WorldWorld_.vy.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalUpVector() const
{
	return TransformData_.LocalWorld_.vy.NormalizeReturn3D();
}

float4 GameEngineTransform::GetWorldBackVector() const
{
	return -TransformData_.WorldWorld_.vz.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalBackVector() const
{
	return -TransformData_.LocalWorld_.vz.NormalizeReturn3D();
}

float4 GameEngineTransform::GetWorldLeftVector() const
{
	return -TransformData_.WorldWorld_.vx.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalLeftVector() const
{
	return -TransformData_.LocalWorld_.vx.NormalizeReturn3D();
}

float4 GameEngineTransform::GetWorldDownVector() const
{
	return -TransformData_.WorldWorld_.vy.NormalizeReturn3D();
}

float4 GameEngineTransform::GetLocalDownVector() const
{
	return -TransformData_.LocalWorld_.vy.NormalizeReturn3D();
}

void GameEngineTransform::TransformUpdate()
{
	// 나의 로컬 크기/회전(자전)/위치 행렬을 생성하고,
	// 이 정보를 통해 로컬월드행렬을 생성
	TransformData_.LocalCalculation();

	// 만약 부모가 존재한다면
	if (nullptr != Parent_)
	{
		// 자신의 월드행렬 = 자신의 로컬월드행렬
		// 자신의 월드행렬 *= 부모의 월드행렬
		TransformData_.ParentSetting(Parent_->TransformData_.WorldWorld_);
	}
	else // 현재 부모가 존재하지않다면
	{
		// 자신의 월드행렬 = 자신의 로컬행렬
		TransformData_.RootCalculation();
	}

	// 충돌 데이터 갱신
	ColData_.OBB.Extents = TransformData_.vWorldScaling_.halffloat4().DxXmfloat3;
	ColData_.OBB.Orientation = TransformData_.vWorldRotation_.ToDegreeQuaternion().DxXmfloat4;
	ColData_.OBB.Center = TransformData_.vWorldPosition_.DxXmfloat3;

	// 
	for (GameEngineTransform* ChildTransform_ : Childs_)
	{
		ChildTransform_->TransformUpdate();
	}
}
