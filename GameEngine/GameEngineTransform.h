#pragma once
#include "GameEngineComponent.h"

class TransformData
{
public:
	// ����
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	// ����
	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	// ��ȯ���
	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	float4x4 Parent_;
	float4x4 WorldWorld_;

	float4x4 View_;
	float4x4 Projection_;

public:
	// ���� ��� ����
	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	// �ڽ��� �θ� �����Ѵ�
	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	// �ڽ��� �θ� �������� �ʴ´�.
	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}
};

// �з� : Ʈ������(Transform)
// �뵵 : 
// ���� : �� ��ü�� ������ǥ���� ��ġ, ũ��, ȸ�� ������ �����ϴ� ����� �����ϰ� �̸� ������� ��ǥ(World Space)�� ��ȯ�ϴ� ����� �����ϴ� Ŭ����
//            ��, �� ��ü�� �θ� ��ü�� ������ �ִ� ��������(�θ�-�ڽ�)�� �̷�� ������� ���ÿ� ���� �θ��� ������ �޾� ��ġ/ũ��/ȸ�� ������ ����ϴ� ��쵵 �ִ�.
class GameEngineTransform
{
private:	// member Var
	TransformData										TransData_;		// ����/���� ũ��/ȸ��/��ġ �� ����, �θ� ����� �����ϴ� Ʈ������ ����
	GameEngineTransform*						Parent_;				// ���� Ʈ�������� �θ� Ʈ������
	std::list<GameEngineTransform*>	Childs_;				// ���� Ʈ�������� �ڽ� Ʈ������ ���

public:
	GameEngineTransform();
	~GameEngineTransform();

protected:		// delete constructer
	GameEngineTransform(const GameEngineTransform& _other) = delete;
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete;

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

public:
	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);

private: // ����ó��
	void AllChildCalculationScaling();									// ��� �ڽ��� ũ�⺯ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)
	void AllChildCalculationRotation();								// ��� �ڽ��� ȸ����ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)
	void AllChildCalculationPosition();								// ��� �ڽ��� ��ġ��ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)

	// ũ�����
	void CalculationLocalScaling();										// �ڽ��� ���� ũ������� ���
	void CalculationWorldScaling();										// �ڽ��� ���� ũ������� ���

	// ȸ�����
	void CalculationLocalRotation();									// �ڽ��� ���� ȸ������� ���
	void CalculationWorldRotation();									// �ڽ��� ���� ȸ������� ���

	// �̵����
	void CalculationLocalPosition();										// �ڽ��� ���� ��ġ����� ���
	void CalculationWorldPosition();									// �ڽ��� ���� ��ġ����� ���

public:
	void SetLocalScaling(const float4& _Value);				// �ڽ��� ����ũ�⸦ Set
	void SetWorldScaling(const float4& _Value);				// �ڽ��� ����ũ�⸦ Set

	void SetLocalRotation(const float4& _Value);			// �ڽ��� ����ȸ���� Set
	void SetWorldRotation(const float4& _Value);			// �ڽ��� ����ȸ���� Set

	void SetLocalPosition(const float4& _Value);				// �ڽ��� ������ġ�� Set
	void SetWorldPosition(const float4& _Value);			// �ڽ��� ������ġ�� Set

public:
	void TransformUpdate();													// ���� ���� �� ���̴��� �����ϴ� ��ü�� ���� ����
};

