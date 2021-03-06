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
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(ButtonCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ?????????????? ?????? ???????????? ???? ????
			ButtonTypeProcess();

			// Button Reset
			Button_->SetChangeAnimation("Default");
			ButtonState_ = Button_State::Normal;
		}
	}

	// ???????? ???????? ???????? ???????? ????????
	if (nullptr != ButtonCollision_ && true == IsPointExhaust_)
	{
		ButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_LevelUpActiveButton::ButtonClick, this, std::placeholders::_1));
	}
}

void MainPlayer_LevelUpActiveButton::SetLevelUpActiveButtonInfo(LevelUpPointType _Type, const float4& _Pos)
{
	// ???? ???? ????
	LevelUpPointType_ = _Type;

	// ?????? ???? ????
	Button_->GetTransform()->SetLocalPosition(_Pos);

	// ?????? ???? ????
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
			// ?????? ??????
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsStateView())
				{
					// ???????? ????
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(100.f, 0.f, 0.f));

					// ?????? ??????
					GlobalValue::CurPlayer->StateViewEnabled(true);
				}
				else
				{
					// ???????? ???????? ????
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// ?????? ????????
					GlobalValue::CurPlayer->StateViewEnabled(false);
				}
			}
			break;
		}
		case LevelUpPointType::SKILL:
		{
			// ?????? ??????
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsSkillView())
				{
					// ???????? ????
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(-100.f, 0.f, 0.f));

					// ?????? ??????
					GlobalValue::CurPlayer->SkillViewEnabled(true);
				}
				else
				{
					// ???????? ???????? ????
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// ?????? ????????
					GlobalValue::CurPlayer->SkillViewEnabled(false);
				}
			}
			break;
		}
	}

}

void MainPlayer_LevelUpActiveButton::LevelUpPointButtonActive()
{
	// ???? ?????????? ???????? ????

	// Flag ??????
	IsPointExhaust_ = true;

	// ???? ?????? ???????? ????
	Button_->SetChangeAnimation("Default");
}

void MainPlayer_LevelUpActiveButton::LevelUpPointExhaust()
{
	// ???? ?????????? ???? ?????? ?????? ???? ?????? ????

	// ???? ?????? ?????? ?????? Flag ????
	IsPointExhaust_ = false;

	// ???? ????????
	Button_->SetChangeAnimation("Disabled");
}
