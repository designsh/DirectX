#include "PreCompile.h"
#include "LoadingAnimation.h"

#include "UserGame.h"

#include <GameEngine/GameEngineImageRenderer.h>

LoadingAnimation::LoadingAnimation() :
	LoadingAnimation_(nullptr)
{
}

LoadingAnimation::~LoadingAnimation()
{
}

void LoadingAnimation::Start()
{
	GameEngineTexture* Loading = GameEngineTextureManager::GetInst().Find("Loading.png");
	Loading->Cut(10, 1);

	LoadingAnimation_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LoadingAnimation_->CreateAnimation("Loading.png", "LoadingAnimation", 0, 9, 0.1f, false);
	LoadingAnimation_->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
	LoadingAnimation_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -20.f));
	LoadingAnimation_->SetChangeAnimation("LoadingAnimation");

	// 애니메이션 종료시 레벨 전환
	LoadingAnimation_->SetEndCallBack("LoadingAnimation", std::bind(&LoadingAnimation::LoadingEnd, this));
}

void LoadingAnimation::Update(float _DeltaTime)
{
}

void LoadingAnimation::LoadingEnd()
{
	// 로딩이 끝났으므로 레벨전환
	UserGame::LevelChange("TownLevel");
}
