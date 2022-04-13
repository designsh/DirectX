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
	// ���� ���� ��� �θ� �����ִٸ�
	if (nullptr != Parent_)
	{
		// ���� �����ִ� �θ𿡰� ���� �ڽ��� �ڽĿ���
		// �������ֱ⸦ ��û�Ѵ�.
		Parent_->DetachChildTransform(this);
	}

	// �θ� ���������ʴٸ�
	Parent_ = _Transform;
	_Transform->Childs_.push_back(this);
}

void GameEngineTransform::DetachChildTransform(GameEngineTransform* _Transform)
{
	// �ڽ��� �ڽ��� �������ֱ⸦ ��û�����Ƿ�
	// �ڽĸ�Ͽ��� �ش� �ڽ��� ����
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
	// �θ��� ũ�Ⱑ ����Ǿ� �ش� �Լ��� ȣ��Ǿ��ٴ� �ǹ��̸�,
	// �ش� �θ� ������ ��� �ڽĵ��� �θ��� ũ�⺯ȭ�� ����
	// ��� �ڽĵ��� ������ ����ũ�� ��ȭ �� ������ġ ��ȭ�� �Ͼ��.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	// �θ��� ȸ���� ����Ǿ� �ش� �Լ��� ȣ��Ǿ��ٴ� �ǹ��̸�,
	// �ش� �θ� ������ ��� �ڽĵ��� �θ��� ȸ����ȭ�� ����
	// ��� �ڽĵ��� ������ ����ȸ�� ��ȭ �� ������ġ ��ȭ�� �Ͼ��.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	// �θ��� ��ġ�� ����Ǿ� �ش� �Լ��� ȣ��Ǿ��ٴ� �ǹ��̸�,
	// �ش� �θ� ������ ��� �ڽĵ��� �θ��� ȸ����ȭ�� ����
	// ��� �ڽĵ��� ������ ������ġ ��ȭ�� �Ͼ��.
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();
		Child->AllChildCalculationPosition();
	}
}

void GameEngineTransform::CalculationLocalScaling()
{
	// �ڽ��� ����ũ�� = �ڽ��� ����ũ�� / �θ��� ����ũ��
	TransformData_.vLocalScaling_ = TransformData_.vWorldScaling_ / Parent_->TransformData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	// �ڽ��� ����ũ�� = �θ��� ����ũ�� * �ڽ��� ����ũ��
	TransformData_.vWorldScaling_ = Parent_->TransformData_.vWorldScaling_ * TransformData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ�� - �θ��� ����ȸ��
	TransformData_.vLocalRotation_ = TransformData_.vWorldRotation_ - Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	// �ڽ��� ����ȸ�� = �θ��� ����ȸ�� + �ڽ��� ����ȸ��
	TransformData_.vWorldRotation_ = Parent_->TransformData_.vWorldRotation_ + TransformData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// ���� : ȸ�� * �̵�
	// ���� : �̵� * ȸ��(������ ������ �������)

	// �ڽ��� ������ġ�� ����Ͽ� �ƹ��� ������ �����ʰ� ��ġ���� ������� ������ġ�� ����ϰ�,
	float4 LocalPosition = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;

	// ������ġ�� ���ؼ� �θ��� ����ȸ���� �����͸� ���Ͽ� ȸ���� �����ϰ�
	LocalPosition.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);

	// �θ��� ũ�⸦ ������� �������� ��ġ�� ����Ѵ�.
	// ��, �θ��� ũ�Ⱑ 0�̸� 0�������°ŹǷ� ������.
	LocalPosition /= Parent_->TransformData_.vWorldScaling_;

	// �������� �θ��� ũ��/ȸ��/��ġ�� ������� ���� ������ġ�� ����Ѵ�.
	TransformData_.vLocalPosition_ = LocalPosition;
}

