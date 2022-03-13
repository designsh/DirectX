#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : �����޼���â �ݱ�
// ���� : 
class GameEngineUIRenderer;
class ErrorMsgPopup;
class ErrorMsgButton : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Button_;

private:
	ErrorMsgPopup* Parent_;

public:
	ErrorMsgButton();
	~ErrorMsgButton();

protected:		// delete constructer
	ErrorMsgButton(const ErrorMsgButton& _other) = delete;
	ErrorMsgButton(ErrorMsgButton&& _other) noexcept = delete;

private:		//delete operator
	ErrorMsgButton& operator=(const ErrorMsgButton& _other) = delete;
	ErrorMsgButton& operator=(const ErrorMsgButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetParentPopup(ErrorMsgPopup* _Parent);
};

