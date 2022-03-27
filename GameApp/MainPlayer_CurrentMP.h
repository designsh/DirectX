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
	void MPConsumption(float _Damage);
};

