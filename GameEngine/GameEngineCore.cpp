#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"
#include "GameEngineInput.h"

// Release
#include "GameEngineResourcesManager.h"

// ============================================= Level ������ ���� ============================================= //
GameEngineLevel* GameEngineCore::NextLevel_ = nullptr;
GameEngineLevel* GameEngineCore::CurrentLevel_ = nullptr;
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel_;

void GameEngineCore::LevelChange(const std::string& _Level)
{
	GameEngineLevel* FindLevel = LevelFind(_Level);
	if (nullptr == FindLevel)
	{
		GameEngineDebug::MsgBoxError("Next Level Is Nullptr");
	}

	NextLevel_ = FindLevel;
}

GameEngineLevel* GameEngineCore::LevelFind(const std::string& _Level)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Level);
	if (FindIter != AllLevel_.end())
	{
		return FindIter->second;
	}
	return nullptr;
}

// ============================================= GameCore ���� ============================================= //
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
	GameEngineTime::GetInst().TimeCheckReset();
	GameEngineWindow::GetInst().Loop(&GameEngineCore::MainLoop);
}

void GameEngineCore::MainLoop()
{
	GameEngineTime::GetInst().TimeCheck();
	GameEngineSoundManager::GetInst().SoundUpdate();
	GameEngineInput::GetInst().Update();

	// ���� ü���� üũ
	if (nullptr != NextLevel_)
	{
		if (nullptr == CurrentLevel_)
		{
			CurrentLevel_ = NextLevel_;
		}
		else
		{
			CurrentLevel_->LevelChangeEndEvent();
			NextLevel_->LevelChangeStartEvent();
			CurrentLevel_ = NextLevel_;
		}

		NextLevel_ = nullptr;
		GameEngineTime::GetInst().TimeCheckReset();
	}

	if (nullptr == CurrentLevel_)
	{
		GameEngineDebug::MsgBoxError("���� ������ �������� �ʽ��ϴ�.");
	}
	CurrentLevel_->LevelUpdate(GameEngineTime::GetInst().GetDeltaTime());
	CurrentLevel_->ActorUpdate(GameEngineTime::GetInst().GetDeltaTime());
	CurrentLevel_->Render();

	// ���� �߰��� ���ó���� ���ŵǴ� ���� or ������Ʈ�� ������Ͽ��� ����
	CurrentLevel_->Release(GameEngineTime::GetInst().GetDeltaTime());
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
	// ������ ���ҽ� �ε�
	EngineResourcesLoad();

	// ������ ���ҽ� ����
	EngineResourcesCreate();

	GameEngineCollision::Init();
	GameEngineSoundManager::GetInst().Initialize();
}

void GameEngineCore::EngineDestory()
{
	// Game Release Function

	// GameLevel Release
	for (auto& Level : AllLevel_)
	{
		if (nullptr != Level.second)
		{
			delete  Level.second;
			Level.second = nullptr;
		}
	}

	// Resource Release
	GameEngineManagerHelper::ManagerRelease();

	// Base Release
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}
