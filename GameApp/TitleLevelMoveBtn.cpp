#include "PreCompile.h"
#include "TitleLevelMoveBtn.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "UserGame.h"

TitleLevelMoveBtn::TitleLevelMoveBtn() :
	PrevMenuBtn_(nullptr),
	MainCollider_(nullptr)
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
	PrevMenuBtn_->GetTransform()->SetLocalScaling(float4(150.f, 40.f, 1.f));
	PrevMenuBtn_->GetTransform()->SetLocalPosition(float4(-WindowSize.ihx() + 130.f, -WindowSize.ihy() + 60.f));
	PrevMenuBtn_->SetChangeAnimation("Default");

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(150.f, 40.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(PrevMenuBtn_->GetTransform()->GetLocalPosition());
}

void TitleLevelMoveBtn::Update(float _DeltaTime)
{
	DebugRender();

	MainCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TitleLevelMoveBtn::PrevButtonClick, this, std::placeholders::_1));
}

void TitleLevelMoveBtn::ChangeStartReset()
{
	PrevMenuBtn_->SetChangeAnimation("Default");
}

void TitleLevelMoveBtn::PrevButtonClick(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Free("MouseLButton"))
	{
		PrevMenuBtn_->SetChangeAnimation("Default");
	}

	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		PrevMenuBtn_->SetChangeAnimation("Click");

		// 캐릭터 선택화면으로 이동
		UserGame::LevelChange("TitleLevel");
	}
}

void TitleLevelMoveBtn::DebugRender()
{
	GetLevel()->PushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);
}
