#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

// 1. AABB 박스충돌 : 두 가지 모두 True여야만 충돌로 판정
//     1) 가로체크 : 두 사각형의 중점 가로 사이의 거리 < 두 사각형의 밑변 절반의 크기 합
//     2) 세로체크 : 두 사각형의 중점 세로 사이의 거리 < 두 사각형의 높이 절반의 크기 합
// 2. OBB 박스 충돌 : 내적을 이용한 투영으로 4가지를 체크하며 4가지 모두 True여야만 충돌로 판단
//      1) 오브젝트 1 Right축 기준 투영
//      2) 오브젝트 1 Up축 기준 투영
//      3) 오브젝트 2 Right축 기준 투영
//      4) 오브젝트 2 Up축 기준 투영
enum class CollisionType
{
	// 2D와 3D 충돌체간의 충돌은 금지한다.
	Point2D,					// 
	CirCle,						// 원
	Rect,							// 사각형
	OrientedRect,			// 회전한사각형

	Point3D,					// 
	Sphere3D,				// 구
	AABBBox3D,			// 박스
	OBBBox3D,				// 회전한박스
	MAX,
};

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

