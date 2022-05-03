#include "PreCompile.h"
#include "TileMapInfoWindow.h"

#include <GameEngine/GameEngineCore.h>

#include "FixedTileMap_Common.h"
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
		// CamPos 
		float4 CameraPos = GameEngineCore::CurrentLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
		ImGui::Text("<<< MainCamera Pos >>>");
		ImGui::Text(("Cam X : " + std::to_string(CameraPos.x) + "  Cam Y : " + std::to_string(CameraPos.y)).c_str());

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
