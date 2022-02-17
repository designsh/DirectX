#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent()
{
	Transform_ = new GameEngineTransform();
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}

GameEngineTransform* GameEngineTransformComponent::GetTransform()
{
	return Transform_;
}

void GameEngineTransformComponent::AttachTransform(GameEngineTransform* _Transform)
{
	Transform_->AttachTransform(_Transform);
}
