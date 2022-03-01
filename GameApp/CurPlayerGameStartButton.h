#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 버튼
// 설명 : 현재 생성한 플레이어로 게임시작
class CurPlayerGameStartButton : public GameEngineActor
{
private:	// member Var

public:
	CurPlayerGameStartButton();
	~CurPlayerGameStartButton();

protected:		// delete constructer
	CurPlayerGameStartButton(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton(CurPlayerGameStartButton&& _other) noexcept = delete;

private:		//delete operator
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

