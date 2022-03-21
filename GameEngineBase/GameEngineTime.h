#pragma once

struct TimeEvent
{
	float Time_;
	std::function<void()> Event_;
};

// �з� : ��ŸŸ�� ����
// �뵵 : 
// ���� : DeltaTime ���� �� ���� ��� ����
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

public:
	GameEngineTime(); // default constructer ����Ʈ ������
	~GameEngineTime(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineTime(const GameEngineTime& _Other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTime(const GameEngineTime&& _Other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTime& operator=(const GameEngineTime&& _Other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	LARGE_INTEGER timeCount_;
	LARGE_INTEGER startCheck_;
	LARGE_INTEGER endCheck_;
	double deltaTime_;

private:
	std::list<TimeEvent*> AllEvent_;
	std::list<TimeEvent*> AddEvent_;

public:	//member Func
	double GetDeltaTimeD()
	{
		return deltaTime_;
	}

	float GetDeltaTime()
	{
		return static_cast<float>(deltaTime_);
	}

public:
	void TimeCheckReset();
	void TimeCheck();

public:
	void AddTimeEvent(float _Time, std::function<void()> _Event);
};

