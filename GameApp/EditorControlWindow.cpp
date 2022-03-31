#include "PreCompile.h"
#include "EditorControlWindow.h"
#include "IsoTileMap.h"

// 0 50
// 49

// -50 0
// 

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

	float4 Pos = Map->GetIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string IsoPosText = "Iso Pos : ";
	IsoPosText += Pos.ToString();
	ImGui::Text(IsoPosText.c_str());

}
