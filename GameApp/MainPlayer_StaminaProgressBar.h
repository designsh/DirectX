#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineProgressBarRenderer;
class MainPlayer_StaminaProgressBar : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* StaminaRenderer_;

public:
	MainPlayer_StaminaProgressBar();
	~MainPlayer_StaminaProgressBar();

protected:		// delete constructer
	MainPlayer_StaminaProgressBar(const MainPlayer_StaminaProgressBar& _other) = delete;
	MainPlayer_StaminaProgressBar(MainPlayer_StaminaProgressBar&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_StaminaProgressBar& operator=(const MainPlayer_StaminaProgressBar& _other) = delete;
	MainPlayer_StaminaProgressBar& operator=(const MainPlayer_StaminaProgressBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void CalculationStaminaConsumption(float _DeltaTime);
};

