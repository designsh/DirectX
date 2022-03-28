#include "PreCompile.h"
#include "ErrorMsgPanel.h"

#include "ErrorMsgPopup.h"
#include "GlobalEnumClass.h"

#include <GameEngine/GameEngineUIRenderer.h>

ErrorMsgPanel::ErrorMsgPanel() :
	Panel_(nullptr),
	ErrorMsgText_(""),
	Parent_(nullptr)
{
}

ErrorMsgPanel::~ErrorMsgPanel()
{
}

void ErrorMsgPanel::Start()
{
	// 에러메세지 창 렌더러 생성
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::ErrorPopup));
	Panel_->SetImage("ErrorMsgBox_Panel.png");
	Panel_->TextSetting("diablo", ErrorMsgText_, 15, FW1_CENTER | FW1_VCENTER, float4::WHITE);
}

void ErrorMsgPanel::Update(float _DeltaTime)
{
}

void ErrorMsgPanel::SetParentPopup(ErrorMsgPopup* _Parent)
{
	Parent_ = _Parent;
}

void ErrorMsgPanel::SetErrorMsg(const std::string& _Text)
{
	ErrorMsgText_ = _Text;

	Panel_->SetPrintText(ErrorMsgText_);
}
