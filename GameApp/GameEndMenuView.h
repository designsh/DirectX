#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEndMenuView : public GameEngineActor
{
private:	// member Var

public:
	GameEndMenuView();
	~GameEndMenuView();

protected:		// delete constructer
	GameEndMenuView(const GameEndMenuView& _other) = delete;
	GameEndMenuView(GameEndMenuView&& _other) noexcept = delete;

private:		//delete operator
	GameEndMenuView& operator=(const GameEndMenuView& _other) = delete;
	GameEndMenuView& operator=(const GameEndMenuView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void InitGameEndMenuView();
};

