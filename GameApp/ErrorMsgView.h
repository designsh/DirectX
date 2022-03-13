#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����â
// �뵵 : ���ӳ� �����޼��� ǥ��
// ���� : 
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

