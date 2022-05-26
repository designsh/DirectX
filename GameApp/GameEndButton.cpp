#include "PreCompile.h"
#include "GameEndButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include "UserGame.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

GameEndButton::GameEndButton() :
	ButtonState_(Button_State::Normal),
	EndButton_(nullptr),
	MainCollision_(nullptr),
	ButtonClickSound_(nullptr)
{
}

GameEndButton::~GameEndButton()
{
}

void GameEndButton::Start()
{
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("LongButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("LongButton_Click.png");
	ButtonClick->Cut(1, 1);

	EndButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	EndButton_->CreateAnimation("LongButton_Stay.png", "Default", 0, 0, 0.1f, false);
	EndButton_->CreateAnimation("LongButton_Click.png", "Click", 0, 0, 0.1f, false);
	EndButton_->GetTransform()->SetLocalScaling(float4(272.f, 35.f, 1.0f));
	EndButton_->GetTransform()->SetLocalPosition(float4(0.f, -200.f));
	EndButton_->SetChangeAnimation("Default");

	// �������� TextSetting
	EndButton_->TextSetting("diablo", "EXIT DIABLO 11", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// �浹ü ����
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(272.f, 35.f, 1.0f));
	MainCollision_->GetTransform()->SetLocalPosition(float4(0.f, -200.f));

	// ���� �÷��̾� ����
	ButtonClickSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void GameEndButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			ButtonClickSound_->Stop();

			// ���� ���� => ������ ����
			GameEngineWindow::GetInst().CloseWindow();
			ButtonState_ = Button_State::Normal;
		}
	}

	// ����׿�
	DebugRender();

	MainCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&GameEndButton::GameEndButtonClick, this, std::placeholders::_1));
}

void GameEndButton::GameEndButtonClick(GameEngineCollision* _OtherCollision)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Click");
		ButtonState_ = Button_State::Click;

		// ȿ���� ���
		ButtonClickSound_->PlayAlone("button.wav");
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Default");
		ButtonClickSound_->Stop();
	}
}

void GameEndButton::ChangeStartReset()
{
	EndButton_->SetChangeAnimation("Default");

	ButtonState_ = Button_State::Normal;
}

void GameEndButton::DebugRender()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
#endif
}
