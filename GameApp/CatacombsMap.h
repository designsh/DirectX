#pragma once
#include <GameEngineBase/GameEnginePathFind.h>
#include <GameEngine/GameEngineActor.h>

#include "RandomTileMap_Common.h"
#include "Navigation_Common.h"

class GameEngineTileMapRenderer;
struct RandomMapWallRenderer
{
	GameEngineTileMapRenderer* Tiles1_;
	GameEngineTileMapRenderer* Tiles2_;
};

// �з� : 
// �뵵 : 
// ���� : �����Ϳ��� �������� �� �÷��̷������� �ε��Ͽ� ���
class GameEngineTileMapRenderer;
class CatacombsMap : public GameEngineActor
{
private:	// member Var
	RandomMapInfo MapInfo_;

private:
	GameEnginePathFind* Navigation_;
	std::unordered_map<__int64, NavigationType> NavCatacombsMap_;

private:
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private: // Ÿ������
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;
	float4 TileSizeHHHalf_;

private: // �ٴ�Ÿ������
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // ��Ÿ������
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;

private:
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// ����/�� Ÿ�� ������
	std::unordered_map<__int64, RandomMapWallRenderer> WallTiles_;			// ��/�� Ÿ�� ������

public:
	CatacombsMap();
	~CatacombsMap();

protected:		// delete constructer
	CatacombsMap(const CatacombsMap& _other) = delete;
	CatacombsMap(CatacombsMap&& _other) noexcept = delete;

private:		//delete operator
	CatacombsMap& operator=(const CatacombsMap& _other) = delete;
	CatacombsMap& operator=(const CatacombsMap&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

private:
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);
	void SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);

private:
	void MapInfoAllClear();
	void AllCorridorClear();
	void AllRoomClear();
	void AllWallClear();

private:
	void MapTextureCutting();

public:
	void CatacombsMapLoad();

private:
	void MapRendering();
	void FloorTileTextureMatching();
	void WallTileTextureMatching();
	void DoorTileTextureMatching();

private:
	void CreateNavigationInfo();

private:
	bool Moveable4WaysCheck(PathIndex _PathIndex);
	bool Moveable8WaysCheck(PathIndex _PathIndex);

public:
	std::list<PathIndex> NavgationFind4Way(float4 _StartPos, float4 _MouseClickPos);
	std::list<PathIndex> NavgationFind8Way(float4 _StartPos, float4 _MouseClickPos);
};

