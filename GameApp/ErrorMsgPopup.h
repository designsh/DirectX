#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : ����â
// �뵵 : ���ӳ� �����޼��� ǥ��
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineSoundPlayer;
class ErrorMsgPopup : public GameEngineActor
{
private:	// member Var
	std::string ErrorMsgText_;
	Button_State ButtonState_;

private:
	GameEngineUIRenderer* ErrorMsgPanel_;
	GameEngineCollision* ErrorMsgCol_;				// �ش� â�� �浹�� ��� ���۵� �Ұ����ϰ� ó���ϱ� ���� �浹ü

private:
	GameEngineUIRenderer* ErrorMsgButton_;
	GameEngineCollision* ErrorMsgBtnCollision_;

private:
	GameEngineSoundPlayer* ButtonClickSound_;

public:
	ErrorMsgPopup();
	~ErrorMsgPopup();

protected:		// delete constructer
	ErrorMsgPopup(const ErrorMsgPopup& _other) = delete;
	ErrorMsgPopup(ErrorMsgPopup&& _other) noexcept = delete;

private:		//delete operator
	ErrorMsgPopup& operator=(const ErrorMsgPopup& _other) = delete;
	ErrorMsgPopup& operator=(const ErrorMsgPopup&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void ErrorMsgPopupActive(const std::string& _ErrorMsg);
	void ErrorMsgPopupDeactive();

public:
	void ErrorMsgDisabled(GameEngineCollision* _Other);
};

