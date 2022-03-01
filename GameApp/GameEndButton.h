#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 타이틀레벨 게임종료버튼
// 설명 : 윈도우 종료
class GameEndButton : public GameEngineActor
{
private:	// member Var

public:
	GameEndButton();
	~GameEndButton();

protected:		// delete constructer
	GameEndButton(const GameEndButton& _other) = delete;
	GameEndButton(GameEndButton&& _other) noexcept = delete;

private:		//delete operator
	GameEndButton& operator=(const GameEndButton& _other) = delete;
	GameEndButton& operator=(const GameEndButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

