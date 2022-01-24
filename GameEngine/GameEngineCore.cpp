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

GameEngineCore::GameEngineCore() // default constructer ����Ʈ ������
{

}

GameEngineCore::~GameEngineCore() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
