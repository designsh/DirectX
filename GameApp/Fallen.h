#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 대기상태에서 일정범위를 순환이동하다가 플레이어 발견시 플레이어에게로 이동하며,
//           플레이어에게 공격을 가한다.
class GameEngineImageRenderer;
class Fallen : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Fallen_;

private: // 몬스터 정보


public:
	Fallen();
	~Fallen();

protected:		// delete constructer
	Fallen(const Fallen& _other) = delete;
	Fallen(Fallen&& _other) noexcept = delete;

private:		//delete operator
	Fallen& operator=(const Fallen& _other) = delete;
	Fallen& operator=(const Fallen&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

