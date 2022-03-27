#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 카타콤 화면
// 용도 : 
// 설명 : 
class MainPlayer;
class MouseObject;
class CatacombsLevel : public GameEngineLevel
{
private:	// member Var
	MainPlayer* MainPlayer_;
	MouseObject* MainMouse_;

public:
	CatacombsLevel();
	~CatacombsLevel();

protected:		// delete constructer
	CatacombsLevel(const CatacombsLevel& _other) = delete;
	CatacombsLevel(CatacombsLevel&& _other) noexcept = delete;

private:		//delete operator
	CatacombsLevel& operator=(const CatacombsLevel& _other) = delete;
	CatacombsLevel& operator=(const CatacombsLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

