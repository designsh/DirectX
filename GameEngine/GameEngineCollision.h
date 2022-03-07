#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

// 1. AABB �ڽ��浹 : �� ���� ��� True���߸� �浹�� ����
//     1) ����üũ : �� �簢���� ���� ���� ������ �Ÿ� < �� �簢���� �غ� ������ ũ�� ��
//     2) ����üũ : �� �簢���� ���� ���� ������ �Ÿ� < �� �簢���� ���� ������ ũ�� ��
// 2. OBB �ڽ� �浹 : ������ �̿��� �������� 4������ üũ�ϸ� 4���� ��� True���߸� �浹�� �Ǵ�
//      1) ������Ʈ 1 Right�� ���� ����
//      2) ������Ʈ 1 Up�� ���� ����
//      3) ������Ʈ 2 Right�� ���� ����
//      4) ������Ʈ 2 Up�� ���� ����
enum class CollisionType
{
	// 2D�� 3D �浹ü���� �浹�� �����Ѵ�.
	Point2D,					// 
	CirCle,						// ��
	Rect,							// �簢��
	OrientedRect,			// ȸ���ѻ簢��

	Point3D,					// 
	Sphere3D,				// ��
	AABBBox3D,			// �ڽ�
	OBBBox3D,				// ȸ���ѹڽ�
	MAX,
};

// �з� : �浹
// �뵵 : �浹����
// ���� : 
class GameEngineCore;
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineCore;
	friend GameEngineLevel;

private:
	static std::function<bool(GameEngineTransform*, GameEngineTransform*)> CollisionCheckFunction[static_cast<int>(CollisionType::MAX)][static_cast<int>(CollisionType::MAX)];

private: // GameEngineCore���� ȣ���ϸ� �� �浹ü�� CallbackFunction �� �����Ͽ� CollisionCheckFunction �� ����
	static void Init();

public:
	static bool CirCleToCirCle(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool Sphere3DToSphere3D(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool RectToRect(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABB3DToAABB3D(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool OrientedRectToOrientedRect(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBB3DToOBB3D(GameEngineTransform* _Left, GameEngineTransform* _Right);

private:	// member Var


public:
	GameEngineCollision();
	~GameEngineCollision();

protected:		// delete constructer
	GameEngineCollision(const GameEngineCollision& _other) = delete;
	GameEngineCollision(GameEngineCollision&& _other) noexcept = delete;

private:		//delete operator
	GameEngineCollision& operator=(const GameEngineCollision& _other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	template<typename UserType>
	void SetCollisionGroup(UserType _Type)
	{
		SetCollisionGroup(static_cast<int>(_Type));
	}

	void SetCollisionGroup(int _Type);

public:
	// �ش� ��ü�� ���ϴ� _OtherGroup���� �浹üũ �� �浹�� �浹ü�� CallbackFunction ȣ��
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public: // CollisionType �� �浹
	void SphereToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void SphereToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void SphereToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public:
	void AABBBoxToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void AABBBoxToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void AABBBoxToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public:
	void OBBBoxToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void OBBBoxToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
	void OBBBoxToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);
};

