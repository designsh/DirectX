#include "PreCompile.h"
#include "MainPlayer_LevelUpActiveButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"
#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"
#include "StatView.h"

MainPlayer_LevelUpActiveButton::MainPlayer_LevelUpActiveButton() :
	IsPointExhaust_(false),
	LevelUpPointType_(LevelUpPointType::NONE),
	ButtonState_(Button_State::Normal),
	Button_(nullptr),
	ButtonCollision_(nullptr)
{
}

MainPlayer_LevelUpActiveButton::~MainPlayer_LevelUpActiveButton()
{
}

void MainPlayer_LevelUpActiveButton::Start()
{
	// ImageCutting
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("LevelUpButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("LevelUpButton_Click.png");
	ButtonClick->Cut(1, 1);
	GameEngineTexture* ButtonDisabled = GameEngineTextureManager::GetInst().Find("LevelUpButton_Disabled.png");
	ButtonDisabled->Cut(1, 1);

	// Create Renderer
	Button_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	Button_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	Button_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	Button_->CreateAnimation("LevelUpButton_Disabled.png", "Disabled", 0, 0, 0.1f, false);
	Button_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	Button_->SetChangeAnimation("Disabled");

	// Create Collision
	ButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
	ButtonCollision_->GetTransform()->SetLocalScaling(Button_->GetTransform()->GetLocalScaling());
}

void MainPlayer_LevelUpActiveButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// Ȱ��ȭ�Ǿ����� Ŭ���� ����ƮŸ�Կ� ���� ó��
			ButtonTypeProcess();

			// Button Reset
			Button_->SetChangeAnimation("Default");
			ButtonState_ = Button_State::Normal;
		}
	}

	// �浹ü�� �����ϰ� �÷��̾� �������� �浹üũ
	if (nullptr != ButtonCollision_ && true == IsPointExhaust_)
	{
		ButtonCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_LevelUpActiveButton::ButtonClick, this, std::placeholders::_1));
	}
}

void MainPlayer_LevelUpActiveButton::SetLevelUpActiveButtonInfo(LevelUpPointType _Type, const float4& _Pos)
{
	// ��ư Ÿ�� ����
	LevelUpPointType_ = _Type;

	// ������ ��ġ ����
	Button_->GetTransform()->SetLocalPosition(_Pos);

	// �浹ü ��ġ ����
	ButtonCollision_->GetTransform()->SetLocalPosition(Button_->GetTransform()->GetLocalPosition());
}

void MainPlayer_LevelUpActiveButton::ButtonClick(GameEngineCollision* _Other)
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

void MainPlayer_LevelUpActiveButton::ButtonTypeProcess()
{
	switch (LevelUpPointType_)
	{
		case LevelUpPointType::STAT:
		{
			// ����â Ȱ��ȭ
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsStateView())
				{
					// �̴ϸ޴� �̵�
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(100.f, 0.f, 0.f));

					// ����â Ȱ��ȭ
					GlobalValue::CurPlayer->StateViewEnabled(true);
				}
				else
				{
					// �̴ϸ޴� �����ڸ� ����
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// ����â ��Ȱ��ȭ
					GlobalValue::CurPlayer->StateViewEnabled(false);
				}
			}
			break;
		}
		case LevelUpPointType::SKILL:
		{
			// ��ųâ Ȱ��ȭ
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsSkillView())
				{
					// �̴ϸ޴� �̵�
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(-100.f, 0.f, 0.f));

					// ����â Ȱ��ȭ
					GlobalValue::CurPlayer->SkillViewEnabled(true);
				}
				else
				{
					// �̴ϸ޴� �����ڸ� ����
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// ����â ��Ȱ��ȭ
					GlobalValue::CurPlayer->SkillViewEnabled(false);
				}
			}
			break;
		}
	}

}

void MainPlayer_LevelUpActiveButton::LevelUpPointButtonActive()
{
	// ���� �÷��̾ �������� ȣ��

	// Flag Ȱ��ȭ
	IsPointExhaust_ = true;

	// ��ư Ȱ��ȭ �ؽ��ķ� ����
	Button_->SetChangeAnimation("Default");
}

void MainPlayer_LevelUpActiveButton::LevelUpPointExhaust()
{
	// ���� �÷��̾��� �ش� Ÿ���� ����Ʈ ��� ������ ȣ��

	// �ش� ������ ����Ʈ ������ Flag ����
	IsPointExhaust_ = false;

	// ��ư ��Ȱ��ȭ
	Button_->SetChangeAnimation("Disabled");
}
