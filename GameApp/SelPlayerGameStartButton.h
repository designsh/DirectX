#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터선택레벨 버튼
// 설명 : 선택된 플레이어로 게임시작
class SelPlayerGameStartButton : public GameEngineActor
{
private:	// member Var

public:
	SelPlayerGameStartButton();
	~SelPlayerGameStartButton();

protected:		// delete constructer
	SelPlayerGameStartButton(const SelPlayerGameStartButton& _other) = delete;
	SelPlayerGameStartButton(SelPlayerGameStartButton&& _other) noexcept = delete;

private:		//delete operator
	SelPlayerGameStartButton& operator=(const SelPlayerGameStartButton& _other) = delete;
	SelPlayerGameStartButton& operator=(const SelPlayerGameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

