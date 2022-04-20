#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 타이틀화면
// 용도 : 
// 설명 : 
class GameStartButton;
class GameEndButton;
class TitleLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	GameStartButton* StartButton_;
	GameEndButton* EndButton_;

public:
	TitleLevel();
	~TitleLevel();

protected:		// delete constructer
	TitleLevel(const TitleLevel& _other) = delete;
	TitleLevel(TitleLevel&& _other) noexcept = delete;

private:		//delete operator
	TitleLevel& operator=(const TitleLevel& _other) = delete;
	TitleLevel& operator=(const TitleLevel&& _other) = delete;

private:
	void CreateLevelActor();

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

