#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineProgressBarRenderer;
class MainPlayer_CurrentHP : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* HPRenderer_;

private:
	float test = 1.0f;

public:
	MainPlayer_CurrentHP();
	~MainPlayer_CurrentHP();

protected:		// delete constructer
	MainPlayer_CurrentHP(const MainPlayer_CurrentHP& _other) = delete;
	MainPlayer_CurrentHP(MainPlayer_CurrentHP&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_CurrentHP& operator=(const MainPlayer_CurrentHP& _other) = delete;
	MainPlayer_CurrentHP& operator=(const MainPlayer_CurrentHP&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void AllHPRecovery();					// 현재 체력 모두 회복
	void HPRecovery(float _Damage);			// 현재 체력 회복
	void HPConsumption(float _Damage);		// 현재 체력 소모

};

