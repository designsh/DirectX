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
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));

	// Image Cutting
	GameEngineTexture* FloorTile = GameEngineTextureManager::GetInst().Find("Town_Floor.png");
	FloorTile->Cut(5, 37);

	// MapEditor Control Window
	EditorControlWindow* Ptr = GameEngineGUI::GetInst()->CreateGUIWindow<EditorControlWindow>("EditorControlWindow");
	Ptr->Off();

	Map = CreateActor<IsoTileMap>();
	Ptr->Map = Map;
	Map->SetFloorTileTexture("Town_Floor.png");

	// 프리카메라 키생성
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

	if (false == GameEngineInput::GetInst().IsKey("CameraZoomClear"))
	{
		GameEngineInput::GetInst().CreateKey("CameraZoomClear", 'Z');
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraZoomIn"))
	{
		GameEngineInput::GetInst().CreateKey("CameraZoomIn", 'X');
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraZoomOut"))
	{
		GameEngineInput::GetInst().CreateKey("CameraZoomOut", 'C');
	}
}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{

	// 카메라이동
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

	// 카메라 줌 인/아웃/해제
	if (true == GameEngineInput::GetInst().Down("CameraZoomClear"))
	{
		// 카메라가 비추는 화면 비율 = 현재 윈도우 크기로 셋팅
		GetMainCamera()->CameraZoomReset();
	}


	if (true == GameEngineInput::GetInst().Press("MouseLButton"))
	{
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
		Map->SetTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
	}

	if (true == GameEngineInput::GetInst().Press("MouseRButton"))
	{
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

		// 
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		Map->DelTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
	}
}
