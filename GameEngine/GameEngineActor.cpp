#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor() :
	Level_(nullptr),
	IsDestroyed_(false),
	DeathTime_(-1.f),
	IsFindObject_(false)
{
}

GameEngineActor::~GameEngineActor()
{
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
	return &Transform_;
}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}

void GameEngineActor::UpdateComponent(float _DeltaTime)
{
	for (GameEngineComponent* Component : ComponentList_)
	{
		Component->Update(_DeltaTime);
	}

	for (GameEngineTransformComponent* Component : TransformComponentList_)
	{
		Component->Update(_DeltaTime);
	}
}

void GameEngineActor::ComponentRelease()
{
	// 컴포넌트 목록이 존재한다면
	if (false == ComponentList_.empty())
	{
		std::list<GameEngineComponent*>::iterator ComponentBeginIter = ComponentList_.begin();
		std::list<GameEngineComponent*>::iterator ComponentEndIter = ComponentList_.end();
		for (; ComponentBeginIter != ComponentEndIter; )
		{
			// 해당 컴포넌트가 사망했다면 목록에서 제거
			if (true == (*ComponentBeginIter)->IsDeath())
			{
				delete* ComponentBeginIter;
				*ComponentBeginIter = nullptr;

				ComponentBeginIter = ComponentList_.erase(ComponentBeginIter);
				continue;
			}

			++ComponentBeginIter;
		}
	}

	// 트랜스폼컴포넌트 목록이 존재한다면
	if (false == TransformComponentList_.empty())
	{
		std::list<GameEngineTransformComponent*>::iterator TransformComponentBeginIter = TransformComponentList_.begin();
		std::list<GameEngineTransformComponent*>::iterator TransformComponentEndIter = TransformComponentList_.end();
		for (; TransformComponentBeginIter != TransformComponentEndIter; )
		{
			// 해당 트랜스폼컴포넌트가 사망했다면 목록에서 제거
			if (true == (*TransformComponentBeginIter)->IsDeath())
			{
				delete* TransformComponentBeginIter;
				*TransformComponentBeginIter = nullptr;

				TransformComponentBeginIter = TransformComponentList_.erase(TransformComponentBeginIter);
				continue;
			}

			++TransformComponentBeginIter;
		}
	}
}

void GameEngineActor::Release(float _Time)
{
	// 해당 액터가 n초뒤 사망하기를 원하는 조건이라면
	// 해당 함수를 호출하여 DeathTime_을 설정하고
	// IsDestroyed_ 루프중간제거 Flag를 On
	// Release() 에 인자를 넘겨주지않는다면 해당 액터는 즉시 사망처리
	if (0.0f >= _Time)
	{
		Death();
	}
	else
	{
		IsDestroyed_ = true;
		DeathTime_ = _Time;
	}
}

void GameEngineActor::ReleaseUpdate(float _DeltaTime)
{
	// n초뒤 사망
	if (false == IsDestroyed_)
	{
		return;
	}

	DeathTime_ -= _DeltaTime;

	if (0.0f >= DeathTime_)
	{
		// 해당 액터가 사망하기 직전에 실행되는 함수
		ReleaseEvent();

		// 해당 액터가 n초뒤(DeathTime_)에 사망하도록 설정되었다면
		Death();
	}
}
