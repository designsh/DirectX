#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class ActiveButtonType
{
	NONE = -1,
	STATVIEW,
	SKILLVIEW,
	MAX
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_LevelUpActiveButton : public GameEngineActor
{
private:	// member Var
	ActiveButtonType ButtonType_;
	Button_State ButtonState_;

private:
	GameEngineUIRenderer* Button_;
	GameEngineCollision* ButtonCollision_;

public:
	MainPlayer_LevelUpActiveButton();
	~MainPlayer_LevelUpActiveButton();

protected:		// delete constructer
	MainPlayer_LevelUpActiveButton(const MainPlayer_LevelUpActiveButton& _other) = delete;
	MainPlayer_LevelUpActiveButton(MainPlayer_LevelUpActiveButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_LevelUpActiveButton& operator=(const MainPlayer_LevelUpActiveButton& _other) = delete;
	MainPlayer_LevelUpActiveButton& operator=(const MainPlayer_LevelUpActiveButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

