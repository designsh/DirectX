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

	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("GroundTile")), { 500, 1000 });

	GameEngineTexture* TileImage = Map->GetFloorTileTexture();
	ImTextureID Id = reinterpret_cast<ImTextureID>(*TileImage->GetShaderResourcesView());
	float4 Size = {80, 40};

	int LineCount = 5;

	for (int i = 0; i < static_cast<int>(TileImage->GetCutCount()); i++)
	{
		float4 CutData = TileImage->GetCutData(i);
		__int64 ImageBtnID = reinterpret_cast<__int64>(Id);
		ImageBtnID += i;
		ImGui::PushID(static_cast<int>(ImageBtnID));
		if (true == ImGui::ImageButton(Id, { Size.x, Size.y }, { CutData.x, CutData.y }, { CutData.x + CutData.z, CutData.y + CutData.w }))
		{
			// 현재 선택된 타일의 인덱스로 변경
			Map->SetSelectTileIndex(i);
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

	ImGui::EndChildFrame();

	ImGui::SameLine();
	  
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 500, 1000 });

	ImGui::EndChildFrame();

}
