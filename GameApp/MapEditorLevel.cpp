#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "EditorControlWindow.h"
#include "IsoTileMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

MapEditorLevel::MapEditorLevel() :
	Map(nullptr),
	MoveSpeed_(1000.f)
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::LevelChangeEndEvent()
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("EditorControlWindow");
	if (nullptr != Ptr)
	{
		Ptr->Off();
	}
}

void MapEditorLevel::LevelChangeStartEvent()
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("EditorControlWindow");
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
#pragma endregion

	GameEngineTexture* FloorGrid = GameEngineTextureManager::GetInst().Find("FloorGrid.png");
	FloorGrid->Cut(1, 1);
	GameEngineTexture* WallGrid = GameEngineTextureManager::GetInst().Find("WallGrid.png");
	WallGrid->Cut(1, 1);

#pragma region Editor Window
	// MapEditor Control Window
	EditorControlWindow* Ptr = GameEngineGUI::GetInst()->CreateGUIWindow<EditorControlWindow>("EditorControlWindow");
	Ptr->Off();


#pragma endregion

#pragma region IsoTileMap Create & Setting
	Map = CreateActor<IsoTileMap>();
	Ptr->Map = Map;
	Map->SetFloorTileTexture("Town_Floor.png");
	Map->SetWallTileTexture("Town_Wall.png");
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

#pragma region 테스트키
	// 테스트키 생성
	if (false == GameEngineInput::GetInst().IsKey("FreeCamera"))
	{
		GameEngineInput::GetInst().CreateKey("FreeCamera", 'o');
	}
#pragma endregion
}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
#pragma region 카메라이동 키체크
	
	if (true == GameEngineInput::GetInst().Press("CameraUp"))
	{
		GetMainCamera()->GetTransform()->SetWorldMove(float4::UP * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraDown"))
	{
		GetMainCamera()->GetTransform()->SetWorldMove(float4::DOWN * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraLeft"))
	{
		GetMainCamera()->GetTransform()->SetWorldMove(float4::LEFT * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraRight"))
	{
		GetMainCamera()->GetTransform()->SetWorldMove(float4::RIGHT * MoveSpeed_ * _DeltaTime);
	}

#pragma endregion

#pragma region 타일관련
	// 타일생성
	if (true == GameEngineInput::GetInst().Press("MouseLButton"))
	{
		EditorControlWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<EditorControlWindow>("EditorControlWindow");

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

		// 카메라 이동을 더한다.
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode)
		{
		case TileType::FLOOR:
			Map->SetFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
			break;
		case TileType::WALL:
			Map->SetWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
			break;
		default:
			break;
		}
	}

	// 타일제거
	if (true == GameEngineInput::GetInst().Press("MouseRButton"))
	{
		EditorControlWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<EditorControlWindow>("EditorControlWindow");
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

		// 해당 위치의 인덱스 타일 목록에서 제거
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode)
		{
		case TileType::FLOOR:
			Map->DelFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
			break;
		case TileType::WALL:
			Map->DelWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
			break;
		default:
			break;
		}
	}

#pragma endregion

#pragma region 테스트키
	if (true == GameEngineInput::GetInst().Down("FreeCamera"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
#pragma endregion
}
