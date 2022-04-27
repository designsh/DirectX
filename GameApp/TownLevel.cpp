#include "PreCompile.h"
#include "TownLevel.h"

#include "TownMap.h"

#include "TileMapInfoWindow.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"

#include "Portal.h"
#include "Storehouse.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"
#include "GlobalEnumClass.h"

#include "MainPlayerInfomation.h"

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
		MainPlayer_ = CreateActor<MainPlayer>(static_cast<int>(UpdateOrder::PLAYER));
		MainPlayer_->GetTransform()->SetWorldPosition(float4(100.f, 100.f));
		GetMainCameraActor()->GetTransform()->SetLocalPosition(MainPlayer_->GetTransform()->GetLocalPosition());
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
	WeaponNPC_ = CreateActor<WeaponNPC>(static_cast<int>(UpdateOrder::NPC));
	WeaponNPC_->GetTransform()->SetWorldPosition(WeaponNPCPos);
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC 생성(잡화상인)
	float4 ChandleryNPCPos = TownMap_->GetTileIndexToPos(TileIndex(22, -17));
	ChandleryNPC_ = CreateActor<ChandleryNPC>(static_cast<int>(UpdateOrder::NPC));
	ChandleryNPC_->GetTransform()->SetWorldPosition(ChandleryNPCPos);
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// 창고오브젝트
	float4 StorehousePos = TownMap_->GetTileIndexToPos(TileIndex(-4, -3));
	StorehousePos.y += 20.f;
	Storehouse_ = CreateActor<Storehouse>(static_cast<int>(UpdateOrder::OBJECT));
	Storehouse_->GetTransform()->SetWorldPosition(StorehousePos);

	// 맵이동 포탈생성(마을->카타콤)
	float4 PortalPos = TownMap_->GetTileIndexToPos(TileIndex(6, 7));
	Portal_ = CreateActor<Portal>(static_cast<int>(UpdateOrder::OBJECT));
	Portal_->GetTransform()->SetWorldPosition(PortalPos);
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("CatacombsLevel");
	Portal_->CreateLevelChangePortal(PortalType::TOWN, NextLevel);
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
	// 배경음악 Off

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
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));

	// TownMap전용 윈도우생성
	TileMapInfoWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<TileMapInfoWindow>("TileMapInfoWindow");
	TileMapInfoWindow_->Off();

#pragma region 맵테스트용
	if (false == GameEngineInput::GetInst().IsKey("MAPUP"))
	{
		GameEngineInput::GetInst().CreateKey("MAPUP", VK_UP);
	}

	if (false == GameEngineInput::GetInst().IsKey("MAPDOWN"))
	{
		GameEngineInput::GetInst().CreateKey("MAPDOWN", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst().IsKey("MAPLEFT"))
	{
		GameEngineInput::GetInst().CreateKey("MAPLEFT", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("MAPRIGHT"))
	{
		GameEngineInput::GetInst().CreateKey("MAPRIGHT", VK_RIGHT);
	}
#pragma endregion
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

#pragma region 테스트키
	if (true == GameEngineInput::GetInst().Press("MAPUP"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldUpVector() * _DeltaTime * 200.f);
	}

	if (true == GameEngineInput::GetInst().Press("MAPDOWN"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldDownVector() * _DeltaTime * 200.f);
	}

	if (true == GameEngineInput::GetInst().Press("MAPLEFT"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldLeftVector() * _DeltaTime * 200.f);
	}

	if (true == GameEngineInput::GetInst().Press("MAPRIGHT"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldRightVector() * _DeltaTime * 200.f);
	}
#pragma endregion
}
