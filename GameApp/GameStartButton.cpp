#include "PreCompile.h"
#include "GameStartButton.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"
#include "GlobalValue.h"

GameStartButton::GameStartButton() :
	ButtonState_(Button_State::Normal),
	StartButton_(nullptr),
	MainCollision_(nullptr),
	ButtonClickSound_(nullptr)
{
}

GameStartButton::~GameStartButton()
{
}

void GameStartButton::Start()
{
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("LongButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("LongButton_Click.png");
	ButtonClick->Cut(1, 1);

	StartButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	StartButton_->CreateAnimation("LongButton_Stay.png", "Default", 0, 0, 0.1f, false);
	StartButton_->CreateAnimation("LongButton_Click.png", "Click", 0, 0, 0.1f, false);
	StartButton_->GetTransform()->SetLocalScaling(float4(272.f, 35.f, 1.0f));
	StartButton_->SetChangeAnimation("Default");

	// ���ӽ��� TextSetting
	StartButton_->TextSetting("diablo", "SINGLE PLAYER", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// �浹ü ����
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(272.f, 35.f, 1.0f));

	// �����÷��̾� ����
	ButtonClickSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void GameStartButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			UserGame::LevelChange("CreateCharacterLevel");
			ButtonState_ = Button_State::Normal;
		}
	}

	// ������
	DebugRender();

	MainCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&GameStartButton::GameStartButtonClick, this, std::placeholders::_1));
}

void GameStartButton::GameStartButtonClick(GameEngineCollision* _OtherCollision)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// Ŭ���� �ִϸ��̼� ���� �� ������ȯ, ���� ���
		StartButton_->SetChangeAnimation("Click");
		ButtonState_ = Button_State::Click;

		// ȿ���� ���
		ButtonClickSound_->PlayAlone("button.wav", 0);
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		StartButton_->SetChangeAnimation("Default");
	}
}

void GameStartButton::ChangeStartReset()
{
	StartButton_->SetChangeAnimation("Default");
}

void GameStartButton::DebugRender()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
#endif
}
