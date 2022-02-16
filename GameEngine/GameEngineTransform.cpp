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
	// ���� ���� ��� �θ� �����ִٸ�
	if (nullptr != Parent_)
	{
		// ���� �����ִ� �θ𿡰� ���� �ڽ��� �ڽĿ���
		// �������ֱ⸦ ��û�Ѵ�.
		Parent_->DetachChild(this);
	}

	// �θ� ���������ʴٸ�
	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	// �ڽ��� �ڽ��� �������ֱ⸦ ��û�����Ƿ�
	// �ڽĸ�Ͽ��� �ش� �ڽ��� ����
	Childs_.remove(_Child);
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
	TransData_.vLocalScaling_ = TransData_.vWorldScaling_ / Parent_->TransData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldScaling()
{
	// �ڽ��� ����ũ�� = �θ��� ����ũ�� * �ڽ��� ����ũ��
	TransData_.vWorldScaling_ = Parent_->TransData_.vWorldScaling_ * TransData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ�� - �θ��� ����ȸ��
	TransData_.vLocalRotation_ = TransData_.vWorldRotation_ - Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	// �ڽ��� ����ȸ�� = �θ��� ����ȸ�� + �ڽ��� ����ȸ��
	TransData_.vWorldRotation_ = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// 
	
}

void GameEngineTransform::CalculationWorldPosition()
{
	// �ڽ��� ������ġ�� �����ͼ�
	float4 CalLocalPos = TransData_.vLocalPosition_;

	// ũ�⸦ ������Ű��
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// ȸ���� ��Ű��
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// �θ��� ��ġ�� �̵��Ѵ�.
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	// �̸� �ڽ��� ������ġ�� ���
	TransData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	// ����ũ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ũ�� = �ڽ��� ����ũ��
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationScaling();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vLocalScaling_ = _Value;

	// �θ��� ������ �޴� �ڽ��� ����ũ�⸦ ���
	CalculationWorldScaling();

	// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
	AllChildCalculationScaling();
}

void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	// ����ũ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ũ�� = �ڽ��� ����ũ��
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationScaling();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vWorldScaling_ = _Value;

	// �θ��� ������ �޴� �ڽ��� ����ũ�⸦ ���
	CalculationLocalScaling();

	// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
	AllChildCalculationScaling();
}

void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	// ����ȸ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ��
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationRotation();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vLocalRotation_ = _Value;

	// �θ��� ������ �޴� ����ȸ���� ���
	CalculationWorldRotation();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	// ����ȸ�� ���͸� �������� ���

	// �θ� ���������ʴٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ����ȸ�� = �ڽ��� ����ȸ��
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;

		// �ڽ��� �����Ѵٸ� �ڽ��� ��� ���
		AllChildCalculationRotation();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vWorldRotation_ = _Value;

	// �θ��� ������ �޴� ����ȸ���� ���
	CalculationLocalRotation();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationRotation();
}

void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	// ������ġ ���͸� �������� ���

	// �θ� ���������ʴ´ٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ������ġ = �ڽ��� ������ġ
		TransData_.vLocalPosition_ = _Value;
		TransData_.vWorldPosition_ = _Value;

		// �ڽ��� �����Ѵٸ� ��� ���
		AllChildCalculationPosition();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vWorldPosition_ = _Value;

	// �θ��� ������ �޴� ������ġ�� ���
	CalculationWorldPosition();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationPosition();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	// ������ġ ���͸� �������� ���

	// �θ� ���������ʴ´ٸ�
	if (nullptr == Parent_)
	{
		// �ڽ��� ������ġ = �ڽ��� ������ġ
		TransData_.vLocalPosition_ = _Value;
		TransData_.vWorldPosition_ = _Value;

		// �ڽ��� �����Ѵٸ� ��� ���
		AllChildCalculationPosition();

		return;
	}

	// �θ� �����Ѵٸ�
	TransData_.vLocalPosition_ = _Value;

	// �θ��� ������ �޴� ������ġ�� ���
	CalculationLocalPosition();

	// �ڽ��� �����Ѵٸ� ��� ���
	AllChildCalculationPosition();
}

void GameEngineTransform::TransformUpdate()
{
	// ���� ���� ũ��/ȸ��(����)/��ġ ����� �����ϰ�,
	// �� ������ ���� ���ÿ�������� ����
	TransData_.LocalCalculation();

	// ���� �θ� �����Ѵٸ�
	if (nullptr != Parent_)
	{
		// �ڽ��� ������� = �ڽ��� ���ÿ������
		// �ڽ��� ������� *= �θ��� �������
		TransData_.ParentSetting(Parent_->TransData_.WorldWorld_);
	}
	else // ���� �θ� ���������ʴٸ�
	{
		// �ڽ��� ������� = �ڽ��� �������
		TransData_.RootCalculation();
	}
}
