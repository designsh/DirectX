#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 에러메세지 팝업창
// 설명 : 
class GameEngineUIRenderer;
class ErrorMsgPopup;
class ErrorMsgPanel : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Panel_;

private:
	std::string ErrorMsgText_;

private:
	ErrorMsgPopup* Parent_;

public:
	ErrorMsgPanel();
	~ErrorMsgPanel();

protected:		// delete constructer
	ErrorMsgPanel(const ErrorMsgPanel& _other) = delete;
	ErrorMsgPanel(ErrorMsgPanel&& _other) noexcept = delete;

private:		//delete operator
	ErrorMsgPanel& operator=(const ErrorMsgPanel& _other) = delete;
	ErrorMsgPanel& operator=(const ErrorMsgPanel&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetParentPopup(ErrorMsgPopup* _Parent);
	void SetErrorMsg(const std::string& _Text);
};

