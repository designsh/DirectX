#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 타이틀레벨 버튼
// 설명 : 캐릭터생성레벨로 이동
class GameEngineUIRenderer;
class GameEngineCollision;
class GameStartButton : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* StartButton_;
	GameEngineCollision* MainCollision_;

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
	void GameStartButtonClick(GameEngineCollision* _OtherCollision);
};

