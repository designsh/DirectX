#pragma once
#include "GameEngineThread.h"
#include "GameEngineIocp.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineThreadQueue
{
private:
	class Job
	{
	public:
		std::function<void()> JobFunction_;
	};

public:
	static void JobWorkThread(GameEngineThread* Thread, GameEngineIocp* _Iocp);

private:	// member Var
	GameEngineIocp Iocp_;
	int ThreadCount_;
	std::vector<GameEngineThread*> Threads_;

public:
	GameEngineThreadQueue(const std::string& _ThreadName, int _ThreadCount = 0);
	~GameEngineThreadQueue();

protected:		// delete constructer
	GameEngineThreadQueue(const GameEngineThreadQueue& _other) = delete;
	GameEngineThreadQueue(GameEngineThreadQueue&& _other) noexcept = delete;

private:		//delete operator
	GameEngineThreadQueue& operator=(const GameEngineThreadQueue& _other) = delete;
	GameEngineThreadQueue& operator=(const GameEngineThreadQueue&& _other) = delete;

public:
	void JobPost(std::function<void()> _Job)
	{
		Job* NewJob = new Job();
		NewJob->JobFunction_ = _Job;
		Iocp_.Makework(-2, NewJob);
	}

	void Destroy()
	{
		for (size_t i = 0; i < ThreadCount_; i++)
		{
			Iocp_.Makework(-1, nullptr);
			Sleep(1);
		}

		for (size_t i = 0; i < Threads_.size(); i++)
		{
			delete Threads_[i];
			Threads_[i] = nullptr;
		}

		Threads_.clear();
	}
};

