#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 마을 화면
// 용도 : 
// 설명 : 
class MainPlayer;
class MouseObject;
class WeaponNPC;
class ChandleryNPC;
class TownMap;
class TileMapInfoWindow;
class TownLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	TownMap* TownMap_;

private:
	MainPlayer* MainPlayer_;
	MouseObject* MainMouse_;

private:
	WeaponNPC* WeaponNPC_;
	ChandleryNPC* ChandleryNPC_;

private:
	TileMapInfoWindow* TileMapInfoWindow_;

public:
	TownLevel();
	~TownLevel();

protected:		// delete constructer
	TownLevel(const TownLevel& _other) = delete;
	TownLevel(TownLevel&& _other) noexcept = delete;

private:		//delete operator
	TownLevel& operator=(const TownLevel& _other) = delete;
	TownLevel& operator=(const TownLevel&& _other) = delete;

private:
	void CreateLevelActor();

public:
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

