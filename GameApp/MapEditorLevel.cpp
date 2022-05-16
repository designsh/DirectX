#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "EditorModeSelectWindow.h"
#include "CreateTileMapWindow.h"
#include "CreateRandomMapWindow.h"

#include "EditorTileMap.h"
#include "EditorRandomMap.h"
#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

bool MapEditorLevel::ResourceLoadEndCheck = false;
EditorMode MapEditorLevel::CurEditorMode = EditorMode::None;

MapEditorLevel::MapEditorLevel() :
	EditorFixedMap_(nullptr),
	EditorRandomMap_(nullptr),
	EditorModeSelWindow_(nullptr),
	TileMapWindow_(nullptr),
	RandomMapWindow_(nullptr),
	MoveSpeed_(1000.f)
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::CreateLevelActor()
{
#pragma region TileTexture Cutting

	// ������ �ؽ���
	GameEngineTexture* TownFloorTile = GameEngineTextureManager::GetInst().Find("Town_Floor.png");
	TownFloorTile->Cut(5, 37);
	GameEngineTexture* TownWallTile = GameEngineTextureManager::GetInst().Find("Town_Wall.png");
	TownWallTile->Cut(31, 1);
	GameEngineTexture* TownObjectTile = GameEngineTextureManager::GetInst().Find("Town_Object.png");
	TownObjectTile->Cut(53, 1);

	// īŸ�޸� �ؽ���
	GameEngineTexture* CatacombsFloorTile = GameEngineTextureManager::GetInst().Find("Catacombs_Floor.png");
	CatacombsFloorTile->Cut(5, 15);
	GameEngineTexture* CatacombsWallTile = GameEngineTextureManager::GetInst().Find("Catacombs_Wall.png");
	CatacombsWallTile->Cut(47, 1);
	GameEngineTexture* CatacombsObjectTile = GameEngineTextureManager::GetInst().Find("Catacombs_Object.png");
	CatacombsObjectTile->Cut(25, 1);

	// ī�������� �ؽ���
	GameEngineTexture* ChaosSanctuaryFloorTile = GameEngineTextureManager::GetInst().Find("ChaosSanctuary_Floor.png");
	ChaosSanctuaryFloorTile->Cut(5, 59);
	GameEngineTexture* ChaosSanctuaryWallTile = GameEngineTextureManager::GetInst().Find("ChaosSanctuary_Wall.png");
	ChaosSanctuaryWallTile->Cut(47, 1);

	// �Ϲݱ׸���
	GameEngineTexture* FloorGridNor = GameEngineTextureManager::GetInst().Find("FloorGrid_Normal.png");
	FloorGridNor->Cut(1, 1);
	GameEngineTexture* WallGridNor = GameEngineTextureManager::GetInst().Find("WallGrid_Normal.png");
	WallGridNor->Cut(1, 1);

	// �ٴ� �׸���
	GameEngineTexture* FloorGridCorridor = GameEngineTextureManager::GetInst().Find("FloorGrid_Corridor.png");
	FloorGridCorridor->Cut(1, 1);

	// ���ͱ׸���
	GameEngineTexture* FloorGridCenter = GameEngineTextureManager::GetInst().Find("FloorGrid_Center.png");
	FloorGridCenter->Cut(1, 1);
	GameEngineTexture* WallGridCenter = GameEngineTextureManager::GetInst().Find("WallGrid_Center.png");
	WallGridCenter->Cut(1, 1);

	// Ư���׸���
	// NONE
	GameEngineTexture* WallGridNone = GameEngineTextureManager::GetInst().Find("WallGrid_None.png");
	WallGridNone->Cut(1, 1);

	// RT_T
	GameEngineTexture* WallGridRT_T = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T.png");
	WallGridRT_T->Cut(1, 1);
	GameEngineTexture* WallGridRT_T_LE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T_LE.png");
	WallGridRT_T_LE->Cut(1, 1);
	GameEngineTexture* WallGridRT_T_RE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T_RE.png");
	WallGridRT_T_RE->Cut(1, 1);

	// RT_B
	GameEngineTexture* WallGridRT_B = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B.png");
	WallGridRT_B->Cut(1, 1);
	GameEngineTexture* WallGridRT_B_LE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B_LE.png");
	WallGridRT_B_LE->Cut(1, 1);
	GameEngineTexture* WallGridRT_B_RE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B_RE.png");
	WallGridRT_B_RE->Cut(1, 1);

	// RB_L
	GameEngineTexture* WallGridRB_L = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L.png");
	WallGridRB_L->Cut(1, 1);
	GameEngineTexture* WallGridRB_L_TE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L_TE.png");
	WallGridRB_L_TE->Cut(1, 1);
	GameEngineTexture* WallGridRB_L_BE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L_BE.png");
	WallGridRB_L_BE->Cut(1, 1);

	// RB_R
	GameEngineTexture* WallGridRB_R = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R.png");
	WallGridRB_R->Cut(1, 1);
	GameEngineTexture* WallGridRB_R_TE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R_TE.png");
	WallGridRB_R_TE->Cut(1, 1);
	GameEngineTexture* WallGridRB_R_BE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R_BE.png");
	WallGridRB_R_BE->Cut(1, 1);

	// BENT
	GameEngineTexture* WallGridBentMulti = GameEngineTextureManager::GetInst().Find("WallGrid_Bent_Multi.png");
	WallGridBentMulti->Cut(1, 1);
	GameEngineTexture* WallGridBentSingle = GameEngineTextureManager::GetInst().Find("WallGrid_Bent_Single.png");
	WallGridBentSingle->Cut(1, 1);

	// DOOR
	GameEngineTexture* DoorGrid_RB_B = GameEngineTextureManager::GetInst().Find("DoorGrid_RB_B.png");
	DoorGrid_RB_B->Cut(1, 1);
	GameEngineTexture* DoorGrid_RB_T = GameEngineTextureManager::GetInst().Find("DoorGrid_RB_T.png");
	DoorGrid_RB_T->Cut(1, 1);
	GameEngineTexture* DoorGrid_RT_L = GameEngineTextureManager::GetInst().Find("DoorGrid_RT_L.png");
	DoorGrid_RT_L->Cut(1, 1);
	GameEngineTexture* DoorGrid_RT_R = GameEngineTextureManager::GetInst().Find("DoorGrid_RT_R.png");
	DoorGrid_RT_R->Cut(1, 1);

	// OBJECT
	GameEngineTexture* ObjectGrid = GameEngineTextureManager::GetInst().Find("ObjectGrid_Object.png");
	ObjectGrid->Cut(1, 1);
#pragma endregion

#pragma region IsoFixedTileMap Create & Setting
	EditorFixedMap_ = CreateActor<EditorTileMap>();
	TileMapWindow_->TileMap_ = EditorFixedMap_;
	EditorFixedMap_->SetFloorTileTexture("Town_Floor.png");
	EditorFixedMap_->SetWallTileTexture("Town_Wall.png");
	EditorFixedMap_->SetObjectTileTexture("Town_Object.png");
#pragma endregion

#pragma region RandomMap Create & Setting
	EditorRandomMap_ = CreateActor<EditorRandomMap>();
	RandomMapWindow_->RandomMap_ = EditorRandomMap_;
#pragma endregion
}

void MapEditorLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	{
		GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("EditorModeSelectWindow");
		if (nullptr != Ptr)
		{
			Ptr->Off();
		}
	}

	{
		GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
		if (nullptr != Ptr)
		{
			Ptr->Off();
		}
	}

	{
		GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateRandomMapWindow");
		if (nullptr != Ptr)
		{
			Ptr->Off();
		}
	}

	// ����ü���� ������ ������� Ŭ���� �÷��� ����
	GameEngineDevice::GetInst().GetBackBufferTarget()->ClearColorChange(float4::BLACK);
}

void MapEditorLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	{
		GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("EditorModeSelectWindow");
		if (nullptr != Ptr)
		{
			Ptr->On();
		}
	}

	// ����ü���� ������ ������� Ŭ���� �÷��� ����
	GameEngineDevice::GetInst().GetBackBufferTarget()->ClearColorChange(float4::BLUE);
}

void MapEditorLevel::LevelStart()
{
#pragma region SetMainCamera
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -300.f));
#pragma endregion

#pragma region Editor Windows
	// Edit Mode Select Window
	EditorModeSelWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<EditorModeSelectWindow>("EditorModeSelectWindow");
	EditorModeSelWindow_->Off();

	// CreateTileMap Window
	TileMapWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");
	TileMapWindow_->Off();

	// CreateRandomMap Window
	RandomMapWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<CreateRandomMapWindow>("CreateRandomMapWindow");
	RandomMapWindow_->Off();
#pragma endregion

