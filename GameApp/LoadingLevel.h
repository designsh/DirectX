#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 로딩화면
// 용도 : 
// 설명 : 
class LoadingLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var

public:
	LoadingLevel();
	~LoadingLevel();

protected:		// delete constructer
	LoadingLevel(const LoadingLevel& _other) = delete;
	LoadingLevel(LoadingLevel&& _other) noexcept = delete;

private:		//delete operator
	LoadingLevel& operator=(const LoadingLevel& _other) = delete;
	LoadingLevel& operator=(const LoadingLevel&& _other) = delete;

private:
	void CreateLevelActor();

public:
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

