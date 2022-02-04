#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"

// Release
#include "GameEngineManager.h"

GameEngineCore* GameEngineCore::MainCore_ = nullptr;

void GameEngineCore::WindowCreate(GameEngineCore& _RuntimeCore)
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", _RuntimeCore.StartWindowSize(), _RuntimeCore.StartWindowPos());

	// ����̽��� ��������� �մϴ�.
	// HWND �����쿡�� �����ϴ� 3D ���̺귯���ϱ� WINDOW API�� ������� ó���Ǿ� �ֽ��ϴ�.
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

GameEngineCore::GameEngineCore() // default constructer ����Ʈ ������
{

}

GameEngineCore::~GameEngineCore() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineCore::GameEngineCore(GameEngineCore&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
