#include "PreCompile.h"
#include "LoadingAnimation.h"

#include "UserGame.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

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

	LoadingAnimation_ = CreateTransformComponent<GameEngineUIRenderer>();
	LoadingAnimation_->CreateAnimation("Loading.png", "LoadingAnimation", 0, 9, 0.1f, false);
	LoadingAnimation_->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
	LoadingAnimation_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(UIRenderOrder::UI0)));
	LoadingAnimation_->SetChangeAnimation("LoadingAnimation");

	// �ִϸ��̼� ����� ���� ��ȯ
	LoadingAnimation_->SetEndCallBack("LoadingAnimation", std::bind(&LoadingAnimation::LoadingEnd, this));
}

void LoadingAnimation::Update(float _DeltaTime)
{
}

void LoadingAnimation::LoadingEnd()
{
	// �ε��� �������Ƿ� ������ȯ
	UserGame::LevelChange("TownLevel");
}
