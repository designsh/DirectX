#include "PreCompile.h"
#include "TownLevel.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"
#include "GlobalEnumClass.h"

#include "MainPlayerInfomation.h"
#include "TileMapInfoWindow.h"

#include "TownMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"

#include "Portal.h"
#include "Storehouse.h"

bool TownLevel::ResourceLoadEndCheck = false;

TownLevel::TownLevel() :
	TownMap_(nullptr),
	MainPlayer_(nullptr),
	MainMouse_(nullptr),
	WeaponNPC_(nullptr),
	ChandleryNPC_(nullptr),
	Portal_(nullptr),
	Storehouse_(nullptr),
	TileMapInfoWindow_(nullptr)
{
}

TownLevel::~TownLevel()
{
}

void TownLevel::CreateLevelActor()
{
	// 리소스 로딩완료시 액터 생성

	// 맵로딩(타일맵 - 고정맵)
	TownMap_ = CreateActor<TownMap>();
	TownMap_->TownLevel_FixedMapLoad();
	GlobalValue::TownMap = TownMap_;

	// 플레이어 생성 및 메인플레이어 지정
	if (nullptr == GlobalValue::CurPlayer)
	{
		float4 PlayerPos = TownMap_->GetTileIndexToPos(TileIndex(-2, -4));
		MainPlayer_ = CreateActor<MainPlayer>();
		MainPlayer_->GetTransform()->SetWorldPosition(PlayerPos);
		GetMainCameraActor()->GetTransform()->SetWorldPosition(float4(MainPlayer_->GetTransform()->GetLocalPosition().x, MainPlayer_->GetTransform()->GetLocalPosition().y));
		GlobalValue::CurPlayer = MainPlayer_;

		// 메인플레이어 정보 생성되었는지 체크
		if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
		{
			// 정보 생성이 되었다면 플레이어의 UI에 필요한 정보 셋팅
			if (nullptr != GlobalValue::CurPlayer)
			{
				GlobalValue::CurPlayer->CreatePlayerUIInfomation();
			}
		}
	}

	// NPC 생성(무기상인)
	float4 WeaponNPCPos = TownMap_->GetTileIndexToPos(TileIndex(-19, -15));
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetWorldPosition(WeaponNPCPos);
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC 생성(잡화상인)
	float4 ChandleryNPCPos = TownMap_->GetTileIndexToPos(TileIndex(22, -17));
	ChandleryNPC_ = CreateActor<ChandleryNPC>();
	ChandleryNPC_->GetTransform()->SetWorldPosition(ChandleryNPCPos);
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// 창고오브젝트
	float4 StorehousePos = TownMap_->GetTileIndexToPos(TileIndex(-4, -3));
	StorehousePos.y += 10.f;
	Storehouse_ = CreateActor<Storehouse>();
	Storehouse_->GetTransform()->SetWorldPosition(StorehousePos);
	GlobalValue::Storehouse = Storehouse_;

	// 맵이동 포탈생성(마을->카타콤)
	float4 PortalPos = TownMap_->GetTileIndexToPos(TileIndex(6, 7));
	Portal_ = CreateActor<Portal>();
	Portal_->GetTransform()->SetWorldPosition(PortalPos);
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("CatacombsLevel");
	Portal_->CreateLevelChangePortal(PortalType::TOWN, NextLevel, true);
	GlobalValue::Portal = Portal_;

	// 마우스
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}
}

void TownLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 체인지
	if (std::string::npos != _NextLevel->GetName().find("CatacombsLevel"))
	{
		// 카타콤배경음으로 변경
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();
			GlobalValue::BackGroundSound->PlayAlone("CatacombsLevel.wav", 99);
		}
	}

	// 전용 윈도우 Off
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("TileMapInfoWindow");
	if (nullptr != Ptr)
	{
		Ptr->Off();
	}
}

void TownLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 배경음악 On

	// 전용 윈도우 On
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("TileMapInfoWindow");
	if (nullptr != Ptr)
	{
		Ptr->On();
	}

	// 메인플레이어의 마을진입 Flag On
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->SetIsTown(true);
		GlobalValue::CurPlayer->GetTransform()->SetWorldPosition(float4(100.f, 100.f));
		GetMainCameraActor()->GetTransform()->SetLocalPosition(GlobalValue::CurPlayer->GetTransform()->GetLocalPosition());
	}
}

void TownLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -300.f));

	// TownMap전용 윈도우생성
	TileMapInfoWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<TileMapInfoWindow>("TileMapInfoWindow");
	TileMapInfoWindow_->Off();
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineInput::GetInst().Down("FREECAMERA"))
	{
		// 프리 카메라 모드 실행
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	// 볼륨 Up & Down Key
	if (true == GameEngineInput::GetInst().Down("VolumeUp"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeUp();
		}
	}
	if (true == GameEngineInput::GetInst().Down("VolumeDown"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeDown();
		}
	}
}
