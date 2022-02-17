#pragma once

// �з� : ������Ʈ
// �뵵 : 
// ���� : 
class GameEngineLevel;
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
	friend GameEngineActor;

private:	// member Var
	GameEngineActor* Actor_;
	GameEngineLevel* Level_;

public:
	GameEngineComponent();
	virtual ~GameEngineComponent() = 0;

protected:		// delete constructer
	GameEngineComponent(const GameEngineComponent& _other) = delete;
	GameEngineComponent(GameEngineComponent&& _other) noexcept = delete;

private:		//delete operator
	GameEngineComponent& operator=(const GameEngineComponent& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineComponent& operator=(const GameEngineComponent&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineActor* GetActor()
	{
		return Actor_;
	}

	GameEngineLevel* GetLevel()
	{
		return Level_;
	}

protected:
	virtual void InitComponent(GameEngineActor* Actor_);
	virtual void Start() = 0;
};

