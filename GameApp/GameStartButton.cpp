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
	StartButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	StartButton_->SetImage("LongButton_Stay.png", float4(430.f, 40.f, 1.0f));

	// 충돌체 생성
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::UI0_Collider));
	MainCollision_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
}

void GameStartButton::Update(float _DeltaTime)
{
	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&GameStartButton::GameStartButtonClick, this, std::placeholders::_1));

	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
}

void GameStartButton::GameStartButtonClick(GameEngineCollision* _OtherCollision)
{
	// 마우스와 충돌시
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 캐릭터 선택화면으로 이동
		UserGame::LevelChange("CreateCharacterLevel");
	}
}
