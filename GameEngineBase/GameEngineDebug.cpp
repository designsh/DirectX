#include "PreCompile.h"
#include "GameEngineDebug.h"

// Static Var

// Static Func
void GameEngineDebug::LeakCheckOn()
{
	// Memory Leak Check
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

void GameEngineDebug::MsgBoxError(const std::string& _Ptr)
{
	MessageBoxA(nullptr, _Ptr.c_str(), "Error", MB_OK);
	assert(false);
}

void GameEngineDebug::AssertFalse()
{
	assert(false);
}

void GameEngineDebug::OutPutDebugString(const std::string& _Text)
{
	OutputDebugStringA(_Text.c_str());
}

// constructer destructer
GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug()
{
}

GameEngineDebug::GameEngineDebug(GameEngineDebug&& _other) noexcept
{
}

//member Func
