#include "PreCompile.h"
#include "CreateTileMapWindow.h"
#include "EditorTileMap.h"
#include "EditorRandomMap.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>
#include <GameEngine/GameEngineCore.h>

CreateTileMapWindow::CreateTileMapWindow() :
	TileMap_(nullptr),
	RandomMap_(nullptr),
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

	// Wall Tile Info
	TileIndex WallTileIndex = TileMap_->GetWallTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
	ImGui::Text("<<< WALL TILE INFOMATION >>>");
	ImGui::Text(("XIndex : " + std::to_string(WallTileIndex.X_) + "  YIndex : " + std::to_string(WallTileIndex.Y_)).c_str());

	float4 WallTilePos = TileMap_->GetWallIsoPos(GameEngineInput::GetInst().GetMouse3DPos());
	std::string WallIsoPosText = "Wall Iso Pos : ";
	WallIsoPosText += WallTilePos.ToString();
	ImGui::Text(WallIsoPosText.c_str());

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

#pragma region 자동맵생성모드관련
	ImGui::Text("<<< Create AutoMap Mode Related >>>");

	// 자동모드 바닥타일정보생성
	ImGui::Text("1. AutoMap Create Size Setting");

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

	ImGui::Text("2. AutoMap Create Floor Tile Infomation");
	if (true == ImGui::Button("CREATE FLOORTILE INFO", ImVec2(200.f, 20.f)))
	{
		TileMap_->CreateFloorTileInfo(FloorXCount_, FloorYCount_, SelectTileIndex_);
	}

	// 자동모드 벽타일정보생성
	ImGui::Text("3. AutoMap Create Wall Tile Infomation");
	if (true == ImGui::Button("CREATE WALLTILE INFO", ImVec2(200.f, 20.f)))
	{
		TileMap_->CreateWallTileInfo();
	}

	// 자동모드 바닥타일 텍스쳐 매칭
	ImGui::Text("4. AutoMap Floor Tile Texture Matching");
	if (true == ImGui::Button("FLOORTILE TEXTURE MATCHING", ImVec2(200.f, 20.f)))
	{
		TileMap_->UpdateFloorTileInfo();
	}

	// 자동모드 벽타일 특별 조건에 의한 벽텍스쳐 매칭
	ImGui::Text("5. AutoMap Wall Tile Texture Index Setting");
	if (true == ImGui::Button("TOWN WALL TEXTURE SET", ImVec2(200.f, 20.f)))
	{
		TileMap_->SetTownWallTexture();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("CATACOMBS WALL TEXTURE SET", ImVec2(200.f, 20.f)))
	{
		TileMap_->SetCatacombsWallTexture();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("CHAOSSANCTUARY WALL TEXTURE SET", ImVec2(200.f, 20.f)))
	{
		TileMap_->SetChaosSanctuaryWallTexture();
	}

	// 자동모드 벽타일 텍스쳐 매칭
	ImGui::Text("6. AutoMap Wall Tile Texture Matching");
	if (true == ImGui::Button("WALLTILE TEXTURE MATCHING", ImVec2(200.f, 20.f)))
	{
		TileMap_->UpdateWallTileInfo();
	}

	// 자동모드 생성한 맵 수정모드
	ImGui::Text("7. Manually Edit Auto-Generated Maps");
	if (TileType::FLOOR == SelectMode_)
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT EDIT TYPE : FLOOR!!!!!!!!");
	}
	else if(TileType::WALL == SelectMode_)
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT EDIT TYPE : WALL!!!!!!!!");
	}
	else if (TileType::OBJECT == SelectMode_)
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT EDIT TYPE : OBJECT!!!!!!!!");
	}

#pragma region 바탁타일목록
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("FloorTile")), { 300, 200 });

	GameEngineTexture* FloorTileImage = TileMap_->GetFloorTileTexture();
	ImTextureID FloorTileId = reinterpret_cast<ImTextureID>(*FloorTileImage->GetShaderResourcesView());
	float4 FloorTileSize = { 80.f, 40.f };

	int LineCount = 3;
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
			LineCount = 3;
		}
	}

	ImGui::EndChildFrame();

	ImGui::SameLine();
