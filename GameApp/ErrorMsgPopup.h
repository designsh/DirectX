#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 에러창
// 용도 : 게임내 에러메세지 표시
// 설명 : 
class ErrorMsgPanel;
class ErrorMsgButton;
class ErrorMsgPopup : public GameEngineActor
{
private:	// member Var
	std::string ErrorMsgText_;

private:
	ErrorMsgPanel* ErrorMsgPanel_;
	ErrorMsgButton* ErrorMsgButton_;

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
};

