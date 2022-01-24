#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"

// Release
#include "GameEngineManager.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

void GameEngineCore::WindowCreate()
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", {1280, 720}, {0, 0});

	// HWND

}

void GameEngineCore::Loop()
{
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();

	MainCore_->GameLoop();
}

GameEngineCore::GameEngineCore() // default constructer 디폴트 생성자
{

}

GameEngineCore::~GameEngineCore() // default destructer 디폴트 소멸자
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineCore::EngineDestory()
{
	// Game Release Function

	// Resource Release
	GameEngineManagerHelper::ManagerRelease();

	// Base Release
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}
