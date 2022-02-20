#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor() :
	Level_(nullptr)
{
	Transform_ = new GameEngineTransform();
}

GameEngineActor::~GameEngineActor()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}

	for (auto& Component : ComponentList_)
	{
		if (nullptr != Component)
		{
			delete Component;
			Component = nullptr;
		}
	}

	for (auto& TransformComponent : TransformComponentList_)
	{
		if (nullptr != TransformComponent)
		{
			delete TransformComponent;
			TransformComponent = nullptr;
		}
	}
}

GameEngineLevel* GameEngineActor::GetLevel() const
{
	return Level_;
}

GameEngineTransform* GameEngineActor::GetTransform()
{
	return 	Transform_;
}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}

void GameEngineActor::TransformUpdate()
{
	Transform_->TransformUpdate();
}

void GameEngineActor::UpdateComponent()
{
	for (GameEngineComponent* Component : ComponentList_)
	{
		Component->Update();
	}

	for (GameEngineTransformComponent* Component : TransformComponentList_)
	{
		Component->Update();
	}
}
