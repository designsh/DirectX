#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"

// Release
#include "GameEngineManager.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

void GameEngineCore::WindowCreate()
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", {1280, 720}, {0, 0});

	// 디바이스가 만들어져야 합니다.
	// HWND 윈도우에서 제공하는 3D 라이브러리니까 WINDOW API를 기반으로 처리되어 있습니다.
	GameEngineDevice::GetInst().Initialize();
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

void GameEngineCore::EngineInitialize()
{
	GameEngineSoundManager::GetInst().Initialize();
}

void GameEngineCore::EngineDestory()
{
	// Game Release Function

	// Resource Release
	GameEngineManagerHelper::ManagerRelease();

	// Base Release
	GameEngineTime::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}
