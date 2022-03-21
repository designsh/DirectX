#pragma once

struct TimeEvent
{
	float Time_;
	std::function<void()> Event_;
};

// 분류 : 델타타임 관리
// 용도 : 
// 설명 : DeltaTime 관리 및 리셋 기능 제공
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
	GameEngineTime(); // default constructer 디폴트 생성자
	~GameEngineTime(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineTime(const GameEngineTime& _Other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTime(const GameEngineTime&& _Other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTime& operator=(const GameEngineTime&& _Other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

