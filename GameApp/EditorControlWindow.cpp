#include "PreCompile.h"
#include "EditorControlWindow.h"
#include "IsoTileMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

// 0 50
// 49

// -50 0
// 

EditorControlWindow::EditorControlWindow() :
	MainCamera_(nullptr)
{
}

EditorControlWindow::~EditorControlWindow()
{
}

void EditorControlWindow::OnGUI()
{
	ImGui::Text(GameEngineInput::GetInst().GetMouse3DPos().ToString().c_str());

	TileIndex Index = Map->GetIndex(GameEngineInput::GetInst().GetMouse3DPos(), MainCamera_->GetTransform()->GetWorldPosition());
	ImGui::Text( ("XIndex : " + std::to_string(Index.X_) + "YIndex : " + std::to_string(Index.Y_)).c_str() );

	float4 Pos = Map->GetIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string IsoPosText = "Iso Pos : ";
	IsoPosText += Pos.ToString();
	ImGui::Text(IsoPosText.c_str());

	if (nullptr != MainCamera_)
	{
		float4 CameraPos = MainCamera_->GetTransform()->GetWorldPosition();
		std::string CameraPosText = "Camera Pos : ";
		CameraPosText += CameraPos.ToString();
		ImGui::Text(CameraPosText.c_str());
	}

}

void EditorControlWindow::SetMainCamera(CameraComponent* _Camera)
{
	MainCamera_ = _Camera;
}
