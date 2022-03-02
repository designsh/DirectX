#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 대기상태에서 일정범위를 순환이동하다가 플레이어 발견시 플레이어에게로 이동하며,
//           플레이어가 공격범위내 진입하면 투사체를 발사하여 플레이어에게 공격을 가하거나, 근접공격을 가한다.
class GameEngineImageRenderer;
class Tainted : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Tainted_;

private: // 몬스터 정보
	bool SpecialAttack_;		// 투사체 공격 여부(기본 : 근접공격)

public:
	Tainted();
	~Tainted();

protected:		// delete constructer
	Tainted(const Tainted& _other) = delete;
	Tainted(Tainted&& _other) noexcept = delete;

private:		//delete operator
	Tainted& operator=(const Tainted& _other) = delete;
	Tainted& operator=(const Tainted&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

