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
	// Editor Fixed TileMap ���� ����� �����ϴ� ������ On & Editor Random TileMap ���� ����� �����ϴ� ������ Off
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

	// Editor Fixed TileMap ���� ����� �����ϴ� ������ Off & Editor Random TileMap ���� ����� �����ϴ� ������ On
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
