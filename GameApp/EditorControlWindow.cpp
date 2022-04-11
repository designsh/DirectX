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
	ZoomMax(5.0f),
	FloorXCount_(0),
	FloorYCount_(0),
	WallXCount_(0),
	WallYCount_(0)
{
}

EditorControlWindow::~EditorControlWindow()
{
}

void EditorControlWindow::OnGUI()
{
	ImGui::Text("<<< Mouse Pos >>>");
	ImGui::Text(GameEngineInput::GetInst().GetMouse3DPos().ToString().c_str());

	ImGui::Text("");

#pragma region BasicInfo
	float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	{
		// Floor Tile Info
		TileIndex Index = Map->GetFloorTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
		ImGui::Text("<<< FLOOR TILE INFOMATION >>>");
		ImGui::Text(("XIndex : " + std::to_string(Index.X_) + "YIndex : " + std::to_string(Index.Y_)).c_str());

		float4 Pos = Map->GetFloorIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
		std::string IsoPosText = "Floor Iso Pos : ";
		IsoPosText += Pos.ToString();
		ImGui::Text(IsoPosText.c_str());
	}

	ImGui::Text("");

	{
		// Wall Tile Info
		TileIndex Index = Map->GetWallTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
		ImGui::Text("<<< WALL TILE INFOMATION >>>");
		ImGui::Text(("XIndex : " + std::to_string(Index.X_) + "YIndex : " + std::to_string(Index.Y_)).c_str());

		float4 Pos = Map->GetWallIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
		std::string IsoPosText = "Wall Iso Pos : ";
		IsoPosText += Pos.ToString();
		ImGui::Text(IsoPosText.c_str());
	}
#pragma endregion

	ImGui::Text("");

#pragma region CameraZoom
	ImGui::Text("<<< Camera Pos >>>");
	std::string CameraPosText = "Camera Pos : ";
	CameraPosText += CameraPos.ToString();
	ImGui::Text(CameraPosText.c_str());

	ImGui::PushItemWidth(308.f); // 크기 고정
	ImGui::SliderFloat("Zoom", &Zoom, ZoomMin, ZoomMax, "%f", 1.0f);
	ImGui::PopItemWidth();
	
	GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom);
#pragma endregion

#pragma region RandomMapButton
	if (true == ImGui::Button("Random_OneRoad", ImVec2(140.f, 30.f)))
	{
		GameEngineRandom Random;

		Map->RandomRoad(Random.RandomInt(3, 10));
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Random_MultiRoad", ImVec2(140.f, 30.f)))
	{
		GameEngineRandom Random;

		Map->RandomRoad(Random.RandomInt(3, 10), true);
	}

#pragma endregion

	ImGui::SameLine();

#pragma region TileMapClear
	if (true == ImGui::Button("AllClear", ImVec2(140.f, 30.f)))
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
			// 현재 선택된 타일이 벽 텍스쳐이므로 텍스쳐 변경
			SelectMode = TileType::FLOOR;

			// 현재 선택된 타일의 인덱스로 변경
			SelectTileIndex_ = i;
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
			SelectMode = TileType::WALL;

			// 현재 선택된 타일의 인덱스로 변경
			SelectTileIndex_ = i;
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

#pragma region FloorTileGrid
	// 테스트용 Floor Grid 생성
	ImGui::Text("<<< CREATE FLOOR TEST GRID >>>");

	ImGui::Text("TileX :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Floor TileX", &FloorXCount_);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::Text("TileY :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Floor TileY", &FloorYCount_);
	ImGui::PopItemWidth();

	ImGui::SameLine();
	if (true == ImGui::Button("FLOOR CREATE", ImVec2(140.f, 20.f)))
	{
		// 기존 테스트용 그리드 모두 제거 후
		Map->ClearFloorGrid();

		// X,Y 카운트만큼 그리드 생성
		Map->CreateFloorGrid(FloorXCount_, FloorYCount_);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("FLOOR CLEAR", ImVec2(140.f, 20.f)))
	{
		// 현재 생성된 테스트용 그리드 제거
		Map->ClearFloorGrid();
	}

#pragma endregion

#pragma region WallTileGrid
	// 테스트용 Wall Grid 생성
	ImGui::Text("<<< CREATE WALL TEST GRID >>>");

	ImGui::Text("TileX :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Wall TileX", &WallXCount_);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::Text("TileY :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Wall TileY", &WallYCount_);
	ImGui::PopItemWidth();

	ImGui::SameLine();
	if (true == ImGui::Button("WALL CREATE", ImVec2(140.f, 20.f)))
	{
		// 기존 테스트용 그리드 모두 제거 후
		Map->ClearWallGrid();

		// X,Y 카운트만큼 그리드 생성
		Map->CreateWallGrid(WallXCount_, WallYCount_);

	}
	ImGui::SameLine();
	if (true == ImGui::Button("WALL CLEAR", ImVec2(140.f, 20.f)))
	{
		// 현재 생성된 테스트용 그리드 제거
		Map->ClearWallGrid();
	}

#pragma endregion

#pragma region Map Save&Load
	if (true == ImGui::Button("SAVE", ImVec2(140.f, 30.f)))
	{
		// 현재 생성한 맵정보 파일로 저장

		// 파일대화상자 로드


		//Map->MapSave();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("LOAD", ImVec2(140.f, 30.f)))
	{
		// 지정된 경로의 맵파일 로드


		// 파일대화상자 로드


		//Map->MapLoad();
	}
#pragma endregion
}
