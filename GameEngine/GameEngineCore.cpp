#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"
#include "GameEngineInput.h"
#include "GameEngineGUI.h"

// Release
#include "GameEngineResourcesManager.h"

#include "CameraComponent.h"

// ============================================= Level 관리자 관련 ============================================= //
GameEngineLevel* GameEngineCore::NextLevel_ = nullptr;
GameEngineLevel* GameEngineCore::CurrentLevel_ = nullptr;
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel_;
GameEngineThreadQueue GameEngineCore::ThreadQueue_ = GameEngineThreadQueue("GameEngineThread");

void GameEngineCore::LevelChange(const std::string& _Level)
{
	GameEngineLevel* FindLevel = LevelFind(_Level);
	if (FindLevel == CurrentLevel_)
	{
		// 동일한 레벨끼리 이동 불가
		return;
	}
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

// ============================================= GameCore 관련 ============================================= //
GameEngineCore* GameEngineCore::MainCore_ = nullptr;

void GameEngineCore::WindowCreate(GameEngineCore& _RuntimeCore)
{
	GameEngineWindow::GetInst().CreateMainWindow("MainWindow", _RuntimeCore.StartWindowSize(), _RuntimeCore.StartWindowPos());
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

	// 레벨 체인지 체크
	if (nullptr != NextLevel_)
	{
		if (nullptr == CurrentLevel_)
		{
			CurrentLevel_ = NextLevel_;
			NextLevel_->LevelChangeStartActorEvent(NextLevel_);
			NextLevel_->LevelChangeStartEvent(NextLevel_);
		}
		else
		{
			CurrentLevel_->LevelChangeEndActorEvent(NextLevel_);
			CurrentLevel_->LevelChangeEndEvent(NextLevel_);
			CurrentLevel_->SetLevelActorMoveProcess();

			NextLevel_->LevelChangeStartActorEvent(CurrentLevel_);
			NextLevel_->LevelChangeStartEvent(CurrentLevel_);
			NextLevel_->SetLevelActorMoveProcess();

			CurrentLevel_ = NextLevel_;
		}

		NextLevel_ = nullptr;
		GameEngineTime::GetInst().TimeCheckReset();
	}

	if (nullptr == CurrentLevel_)
	{
		GameEngineDebug::MsgBoxError("현재 레벨이 존재하지 않습니다.");
	}
	CurrentLevel_->LevelUpdate(GameEngineTime::GetInst().GetDeltaTime());
	CurrentLevel_->ActorUpdate(GameEngineTime::GetInst().GetDeltaTime());
	CurrentLevel_->Render();

	// 루프 중간에 사망처리로 제거되는 액터 or 컴포넌트를 관리목록에서 제거
	CurrentLevel_->Release(GameEngineTime::GetInst().GetDeltaTime());
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
	// 디바이스가 만들어져야 합니다.
	// HWND 윈도우에서 제공하는 3D 라이브러리니까 WINDOW API를 기반으로 처리되어 있습니다.
	GameEngineDevice::GetInst().Initialize();

	// 엔진용 리소스 로드
	EngineResourcesLoad();

	// 엔진용 리소스 생성
	EngineResourcesCreate();

	GameEngineDevice::GetInst().CreateSwapChain();

	GameEngineGUI::GetInst()->Initialize();

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

	// Thread Release
	ThreadQueue_.Destroy();

	// Resource Release
	GameEngineManagerHelper::ManagerRelease();

	// Base Release
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
	GameEngineGUI::Destroy();
	GameEngineDevice::Destroy();
	GameEngineWindow::Destroy();
}
