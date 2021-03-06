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
	CreateCorridorCnt_(0),
	CorridorThick_(0),
	CorridorLenCnt_(0),
	CorridorDirCnt_(0),
	RoomCount_(0),
	RoomMaxWidthIndex_(0),
	RoomMaxHeightIndex_(0),
	FileName_{}
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

#pragma region ī?޶?????/?ƿ?
	ImGui::Text("<<< Camera Pos >>>");
	std::string CameraPosText = "Camera Pos : ";
	CameraPosText += CameraPos.ToString();
	ImGui::Text(CameraPosText.c_str());

	ImGui::Text("ZOOM");
	ImGui::SameLine();
	ImGui::PushItemWidth(308.f); // ũ?? ????
	ImGui::SliderFloat("##Zoom", &Zoom_, ZoomMin_, ZoomMax_, "%f", 1.0f);
	ImGui::PopItemWidth();

	GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom_);

	// ????/?ƿ? ????
	ImGui::SameLine();
	if (true == ImGui::Button("RESET", ImVec2(200.f, 20.f)))
	{
		Zoom_ = 1.f;
		GameEngineCore::CurrentLevel()->GetMainCamera()->CameraZoomSetting(Zoom_);
	}

#pragma endregion

	ImGui::Text("");

#pragma region ?????ʻ???????
	ImGui::Text("<<< Create RandomMap Function >>>");

	ImGui::Text("");
	ImGui::Text("0. All Clear");
	if (true == ImGui::Button("AllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("CorridorAllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllCorridorClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("RoomAllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllRoomClear();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("WallAllClear", ImVec2(200.f, 20.f)))
	{
		RandomMap_->AllWallClear();
	}

#pragma region ?????? ????(????->??->??/?????? ??????)
	// 1~3. ???? ?? ?׸??巻???? ????
	// 4. Ÿ?Կ? ?´? ?ؽ??? ??Ī?Ͽ? Ÿ?? ?????? ????

	// 1. ???????? ???? ????
	ImGui::Text("");
	ImGui::Text("1. Create Random Corridor");
	ImGui::Text("Create Count :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##CreateCount", &CreateCorridorCnt_);
	if (0 >= CreateCorridorCnt_)
	{
		CreateCorridorCnt_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("Corridor Thick :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##CorridorThick", &CorridorThick_);
	if (0 >= CorridorThick_)
	{
		CorridorThick_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("Length Count :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##LengthCount", &CorridorLenCnt_);
	if (0 >= CorridorLenCnt_)
	{
		CorridorLenCnt_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("Dir Count :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##DirCount", &CorridorDirCnt_);
	if (4 <= CorridorDirCnt_)
	{
		CorridorDirCnt_ = 4;
	}
	else if (CorridorDirCnt_ <= 0)
	{
		CorridorDirCnt_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (true == ImGui::Button("CreateCorridor", ImVec2(200.f, 20.f)))
	{
		RandomMap_->CreateRandomCorridor(CreateCorridorCnt_, CorridorThick_, CorridorLenCnt_, CorridorDirCnt_);
	}

	// 2. ?? ??ġ(???? ????)
	ImGui::Text("");
	ImGui::Text("2. Room Arrangement");
	ImGui::Text("Create Room Count :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##CreateRoomCount", &RoomCount_);
	if (0 >= RoomCount_)
	{
		RoomCount_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("Max Width Index :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##RoomMaxWidthIndex", &RoomMaxWidthIndex_);
	if (0 >= RoomMaxWidthIndex_)
	{
		RoomMaxWidthIndex_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text("Max Height Index :");
	ImGui::SameLine();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("##RoomMaxHeightIndex", &RoomMaxHeightIndex_);
	if (0 >= RoomMaxHeightIndex_)
	{
		RoomMaxHeightIndex_ = 0;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (true == ImGui::Button("RoomArrange", ImVec2(200.f, 20.f)))
	{
		RandomMap_->CreateRoomArrange(RoomCount_, RoomMaxWidthIndex_, RoomMaxHeightIndex_);
	}

	// 3. ???? ??ġ
	ImGui::Text("");
	ImGui::Text("3. Wall Arrangement");
	if (true == ImGui::Button("WallArrange", ImVec2(200.f, 20.f)))
	{
		RandomMap_->CreateWall();
	}

#pragma endregion

	ImGui::Text("");
	ImGui::Text("4. Select Texture Setting");
	if (true == ImGui::Button("Catacombs", ImVec2(200.f, 20.f)))
	{
		RandomMap_->CatacombsTextrueSetting();
	}

#pragma region ??ŹŸ?ϸ???
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
				// ???? ???õ? Ÿ???? ?ε????? ????
				RandomMap_->SetSelectFloorTileIndex(i);
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

#pragma region ??Ÿ?ϸ???
	if (nullptr != RandomMap_->GetWallTileTexture())
	{
		ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 500, 200 });

		// ??
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
				// ???? ???õ? Ÿ???? ?ε????? ????
				RandomMap_->SetSelectWallTile1Index(i);
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
	ImGui::Text("");

	// 4. ?? Ÿ?ϵ??? ?ؽ??Ŀ? ??Ī
	ImGui::Text("");
	ImGui::Text("5. Tile Texture Matching");
	if (true == ImGui::Button("FLOOR MATCHING", ImVec2(200.f, 20.f)))
	{
		RandomMap_->FloorTileTextureMatching();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("WALL MATCHING", ImVec2(200.f, 20.f)))
	{
		RandomMap_->WallTileTextureMatching();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("DOOR MATCHING", ImVec2(200.f, 20.f)))
	{
		RandomMap_->DoorTileTextureMatching();
	}

	// 5. ?????? ????
	ImGui::Text("");
	ImGui::Text("6. RandomMap Save & Load");

	ImGui::PushItemWidth(300.f);
	ImGui::InputText("##", FileName_, sizeof(FileName_));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (true == ImGui::Button("SAVE", ImVec2(200.f, 20.f)))
	{
		// ???ڿ? ????
		std::string FileName;
		FileName.clear();
		FileName = FileName_;
		
		// ?ش? ???ϸ????? ???? ????
		RandomMap_->RandomMapSave(FileName);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("LOAD", ImVec2(200.f, 20.f)))
	{
		// ???ڿ? ????
		std::string FileName(FileName_);
		FileName.clear();
		FileName = FileName_;

		// ?ش? ???ϸ????? ???? ?ε?
		RandomMap_->RandomMapLoad(FileName);
	}
}
