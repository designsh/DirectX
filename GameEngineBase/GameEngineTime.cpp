#include "PreCompile.h"
#include "GameEngineTime.h"

// Static Var
GameEngineTime* GameEngineTime::Inst = new GameEngineTime();

// Static Func

// constructer destructer
GameEngineTime::GameEngineTime()
{
	TimeCheckReset();
}

GameEngineTime::~GameEngineTime()
{
}

GameEngineTime::GameEngineTime(const GameEngineTime&& _Other)
	: timeCount_(_Other.timeCount_),
	startCheck_(_Other.startCheck_),
	endCheck_(_Other.endCheck_)
{
}

// �ð��� �غ� �Ѵ�.
void GameEngineTime::TimeCheckReset()
{
	// window�� ���� �������ϴ�.
	QueryPerformanceFrequency(&timeCount_);
	QueryPerformanceCounter(&startCheck_);
	QueryPerformanceCounter(&endCheck_);
}

void GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&endCheck_);
	deltaTime_ = static_cast<double>((endCheck_.QuadPart - startCheck_.QuadPart)) / static_cast<double>(timeCount_.QuadPart);
	startCheck_.QuadPart = endCheck_.QuadPart;
}