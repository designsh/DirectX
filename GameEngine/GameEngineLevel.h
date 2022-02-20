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

// ================================== Renderer ���� ================================== //
private:
	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

// =================================== Camera ���� ================================== //
private:
	CameraActor* MainCameraActor_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

// ================================== Renderer ���� ================================== //
private:
	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

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

public: // ����ü���� ����
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;

public: // �������� �� ���Ű���
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;

public:
	void Init();
};

