#include "PreCompile.h"
#include "TileMapInfoWindow.h"

#include <GameEngine/GameEngineCore.h>

#include "TileMap_Common.h"
#include "GlobalValue.h"
#include "TownMap.h"

TileMapInfoWindow::TileMapInfoWindow() :
	TownMap_(nullptr)
{
}

TileMapInfoWindow::~TileMapInfoWindow()
{
}

void TileMapInfoWindow::OnGUI()
{
	if (nullptr != GlobalValue::TownMap)
	{
		float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();

		// Floor Tile Info
		ImGui::Text("<<<< FLOOR INFOMATION >>>>");
		TileIndex FloorTileIndex = GlobalValue::TownMap->GetFloorTileIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
		ImGui::Text(("XIndex : " + std::to_string(FloorTileIndex.X_) + "  YIndex : " + std::to_string(FloorTileIndex.Y_)).c_str());

		// Wall Tile Info & Object Tile Info & Navigation Info
		ImGui::Text("<<<< NAVIGATION INFOMATION >>>>");
		TileIndex WallTileIndex = GlobalValue::TownMap->GetNavigationIndex(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
		NavigationType CurTileType = GlobalValue::TownMap->GetTileToNaviType(GameEngineInput::GetInst().GetMouse3DPos() + CameraPos);
		ImGui::Text(("XIndex : " + std::to_string(WallTileIndex.X_) + "  YIndex : " + std::to_string(WallTileIndex.Y_)).c_str());
		if (NavigationType::NOR == CurTileType)
		{
			ImGui::Text("TYPE : NONE");
		}
		else
		{
			ImGui::Text("TYPE : WALL");
		}
	}
}
