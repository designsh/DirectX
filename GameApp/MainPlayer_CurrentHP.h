#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class MainPlayer_CurrentHP : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* HPRenderer_;

private:


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
	void SetImageCutting(float _Damage);
};

