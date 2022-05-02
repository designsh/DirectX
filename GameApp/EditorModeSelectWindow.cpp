#include "PreCompile.h"
#include "EditorModeSelectWindow.h"

EditorModeSelectWindow::EditorModeSelectWindow()
{
}

EditorModeSelectWindow::~EditorModeSelectWindow()
{
}

void EditorModeSelectWindow::OnGUI()
{
	// Editor Fixed TileMap 관련 기능을 포함하는 윈도우 On & Editor Random TileMap 관련 기능을 포함하는 윈도우 Off
	if (true == ImGui::Button("Fixed TileMap Mode"))
	{
		GameEngineGUIWindow* FixedPtr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
		if (nullptr != FixedPtr)
		{
			FixedPtr->On();
		}

		GameEngineGUIWindow* RandomPtr = GameEngineGUI::GetInst()->FindGUIWindow("CreateRandomMapWindow");
		if (nullptr != RandomPtr)
		{
			RandomPtr->Off();
		}
	}

	ImGui::SameLine();

	// Editor Fixed TileMap 관련 기능을 포함하는 윈도우 Off & Editor Random TileMap 관련 기능을 포함하는 윈도우 On
	if (true == ImGui::Button("Random TileMap Mode"))
	{
		GameEngineGUIWindow* FixedPtr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
		if (nullptr != FixedPtr)
		{
			FixedPtr->Off();
		}

		GameEngineGUIWindow* RandomPtr = GameEngineGUI::GetInst()->FindGUIWindow("CreateRandomMapWindow");
		if (nullptr != RandomPtr)
		{
			RandomPtr->On();
		}
	}
}
