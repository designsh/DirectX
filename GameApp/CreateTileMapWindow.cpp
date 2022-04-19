#include "PreCompile.h"
#include "CreateTileMapWindow.h"
#include "TileMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineCore.h>

CreateTileMapWindow::CreateTileMapWindow() :
	TileMap_(nullptr),
	Zoom_(1.0f),
	ZoomMin_(0.1f),
	ZoomMax_(5.0f),
	FloorXCount_(0),
	FloorYCount_(0),
	WallXCount_(0),
	WallYCount_(0),
	SelectMode_(TileType::FLOOR),
	SelectTileIndex_(0)
{
}

CreateTileMapWindow::~CreateTileMapWindow()
{
}

void CreateTileMapWindow::OnGUI()
{
#pragma region 마우스위치
	ImGui::Text("<<< Mouse Pos >>>");
	ImGui::Text(GameEngineInput::GetInst().GetMouse3DPos().ToString().c_str());
#pragma endregion

	ImGui::Text("");

#pragma region BasicInfo
	float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

	// Floor Tile Info
	TileIndex FloorTileIndex = TileMap_->GetFloorTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text("<<< FLOOR TILE INFOMATION >>>");
	ImGui::Text(("XIndex : " + std::to_string(FloorTileIndex.X_) + "  YIndex : " + std::to_string(FloorTileIndex.Y_)).c_str());

	float4 FloorTilePos = TileMap_->GetFloorIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string FloorIsoPosText = "Floor Iso Pos : ";
	FloorIsoPosText += FloorTilePos.ToString();
	ImGui::Text(FloorIsoPosText.c_str());

	ImGui::Text("");

	// Wall Tile Info
	TileIndex WallTileIndex = TileMap_->GetWallTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text("<<< WALL TILE INFOMATION >>>");
	ImGui::Text(("XIndex : " + std::to_string(WallTileIndex.X_) + "  YIndex : " + std::to_string(WallTileIndex.Y_)).c_str());

	float4 WallTilePos = TileMap_->GetWallIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string WallIsoPosText = "Wall Iso Pos : ";
	WallIsoPosText += WallTilePos.ToString();
	ImGui::Text(WallIsoPosText.c_str());

#pragma endregion

	ImGui::Text("");

#pragma region 카메라줌인/아웃
	ImGui::Text("<<< Camera Pos >>>");
	std::string CameraPosText = "Camera Pos : ";
	CameraPosText += CameraPos.ToString();
	ImGui::Text(CameraPosText.c_str());

	ImGui::PushItemWidth(308.f); // 크기 고정
	ImGui::SliderFloat("Zoom", &Zoom_, ZoomMin_, ZoomMax_, "%f", 1.0f);
	ImGui::PopItemWidth();

	GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom_);
#pragma endregion

	ImGui::Text("");

#pragma region 수동맵생성모드관련
	ImGui::Text("<<< Create ManualMap Mode Related >>>");

#pragma region 바탁타일목록
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("FloorTile")), { 500, 200 });

	GameEngineTexture* FloorTileImage = TileMap_->GetFloorTileTexture();
	ImTextureID FloorTileId = reinterpret_cast<ImTextureID>(*FloorTileImage->GetShaderResourcesView());
	float4 FloorTileSize = { 80.f, 40.f };

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
			SelectMode_ = TileType::FLOOR;

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

	ImGui::SameLine();
#pragma endregion

#pragma region 벽타일목록
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 500, 200 });

	// 벽
	GameEngineTexture* WallTileImage = TileMap_->GetWallTileTexture();
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
			SelectMode_ = TileType::WALL;

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

#pragma region 바탁타일렌더링모드 선택버튼
	if (true == ImGui::Button("RenderingGridMode", ImVec2(140.f, 30.f)))
	{
		TileMap_->SetTileRenderingMode(TileRenderingType::GRID);
	}

	ImGui::SameLine();

	if (true == ImGui::Button("RenderingTileMode", ImVec2(140.f, 30.f)))
	{
		TileMap_->SetTileRenderingMode(TileRenderingType::TILE);
	}

	ImGui::SameLine();

	if (true == ImGui::Button("RenderingAllMode", ImVec2(140.f, 30.f)))
	{
		TileMap_->SetTileRenderingMode(TileRenderingType::ALL);
	}
#pragma endregion

#pragma endregion

	ImGui::Text("");

#pragma region 자동맵생성모드관련
	ImGui::Text("<<< Create AutoMap Mode Related >>>");

	// 자동모드 바닥타일정보생성
	ImGui::Text("1. ");
	ImGui::SameLine();

	ImGui::Text("Floor TileX :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Floor TileX", &FloorXCount_);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	ImGui::Text("Floor TileY :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##Floor TileY", &FloorYCount_);
	ImGui::PopItemWidth();

	ImGui::Text("2. ");
	ImGui::SameLine();
	if (true == ImGui::Button("CREATE FLOORTILE INFO", ImVec2(200.f, 30.f)))
	{
		TileMap_->CreateFloorTileInfo(FloorXCount_, FloorYCount_);
	}

	// 자동모드 벽타일정보생성
	ImGui::Text("3. ");
	ImGui::SameLine();
	if (true == ImGui::Button("CREATE WALLTILE INFO", ImVec2(200.f, 30.f)))
	{
		TileMap_->CreateWallTileInfo();
	}

	// 자동모드 바닥타일 텍스쳐 매칭


	// 자동모드 벽타일 텍스쳐 매칭



#pragma endregion

	ImGui::Text("");

#pragma region 랜덤맵생성모드관련
	ImGui::Text("<<< Create RandomMap Mode Related >>>");







#pragma endregion

	ImGui::Text("");

#pragma region 맵파일저장/로드 관련









#pragma endregion
}
