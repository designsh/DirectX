#include "PreCompile.h"
#include "ErrorMsgPanel.h"

#include "ErrorMsgPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>

ErrorMsgPanel::ErrorMsgPanel() :
	Panel_(nullptr)
{
}

ErrorMsgPanel::~ErrorMsgPanel()
{
}

void ErrorMsgPanel::Start()
{
	// 에러메세지 창 렌더러 생성


}

void ErrorMsgPanel::Update(float _DeltaTime)
{
}

void ErrorMsgPanel::SetParentPopup(ErrorMsgPopup* _Parent)
{
	Parent_ = _Parent;
}