void GameEngineTransform::CalculationWorldPosition()
{
	// �ڽ��� ������ġ�� �����ͼ�
	float4 CalWorldPos = TransformData_.vLocalPosition_;

	// ũ�⸦ ������Ű��
	CalWorldPos *= Parent_->TransformData_.vWorldScaling_;

	// ȸ���� ��Ű��
	CalWorldPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);

	// �θ��� ��ġ�� �̵��Ѵ�.
	CalWorldPos += Parent_->TransformData_.vWorldPosition_;

	// �̸� �ڽ��� ������ġ�� ���
	TransformData_.vWorldPosition_ = CalWorldPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	// ����ũ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ũ�� = �ڽ��� ����ũ��
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationScaling();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vLocalScaling_ = _Value;

	// �θ��� ������ �޴� �ڽ��� ����ũ�⸦ ���
	CalculationWorldScaling();

	// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
	AllChildCalculationScaling();

	// ��� ��Ŀ� ����
	TransformUpdate();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	// ����ũ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ũ�� = �ڽ��� ����ũ��
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationScaling();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vWorldScaling_ = _Value;

	// �θ��� ������ �޴� �ڽ��� ����ũ�⸦ ���
	CalculationLocalScaling();

	// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
	AllChildCalculationScaling();

	// ��� ��Ŀ� ����
	TransformUpdate();
}

void GameEngineTransform::SetLocalRotationDegree(const float4& _Value)
{
	// ����ȸ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ��
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationRotation();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vLocalRotation_ = _Value;

	// �θ��� ������ �޴� ����ȸ���� ���
	CalculationWorldRotation();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationRotation();

	// ��� ��Ŀ� ����
	TransformUpdate();
}

void GameEngineTransform::SetWorldRotationDegree(const float4& _Value)
{
	// ����ȸ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ��
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationRotation();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vWorldRotation_ = _Value;

	// �θ��� ������ �޴� ����ȸ���� ���
	CalculationLocalRotation();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationRotation();

	// ��� ��Ŀ� ����
	TransformUpdate();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	// ������ġ ���͸� �������� ���

	// �θ� ���������ʴ´ٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ������ġ = �ڽ��� ������ġ
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;

		// �ڽ��� �����Ѵٸ� ��� ���
		AllChildCalculationPosition();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vLocalPosition_ = _Value;

	// �θ��� ������ �޴� ������ġ�� ���
	CalculationWorldPosition();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationPosition();

	// ��� ��Ŀ� ����
	TransformUpdate();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	// ������ġ ���͸� �������� ���

	// �θ� ���������ʴ´ٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ������ġ = �ڽ��� ������ġ
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;

		// �ڽ��� �����Ѵٸ� ��� ���
		AllChildCalculationPosition();

		// ��� ��Ŀ� ����
		TransformUpdate();

		return;
	}

	// �θ� �����Ѵٸ�
	TransformData_.vWorldPosition_ = _Value;

	// �θ��� ������ �޴� ������ġ�� ���
	CalculationLocalPosition();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationPosition();

	// ��� ��Ŀ� ����
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

	// ���� �� �ڽĵ���� ��� ��� ��
	AllChildCalculationScaling();
	AllChildCalculationRotation();
	AllChildCalculationPosition();

	// ������Ʈ
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
	// ���� ���� ũ��/ȸ��(����)/��ġ ����� �����ϰ�,
	// �� ������ ���� ���ÿ�������� ����
	TransformData_.LocalCalculation();

	// ���� �θ� �����Ѵٸ�
	if (nullptr != Parent_)
	{
		// �ڽ��� ������� = �ڽ��� ���ÿ������
		// �ڽ��� ������� *= �θ��� �������
		TransformData_.ParentSetting(Parent_->TransformData_.WorldWorld_);
	}
	else // ���� �θ� ���������ʴٸ�
	{
		// �ڽ��� ������� = �ڽ��� �������
		TransformData_.RootCalculation();
	}

	// �浹 ������ ����
	ColData_.OBB.Extents = TransformData_.vWorldScaling_.halffloat4().DxXmfloat3;
	ColData_.OBB.Orientation = TransformData_.vWorldRotation_.ToDegreeQuaternion().DxXmfloat4;
	ColData_.OBB.Center = TransformData_.vWorldPosition_.DxXmfloat3;

	// 
	for (GameEngineTransform* ChildTransform_ : Childs_)
	{
		ChildTransform_->TransformUpdate();
	}
}
