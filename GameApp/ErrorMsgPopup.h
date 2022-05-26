#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 에러창
// 용도 : 게임내 에러메세지 표시
// 설명 : 
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
	GameEngineCollision* ErrorMsgCol_;				// 해당 창과 충돌중 어떠한 동작도 불가능하게 처리하기 위한 충돌체

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

