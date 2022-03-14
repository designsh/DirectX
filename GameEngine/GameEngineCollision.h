#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"
#include "Enums.h"

// 분류 : 충돌
// 용도 : 충돌관리
// 설명 : 
class GameEngineCore;
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineCore;
	friend GameEngineLevel;

private:
	static std::function<bool(GameEngineTransform*, GameEngineTransform*)> CollisionCheckFunction[static_cast<int>(CollisionType::MAX)][static_cast<int>(CollisionType::MAX)];

private: // GameEngineCore에서 호출하며 각 충돌체별 CallbackFunction 을 지정하여 CollisionCheckFunction 에 저장
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
	// 해당 객체가 원하는 _OtherGroup과의 충돌체크 후 충돌한 충돌체의 CallbackFunction 호출
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public: // CollisionType 별 충돌
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

