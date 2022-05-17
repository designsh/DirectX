#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 카타콤 화면
// 용도 : 
// 설명 : 
class MainPlayer;
class MouseObject;
class CatacombsMap;
class MonsterTopHPBar;
class CatacombsLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	CatacombsMap* CatacombsMap_;
	MainPlayer* MainPlayer_;
	MouseObject* MainMouse_;

private:
	MonsterTopHPBar* TopHPBar_;

public:
	CatacombsLevel();
	~CatacombsLevel();

protected:		// delete constructer
	CatacombsLevel(const CatacombsLevel& _other) = delete;
	CatacombsLevel(CatacombsLevel&& _other) noexcept = delete;

private:		//delete operator
	CatacombsLevel& operator=(const CatacombsLevel& _other) = delete;
	CatacombsLevel& operator=(const CatacombsLevel&& _other) = delete;

private:
	void CreateLevelActor();

public:
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

