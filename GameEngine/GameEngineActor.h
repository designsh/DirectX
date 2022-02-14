#pragma once

// �з� : ����
// �뵵 : 
// ���� : ��� ��ü�� ���� ����� �����ϰ� ����, ������ ����� ����
class GameEngineLevel;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel* Level_;		// ������ ���� ������ �˰��ִ´�.

public:
	GameEngineActor(); // default constructer ����Ʈ ������
	~GameEngineActor(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineActor(GameEngineActor&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	virtual void Update(float _DeltaTime);

public:
	GameEngineLevel* GetLevel() const;
	void SetLevel(GameEngineLevel* Level);
};

