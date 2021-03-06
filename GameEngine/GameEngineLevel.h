#pragma once
#include "GameEngineActor.h"
#include "Enums.h"

// 분류 : 레벨(씬)
// 용도 : 
// 설명 : 
class CameraActor;
class CameraComponent;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCollision;
class GameEngineDebugRenderData;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineLevelControlWindow;
	friend class GameEngineCore;
	friend class GameEngineRenderer;
	friend class GameEngineCollision;

private:
	class NextLevelActor
	{
	public:
		GameEngineActor* Actor_;
		GameEngineLevel* Level_;
	};

	// ==================================== Actor 관련 =================================== //
private:	// member Var
	// Key값 : 갱신순서(우선순위 판단 오더)
	// Value값 : 액터목록
	std::map<int, std::list<GameEngineActor*>> ActorList_;
	std::map<std::string, GameEngineActor*> FindActorMap_;
	std::vector<NextLevelActor> NextLevelActorsData_;

	// =================================== Camera 관련 ================================== //
private:
	CameraActor* MainCameraActor_;		// 
	CameraActor* UICameraActor_;			// 

// =================================== Collision 관련 ================================== //
private:
	std::map<int, std::list<GameEngineCollision*>> CollisionList_;

private:
	std::list<TimeEvent*> AllEvent_;
	std::list<TimeEvent*> AddEvent_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private: // 충돌체관련 기능
	inline std::list<GameEngineCollision*>& GetCollisionGroup(int _Group)
	{
		return CollisionList_[_Group];
	}

	void ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision);

private:
	void LevelChangeEndActorEvent(GameEngineLevel* _NextLevel);
	void LevelChangeStartActorEvent(GameEngineLevel* _PrevLevel);

private:
	void SetLevelActorMoveProcess();

public:
	template<typename UserEnumType>
	void PushCollision(GameEngineCollision* _Collision, UserEnumType _Group)
	{
		PushCollision(_Collision, static_cast<int>(_Group));
	}

	void PushCollision(GameEngineCollision* _Collision, int _Group);

public:
	void PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type);
	void UIPushDebugRender(GameEngineTransform* _Transform, CollisionType _Type);

public:
	template<typename ActorType>
	ActorType* CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename ActorType>
	ActorType* CreateActor(std::string _Name, bool _IsFind = false, int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->IsFindObject_ = _IsFind;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		if (true == _IsFind)
		{
			FindActorMap_.insert(std::make_pair(_Name, NewActor));
		}

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);
		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename ActorType>
	ActorType* FindActor(std::string _Name)
	{
		if (FindActorMap_.end() == FindActorMap_.find(_Name))
		{
			return nullptr;
		}

		return dynamic_cast<ActorType>(FindActorMap_[_Name]);
	}

public:
	void ActorUpdate(float _DeltaTime);
	void Render();

public:
	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();
	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();

public: // 레벨체인지 관련
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) = 0;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) = 0;

public: // 레벨시작 및 갱신관련
	void Init();
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;

public:
	void Release(float _DeltaTime);

public:
	void AddTimeEvent(float _Time, std::function<void()> _Event);
	void TimeEventUpdate();

public:
	void SetLevelActorMove(GameEngineLevel* _NextLevel, GameEngineActor* _Actor);
};

