#include "PreCompile.h"
#include "EditorControlWindow.h"
#include <GameEngine\GameEngineInput.h>
#include "IsoTileMap.h"
#include <string>

EditorControlWindow::EditorControlWindow()
{
}

EditorControlWindow::~EditorControlWindow()
{
}

void EditorControlWindow::OnGUI()
{
	ImGui::Text(GameEngineInput::GetInst().GetMouse3DPos().ToString().c_str());

	TileIndex Index = Map->GetIndex(GameEngineInput::GetInst().GetMouse3DPos());
	ImGui::Text( ("XIndex : " + std::to_string(Index.X_) + "YIndex : " + std::to_string(Index.Y_)).c_str() );

}
