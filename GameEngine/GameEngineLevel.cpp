#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"
#include "CameraActor.h"
#include "CameraComponent.h"

GameEngineLevel::GameEngineLevel() :
	MainCameraActor_(nullptr),
	UICameraActor_(nullptr)
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

			Actor->TransformUpdate();
		}
	}

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
			Actor->UpdateComponent(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render()
{
	GameEngineDevice::RenderStart();

	// MainCamera�� ������ ��� �������� ������
	MainCameraActor_->GetCamera()->Render();

	// UICamera�� ������ ��� �������� ������
	UICameraActor_->GetCamera()->Render();

	GameEngineDevice::RenderEnd();
}

CameraActor* GameEngineLevel::GetMainCameraActor()
{
	return MainCameraActor_;
}

CameraComponent* GameEngineLevel::GetMainCamera()
{
	return MainCameraActor_->GetCamera();
}

CameraActor* GameEngineLevel::GetUICameraActor()
{
	return UICameraActor_;
}

CameraComponent* GameEngineLevel::GetUICamera()
{
	return UICameraActor_->GetCamera();
}

void GameEngineLevel::Init()
{
	// ���� �ʱ�ȭ�� ����ī�޶� �ݵ�� �����Ѵ�.
	MainCameraActor_ = CreateActor<CameraActor>();

	// UI Camera ���͸� �����ϸ� ����Ÿ���� ������������ �����Ѵ�.
	UICameraActor_ = CreateActor<CameraActor>();
	UICameraActor_->GetCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	UICameraActor_->GetCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void GameEngineLevel::Release(float _DeltaTime)
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->ReleaseUpdate(_DeltaTime);
		}
	}

	MainCameraActor_->GetCamera()->ReleaseRenderer();
	UICameraActor_->GetCamera()->ReleaseRenderer();

	std::map<int, std::list<GameEngineActor*>>::iterator ActorMapBeginIter = ActorList_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator ActorMapEndIter = ActorList_.end();
	for (; ActorMapBeginIter != ActorMapEndIter; ++ActorMapBeginIter)
	{
		std::list<GameEngineActor*>& Actors = ActorMapBeginIter->second;

		std::list<GameEngineActor*>::iterator ActorsBeginIter = Actors.begin();
		std::list<GameEngineActor*>::iterator ActorsEndIter = Actors.end();

		for (; ActorsBeginIter != ActorsEndIter; )
		{
			GameEngineActor* ReleaseActor = *ActorsBeginIter;

			if (nullptr == ReleaseActor)
			{
				GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
			}

			ReleaseActor->ComponentRelease();

			if (true == ReleaseActor->IsDeath())
			{
				delete* ActorsBeginIter;
				*ActorsBeginIter = nullptr;

				ActorsBeginIter = Actors.erase(ActorsBeginIter);

				continue;
			}

			++ActorsBeginIter;
		}
	}
}
