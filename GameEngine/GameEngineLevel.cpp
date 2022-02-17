#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;
		for (GameEngineActor* Actor : Actors)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}
}

void GameEngineLevel::PushRenderer(int _Order, GameEngineRenderer* _Renderer)
{
	RendererList_[_Order].push_back(_Renderer);
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;
		for (GameEngineActor* Actor : Actors)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render()
{
	GameEngineDevice::RenderStart();

	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->Render();
		}
	}

	GameEngineDevice::RenderEnd();
}
