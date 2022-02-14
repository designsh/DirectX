#include "PreCompile.h"
#include "GameEngineLevel.h"

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
}

void GameEngineLevel::LevelChangeEndEvent()
{
}

void GameEngineLevel::LevelChangeStartEvent()
{
}

void GameEngineLevel::Update(float _DeltaTime)
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
