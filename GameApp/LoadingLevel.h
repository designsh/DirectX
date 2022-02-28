#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 로딩화면
// 용도 : 
// 설명 : 
class LoadingLevel : public GameEngineLevel
{
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

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};

