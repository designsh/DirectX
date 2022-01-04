#pragma once
// �з� :
// �뵵 :
// ���� :
class GameEngineTime
{

private:
	static GameEngineTime* Inst;

public:
	static GameEngineTime& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:
	LARGE_INTEGER timeCount_;
	LARGE_INTEGER startCheck_;
	LARGE_INTEGER endCheck_;
	double deltaTime_;

public:
	// ���⿡ �̷��� ����� ������ ����
	// �����ϴ°� �⺻�ڷ����̾
	double GetDeltaTimeD()
	{
		return deltaTime_;
	}

	float GetDeltaTime()
	{
		return static_cast<float>(deltaTime_);
	}
public:
	GameEngineTime(); // default constructer ����Ʈ ������
	~GameEngineTime(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineTime(const GameEngineTime& _Other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTime(const GameEngineTime&& _Other); // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTime& operator=(const GameEngineTime&& _Other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	void TimeCheckReset();
	void TimeCheck();
};

