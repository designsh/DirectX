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
	Sphere,				// ��
	AABBBox,			// AABB : ���ĵ� ��
	OBBBox,			// OBB : �ڽ��� �Բ� �൵ ȸ��
	MAX,
};

// �з� : �浹
// �뵵 : �浹����
// ���� : 
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineLevel;

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
	// �ش� ��ü�� ���ϴ� _OtherGroup���� �浹üũ �� �浹�� �浹ü ���͹�ȯ
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::vector<GameEngineCollision*>& _ColVector);

	// �ش� ��ü�� ���ϴ� _OtherGroup���� �浹üũ �� �浹�� �浹ü�� CallbackFunction ȣ��
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public: // CollisionType �� �浹

};

