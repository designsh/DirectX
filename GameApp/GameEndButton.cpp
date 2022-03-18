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
	EndButton_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
	EndButton_->GetTransform()->SetLocalPosition(float4(0.f, -300.f));
	EndButton_->SetChangeAnimation("Default");

	// �浹ü ����
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
	MainCollision_->GetTransform()->SetLocalPosition(float4(0.f, -300.f));
}

void GameEndButton::Update(float _DeltaTime)
{
	// ����׿�
	DebugRender();

	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&GameEndButton::GameEndButtonClick, this, std::placeholders::_1));
}

void GameEndButton::GameEndButtonClick(GameEngineCollision* _OtherCollision)
{
	// ���콺�� �浹��
	if (true == GameEngineInput::GetInst().Free("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Default");
	}

	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		EndButton_->SetChangeAnimation("Click");

		// ���� ���� => ������ ����
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
