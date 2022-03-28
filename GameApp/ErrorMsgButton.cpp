#include "PreCompile.h"
#include "ErrorMsgButton.h"

#include "ErrorMsgPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

ErrorMsgButton::ErrorMsgButton() :
	Button_(nullptr),
	ButtonCollision_(nullptr),
	ButtonState_(Button_State::Normal)
{
}

ErrorMsgButton::~ErrorMsgButton()
{
}

void ErrorMsgButton::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���� �޼��� â �ݱ� ��ư ����
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("ShortButton_Click.png");
	ButtonClick->Cut(1, 1);

	Button_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::ErrorPopup_Button));
	Button_->CreateAnimation("ShortButton_Stay.png", "Default", 0, 0, 0.1f, false);
	Button_->CreateAnimation("ShortButton_Click.png", "Click", 0, 0, 0.1f, false);
	Button_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	//Button_->GetTransform()->SetLocalPosition(float4());
	Button_->SetChangeAnimation("Default");

	// ���ӽ��� TextSetting
	Button_->TextSetting("diablo", "OK", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// �浹ü ����
	ButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::ErrorPopup_Collider));
	ButtonCollision_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	ButtonCollision_->GetTransform()->SetLocalPosition(Button_->GetTransform()->GetLocalPosition());
}

void ErrorMsgButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ش� �˾� Off
			if (nullptr != Parent_)
			{
				Parent_->ErrorMsgPopupDeactive();
			}

			ButtonState_ = Button_State::Normal;
		}
	}


	ButtonCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&ErrorMsgButton::ErrorPopupClose, this, std::placeholders::_1));
}

void ErrorMsgButton::SetParentPopup(ErrorMsgPopup* _Parent)
{
	Parent_ = _Parent;
}

void ErrorMsgButton::ErrorPopupClose(GameEngineCollision* _Other)
{	
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		Button_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		Button_->SetChangeAnimation("Default");
	}
}
