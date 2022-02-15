#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 
// 용도 : 
// 설명 : 
class TitleLevel : public GameEngineLevel
{
private:	// member Var

public:
	TitleLevel();
	~TitleLevel();

protected:		// delete constructer
	TitleLevel(const TitleLevel& _other) = delete;
	TitleLevel(TitleLevel&& _other) noexcept = delete;

private:		//delete operator
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

