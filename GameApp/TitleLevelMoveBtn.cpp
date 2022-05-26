#include "PreCompile.h"
#include "TitleLevelMoveBtn.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "UserGame.h"

TitleLevelMoveBtn::TitleLevelMoveBtn() :
	ButtonState_(Button_State::Normal),
	PrevMenuBtn_(nullptr),
	MainCollider_(nullptr),
	ButtonClickSound_(nullptr)
{
}

TitleLevelMoveBtn::~TitleLevelMoveBtn()
{
}

void TitleLevelMoveBtn::Start()
{
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("ShortButton_Click.png");
	ButtonClick->Cut(1, 1);

	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	PrevMenuBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	PrevMenuBtn_->CreateAnimation("ShortButton_Stay.png", "Default", 0, 0, 0.1f, false);
	PrevMenuBtn_->CreateAnimation("ShortButton_Click.png", "Click", 0, 0, 0.1f, false);
	PrevMenuBtn_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	PrevMenuBtn_->GetTransform()->SetLocalPosition(float4(-WindowSize.ihx() + 80.f, -WindowSize.ihy() + 60.f));
	PrevMenuBtn_->SetChangeAnimation("Default");

	// PREV TextSetting
	PrevMenuBtn_->TextSetting("diablo", "PREV", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(PrevMenuBtn_->GetTransform()->GetLocalPosition());

	// 사운드플레이어 생성
	ButtonClickSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void TitleLevelMoveBtn::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 캐릭터 선택화면으로 이동
			UserGame::LevelChange("TitleLevel");

			ButtonState_ = Button_State::Normal;
		}
	}

	DebugRender();

	MainCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TitleLevelMoveBtn::PrevButtonClick, this, std::placeholders::_1));
}

void TitleLevelMoveBtn::ChangeStartReset()
{
	PrevMenuBtn_->SetChangeAnimation("Default");

	ButtonState_ = Button_State::Normal;
}

void TitleLevelMoveBtn::PrevButtonClick(GameEngineCollision* _OtherCollision)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		PrevMenuBtn_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;

		// 효과음 재생
		ButtonClickSound_->PlayAlone("button.wav", 0);
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		PrevMenuBtn_->SetChangeAnimation("Default");
	}
}

void TitleLevelMoveBtn::DebugRender()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);
#endif
}
