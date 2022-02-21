#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor() :
	Level_(nullptr),
	IsDestroyed_(false),
	DeathTime_(-1.f)
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

void GameEngineActor::ComponentRelease()
{
	// ������Ʈ ����� �����Ѵٸ�
	if (false == ComponentList_.empty())
	{
		std::list<GameEngineComponent*>::iterator ComponentBeginIter = ComponentList_.begin();
		std::list<GameEngineComponent*>::iterator ComponentEndIter = ComponentList_.end();
		for (; ComponentBeginIter != ComponentEndIter; )
		{
			// �ش� ������Ʈ�� ����ߴٸ� ��Ͽ��� ����
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

	// Ʈ������������Ʈ ����� �����Ѵٸ�
	if (false == TransformComponentList_.empty())
	{
		std::list<GameEngineTransformComponent*>::iterator TransformComponentBeginIter = TransformComponentList_.begin();
		std::list<GameEngineTransformComponent*>::iterator TransformComponentEndIter = TransformComponentList_.end();
		for (; TransformComponentBeginIter != TransformComponentEndIter; )
		{
			// �ش� Ʈ������������Ʈ�� ����ߴٸ� ��Ͽ��� ����
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
	// �ش� ���Ͱ� n�ʵ� ����ϱ⸦ ���ϴ� �����̶��
	// �ش� �Լ��� ȣ���Ͽ� DeathTime_�� �����ϰ�
	// IsDestroyed_ �����߰����� Flag�� On
	// Release() �� ���ڸ� �Ѱ������ʴ´ٸ� �ش� ���ʹ� ��� ���ó��
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
	// n�ʵ� ���
	if (false == IsDestroyed_)
	{
		return;
	}

	DeathTime_ -= _DeltaTime;

	if (0.0f >= DeathTime_)
	{
		// �ش� ���Ͱ� ����ϱ� ������ ����Ǵ� �Լ�
		ReleaseEvent();

		// �ش� ���Ͱ� n�ʵ�(DeathTime_)�� ����ϵ��� �����Ǿ��ٸ�
		Death();
	}
}
