#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 타이틀레벨 게임시작버튼
// 용도 : 
// 설명 : 캐릭터생성레벨로 이동
class GameStartButton : public GameEngineActor
{
private:	// member Var

public:
	GameStartButton();
	~GameStartButton();

protected:		// delete constructer
	GameStartButton(const GameStartButton& _other) = delete;
	GameStartButton(GameStartButton&& _other) noexcept = delete;

private:		//delete operator
	GameStartButton& operator=(const GameStartButton& _other) = delete;
	GameStartButton& operator=(const GameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

