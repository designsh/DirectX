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
	// ���� �޼��� â(����)
	ErrorMsgPanel_ = GetLevel()->CreateActor<ErrorMsgPanel>();
	ErrorMsgPanel_->SetParentPopup(this);
	ErrorMsgPanel_->Off();

	// ���� Ȯ�� ��ư(����)
	ErrorMsgButton_ = GetLevel()->CreateActor<ErrorMsgButton>();
	ErrorMsgButton_->SetParentPopup(this);
	ErrorMsgButton_->Off();
}

void ErrorMsgPopup::Update(float _DeltaTime)
{
}

void ErrorMsgPopup::ErrorMsgPopupActive(const std::string& _ErrorMsg)
{
	ErrorMsgText_ = _ErrorMsg;

	// �����޼���â Ȱ��ȭ
	ErrorMsgPanel_->On();
	ErrorMsgButton_->On();
}

void ErrorMsgPopup::ErrorMsgPopupDeactive()
{
	// ���� �޼���â ��Ȱ��ȭ
	ErrorMsgPanel_->Death();
	ErrorMsgButton_->Death();
}
