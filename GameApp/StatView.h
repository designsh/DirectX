#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class StatView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Panel_;
	GameEngineUIRenderer* PlayerID_;

public:
	StatView();
	~StatView();

protected:		// delete constructer
	StatView(const StatView& _other) = delete;
	StatView(StatView&& _other) noexcept = delete;

private:		//delete operator
	StatView& operator=(const StatView& _other) = delete;
	StatView& operator=(const StatView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

