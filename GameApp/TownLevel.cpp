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
	// ���ҽ� �ε��Ϸ�� ���� ����

	// �ʷε�(Ÿ�ϸ� - ������)
	TownMap_ = CreateActor<TownMap>();
	TownMap_->TownLevel_FixedMapLoad();
	GlobalValue::TownMap = TownMap_;

	// NPC ����(�������) - �׽�Ʈ ��ġ
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetWorldPosition(float4(-270.f, 504.f, 10.f));
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC ����(��ȭ����) - �׽�Ʈ ��ġ
	ChandleryNPC_ = CreateActor<ChandleryNPC>();
	ChandleryNPC_->GetTransform()->SetWorldPosition(float4(-1420.f, 170.f, 10.f));
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// â�������Ʈ
	Storehouse_ = CreateActor<Storehouse>();
	Storehouse_->GetTransform()->SetWorldPosition(float4(-150.f, 60.f));

	// ���̵� ��Ż����(����->īŸ��)
	Portal_ = CreateActor<Portal>();
	Portal_->GetTransform()->SetWorldPosition(float4(-20.f, -250.f));
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("CatacombsLevel");
	Portal_->CreateLevelChangePortal(PortalType::TOWN, NextLevel);
	GlobalValue::Portal = Portal_;

	// ���콺
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		MainPlayer_->GetTransform()->SetWorldPosition(float4(100.f, 100.f));
		GetMainCameraActor()->GetTransform()->SetLocalPosition(MainPlayer_->GetTransform()->GetLocalPosition());
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
}

void TownLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� Off

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
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));

	// TownMap���� ���������
	TileMapInfoWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<TileMapInfoWindow>("TileMapInfoWindow");
	TileMapInfoWindow_->Off();

#pragma region ���׽�Ʈ��
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
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

#pragma region �׽�ƮŰ
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
