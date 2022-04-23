#pragma once
#include <GameEngine/GameEngineActor.h>
#include "TileMap_Common.h"

// 분류 : 맵(MAP)
// 용도 : 고정맵
// 설명 : 바닥,벽,오브젝트 정보를 로드하여 화면에 맵을 렌더링하며, 해당 정보들을 이용하여 
//        맵내에 존재하는 액터(NPC, PLAYER, ...)의 움직임을 제어하는 네비게이션정보를 생성한다.

class GameEngineTileMapRenderer;
class TownMap : public GameEngineActor
{
private:
	class WallTileRenderer
	{
	public:
		GameEngineTileMapRenderer* WallTiles1_;
		GameEngineTileMapRenderer* WallTiles2_;

		WallTileRenderer() : WallTiles1_(nullptr), WallTiles2_(nullptr)
		{
		}
	};

private:	// member Var
	MapType MapType_;

private: // 맵의 각 타입별(바닥,벽,오브젝트) 정보
	std::vector<std::vector<FloorTileInfo>> TownMap_FloorTileInfo_;
	std::vector<std::vector<WallTileInfo>> TownMap_WallTileInfo_;
	std::vector<std::vector<ObjectTileInfo>> TownMap_ObjectTileInfo_;

private: // 타일 렌더러
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, WallTileRenderer> WallTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;

private: // 해당 맵의 네비게이션 정보


public:
	TownMap();
	~TownMap();

protected:		// delete constructer
	TownMap(const TownMap& _other) = delete;
	TownMap(TownMap&& _other) noexcept = delete;

private:		//delete operator
	TownMap& operator=(const TownMap& _other) = delete;
	TownMap& operator=(const TownMap&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void MapInfoAllClear();
	void MapTextureCutting();

public:
	bool TownLevel_FixedMapLoad();
	void CreatedAfterLoadingTiles();
	void CreateNavigationInfo();
};

