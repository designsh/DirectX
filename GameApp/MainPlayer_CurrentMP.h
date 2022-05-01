#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineProgressBarRenderer;
class MainPlayer_CurrentMP : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* MPRenderer_;

public:
	MainPlayer_CurrentMP();
	~MainPlayer_CurrentMP();

protected:		// delete constructer
	MainPlayer_CurrentMP(const MainPlayer_CurrentMP& _other) = delete;
	MainPlayer_CurrentMP(MainPlayer_CurrentMP&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_CurrentMP& operator=(const MainPlayer_CurrentMP& _other) = delete;
	MainPlayer_CurrentMP& operator=(const MainPlayer_CurrentMP&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void AllMPRecovery();					// 현재 마력 모두 회복
	void MPRecovery(float _Damage);			// 현재 마력 회복
	void MPConsumption(float _Damage);		// 현재 마력 소모
};

