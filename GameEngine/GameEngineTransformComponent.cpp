#include "PreCompile.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"

GameEngineTransformComponent::GameEngineTransformComponent()
{
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
}

GameEngineTransform* GameEngineTransformComponent::GetTransform()
{
	return &Transform_;
}

void GameEngineTransformComponent::AttachTransform(GameEngineTransform* _Transform)
{
	Transform_.AttachTransform(_Transform);
}
