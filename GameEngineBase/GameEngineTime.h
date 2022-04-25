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
	std::map<int, float> TimeScale_;

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

	float GetDeltaTime(int _Index)
	{
		if (TimeScale_.end() == TimeScale_.find(_Index))
		{
			TimeScale_[_Index] = 1.0f;
		}

		return static_cast<float>(deltaTime_) * TimeScale_[_Index];
	}

public:
	void TimeCheckReset();
	void TimeCheck();

public:
	void AddTimeEvent(float _Time, std::function<void()> _Event);

public:
	template<typename EnumType>
	void SetTimeScale(EnumType _Index, float _Scale)
	{
		SetTimeScale(static_cast<int>(_Index), _Scale);
	}

	void SetTimeScale(int _Index, float _Scale)
	{
		if (TimeScale_.end() == TimeScale_.find(_Index))
		{
			TimeScale_[_Index] = 1.0f;
		}

		TimeScale_[_Index] = _Scale;
	}

	template<typename EnumType>
	float GetTimeScale(EnumType _Index)
	{
		return GetTimeScale(static_cast<int>(_Index));
	}

	float GetTimeScale(int _Index)
	{
		if (TimeScale_.end() == TimeScale_.find(_Index))
		{
			TimeScale_[_Index] = 1.0f;
		}

		return TimeScale_[_Index];
	}
};

