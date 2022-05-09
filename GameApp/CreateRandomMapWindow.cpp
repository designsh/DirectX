#include "PreCompile.h"
#include "CreateRandomMapWindow.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineCore.h>

#include "EditorRandomMap.h"

CreateRandomMapWindow::CreateRandomMapWindow() :
	RandomMap_(nullptr),
	Zoom_(1.0f),
	ZoomMin_(0.1f),
	ZoomMax_(5.0f),
	MaxIndexX_(0),
	MaxIndexY_(0),
	RoomCnt_(0),
	RoomWidth_(0),
	RoomHeight_(0)
{
}

CreateRandomMapWindow::~CreateRandomMapWindow()
{
}

void CreateRandomMapWindow::OnGUI()
{
#pragma region BasicInfo
	float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

	// Floor Tile Info
	TileIndex FloorTileIndex = RandomMap_->GetFloorTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text("<<< FLOOR TILE INFOMATION >>>");
	ImGui::Text(("XIndex : " + std::to_string(FloorTileIndex.X_) + "  YIndex : " + std::to_string(FloorTileIndex.Y_)).c_str());

	// Wall Tile Info
	TileIndex WallTileIndex = RandomMap_->GetWallTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text("<<< WALL TILE INFOMATION >>>");
	ImGui::Text(("XIndex : " + std::to_string(WallTileIndex.X_) + "  YIndex : " + std::to_string(WallTileIndex.Y_)).c_str());

#pragma endregion

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

#pragma region 랜덤맵생성관련
	ImGui::Text("<<< Create RandomMap Function >>>");

	ImGui::Text("");
	ImGui::Text("0. All Clear");
	if (true == ImGui::Button("AllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("RandomRoadClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllRandomRoadClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("RoomAllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllRoomClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("CorridorAllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllCorridorClear();
	}

	ImGui::Text("");
	ImGui::Text("1. Select Texture Setting");
	if (true == ImGui::Button("Catacombs", ImVec2(200.f, 20.f)))
	{
		RandomMap_->CatacombsTextrueSetting();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("ChaosSanctuary", ImVec2(200.f, 20.f)))
	{
		RandomMap_->ChaosSanctuaryTextrueSetting();
	}

#pragma region 바탁타일목록
	if (nullptr != RandomMap_->GetFloorTileTexture())
	{
		ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("FloorTile")), { 500, 200 });

		GameEngineTexture* FloorTileImage = RandomMap_->GetFloorTileTexture();
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
				// 현재 선택된 타일의 인덱스로 변경
				RandomMap_->SelectFloorTileIndex_ = i;
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
	}
	ImGui::SameLine();
#pragma endregion

#pragma region 벽타일목록
	if (nullptr != RandomMap_->GetWallTileTexture())
	{
		ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 500, 200 });

		// 벽
		GameEngineTexture* WallTileImage = RandomMap_->GetWallTileTexture();
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
				// 현재 선택된 타일의 인덱스로 변경
				RandomMap_->SelectWallTileIndex_ = i;
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
	}
#pragma endregion

#pragma region 랜덤복도생성
	ImGui::Text("");
	ImGui::Text("0000. Create Random Road");
	if (true == ImGui::Button("CreateRoad", ImVec2(200.f, 20.f)))
	{
		RandomMap_->RandomRoad(5, true);
	}
#pragma endregion

	ImGui::Text("");
	ImGui::Text("2. Create Random Room");

	// 생성하려는 맵의 최대 크기
	ImGui::Text("1) Map Max Size Setting");
	ImGui::Text("MaxIndex X :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##MaxIndexX", &MaxIndexX_);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("MapMaxHeight :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##MaxIndexY", &MaxIndexY_);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (true == ImGui::Button("MapSize Setting", ImVec2(200.f, 20.f)))
	{
		RandomMap_->TotalMapScale(MaxIndexX_, MaxIndexY_);
	}

	ImGui::Text("");
	ImGui::Text("2) Room Info Setting");
	ImGui::Text("Room Count :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##RoomCount", &RoomCnt_);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::Text("Room Width :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##RoomWidth", &RoomWidth_);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::Text("Room Height :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##RoomHeight", &RoomHeight_);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (true == ImGui::Button("CreateRoom", ImVec2(200.f, 20.f)))
	{
		RandomMap_->RandomRoom(RoomCnt_, RoomWidth_, RoomHeight_);
	}

	// 룸 밀어내기
	ImGui::Text("");
	ImGui::Text("3) Room Push Out");
	if (true == ImGui::Button("RoomPushOut", ImVec2(200.f, 20.f)))
	{
		RandomMap_->RoomPushOut();
	}

	// 룸과룸 거리측정 및 정보 저장
	ImGui::Text("");
	ImGui::Text("4) Room Distance Measurement");
	if (true == ImGui::Button("RoomDistance", ImVec2(200.f, 20.f)))
	{
		RandomMap_->RoomDistanceMeasurement();
	}

	// 복도연결
	ImGui::Text("");
	ImGui::Text("3. Room Connection");
	if (true == ImGui::Button("RoomConnection", ImVec2(200.f, 20.f)))
	{
		RandomMap_->RoomConnection();
	}

	// 룸/복도 벽정보 생성


	// 문정보 생성


#pragma endregion
}
