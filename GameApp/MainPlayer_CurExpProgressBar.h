#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineProgressBarRenderer;
class MainPlayer_CurExpProgressBar : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* ExpRenderer_;

private:
	bool Reflection_;								// 경험치 업데이트 완료시 true
													// 플레이어의 현재 경험치가 변경되면 false
	int CurEXP_;									// 플레이어의 현재 경험치

public:
	MainPlayer_CurExpProgressBar();
	~MainPlayer_CurExpProgressBar();

protected:		// delete constructer
	MainPlayer_CurExpProgressBar(const MainPlayer_CurExpProgressBar& _other) = delete;
	MainPlayer_CurExpProgressBar(MainPlayer_CurExpProgressBar&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_CurExpProgressBar& operator=(const MainPlayer_CurExpProgressBar& _other) = delete;
	MainPlayer_CurExpProgressBar& operator=(const MainPlayer_CurExpProgressBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

