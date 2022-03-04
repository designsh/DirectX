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
	Sphere,				// 구
	AABBBox,			// AABB : 정렬된 축
	OBBBox,			// OBB : 박스와 함께 축도 회전
	MAX,
};

// 분류 : 충돌
// 용도 : 충돌관리
// 설명 : 
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
	// 해당 객체가 원하는 _OtherGroup과의 충돌체크 후 충돌한 충돌체 벡터반환
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::vector<GameEngineCollision*>& _ColVector);

	// 해당 객체가 원하는 _OtherGroup과의 충돌체크 후 충돌한 충돌체의 CallbackFunction 호출
	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);

public: // CollisionType 별 충돌

};

