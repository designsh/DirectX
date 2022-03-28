#include "PreCompile.h"
#include "ErrorMsgPopup.h"

#include "ErrorMsgPanel.h"
#include "ErrorMsgButton.h"

#include <GameEngine/GameEngineLevel.h>

ErrorMsgPopup::ErrorMsgPopup() :
	ErrorMsgPanel_(nullptr),
	ErrorMsgButton_(nullptr)
{
}

ErrorMsgPopup::~ErrorMsgPopup()
{
}

void ErrorMsgPopup::Start()
{	
	// 에러 메세지 창(액터)
	ErrorMsgPanel_ = GetLevel()->CreateActor<ErrorMsgPanel>();
	ErrorMsgPanel_->SetParentPopup(this);
	ErrorMsgPanel_->Off();

	// 에러 확인 버튼(액터)
	ErrorMsgButton_ = GetLevel()->CreateActor<ErrorMsgButton>();
	ErrorMsgButton_->SetParentPopup(this);
	ErrorMsgButton_->Off();
}

void ErrorMsgPopup::Update(float _DeltaTime)
{
}

void ErrorMsgPopup::ErrorMsgPopupActive(const std::string& _ErrorMsg)
{
	ErrorMsgPanel_->SetErrorMsg(_ErrorMsg);

	// 에러메세지창 활성화
	ErrorMsgPanel_->On();
	ErrorMsgButton_->On();
}

void ErrorMsgPopup::ErrorMsgPopupDeactive()
{
	// 에러 메세지창 비활성화
	ErrorMsgPanel_->Off();
	ErrorMsgButton_->Off();
}
