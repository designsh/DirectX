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
#include "GameEngineUIRenderer.h"

GameEngineLevel::GameEngineLevel() :
	MainCameraActor_(nullptr),
	UICameraActor_(nullptr)
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (auto& Event : AddEvent_)
	{
		delete Event;
	}
	AddEvent_.clear();

	for (auto& Event : AllEvent_)
	{
		delete Event;
	}
	AllEvent_.clear();

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
	// Level Time Eventer Update
	TimeEventUpdate();

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
	// �����(����ü���� ������ ����Ÿ��) Ŭ����
	GameEngineDevice::RenderStart();

	// Global Font RenderTarget Clear
	GameEngineUIRenderer::GlobalFontTargetClear();

	// ����ī�޶� ����ִ� ����Ÿ�� Ŭ����
	MainCameraActor_->GetCamera()->ClearCameraTarget();

	// UIī�޶� ����ִ� ����Ÿ�� Ŭ����
	UICameraActor_->GetCamera()->ClearCameraTarget();

	// ������ Camera�� ������ ��� �������� ������
	MainCameraActor_->GetCamera()->Render();
	MainCameraActor_->GetCamera()->DebugRender();
	UICameraActor_->GetCamera()->Render();

	// ������ ī�޶� �ڽ��� ����Ÿ���� �����Ƿ�, ���������� ����ü�����κ��� ���� ����Ÿ��(�����)�� ��� �������׸��� ����
	// ���� : ������ Ÿ�ٿ� �׷����ִ� �������� �������ʰ� �״�� ��ġ�� ��
	GameEngineDevice::GetBackBufferTarget()->Merge(MainCameraActor_->GetCamera()->GetCameraRenderTarget());
	GameEngineDevice::GetBackBufferTarget()->Merge(UICameraActor_->GetCamera()->GetCameraRenderTarget());

	// ����ü��(ȭ�鿡 �ѷ���)
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

void GameEngineLevel::AddTimeEvent(float _Time, std::function<void()> _Event)
{
	AddEvent_.push_back(new TimeEvent{ _Time, _Event });
}

void GameEngineLevel::TimeEventUpdate()
{
	for (auto& Event : AddEvent_)
	{
		AllEvent_.push_back(Event);
	}
	AddEvent_.clear();

	for (auto& Event : AllEvent_)
	{
		Event->Time_ -= GameEngineTime::GetInst().GetDeltaTime();
		if (0 >= Event->Time_)
		{
			Event->Event_();
		}
	}

	std::list<TimeEvent*>::iterator StartIter = AllEvent_.begin();
	std::list<TimeEvent*>::iterator EndIter = AllEvent_.end();

	for (; StartIter != EndIter; )
	{
		if (0 >= (*StartIter)->Time_)
		{
			delete* StartIter;
			StartIter = AllEvent_.erase(StartIter);
			continue;
		}
		++StartIter;
	}
}
