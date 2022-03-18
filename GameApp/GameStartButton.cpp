#include "PreCompile.h"
#include "GameStartButton.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"

GameStartButton::GameStartButton() :
	StartButton_(nullptr),
	MainCollision_(nullptr)
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
	StartButton_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
	StartButton_->SetChangeAnimation("Default");

	// 충돌체 생성
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
}

void GameStartButton::Update(float _DeltaTime)
{
	// 디버깅용
	DebugRender();

	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&GameStartButton::GameStartButtonClick, this, std::placeholders::_1));

}

void GameStartButton::GameStartButtonClick(GameEngineCollision* _OtherCollision)
{
	// 마우스와 충돌시
	if (true == GameEngineInput::GetInst().Free("MouseLButton"))
	{
		StartButton_->SetChangeAnimation("Default");
	}

	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		StartButton_->SetChangeAnimation("Click");

		// 캐릭터 선택화면으로 이동
		UserGame::LevelChange("CreateCharacterLevel");
	}
}

void GameStartButton::ChangeStartReset()
{
	StartButton_->SetChangeAnimation("Default");
}

void GameStartButton::DebugRender()
{
	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
}
