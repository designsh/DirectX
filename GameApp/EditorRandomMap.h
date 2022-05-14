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
struct RandomMapWallRenderer
{
	GameEngineTileMapRenderer* Tiles1_;
	GameEngineTileMapRenderer* Tiles2_;
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
	static bool Compare(std::pair<int, float>& _First, std::pair<int, float>& _Second);

private:
	bool FloorGridesActive_;
	bool WallGridesActive_;

private:
	GameEngineRandom RoadRandom_;
	std::vector<float4> RandomStartPos_;

private: // 랜덤맵 정보관련
	RandomMapInfo MapInfo_;

private:
	int SelectFloorTileIndex_;
	int SelectWallTile1Index_;
	int SelectWallTile2Index_;

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

private: // 랜덤맵 타일렌더러 생성관련
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// 복도/룸 타일 렌더러
	std::unordered_map<__int64, RandomMapWallRenderer> WallTiles_;			// 벽/문 타일 렌더러

private: // 랜덤맵 그리드렌더러 생성관련
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;	// 복도/룸 그리드 렌더러
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;	// 벽/문 그리드 렌더러

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

public: // 타일인덱스 셋팅
	void SetSelectFloorTileIndex(int _Index = 0);
	void SetSelectWallTile1Index(int _Index = 0);
	void SetSelectWallTile2Index(int _Index = 0);

public:
	void FloorGridesSwitching();
	void WallGridesSwitching();

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

public: // 타일 렌더러 생성관련
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);
	void SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);

public: // 그리드 렌더러 생성관련
	void SetFloorGrid(float4 _Pos, RandomMapTileType _TileType, bool _CenterFlag = false);
	void SetFloorGrid(TileIndex _Index, RandomMapTileType _TileType, bool _CenterFlag = false);
	void SetWallGrid(float4 _Pos, RandomWallBasicType _BasicType = RandomWallBasicType::WALL, RandomWallDetailType _DetailType = RandomWallDetailType::NORMAL);
	void SetWallGrid(TileIndex _Index, RandomWallBasicType _BasicType = RandomWallBasicType::WALL, RandomWallDetailType _DetailType = RandomWallDetailType::NORMAL);

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
	bool Corridor8WaySearch(TileIndex _CheckTileIndex);
	void CorridorGridRendering();

	// 2. 복도를 기준으로 룸정보 생성
	void CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void SetTheFarthestRoom(int _CheckRoomIndex);
	bool RoomIntersectsCheck(const std::vector<TileIndex>& _TileList);
	bool RoomOverlapCheck(TileIndex _CenterTile);
	void CorridorOverlapTileIndexCheck(TileIndex _TileIndex);
	void RoomGridRendering();

	// 3. 복도/룸 정보를 이용하여 벽정보 생성
	void CreateWall();
	void CreateWallInfo();
	void CreateOutWallInfo();
	void CreateRoomWallInfo();
	void SearchOutWall();
	void UpdateOutWallInfo();
	void UpdateRoomWallInfo();
	void RemainingWallTreatment();
	bool WallOverlapCheck(TileIndex _WallTileIndex);
	bool Wall8WaySearch(TileIndex _TileIndex);
	void WallGridRendering();

	// 4. 복도<->룸 or 룸<->룸 연결 문정보 생성
	void CreateDoorInfo();
	bool Door8WaySearch(TileIndex _DoorTileIndex, RandomWallCheckDir _CheckDir);
	RandomMapTileType DoorInfoSettingCheck(TileIndex _CheckTile, int _CurRoomNo);

	// 5. 모든 타일타입과 텍스쳐매칭에 따른 타일 렌더링
	void FloorTileTextureMatching();
	void WallTileTextureMatching();
	void DoorTileTextureMatching();

	// 6. Save & Load
	void RandomMapSave(const std::string& _FileName);
	void RandomMapLoad(const std::string& _FileName);
};

