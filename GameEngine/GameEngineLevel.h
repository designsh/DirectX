#pragma once
#include "GameEngineActor.h"
#include "Enums.h"

// �з� : ����(��)
// �뵵 : 
// ���� : 
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

	// ==================================== Actor ���� =================================== //
private:	// member Var
	// Key�� : ���ż���(�켱���� �Ǵ� ����)
	// Value�� : ���͸��
	std::map<int, std::list<GameEngineActor*>> ActorList_;
	std::map<std::string, GameEngineActor*> FindActorMap_;
	std::vector<NextLevelActor> NextLevelActorsData_;

	// =================================== Camera ���� ================================== //
private:
	CameraActor* MainCameraActor_;		// 
	CameraActor* UICameraActor_;			// 

// =================================== Collision ���� ================================== //
private:
	std::map<int, std::list<GameEngineCollision*>> CollisionList_;

private:
	std::list<TimeEvent*> AllEvent_;
	std::list<TimeEvent*> AddEvent_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private: // �浹ü���� ���
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

public: // ����ü���� ����
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) = 0;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) = 0;

public: // �������� �� ���Ű���
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

