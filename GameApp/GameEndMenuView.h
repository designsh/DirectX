#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineLevel;
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
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void InitGameEndMenuView();
};

