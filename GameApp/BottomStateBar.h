#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 하단상태바
// 설명 : 플레이어의 하단상태바관리
class GameEngineUIRenderer;
class BottomStateBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* BottomStateBar_;

public:
	BottomStateBar();
	~BottomStateBar();

protected:		// delete constructer
	BottomStateBar(const BottomStateBar& _other) = delete;
	BottomStateBar(BottomStateBar&& _other) noexcept = delete;

private:		//delete operator
	BottomStateBar& operator=(const BottomStateBar& _other) = delete;
	BottomStateBar& operator=(const BottomStateBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

