#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineIocp
{
private:	// member Var
	HANDLE IocpHandle_;

public:
	GameEngineIocp();
	~GameEngineIocp();

protected:		// delete constructer
	GameEngineIocp(const GameEngineIocp& _other) = delete;
	GameEngineIocp(GameEngineIocp&& _other) noexcept = delete;

private:		//delete operator
	GameEngineIocp& operator=(const GameEngineIocp& _other) = delete;
	GameEngineIocp& operator=(const GameEngineIocp&& _other) = delete;

public:
	bool Start(int ThreadCount = 0);
	BOOL WaitforWork(DWORD& lpNumberOfBytesTransferred, ULONG_PTR& lpCompletionKey, LPOVERLAPPED& lpOverlapped, DWORD dwMilliseconds = INFINITE);
	BOOL Makework(DWORD _WorkParameter, void* _Ptr);
};

