#include "PreCompile.h"
#include "EditorControlWindow.h"
#include "IsoTileMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineCore.h>

// 0 50
// 49

// -50 0
// 

EditorControlWindow::EditorControlWindow() :
	Map(nullptr),
	Zoom(1.0f),
	ZoomMin(0.1f),
	ZoomMax(5.0f)
{
}

EditorControlWindow::~EditorControlWindow()
{
}

void EditorControlWindow::OnGUI()
{
	ImGui::Text(GameEngineInput::GetInst().GetMouse3DPos().ToString().c_str());

	float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	TileIndex Index = Map->GetIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text( ("XIndex : " + std::to_string(Index.X_) + "YIndex : " + std::to_string(Index.Y_)).c_str() );

	float4 Pos = Map->GetIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string IsoPosText = "Iso Pos : ";
	IsoPosText += Pos.ToString();
	ImGui::Text(IsoPosText.c_str());

	std::string CameraPosText = "Camera Pos : ";
	CameraPosText += CameraPos.ToString();
	ImGui::Text(CameraPosText.c_str());

	ImGui::SliderFloat("Zoom", &Zoom, ZoomMin, ZoomMax, "%f", 1.0f);

	GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom);

	GameEngineTexture* TileImage = Map->GetFloorTileTexture();
	ImTextureID Id = reinterpret_cast<ImTextureID>(*TileImage->GetShaderResourcesView());
	float4 Size = {80, 40};

	int LineCount = 5;

	for (size_t i = 0; i < TileImage->GetCutCount(); i++)
	{
		float4 CutData = TileImage->GetCutData(i);
		ImGui::PushID(reinterpret_cast<int>(Id) + i);
		if (true == ImGui::ImageButton(Id, { Size.x, Size.y }, { CutData.x, CutData.y }, { CutData.x + CutData.z, CutData.y + CutData.w }))
		{
			int a = 0;
		}
		ImGui::PopID();

		--LineCount;

		if (0 != LineCount)
		{
			ImGui::SameLine();
		}

		if (0 == LineCount)
		{
			LineCount = 5;
		}
	}
}
