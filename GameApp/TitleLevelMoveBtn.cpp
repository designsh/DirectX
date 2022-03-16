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
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	PrevMenuBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	PrevMenuBtn_->SetImage("ShortButton_Stay.png", float4(150.f, 40.f));
	PrevMenuBtn_->GetTransform()->SetLocalPosition(float4(-WindowSize.ihx() + 130.f, -WindowSize.ihy() + 60.f));

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(150.f, 40.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(PrevMenuBtn_->GetTransform()->GetLocalPosition());
}

void TitleLevelMoveBtn::Update(float _DeltaTime)
{
	MainCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&TitleLevelMoveBtn::PrevButtonClick, this, std::placeholders::_1));

	GetLevel()->PushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);
}

void TitleLevelMoveBtn::PrevButtonClick(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 캐릭터 선택화면으로 이동
		UserGame::LevelChange("TitleLevel");
	}
}
