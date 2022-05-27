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
	// ���ҽ� �ε��Ϸ�� ���� ����

	// �ʷε�(Ÿ�ϸ� - ������)
	TownMap_ = CreateActor<TownMap>();
	TownMap_->TownLevel_FixedMapLoad();
	GlobalValue::TownMap = TownMap_;

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		float4 PlayerPos = TownMap_->GetTileIndexToPos(TileIndex(-2, -4));
		MainPlayer_ = CreateActor<MainPlayer>();
		MainPlayer_->GetTransform()->SetWorldPosition(PlayerPos);
		GetMainCameraActor()->GetTransform()->SetWorldPosition(float4(MainPlayer_->GetTransform()->GetLocalPosition().x, MainPlayer_->GetTransform()->GetLocalPosition().y));
		GlobalValue::CurPlayer = MainPlayer_;

		// �����÷��̾� ���� �����Ǿ����� üũ
		if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
		{
			// ���� ������ �Ǿ��ٸ� �÷��̾��� UI�� �ʿ��� ���� ����
			if (nullptr != GlobalValue::CurPlayer)
			{
				GlobalValue::CurPlayer->CreatePlayerUIInfomation();
			}
		}
	}

	// NPC ����(�������)
	float4 WeaponNPCPos = TownMap_->GetTileIndexToPos(TileIndex(-19, -15));
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetWorldPosition(WeaponNPCPos);
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC ����(��ȭ����)
	float4 ChandleryNPCPos = TownMap_->GetTileIndexToPos(TileIndex(22, -17));
	ChandleryNPC_ = CreateActor<ChandleryNPC>();
	ChandleryNPC_->GetTransform()->SetWorldPosition(ChandleryNPCPos);
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// â�������Ʈ
	float4 StorehousePos = TownMap_->GetTileIndexToPos(TileIndex(-4, -3));
	StorehousePos.y += 10.f;
	Storehouse_ = CreateActor<Storehouse>();
	Storehouse_->GetTransform()->SetWorldPosition(StorehousePos);
	GlobalValue::Storehouse = Storehouse_;

	// ���̵� ��Ż����(����->īŸ��)
	float4 PortalPos = TownMap_->GetTileIndexToPos(TileIndex(6, 7));
	Portal_ = CreateActor<Portal>();
	Portal_->GetTransform()->SetWorldPosition(PortalPos);
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("CatacombsLevel");
	Portal_->CreateLevelChangePortal(PortalType::TOWN, NextLevel, true);
	GlobalValue::Portal = Portal_;

	// ���콺
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}
}

void TownLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� ü����
	if (std::string::npos != _NextLevel->GetName().find("CatacombsLevel"))
	{
		// īŸ�޹�������� ����
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();
			GlobalValue::BackGroundSound->PlayAlone("CatacombsLevel.wav", 99);
		}
	}

	// ���� ������ Off
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("TileMapInfoWindow");
	if (nullptr != Ptr)
	{
		Ptr->Off();
	}
}

void TownLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On

	// ���� ������ On
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("TileMapInfoWindow");
	if (nullptr != Ptr)
	{
		Ptr->On();
	}

	// �����÷��̾��� �������� Flag On
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

	// TownMap���� ���������
	TileMapInfoWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<TileMapInfoWindow>("TileMapInfoWindow");
	TileMapInfoWindow_->Off();
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineInput::GetInst().Down("FREECAMERA"))
	{
		// ���� ī�޶� ��� ����
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	// ���� Up & Down Key
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
