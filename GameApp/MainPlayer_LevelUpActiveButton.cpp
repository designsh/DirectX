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
			// 활성화되었을때 클릭시 포인트타입에 따라 처리
			ButtonTypeProcess();

			// Button Reset
			Button_->SetChangeAnimation("Default");
			ButtonState_ = Button_State::Normal;
		}
	}

	// 충돌체가 존재하고 플레이어 레벨업시 충돌체크
	if (nullptr != ButtonCollision_ && true == IsPointExhaust_)
	{
		ButtonCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_LevelUpActiveButton::ButtonClick, this, std::placeholders::_1));
	}
}

void MainPlayer_LevelUpActiveButton::SetLevelUpActiveButtonInfo(LevelUpPointType _Type, const float4& _Pos)
{
	// 버튼 타입 저장
	LevelUpPointType_ = _Type;

	// 렌더러 위치 지정
	Button_->GetTransform()->SetLocalPosition(_Pos);

	// 충돌체 위치 지정
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
			// 상태창 활성화
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsStateView())
				{
					// 미니메뉴 이동
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(100.f, 0.f, 0.f));

					// 스탯창 활성화
					GlobalValue::CurPlayer->StateViewEnabled(true);
				}
				else
				{
					// 미니메뉴 원래자리 복귀
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// 스탯창 비활성화
					GlobalValue::CurPlayer->StateViewEnabled(false);
				}
			}
			break;
		}
		case LevelUpPointType::SKILL:
		{
			// 스킬창 활성화
			if (nullptr != GlobalValue::CurPlayer)
			{
				if (false == GlobalValue::CurPlayer->GetIsSkillView())
				{
					// 미니메뉴 이동
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(false, float4(-100.f, 0.f, 0.f));

					// 스탯창 활성화
					GlobalValue::CurPlayer->SkillViewEnabled(true);
				}
				else
				{
					// 미니메뉴 원래자리 복귀
					GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

					// 스탯창 비활성화
					GlobalValue::CurPlayer->SkillViewEnabled(false);
				}
			}
			break;
		}
	}

}

void MainPlayer_LevelUpActiveButton::LevelUpPointButtonActive()
{
	// 현재 플레이어가 레벨업시 호출

	// Flag 활성화
	IsPointExhaust_ = true;

	// 버튼 활성화 텍스쳐로 변경
	Button_->SetChangeAnimation("Default");
}

void MainPlayer_LevelUpActiveButton::LevelUpPointExhaust()
{
	// 현재 플레이어의 해당 타입의 포인트 모두 소진시 호출

	// 해당 레벨업 포인트 소진시 Flag 해제
	IsPointExhaust_ = false;

	// 버튼 비활성화
	Button_->SetChangeAnimation("Disabled");
}
