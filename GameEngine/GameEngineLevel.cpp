#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "GameEngineCollision.h"
#include "GameEngineDebugRenderData.h"
#include "GameEngineRenderTarget.h"

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

void GameEngineLevel::ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision)
{
	CollisionList_[_Collision->GetOrder()].remove(_Collision);
	_Collision->SetOrder(_Group);
	CollisionList_[_Collision->GetOrder()].push_back(_Collision);
}

void GameEngineLevel::ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer)
{
	MainCameraActor_->GetCamera()->ChangeRendererGroup(_Group, _Renderer);
}

void GameEngineLevel::LevelChangeEndActorEvent()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->LevelChangeEndEvent();
		}
	}
}

void GameEngineLevel::LevelChangeStartActorEvent()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->LevelChangeStartEvent();
		}
	}
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _Group)
{
	CollisionList_[_Group].push_back(_Collision);
}

void GameEngineLevel::PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type)
{
	MainCameraActor_->GetCamera()->PushDebugRender(_Transform, _Type);
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
			Actor->UpdateComponent(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render()
{
	// 백버퍼(스왑체인이 제공한 렌더타겟) 클리어
	GameEngineDevice::RenderStart();

	// 메인카메라가 들고있는 렌더타겟 클리어
	MainCameraActor_->GetCamera()->ClearCameraTarget();

	// UI카메라가 들고있는 렌더타겟 클리어
	UICameraActor_->GetCamera()->ClearCameraTarget();

	// 각각의 Camera가 가지는 모든 렌더러를 렌더링
	MainCameraActor_->GetCamera()->Render();
	MainCameraActor_->GetCamera()->DebugRender();
	UICameraActor_->GetCamera()->Render();

	// 각각의 카메라가 자신의 렌더타겟을 가지므로, 최종적으로 스왑체인으로부터 얻어온 렌더타겟(백버퍼)에 모든 렌더링항목을 병합
	// 병합 : 본래의 타겟에 그려져있는 렌더들을 지우지않고 그대로 합치는 것
	GameEngineDevice::GetBackBufferTarget()->Merge(MainCameraActor_->GetCamera()->GetCameraRenderTarget());
	GameEngineDevice::GetBackBufferTarget()->Merge(UICameraActor_->GetCamera()->GetCameraRenderTarget());

	// 스왑체인(화면에 뿌려라)
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
	// 레벨 초기화시 메인카메라를 반드시 생성한다.
	MainCameraActor_ = CreateActor<CameraActor>();

	// UI Camera 액터를 생성하며 투영타입을 직교투영으로 고정한다.
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

	// Collision Release
	std::map<int, std::list<GameEngineCollision*>>::iterator CollisionMapBeginIter = CollisionList_.begin();
	std::map<int, std::list<GameEngineCollision*>>::iterator CollisionMapEndIter = CollisionList_.end();
	for (; CollisionMapBeginIter != CollisionMapEndIter; ++CollisionMapBeginIter)
	{
		std::list<GameEngineCollision*>& Collisions = CollisionMapBeginIter->second;

		std::list<GameEngineCollision*>::iterator CollisionsBeginIter = Collisions.begin();
		std::list<GameEngineCollision*>::iterator CollisionsEndIter = Collisions.end();
		for (; CollisionsBeginIter != CollisionsEndIter; )
		{
			GameEngineCollision* ReleaseCollision = *CollisionsBeginIter;
			if (nullptr == ReleaseCollision)
			{
				GameEngineDebug::MsgBoxError("Release Collision Is Nullptr!!!!");
			}

			if (true == ReleaseCollision->IsDeath())
			{
				CollisionsBeginIter = Collisions.erase(CollisionsBeginIter);

				continue;
			}

			++CollisionsBeginIter;
		}
	}

	// Actor Release
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
