#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>

#include "RandomTileMap_Common.h"

enum class LevelType
{
	None = -1,
	Catacombs,
	ChaosSanctuary,
};

class GameEngineTileMapRenderer;
struct RoomRender
{
	std::unordered_map<__int64, GameEngineTileMapRenderer*> TileRenderer_;
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTileMapRenderer;
class EditorRandomMap : public GameEngineActor
{
public:
	static LevelType CurLevelType;

private:
	static std::vector<int> IgnoreRange;
	static std::vector<std::vector<float4>> RandomRange;
	static std::vector<std::vector<int>> RandomReversRange;
	static std::vector<std::vector<int>> RandomNextRange;

private:
	GameEngineRandom RoadRandom_;
	std::vector<float4> RandomStartPos_;

private: // 랜덤맵 정보관련
	RandomMapInfo MapInfo_;

public:
	int SelectFloorTileIndex_;
	int SelectWallTileIndex_;

private:
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private: // 타일정보
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;
	float4 TileSizeHHHalf_;

private: // 바닥타일정보
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // 벽타일정보
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;

private: // 랜덤맵 생성관련
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// 복도/룸 렌더러
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallTiles_;		// 벽/문 렌더러

public:
	EditorRandomMap();
	~EditorRandomMap();

protected:		// delete constructer
	EditorRandomMap(const EditorRandomMap& _other) = delete;
	EditorRandomMap(EditorRandomMap&& _other) noexcept = delete;

private:		//delete operator
	EditorRandomMap& operator=(const EditorRandomMap& _other) = delete;
	EditorRandomMap& operator=(const EditorRandomMap&& _other) = delete;

private:
	void Start() override;

public: // 텍스쳐 셋팅
	void CatacombsTextrueSetting();
	void ChaosSanctuaryTextrueSetting();

public: // 텍스쳐 Get
	inline GameEngineTexture* GetFloorTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(FloorTileTextureName_);
	}

	inline GameEngineTexture* GetWallTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(WallTileTextureName_);
	}

public:
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

public:
	float4 GetFloorTileIndexToPos(TileIndex _TileIndex);
	float4 GetWallTileIndexToPos(TileIndex _TileIndex);

public:
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_);
	void SetWallTile(TileIndex _Index, int CurTileIndex_);

public: // 정보 클리어관련

	// 1) 랜덤맵 관련 모든 정보 및 렌더러 제거
	void AllClear();

	// 2) 랜덤으로 설치한 복도 렌더러 및 정보 제거
	void AllCorridorClear();

	// 3) 배치된 룸 렌더러 및 정보제거
	void AllRoomClear();

	// 4) 배치된 벽/문 렌더러 및 정보제거
	void AllWallClear();
	
public: // 랜덤맵 생성 관련
	// 1. 랜덤방향 복도정보 생성
	void CreateRandomCorridor(int _Create, int _Thickness, int _LenTileCount, int _DirCnt);
	void CreateRandomCorridorInfo(int _Create, int _Thickness, int _LenTileCount, int _DirCnt);
	bool CorridorOverlapCheck(TileIndex _TileIndex);
	void CorridorRendering();

	// 2. 복도를 기준으로 룸정보 생성
	void CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	bool RoomOvelapCheck(TileIndex _CenterTile);
	void RoomRendering();

	// 3. 복도/룸 정보를 이용하여 벽/문 정보 생성
	void CreateWall();
	void CreateWallInfo();
	void WallRendering();
};

