#include "PreCompile.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

void GameEngineThread::GameServerThreadFunction(GameEngineThread* _Thread, std::string _Name)
{
	std::wstring WName = L"";
	GameEngineString::AnsiToUnicode(_Name, WName);

	SetThreadDescription(GetCurrentThread(), WName.c_str());

	_Thread->ThreadFunction_(_Thread);
}

GameEngineThread::GameEngineThread()
{
}

GameEngineThread::~GameEngineThread()
{
	Join();
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _Function)
{
	ThreadFunction_ = _Function;
	Thread_ = std::thread(GameServerThreadFunction, this, _ThreadName);
}

void GameEngineThread::Join()
{
	Thread_.join();
}
