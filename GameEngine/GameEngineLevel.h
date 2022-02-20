#pragma once
#include "GameEngineActor.h"

// 분류 : 레벨(씬)
// 용도 : 
// 설명 : 
class CameraActor;
class CameraComponent;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;

// ==================================== Actor 관련 =================================== //
private:	// member Var
	// Key값 : 갱신순서(우선순위 판단 오더)
	// Value값 : 액터목록
	std::map<int, std::list<GameEngineActor*>> ActorList_;

// ================================== Renderer 관련 ================================== //
private:
	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

// =================================== Camera 관련 ================================== //
private:
	CameraActor* MainCameraActor_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

// ================================== Renderer 관련 ================================== //
private:
	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

// ==================================== Actor 관련 =================================== //
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

public: // 레벨체인지 관련
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;

public: // 레벨시작 및 갱신관련
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;

public:
	void Init();
};

