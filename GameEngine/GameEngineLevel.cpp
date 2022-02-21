#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"
#include "CameraActor.h"
#include "CameraComponent.h"

GameEngineLevel::GameEngineLevel() :
	MainCameraActor_(nullptr)
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
		}
	}
}

void GameEngineLevel::Render()
{
	GameEngineDevice::RenderStart();

	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;
		float4x4 View = MainCameraActor_->GetViewMatrix();
		float4x4 Porjection = MainCameraActor_->GetPorjectionMatrix();

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->GetTransform()->GetTransformData().Projection_ = Porjection;
			Renderer->GetTransform()->GetTransformData().View_ = View;

			Renderer->Render();
		}
	}

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

void GameEngineLevel::Init()
{
	// 레벨 초기화시 메인카메라를 반드시 생성한다.
	MainCameraActor_ = CreateActor<CameraActor>();
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

	std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapBeginIter = RendererList_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapEndIter = RendererList_.end();
	for (; RenderMapBeginIter != RenderMapEndIter; ++RenderMapBeginIter)
	{
		std::list<GameEngineRenderer*>& Renderers = RenderMapBeginIter->second;

		std::list<GameEngineRenderer*>::iterator RendererBeginIter = Renderers.begin();
		std::list<GameEngineRenderer*>::iterator RendererEndIter = Renderers.end();

		for (; RendererBeginIter != RendererEndIter; )
		{
			GameEngineRenderer* ReleaseRenderer = *RendererBeginIter;

			if (nullptr == ReleaseRenderer)
			{
				GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
			}

			if (true == ReleaseRenderer->IsDeath())
			{
				RendererBeginIter = Renderers.erase(RendererBeginIter);

				continue;
			}

			++RendererBeginIter;
		}
	}

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
