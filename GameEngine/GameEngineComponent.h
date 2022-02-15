#pragma once

// �з� : ������Ʈ
// �뵵 : 
// ���� : 
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineActor* Actor_;

public:
	GameEngineComponent();
	~GameEngineComponent();

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

public:
	virtual void InitComponent(GameEngineActor* _Actor);
};

