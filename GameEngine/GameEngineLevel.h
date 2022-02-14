#pragma once
#include "GameEngineActor.h"

// �з� : ����(��)
// �뵵 : 
// ���� : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;

private:	// member Var
	// Key�� : ���ż���(�켱���� �Ǵ� ����)
	// Value�� : ���͸��
	std::map<int, std::list<GameEngineActor*>> ActorList_;

public:
	GameEngineLevel();
	~GameEngineLevel();

protected:		// delete constructer
	GameEngineLevel(const GameEngineLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public: // ���� ���ø��Լ��� ����
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

