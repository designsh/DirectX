#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 마을 화면
// 용도 : 
// 설명 : 
class MainPlayer;
class MouseObject;
class WeaponNPC;
class TownLevel : public GameEngineLevel
{
private:	// member Var
	MainPlayer* MainPlayer_;
	MouseObject* MainMouse_;

private:
	WeaponNPC* WeaponNPC_;

public:
	TownLevel();
	~TownLevel();

protected:		// delete constructer
	TownLevel(const TownLevel& _other) = delete;
	TownLevel(TownLevel&& _other) noexcept = delete;

private:		//delete operator
	TownLevel& operator=(const TownLevel& _other) = delete;
	TownLevel& operator=(const TownLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

