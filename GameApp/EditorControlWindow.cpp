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
#pragma region BasicInfo
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
#pragma endregion

#pragma region CameraZomm
	ImGui::SliderFloat("Zoom", &Zoom, ZoomMin, ZoomMax, "%f", 1.0f);
	GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom);
#pragma endregion

#pragma region RandomMapButton
	if (true == ImGui::Button("RandomRoad"))
	{
		GameEngineRandom Random;

		Map->RandomRoad(Random.RandomInt(3, 10));
	}
#pragma endregion

	ImGui::SameLine();

#pragma region TileMapClear
	if (true == ImGui::Button("MapAllClear"))
	{
		// 현재 생성된 모든 맵 클리어
		Map->AllTileClear();
	}
#pragma endregion

#pragma region FloorTile
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("FloorTile")), { 500, 500 });

	// 바닥
	GameEngineTexture* FloorTileImage = Map->GetFloorTileTexture();
	ImTextureID FloorTileId = reinterpret_cast<ImTextureID>(*FloorTileImage->GetShaderResourcesView());
	float4 FloorTileSize = {80.f, 40.f};

	int LineCount = 5;
	for (int i = 0; i < static_cast<int>(FloorTileImage->GetCutCount()); i++)
	{
		float4 FloorTileCutData = FloorTileImage->GetCutData(i);
		__int64 FloorImageBtnID = reinterpret_cast<__int64>(FloorTileId);
		FloorImageBtnID += i;
		ImGui::PushID(static_cast<int>(FloorImageBtnID));
		if (true == ImGui::ImageButton(FloorTileId, { FloorTileSize.x, FloorTileSize.y }, { FloorTileCutData.x, FloorTileCutData.y }, { FloorTileCutData.x + FloorTileCutData.z, FloorTileCutData.y + FloorTileCutData.w }))
		{
			// 현재 선택된 타일이 바닥 텍스쳐이므로 텍스쳐 변경
			Map->SetTileType(TileType::FLOOR);

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
#pragma endregion

	ImGui::SameLine();

#pragma region WallTile
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 500, 500 });

	// 벽
	GameEngineTexture* WallTileImage = Map->GetWallTileTexture();
	ImTextureID WallTileId = reinterpret_cast<ImTextureID>(*WallTileImage->GetShaderResourcesView());
	float4 WallTileSize = { 80.f, 160.f };

	int WallTileLineCount = 5;
	for (int i = 0; i < static_cast<int>(WallTileImage->GetCutCount()); i++)
	{
		float4 WallCutData = WallTileImage->GetCutData(i);
		__int64 WallImageBtnID = reinterpret_cast<__int64>(WallTileId);
		WallImageBtnID += i;
		ImGui::PushID(static_cast<int>(WallImageBtnID));
		if (true == ImGui::ImageButton(WallTileId, { WallTileSize.x, WallTileSize.y }, { WallCutData.x, WallCutData.y }, { WallCutData.x + WallCutData.z, WallCutData.y + WallCutData.w }))
		{
			// 현재 선택된 타일이 벽 텍스쳐이므로 텍스쳐 변경
			Map->SetTileType(TileType::WALL);

			// 현재 선택된 타일의 인덱스로 변경
			Map->SetSelectTileIndex(i);
		}
		ImGui::PopID();

		--WallTileLineCount;

		if (0 != WallTileLineCount)
		{
			ImGui::SameLine();
		}

		if (0 == WallTileLineCount)
		{
			WallTileLineCount = 5;
		}
	}


	ImGui::EndChildFrame();
#pragma endregion
}
