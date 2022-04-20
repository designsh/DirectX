#include "PreCompile.h"
#include "GameEngineIocp.h"

GameEngineIocp::GameEngineIocp() :
	IocpHandle_(nullptr)
{
}

GameEngineIocp::~GameEngineIocp()
{
}

bool GameEngineIocp::Start(int ThreadCount)
{
	IocpHandle_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	if (nullptr == IocpHandle_)
	{
		return false;
	}

	return true;
}

BOOL GameEngineIocp::WaitforWork(DWORD& lpNumberOfBytesTransferred, ULONG_PTR& lpCompletionKey, LPOVERLAPPED& lpOverlapped, DWORD dwMilliseconds)
{
	return GetQueuedCompletionStatus(IocpHandle_, &lpNumberOfBytesTransferred, &lpCompletionKey, &lpOverlapped, dwMilliseconds);
}

BOOL GameEngineIocp::Makework(DWORD _WorkParameter, void* _Ptr)
{
	return PostQueuedCompletionStatus(IocpHandle_, _WorkParameter, reinterpret_cast<ULONG_PTR>(_Ptr), nullptr);
}
