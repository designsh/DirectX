#pragma once
#include "GameEngineComponent.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

union CollisionData
{
public:
	DirectX::BoundingSphere				Sphere;		// ��
	DirectX::BoundingBox				AABB;		// ȸ���� ����ϸ� �ȵǴ� �ڽ�
	DirectX::BoundingOrientedBox		OBB;		// ȸ���� �ڽ�

	CollisionData() : OBB()
	{
	}
};

// �� ��ü�� ���� �������� ��ġ, ũ��, ȸ�� ������ ���� �������� ��ġ, ũ��, ȸ�� ������ ���Ͽ�
// �����ϴ� ������ ����� �����ϴ� Ŭ����
class TransformData
{
public:
	// ���� : ���� ���������� ����(0,0,0)�� ����
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	// ���� : 1. �θ� O : �θ��� ��ġ(����)�� ����
	//            2. �θ� X : ���� ���������� ����(0,0,0)�� ����
	// Ex) A������Ʈ�� �ڽ� ������Ʈ�� B������Ʈ��� �����Ѵٸ�
	//        B������Ʈ�� ������ġ�� A������Ʈ�� ��ġ(100, 0, 0)�̶��
	//        A������Ʈ�� ��ġ(100,0,0)�κ����� B������Ʈ�� ��ġ�� �����ȴ�
	//        A������Ʈ�� B������Ʈ�� ���ļ� �����Ǿ��ٸ� A������Ʈ�� ������ġ�� �ֻ��� ������Ʈ�̹Ƿ�
	//        100,0,0�� ������ġ�� �ǰ�, B������Ʈ�� 100,0,0�� �����̹Ƿ� ��ġ�� 0,0,0�� �ȴ�.
	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	// ��ȯ���
	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	// �θ����
	float4x4 Parent_;

	// �������
	float4x4 WorldWorld_;

	// �����
	float4x4 View_;

	// �������
	float4x4 Projection_;

	// �������
	float4x4 WVP;

public:
	TransformData() : 
		vWorldScaling_(float4::ONE), 
		vLocalScaling_(float4::ONE)
	{
	}

public:
	// �������(ũ��/ȸ��/��ġ/����) ����
	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	// �θ���� : �θ� �����Ѵٸ� ��� ����� ���ɶ� �θ��� ����� ������ �޴´�.
	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	// �ڽ��� �θ� �������� �ʴ´�.
	// �ڽ��� �ֻ��� Ʈ�������̹Ƿ� �θ��� ������ �����ʴ´�.
	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}

	// ��������� ���
	void WVPCalculation()
	{
		WVP = WorldWorld_ * View_ * Projection_;
	}
};

// �з� : Ʈ������(Transform)
// �뵵 : 
// ���� : �� ��ü�� ������ǥ���� ��ġ, ũ��, ȸ�� ������ �����ϴ� ����� �����ϰ� �̸� ������� ��ǥ(World Space)�� ��ȯ�ϴ� ����� �����ϴ� Ŭ����
//            ��, �� ��ü�� �θ� ��ü�� ������ �ִ� ��������(�θ�-�ڽ�)�� �̷�� ������� ���ÿ� ���� �θ��� ������ �޾� ��ġ/ũ��/ȸ�� ������ ����ϴ� ��쵵 �ִ�.
class GameEngineTransform
{
private:	// member Var
	TransformData									TransformData_;		// ����/���� ũ��/ȸ��/��ġ �� ����, �θ� ����� �����ϴ� Ʈ������ ����
	GameEngineTransform*							Parent_;			// ���� Ʈ�������� �θ� Ʈ������
	std::vector<GameEngineTransform*>				Childs_;			// ���� Ʈ�������� �ڽ� Ʈ������ ���

private:
	CollisionData									ColData_;			// 

public:
	GameEngineTransform();
	~GameEngineTransform();

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

public:
	void AttachTransform(GameEngineTransform* _Transform);
	void DetachChildTransform(GameEngineTransform* _Transform);

public:
	TransformData& GetTransformData();

public: // �浹ü ����
	inline const CollisionData& GetCollisionData()
	{
		return ColData_;
	}

	inline const DirectX::BoundingSphere& GetSphere()
	{
		return ColData_.Sphere;
	}

