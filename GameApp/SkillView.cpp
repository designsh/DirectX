#include "PreCompile.h"
#include "SkillView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

SkillView::SkillView() :
	PanelRenderer_(nullptr),
	CloseButton_(nullptr),
	MainCollider_(nullptr),
	ButtonState_(Button_State::Normal)
{
}

SkillView::~SkillView()
{
}

void SkillView::Start()
{
	// Screen Harf Size
	float4 ScreenHarfSzie = GameEngineWindow::GetInst().GetSize().halffloat4();

	// Create Panel Renderer
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_SkillView_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	PanelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	PanelRenderer_->SetImage("Player_SkillView_Panel.png");
	PanelRenderer_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x, 24.f));

	// Button Image Cutting
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

	// Create Button Renderer
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-176.f, -166.f));
	CloseButton_->SetChangeAnimation("Default");

	// Create Button Collision
	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	Off();
}

void SkillView::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				GlobalValue::CurPlayer->SkillViewEnabled(false);
			}

			ButtonState_ = Button_State::Normal;
		}
	}

	MainCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::CloseButtonClick, this, std::placeholders::_1));
}

void SkillView::InitSkillView()
{
	// 메인플레이어 정보를 이용하여 String Setting
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();




}

void SkillView::CloseButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Default");
	}
}