#pragma region CreateKey
	if (false == GameEngineInput::GetInst().IsKey("CameraUp"))
	{
		GameEngineInput::GetInst().CreateKey("CameraUp", VK_UP);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraDown"))
	{
		GameEngineInput::GetInst().CreateKey("CameraDown", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraLeft"))
	{
		GameEngineInput::GetInst().CreateKey("CameraLeft", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraRight"))
	{
		GameEngineInput::GetInst().CreateKey("CameraRight", VK_RIGHT);
	}
#pragma endregion

#pragma region �׸��� ON/OFF
	// �ٴ�Ÿ�� �׸��� On/Off
	if (false == GameEngineInput::GetInst().IsKey("FloorGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("FloorGrideSwitching", 'i');
	}

	// ��Ÿ�� �׸��� On/Off
	if (false == GameEngineInput::GetInst().IsKey("WallGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("WallGrideSwitching", 'o');
	}

	// ������ƮŸ�� �׸��� On/Off
	if (false == GameEngineInput::GetInst().IsKey("ObjectGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("ObjectGrideSwitching", 'p');
	}
#pragma endregion
}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
	{
		return;
	}

#pragma region EditorModeCheck
	if (EditorMode::Fixed == CurEditorMode)
	{
		FixedMapControlMode();
	}
	else if (EditorMode::Random == CurEditorMode)
	{
		RandomMapControlMode();
	}
#pragma endregion

#pragma region ī�޶��̵� Űüũ
	
	if (true == GameEngineInput::GetInst().Press("CameraUp"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::UP * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraDown"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::DOWN * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraLeft"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::LEFT * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraRight"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::RIGHT * MoveSpeed_ * _DeltaTime);
	}
#pragma endregion
}

void MapEditorLevel::FixedMapControlMode()
{
	// ������ �����찡 Ȱ��ȭ �Ǿ��ְ� ���� ������ ��尡 FixedMode�϶� ���Ǵ� ��Ʈ��

#pragma region �׸��� ON/OFF
	// �ٴ�Ÿ�� �׸��� On/Off
	if (true == GameEngineInput::GetInst().Down("FloorGrideSwitching"))
	{
		if (nullptr != EditorFixedMap_)
		{
			EditorFixedMap_->FloorGridesSwitching();
		}
	}

	// ��Ÿ�� �׸��� On/Off
	if (true == GameEngineInput::GetInst().Down("WallGrideSwitching"))
	{
		if (nullptr != EditorFixedMap_)
		{
			EditorFixedMap_->WallGridesSwitching();
		}
	}

	// ������ƮŸ�� �׸��� On/Off
	if (true == GameEngineInput::GetInst().Down("ObjectGrideSwitching"))
	{
		if (nullptr != EditorFixedMap_)
		{
			EditorFixedMap_->ObjectGridesSwitching();
		}
	}
#pragma endregion

#pragma region �Ŵ���ʻ���������
	// Ÿ�ϻ���
	if (true == GameEngineInput::GetInst().Press("MouseLButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");

		// ī�޶� �̵��� ���Ѵ�.
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				if (FloorRenderingType::TILE == EditorFixedMap_->GetCurFloorRenderType())
				{
					EditorFixedMap_->SetFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					EditorFixedMap_->SetFloorGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
			case TileType::WALL:
			{
				if (WallRenderingType::TILE1 == EditorFixedMap_->GetCurWallRenderType() || WallRenderingType::TILE2 == EditorFixedMap_->GetCurWallRenderType())
				{
					EditorFixedMap_->SetWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					EditorFixedMap_->SetWallGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
			case TileType::OBJECT:
			{
				if (ObjectRenderingType::TILE == EditorFixedMap_->GetCurObjectRenderType())
				{
					EditorFixedMap_->SetObjectTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					EditorFixedMap_->SetObjectGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
		}
	}

	// Ÿ������
	if (true == GameEngineInput::GetInst().Press("MouseRButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");

		// �ش� ��ġ�� �ε��� Ÿ�� ��Ͽ��� ����
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				if (FloorRenderingType::TILE == EditorFixedMap_->GetCurFloorRenderType())
				{
					EditorFixedMap_->DelFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					EditorFixedMap_->DelFloorGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
			case TileType::WALL:
			{
				if (WallRenderingType::TILE1 == EditorFixedMap_->GetCurWallRenderType() || WallRenderingType::TILE2 == EditorFixedMap_->GetCurWallRenderType())
				{
					EditorFixedMap_->DelWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					EditorFixedMap_->DelWallGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
			case TileType::OBJECT:
			{
				if (ObjectRenderingType::TILE == EditorFixedMap_->GetCurObjectRenderType())
				{
					EditorFixedMap_->DelObjectTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					EditorFixedMap_->DelObjectGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
		}
	}
#pragma endregion
}

void MapEditorLevel::RandomMapControlMode()
{
	// ������ �����찡 Ȱ��ȭ �Ǿ��ְ� ���� ������ ��尡 RandomMode�϶� ���Ǵ� ��Ʈ��
	
	// �ٴ�Ÿ�� �׸��� On/Off
	if (true == GameEngineInput::GetInst().Down("FloorGrideSwitching"))
	{
		if (nullptr != EditorRandomMap_)
		{
			EditorRandomMap_->FloorGridesSwitching();
		}
	}

	// ��Ÿ�� �׸��� On/Off
	if (true == GameEngineInput::GetInst().Down("WallGrideSwitching"))
	{
		if (nullptr != EditorRandomMap_)
		{
			EditorRandomMap_->WallGridesSwitching();
		}
	}


}
