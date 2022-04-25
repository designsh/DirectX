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
	// �θ� ����(ObjectBase)
	SetParent(_Actor);

	// �θ� ���͸� ����(Member Value)
	Actor_ = _Actor;
}

