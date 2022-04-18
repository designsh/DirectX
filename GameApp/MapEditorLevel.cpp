#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "CreateTileMapWindow.h"
#include "TileMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

MapEditorLevel::MapEditorLevel() :
	TileMap_(nullptr),
	MoveSpeed_(1000.f)
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::LevelChangeEndEvent()
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
	if (nullptr != Ptr)
	{
		Ptr->Off();
	}
}

void MapEditorLevel::LevelChangeStartEvent()
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
	if (nullptr != Ptr)
	{
		Ptr->On();
	}
}

void MapEditorLevel::LevelStart()
{
#pragma region SetMainCamera
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));
#pragma endregion

#pragma region TileTexture Cutting
	GameEngineTexture* FloorTile = GameEngineTextureManager::GetInst().Find("Town_Floor.png");
	FloorTile->Cut(5, 37);
	GameEngineTexture* WallTile = GameEngineTextureManager::GetInst().Find("Town_Wall.png");
	WallTile->Cut(31, 1);

	// �Ϲݱ׸���
	GameEngineTexture* FloorGridNor = GameEngineTextureManager::GetInst().Find("FloorGrid_Normal.png");
	FloorGridNor->Cut(1, 1);
	GameEngineTexture* WallGridNor = GameEngineTextureManager::GetInst().Find("WallGrid_Normal.png");
	WallGridNor->Cut(1, 1);

	// ���ͱ׸���
	GameEngineTexture* FloorGridCenter = GameEngineTextureManager::GetInst().Find("FloorGrid_Center.png");
	FloorGridCenter->Cut(1, 1);
	GameEngineTexture* WallGridCenter = GameEngineTextureManager::GetInst().Find("WallGrid_Center.png");
	WallGridCenter->Cut(1, 1);

	// Ư���׸���
	GameEngineTexture* WallGridRT = GameEngineTextureManager::GetInst().Find("WallGrid_RT.png");
	WallGridRT->Cut(1, 1);
	GameEngineTexture* WallGridRB = GameEngineTextureManager::GetInst().Find("WallGrid_RB.png");
	WallGridRB->Cut(1, 1);
	GameEngineTexture* WallGridBent = GameEngineTextureManager::GetInst().Find("WallGrid_Bent.png");
	WallGridBent->Cut(1, 1);

#pragma endregion

#pragma region Editor Window
	// CreateTileMap Window
	CreateTileMapWindow* TileMapWindow = GameEngineGUI::GetInst()->CreateGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");
	TileMapWindow->Off();

#pragma endregion

#pragma region IsoTileMap Create & Setting
	TileMap_ = CreateActor<TileMap>();
	TileMapWindow->TileMap_ = TileMap_;
	TileMap_->SetFloorTileTexture("Town_Floor.png");
	TileMap_->SetWallTileTexture("Town_Wall.png");
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

#pragma region �׽�ƮŰ
	// �׽�ƮŰ ����
	if (false == GameEngineInput::GetInst().IsKey("FreeCamera"))
	{
		GameEngineInput::GetInst().CreateKey("FreeCamera", 'o');
	}
#pragma endregion
}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
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

#pragma region �Ŵ���ʻ���������
	// Ÿ�ϻ���
	if (true == GameEngineInput::GetInst().Press("MouseLButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");

		float4 WindowPos = GameEngineInput::GetInst().GetMousePos();

		if (0 > WindowPos.x)
		{
			return;
		}

		if (0 > WindowPos.y)
		{
			return;
		}

		if (WindowPos.x > GameEngineWindow::GetInst().GetSize().x)
		{
			return;
		}

		if (WindowPos.y > GameEngineWindow::GetInst().GetSize().y)
		{
			return;
		}

		// ī�޶� �̵��� ���Ѵ�.
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				TileMap_->SetFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				break;
			}
			case TileType::WALL:
			{
				TileMap_->SetWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				break;
			}
		}
	}

	// Ÿ������
	if (true == GameEngineInput::GetInst().Press("MouseRButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");
		float4 WindowPos = GameEngineInput::GetInst().GetMousePos();

		if (0 > WindowPos.x)
		{
			return;
		}

		if (0 > WindowPos.y)
		{
			return;
		}

		if (WindowPos.x > GameEngineWindow::GetInst().GetSize().x)
		{
			return;
		}

		if (WindowPos.y > GameEngineWindow::GetInst().GetSize().y)
		{
			return;
		}

		// �ش� ��ġ�� �ε��� Ÿ�� ��Ͽ��� ����
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				TileMap_->DelFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				break;
			}
			case TileType::WALL:
			{
				TileMap_->DelWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				break;
			}
		}
	}

#pragma endregion

#pragma region �ڵ��ʻ���������





#pragma endregion

#pragma region �����ʻ���������







#pragma endregion

#pragma region �׽�ƮŰ
	if (true == GameEngineInput::GetInst().Down("FreeCamera"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
#pragma endregion
}
