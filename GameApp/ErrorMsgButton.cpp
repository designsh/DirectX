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
	// ���� �޼��� â �ݱ� ��ư ����


}

void ErrorMsgButton::Update(float _DeltaTime)
{
	// ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ����
	// �����޼��� �˾��� �����Ų��.
	// Parent_->ErrorMsgPopupDeactive(); ȣ��

}

void ErrorMsgButton::SetParentPopup(ErrorMsgPopup* _Parent)
{
	Parent_ = _Parent;
}