#pragma endregion

#pragma region 벽타일목록
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("WallTile")), { 300, 200 });

	// 벽
	GameEngineTexture* WallTileImage = TileMap_->GetWallTileTexture();
	ImTextureID WallTileId = reinterpret_cast<ImTextureID>(*WallTileImage->GetShaderResourcesView());
	float4 WallTileSize = { 80.f, 160.f };

	int WallTileLineCount = 3;
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
			WallTileLineCount = 3;
		}
	}

	ImGui::EndChildFrame();
#pragma endregion

	ImGui::SameLine();

#pragma region 오브젝트타일목록
	ImGui::BeginChildFrame(static_cast<ImGuiID>(reinterpret_cast<uint64_t>("ObjectTile")), { 300, 200 });

	// 벽
	GameEngineTexture* ObjectTileImage = TileMap_->GetObjectTileTexture();
	ImTextureID ObjectTileId = reinterpret_cast<ImTextureID>(*ObjectTileImage->GetShaderResourcesView());
	float4 ObjectTileSize = { 80.f, 160.f };

	int ObjectTileLineCount = 3;
	for (int i = 0; i < static_cast<int>(ObjectTileImage->GetCutCount()); i++)
	{
		float4 ObjectCutData = ObjectTileImage->GetCutData(i);
		__int64 ObjectImageBtnID = reinterpret_cast<__int64>(ObjectTileId);
		ObjectImageBtnID += i;
		ImGui::PushID(static_cast<int>(ObjectImageBtnID));
		if (true == ImGui::ImageButton(ObjectTileId, { ObjectTileSize.x, ObjectTileSize.y }, { ObjectCutData.x, ObjectCutData.y }, { ObjectCutData.x + ObjectCutData.z, ObjectCutData.y + ObjectCutData.w }))
		{
			// 현재 선택된 타일이 벽 텍스쳐이므로 텍스쳐 변경
			SelectMode_ = TileType::OBJECT;

			// 현재 선택된 타일의 인덱스로 변경
			SelectTileIndex_ = i;
		}
		ImGui::PopID();

		--ObjectTileLineCount;

		if (0 != ObjectTileLineCount)
		{
			ImGui::SameLine();
		}

		if (0 == ObjectTileLineCount)
		{
			ObjectTileLineCount = 3;
		}
	}

	ImGui::EndChildFrame();
#pragma endregion

