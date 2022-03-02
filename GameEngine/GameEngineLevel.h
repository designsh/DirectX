#pragma once
#include "GameEngineActor.h"

// �з� : ����(��)
// �뵵 : 
// ���� : 
class CameraActor;
class CameraComponent;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;

// ==================================== Actor ���� =================================== //
private:	// member Var
	// Key�� : ���ż���(�켱���� �Ǵ� ����)
	// Value�� : ���͸��
	std::map<int, std::list<GameEngineActor*>> ActorList_;

// =================================== Camera ���� ================================== //
private:
	CameraActor* MainCameraActor_;		// 
	CameraActor* UICameraActor_;			// 

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

// ==================================== Actor ���� =================================== //
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

public:
	void ActorUpdate(float _DeltaTime);
	void Render();

public:
	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();
	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();

public: // ����ü���� ����
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;

public: // �������� �� ���Ű���
	void Init();
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;

public:
	void Release(float _DeltaTime);
};
