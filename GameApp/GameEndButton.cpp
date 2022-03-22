#include "PreCompile.h"
#include "GameEndButton.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"

GameEndButton::GameEndButton() :
	EndButton_(nullptr),
	MainCollision_(nullptr)
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

	// 게임종료 TextSetting
	EndButton_->TextSetting("Diablo", "EXIT DIABLO 11", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// 충돌체 생성
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(272.f, 35.f, 1.0f));
	MainCollision_->GetTransform()->SetLocalPosition(float4(0.f, -200.f));
}

void GameEndButton::Update(float _DeltaTime)
{
	// 디버그용
	DebugRender();

	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&GameEndButton::GameEndButtonClick, this, std::placeholders::_1));
}

void GameEndButton::GameEndButtonClick(GameEngineCollision* _OtherCollision)
{
	// 마우스와 충돌시
	if (true == GameEngineInput::GetInst().Free("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Default");
	}

	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Click");

		// 게임 종료 => 윈도우 종료
		GameEngineWindow::GetInst().CloseWindow();
	}
}

void GameEndButton::ChangeStartReset()
{
	EndButton_->SetChangeAnimation("Default");
}

void GameEndButton::DebugRender()
{
	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
}
