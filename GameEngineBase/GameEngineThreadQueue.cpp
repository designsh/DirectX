#include "PreCompile.h"
#include "GameEngineThreadQueue.h"

void GameEngineThreadQueue::JobWorkThread(GameEngineThread* Thread, GameEngineIocp* _Iocp)
{
	DWORD lpNumberOfBytesTransferred = 0;
	ULONG_PTR lpCompletionKey = 0;
	LPOVERLAPPED Ptr = nullptr;
	while (true)
	{
		_Iocp->WaitforWork(lpNumberOfBytesTransferred, lpCompletionKey, Ptr);

		switch (lpNumberOfBytesTransferred)
		{
			case -1:
			{
				return;
			}
			case -2:
			{
				Job* PostJob = reinterpret_cast<Job*>(lpCompletionKey);
				PostJob->JobFunction_();
				delete PostJob;
				break;
			}
		}
	}
}

GameEngineThreadQueue::GameEngineThreadQueue(const std::string& _ThreadName, int _ThreadCount)
{
	ThreadCount_ = _ThreadCount;
	if (ThreadCount_ == 0)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount_ = Info.dwNumberOfProcessors - 2;
	}

	if (ThreadCount_ <= 0)
	{
		ThreadCount_ = 1;
	}

	Iocp_.Start(ThreadCount_);
	for (size_t i = 0; i < ThreadCount_; i++)
	{
		GameEngineThread* NewThread = new GameEngineThread();
		std::string ThreadName = _ThreadName + std::to_string(static_cast<int>(i));
		NewThread->Start(ThreadName, std::bind(JobWorkThread, NewThread, &Iocp_));
		Threads_.push_back(NewThread);
	}
}

GameEngineThreadQueue::~GameEngineThreadQueue()
{
	Destroy();
}
