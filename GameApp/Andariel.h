#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 보스몬스터
// 용도 : 카타콤레벨의 최종보스
// 설명 : 필드(전체맵)에서 플레이어가 최초 스폰한 방의 위치와 가장 먼 위치에 존재하는 방에 스폰하며,
//            일반공격(근접공격)과 스킬공격(원거리) 패턴을 가진다.
//            단 1마리만 필드에 스폰하며, 사망시 사망 이펙트(카메라 쉐이킹, 불꽃오브젝트 소환 등)을 실행하며,
//            사망이펙트 종료시 Boss Portal(Auto)를 스폰하여 플레이어가 다음 레벨로 진입할 수 있게 제공한다.
//            사망이펙트와 동시에 대량의 아이템 or 골드를 드랍한다.
class GameEngineImageRenderer;
class GameEngineCollision;
class Andariel : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Andariel_;
	GameEngineCollision* BodyCollider_;
	GameEngineCollision* AttackCollider_;

private:
	std::list<PathIndex> MovePath_;

public:
	Andariel();
	~Andariel();

protected:		// delete constructer
	Andariel(const Andariel& _other) = delete;
	Andariel(Andariel&& _other) noexcept = delete;

private:		//delete operator
	Andariel& operator=(const Andariel& _other) = delete;
	Andariel& operator=(const Andariel&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

