#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 버튼
// 설명 : 현재 생성한 플레이어로 게임시작
class GameEngineUIRenderer;
class TitleLevelMoveBtn : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* PrevMenuBtn_;

public:
	TitleLevelMoveBtn();
	~TitleLevelMoveBtn();

protected:		// delete constructer
	TitleLevelMoveBtn(const TitleLevelMoveBtn& _other) = delete;
	TitleLevelMoveBtn(TitleLevelMoveBtn&& _other) noexcept = delete;

private:		//delete operator
	TitleLevelMoveBtn& operator=(const TitleLevelMoveBtn& _other) = delete;
	TitleLevelMoveBtn& operator=(const TitleLevelMoveBtn&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

