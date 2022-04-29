#include "PreCompile.h"
#include "ErrorMsgPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "MouseObject.h"

ErrorMsgPopup::ErrorMsgPopup() :
	ErrorMsgText_(),
	ButtonState_(Button_State::Normal),
	ErrorMsgPanel_(nullptr),
	ErrorMsgCol_(nullptr),
	ErrorMsgButton_(nullptr),
	ErrorMsgBtnCollision_(nullptr)
{
}

ErrorMsgPopup::~ErrorMsgPopup()
{
}

void ErrorMsgPopup::Start()
{	
	// ���� �޼��� â �ݱ� ��ư ����
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("ShortButton_Click.png");
	ButtonClick->Cut(1, 1);

	// ���� �޼��� â
	ErrorMsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
	ErrorMsgPanel_->SetImage("ErrorMsgBox_Panel.png");
	ErrorMsgPanel_->TextSetting("diablo", ErrorMsgText_, 15, FW1_CENTER | FW1_VCENTER, float4::WHITE);

	// ���콺�� �浹���϶� ���콺 ���� ����
	ErrorMsgCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
	ErrorMsgCol_->GetTransform()->SetLocalScaling(ErrorMsgPanel_->GetTransform()->GetLocalScaling());
	ErrorMsgCol_->GetTransform()->SetLocalPosition(ErrorMsgCol_->GetTransform()->GetLocalPosition());

	// ���� Ȯ�� ��ư(����)
	ErrorMsgButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	ErrorMsgButton_->CreateAnimation("ShortButton_Stay.png", "Default", 0, 0, 0.1f, false);
	ErrorMsgButton_->CreateAnimation("ShortButton_Click.png", "Click", 0, 0, 0.1f, false);
	ErrorMsgButton_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	ErrorMsgButton_->GetTransform()->SetLocalPosition(float4(0.f, -60.f));
	ErrorMsgButton_->SetChangeAnimation("Default");

	// ���ӽ��� TextSetting
	ErrorMsgButton_->TextSetting("diablo", "OK", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// �浹ü ����
	ErrorMsgBtnCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	ErrorMsgBtnCollision_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	ErrorMsgBtnCollision_->GetTransform()->SetLocalPosition(ErrorMsgButton_->GetTransform()->GetLocalPosition());

}

void ErrorMsgPopup::Update(float _DeltaTime)
{
	if (nullptr != ErrorMsgCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ErrorMsgCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
	}

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ش� â ��Ȱ��
			ErrorMsgPopupDeactive();

			ButtonState_ = Button_State::Normal;
		}
	}

	// ��ư �浹üũ
	ErrorMsgBtnCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&ErrorMsgPopup::ErrorMsgDisabled, this, std::placeholders::_1));
}

void ErrorMsgPopup::ErrorMsgPopupActive(const std::string& _ErrorMsg)
{
	// ErrorMsg Setting
	ErrorMsgText_ = _ErrorMsg;

	// ErrorMsgText�� �������ڼ��� �Ѿ�� �ٹٲ� Flag �߰� - ����
	ErrorMsgPanel_->SetPrintText(ErrorMsgText_);

	// Ȱ��ȭ
	On();
}

void ErrorMsgPopup::ErrorMsgPopupDeactive()
{
	// �ش� �浹 Flag�� ������Ű��
	if (nullptr != GlobalValue::CurMouse && true == GlobalValue::CurMouse->GetUIPopupCollision())
	{
		GlobalValue::CurMouse->UIPopupCollisionOff();
	}

	// �ش� ���� ���ó��
	Death();
}

void ErrorMsgPopup::ErrorMsgDisabled(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		ErrorMsgButton_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		ErrorMsgButton_->SetChangeAnimation("Default");
	}
}
