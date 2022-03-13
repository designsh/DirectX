#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 에러창
// 용도 : 게임내 에러메세지 표시
// 설명 : 
class GameEngineUIRenderer;
class ErrorMsgView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* ErroMsgView_;

public:
	ErrorMsgView();
	~ErrorMsgView();

protected:		// delete constructer
	ErrorMsgView(const ErrorMsgView& _other) = delete;
	ErrorMsgView(ErrorMsgView&& _other) noexcept = delete;

private:		//delete operator
	ErrorMsgView& operator=(const ErrorMsgView& _other) = delete;
	ErrorMsgView& operator=(const ErrorMsgView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

