#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 대기상태에서 일정범위를 순환이동하다가 플레이어 발견시 플레이어에게로 이동하며,
//           플레이어가 공격범위내 진입하면 근접공격을 가한다.
class GameEngineImageRenderer;
class Zombie : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Zombie_;

public:
	Zombie();
	~Zombie();

protected:		// delete constructer
	Zombie(const Zombie& _other) = delete;
	Zombie(Zombie&& _other) noexcept = delete;

private:		//delete operator
	Zombie& operator=(const Zombie& _other) = delete;
	Zombie& operator=(const Zombie&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

