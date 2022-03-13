#include "PreCompile.h"
#include "ErrorMsgButton.h"

#include "ErrorMsgPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>

ErrorMsgButton::ErrorMsgButton() :
	Button_(nullptr)
{
}

ErrorMsgButton::~ErrorMsgButton()
{
}

void ErrorMsgButton::Start()
{
	// 에러 메세지 창 닫기 버튼 생성


}

void ErrorMsgButton::Update(float _DeltaTime)
{
	// 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시
	// 에러메세지 팝업을 종료시킨다.
	// Parent_->ErrorMsgPopupDeactive(); 호출

}

void ErrorMsgButton::SetParentPopup(ErrorMsgPopup* _Parent)
{
	Parent_ = _Parent;
}
