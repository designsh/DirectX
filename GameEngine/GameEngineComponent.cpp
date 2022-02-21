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
	// 부모를 설정(ObjectBase)
	SetParent(_Actor);

	// 부모 액터를 지정(Member Value)
	Actor_ = _Actor;

	// 부모액터의 레벨이 나의 레벨이 됨
	Level_ = Actor_->GetLevel();
}

