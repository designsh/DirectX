#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() :
	TransData_{},
	Parent_(nullptr)	
{
}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	// 현재 내가 어떠한 부모에 속해있다면
	if (nullptr != Parent_)
	{
		// 현재 속해있는 부모에게 나를 자신의 자식에서
		// 제거해주기를 요청한다.
		Parent_->DetachChild(this);
	}

	// 부모가 존재하지않다면
	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	// 자식이 자신을 해제해주기를 요청했으므로
	// 자식목록에서 해당 자식을 제거
	Childs_.remove(_Child);
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
	TransData_.vLocalScaling_ = TransData_.vWorldScaling_ / Parent_->TransData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	// 자신의 월드크기 = 부모의 월드크기 * 자신의 로컬크기
	TransData_.vWorldScaling_ = Parent_->TransData_.vWorldScaling_ * TransData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	// 자신의 로컬회전 = 자신의 월드회전 - 부모의 월드회전
	TransData_.vLocalRotation_ = TransData_.vWorldRotation_ - Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	// 자신의 월드회전 = 부모의 월드회전 + 자신의 로컬회전
	TransData_.vWorldRotation_ = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// 
	
}

void GameEngineTransform::CalculationWorldPosition()
{
	// 자신의 로컬위치를 가져와서
	float4 CalLocalPos = TransData_.vLocalPosition_;

	// 크기를 증가시키고
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// 회전을 시키고
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// 부모의 위치로 이동한다.
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	// 이를 자신의 월드위치로 계산
	TransData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	// 로컬크기 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드크기 = 자신의 로컬크기
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationScaling();

		return;
	}

	// 부모가 존재한다면
	TransData_.vLocalScaling_ = _Value;

	// 부모의 영향을 받는 자신의 월드크기를 계산
	CalculationWorldScaling();

	// 자식이 존재한다면 자식을 모두 계산
	AllChildCalculationScaling();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	// 월드크기 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드크기 = 자신의 로컬크기
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationScaling();

		return;
	}

	// 부모가 존재한다면
	TransData_.vWorldScaling_ = _Value;

	// 부모의 영향을 받는 자신의 로컬크기를 계산
	CalculationLocalScaling();

	// 자식이 존재한다면 자식을 모두 계산
	AllChildCalculationScaling();
}

void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	// 로컬회전 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드회전 = 자신의 로컬회전
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationRotation();

		return;
	}

	// 부모가 존재한다면
	TransData_.vLocalRotation_ = _Value;

	// 부모의 영향을 받는 월드회전을 계산
	CalculationWorldRotation();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	// 월드회전 벡터를 수신했을 경우

	// 부모가 존재하지않다면
	if (nullptr == Parent_)
	{
		// 자신의 월드회전 = 자신의 로컬회전
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;

		// 자식이 존재한다면 자식을 모두 계산
		AllChildCalculationRotation();

		return;
	}

	// 부모가 존재한다면
	TransData_.vWorldRotation_ = _Value;

	// 부모의 영향을 받는 로컬회전을 계산
	CalculationLocalRotation();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationRotation();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	// 로컬위치 벡터를 수신했을 경우

	// 부모가 존재하지않는다면
	if (nullptr == Parent_)
	{
		// 자신의 월드위치 = 자신의 로컬위치
		TransData_.vLocalPosition_ = _Value;
		TransData_.vWorldPosition_ = _Value;

		// 자식이 존재한다면 모두 계산
		AllChildCalculationPosition();

		return;
	}

	// 부모가 존재한다면
	TransData_.vWorldPosition_ = _Value;

	// 부모의 영향을 받는 월드위치을 계산
	CalculationWorldPosition();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationPosition();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	// 월드위치 벡터를 수신했을 경우

	// 부모가 존재하지않는다면
	if (nullptr == Parent_)
	{
		// 자신의 월드위치 = 자신의 로컬위치
		TransData_.vLocalPosition_ = _Value;
		TransData_.vWorldPosition_ = _Value;

		// 자식이 존재한다면 모두 계산
		AllChildCalculationPosition();

		return;
	}

	// 부모가 존재한다면
	TransData_.vLocalPosition_ = _Value;

	// 부모의 영향을 받는 로컬위치을 계산
	CalculationLocalPosition();

	// 자식이 존재한다면 모두 계산
	AllChildCalculationPosition();
}

void GameEngineTransform::TransformUpdate()
{
	// 나의 로컬 크기/회전(자전)/위치 행렬을 생성하고,
	// 이 정보를 통해 로컬월드행렬을 생성
	TransData_.LocalCalculation();

	// 만약 부모가 존재한다면
	if (nullptr != Parent_)
	{
		// 자신의 월드행렬 = 자신의 로컬월드행렬
		// 자신의 월드행렬 *= 부모의 월드행렬
		TransData_.ParentSetting(Parent_->TransData_.WorldWorld_);
	}
	else // 현재 부모가 존재하지않다면
	{
		// 자신의 월드행렬 = 자신의 로컬행렬
		TransData_.RootCalculation();
	}
}
