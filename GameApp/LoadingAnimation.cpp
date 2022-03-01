#include "PreCompile.h"
#include "LoadingAnimation.h"

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
	// �ܼ��׽�Ʈ��
	LoadingAnimation_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LoadingAnimation_->SetImage("Loading_00.png");
}

void LoadingAnimation::Update(float _DeltaTime)
{
}
