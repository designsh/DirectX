#include "PreCompile.h"
#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent() :
	Actor_(nullptr),
	Level_(nullptr)
{
}

GameEngineComponent::~GameEngineComponent()
{
}

void GameEngineComponent::InitComponent(GameEngineActor* _Actor)
{
	Actor_ = _Actor;
	Level_ = Actor_->GetLevel();
}