	inline const DirectX::BoundingOrientedBox& GetOBB()
	{
		return ColData_.OBB;
	}

	inline const DirectX::BoundingBox& GetAABB()
	{
		return ColData_.AABB;
	}

private: // ����ó��
	void AllChildCalculationScaling();						// ��� �ڽ��� ũ�⺯ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)
	void AllChildCalculationRotation();						// ��� �ڽ��� ȸ����ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)
	void AllChildCalculationPosition();						// ��� �ڽ��� ��ġ��ȭ�� ���(�θ� �����Ѵٸ� �θ������ ������ ����)

	// ũ�����
	void CalculationLocalScaling();							// �ڽ��� ���� ũ������� ���
	void CalculationWorldScaling();							// �ڽ��� ���� ũ������� ���

	// ȸ�����
	void CalculationLocalRotation();						// �ڽ��� ���� ȸ������� ���
	void CalculationWorldRotation();						// �ڽ��� ���� ȸ������� ���

	// �̵����
	void CalculationLocalPosition();						// �ڽ��� ���� ��ġ����� ���
	void CalculationWorldPosition();						// �ڽ��� ���� ��ġ����� ���

public:
	void SetLocalScaling(const float4& _Value);				// �ڽ��� ����ũ�⸦ Set
	void SetWorldScaling(const float4& _Value);				// �ڽ��� ����ũ�⸦ Set
	void SetLocalRotationDegree(const float4& _Value);		// �ڽ��� ����ȸ���� Set
	void SetWorldRotationDegree(const float4& _Value);		// �ڽ��� ����ȸ���� Set
	void SetLocalPosition(const float4& _Value);			// �ڽ��� ������ġ�� Set
	void SetWorldPosition(const float4& _Value);			// �ڽ��� ������ġ�� Set

public:
	void AddLocalDeltaTimeRotation(const float4& _Value);	// DeltaTime ������ �޾� ����ȸ��
	void AddWorldDeltaTimeRotation(const float4& _Value);	// DeltaTime ������ �޾� ����ȸ��
	void SetLocalDeltaTimeMove(const float4& _Value);		// DeltaTime ������ �޾� �����̵�
	void SetWorldDeltaTimeMove(const float4& _Value);		// DeltaTime ������ �޾� �����̵�

public:
	void AddLocalRotationDegreeX(const float _Value);		// 
	void AddWorldRotationDegreeX(const float _Value);		// 
	void AddLocalRotationDegreeY(const float _Value);		// 
	void AddWorldRotationDegreeY(const float _Value);		// 
	void AddLocalRotationDegreeZ(const float _Value);		// 
	void AddWorldRotationDegreeZ(const float _Value);		// 

public: // Normal Update ����
	void SetLocalMove(const float4& _Value);				// _Value��ŭ �����̵�
	void SetWorldMove(const float4& _Value);				// _Value��ŭ �����̵�

public:
	void SetLocalZOrder(float _Value);						// ZOrder ����(����)
	void SetWorldZOrder(float _Value);						// ZOrder ����(����)

public:
	void Copy(const GameEngineTransform& _Other);			// ����ī�޶� ����� Ʈ�����������ͷ� �ǵ�����

public: // �⺻ ������� ����
	float4 GetLocalScaling() const;
	float4 GetWorldScaling() const;
	float4 GetLocalRotation() const;
	float4 GetWorldRotation() const;
	float4 GetLocalPosition() const;
	float4 GetWorldPosition() const;

public: // ī�޶� ����
	float4 GetWorldForwardVector() const;
	float4 GetLocalForwardVector() const;
	float4 GetWorldRightVector() const;
	float4 GetLocalRightVector() const;
	float4 GetWorldUpVector() const;
	float4 GetLocalUpVector() const;
	float4 GetWorldBackVector() const;
	float4 GetLocalBackVector() const;
	float4 GetWorldLeftVector() const;
	float4 GetLocalLeftVector() const;
	float4 GetWorldDownVector() const;
	float4 GetLocalDownVector() const;

public:
	void TransformUpdate();									// ���� ���� �� ���̴��� �����ϴ� ��ü�� ���� ����
};