#pragma region 타일렌더링모드 선택버튼

	// 바닥타일 수정모드(렌더링 타입전환)
	ImGui::Text("8. Select Floor Tile & Gride EditMode");
	if (FloorRenderingType::TILE == TileMap_->GetCurFloorRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : TILE MODE!!!!!!!!!!!");
	}
	else if (FloorRenderingType::GRID == TileMap_->GetCurFloorRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GRID MODE!!!!!!!!!!!");
	}

	if (true == ImGui::Button("F: TILE", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetFloorRenderingMode(FloorRenderingType::TILE);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("F: GRID", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetFloorRenderingMode(FloorRenderingType::GRID);
	}

	// 벽타일 수정모드(렌더링 타입전환)
	ImGui::Text("9. Select Wall Tile & Gride EditMode");
	if (WallRenderingType::TILE1 == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : TILE1 MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::TILE2 == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : TILE2 MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_NOR == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD NORMAL MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_NONE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD NONE MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_T == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(ABOVE THE CENTER) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_T_LE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(TOP : LEFT END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_T_RE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(TOP : RIGHT END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_B == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(BELOW THE CENTER) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_B_LE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(BOT : LEFT END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RT_B_RE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT TOP(BOT : RIGHT END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_L == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(LEFT THE CENTER) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_L_TE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(LEFT : TOP END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_L_BE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(LEFT : BOTTOM END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_R == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(RIGHT THE CENTER) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_R_TE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(RIGHT : TOP END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_RB_R_BE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD RIGHT BOTTOM(RIGHT : BOTTOM END) MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_BENT_SINGLE == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD BENT SINGLE MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_BENT_MULTI1 == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD BENT MULTI1 MODE!!!!!!!!!!!");
	}
	else if (WallRenderingType::GRID_BENT_MULTI2 == TileMap_->GetCurWallRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GIRD BENT MULTI2 MODE!!!!!!!!!!!");
	}

	// WALL EDIT MODE SELECT BUTTON
	if (true == ImGui::Button("W: TILE1", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::TILE1);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("W: TILE2", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::TILE2);
	}

	// NORMAL / NONE
	if (true == ImGui::Button("W: GRID NORMAL", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_NOR);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID NONE", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_NONE);
	}

	// RT_T
	if (true == ImGui::Button("W: GRID RIGHT TOP(ABOVE THE CENTER)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_T);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT TOP(TOP : LEFT END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_T_LE);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT TOP(TOP : RIGHT END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_T_RE);
	}

	// RT_B
	if (true == ImGui::Button("W: GRID RIGHT TOP(BELOW THE CENTER)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_B);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT TOP(BOTTOM : LEFT END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_B_LE);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT TOP(BOTTOM : RIGHT END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RT_B_RE);
	}

	// RB_L
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(LEFT THE CENTER)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_L);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(LEFT : BOTTOM END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_L_BE);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(LEFT : TOP END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_L_TE);
	}

	// RB_R
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(RIGHT THE CENTER)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_R);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(RIGHT : BOTTOM END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_R_BE);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID RIGHT BOTTOM(RIGHT : TOP END)", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_RB_R_TE);
	}

	// BENT
	if (true == ImGui::Button("W: GRID BENT SINGLE", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_BENT_SINGLE);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID BENT MULTI1", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_BENT_MULTI1);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("W: GRID BENT MULTI2", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetWallRenderingMode(WallRenderingType::GRID_BENT_MULTI2);
	}

	// OBJECT 수정
	ImGui::Text("10. Select Object Tile & Gride EditMode");
	if (ObjectRenderingType::TILE == TileMap_->GetCurObjectRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : TILE MODE!!!!!!!!!!!");
	}
	else if (ObjectRenderingType::GRID_NORMAL == TileMap_->GetCurObjectRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GRID NORMAL MODE!!!!!!!!!!!");
	}
	else if (ObjectRenderingType::GRID_OBJECT == TileMap_->GetCurObjectRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GRID OBJECT MODE!!!!!!!!!!!");
	}
	else if (ObjectRenderingType::GRID_WALL == TileMap_->GetCurObjectRenderType())
	{
		ImGui::SameLine();
		ImGui::Text("CURRENT MODE : GRID WALL MODE!!!!!!!!!!!");
	}

	if (true == ImGui::Button("O: TILE", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetObjectRenderingMode(ObjectRenderingType::TILE);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("O : GRID NORMAL", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetObjectRenderingMode(ObjectRenderingType::GRID_NORMAL);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("O : GRID OBJECT", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetObjectRenderingMode(ObjectRenderingType::GRID_OBJECT);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("O : GRID WALL", ImVec2(140.f, 20.f)))
	{
		TileMap_->SetObjectRenderingMode(ObjectRenderingType::GRID_WALL);
	}
#pragma endregion

	// AUTOMAP ALL CLEAR
	ImGui::Text("... AutoMap All Clear");
	if (true == ImGui::Button("Auto Map ALL Clear", ImVec2(140.f, 20.f)))
	{
		TileMap_->AutoModeTileAllClear();
	}

#pragma endregion

#pragma region 맵파일저장/로드 관련
	ImGui::Text("<<< MAP FILE SAVE & LOAD >>>");
	if (true == ImGui::Button("SAVE", ImVec2(140.f, 20.f)))
	{
		TileMap_->MapFileSave();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("LOAD", ImVec2(140.f, 20.f)))
	{
		TileMap_->MapFileLoad();
	}
#pragma endregion
}
