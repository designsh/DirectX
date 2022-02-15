#include "PreCompile.h"
#include "GameEngineComponent.h"

GameEngineComponent::GameEngineComponent() :
	Actor_(nullptr)
{

}

GameEngineComponent::~GameEngineComponent()
{

}

void GameEngineComponent::InitComponent(GameEngineActor* _Actor)
{
	Actor_ = _Actor;
}

