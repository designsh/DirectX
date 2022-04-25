#include "PreCompile.h"
#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent() :
	Actor_(nullptr)
{
}

GameEngineComponent::~GameEngineComponent()
{
}

GameEngineLevel* GameEngineComponent::GetLevel()
{
	return Actor_->GetLevel();
}

void GameEngineComponent::InitComponent(GameEngineActor* _Actor)
{
	// 부모를 설정(ObjectBase)
	SetParent(_Actor);

	// 부모 액터를 지정(Member Value)
	Actor_ = _Actor;
}

