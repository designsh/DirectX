#pragma once
#include "GameEngineActor.h"

// 분류 : 레벨(씬)
// 용도 : 
// 설명 : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;

private:	// member Var
	// Key값 : 갱신순서(우선순위 판단 오더)
	// Value값 : 액터목록
	std::map<int, std::list<GameEngineActor*>> ActorList_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public: // 추후 템플릿함수로 변경
	void CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new GameEngineActor();

		NewActor->SetLevel(this);

		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);
	}

public:
	virtual void LevelChangeEndEvent();
	virtual void LevelChangeStartEvent();

public:
	virtual void Update(float _DeltaTime);
};

