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

// �з� : 
// �뵵 : 
// ���� : 
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

private: // ������ ��������
	RandomMapInfo MapInfo_;

private:
	int SelectFloorTileIndex_;
	int SelectWallTile1Index_;
	int SelectWallTile2Index_;

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

private: // ������ Ÿ�Ϸ����� ��������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// ����/�� Ÿ�� ������
	std::unordered_map<__int64, RandomMapWallRenderer> WallTiles_;			// ��/�� Ÿ�� ������

private: // ������ �׸��巻���� ��������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;	// ����/�� �׸��� ������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;	// ��/�� �׸��� ������

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

public: // �ؽ��� ����
	void CatacombsTextrueSetting();
	void ChaosSanctuaryTextrueSetting();

public: // Ÿ���ε��� ����
	void SetSelectFloorTileIndex(int _Index = 0);
	void SetSelectWallTile1Index(int _Index = 0);
	void SetSelectWallTile2Index(int _Index = 0);

public:
	void FloorGridesSwitching();
	void WallGridesSwitching();

public: // �ؽ��� Get
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

public: // Ÿ�� ������ ��������
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);
	void SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);

public: // �׸��� ������ ��������
	void SetFloorGrid(float4 _Pos, RandomMapTileType _TileType, bool _CenterFlag = false);
	void SetFloorGrid(TileIndex _Index, RandomMapTileType _TileType, bool _CenterFlag = false);
	void SetWallGrid(float4 _Pos, RandomWallBasicType _BasicType = RandomWallBasicType::WALL, RandomWallDetailType _DetailType = RandomWallDetailType::NORMAL);
	void SetWallGrid(TileIndex _Index, RandomWallBasicType _BasicType = RandomWallBasicType::WALL, RandomWallDetailType _DetailType = RandomWallDetailType::NORMAL);

public: // ���� Ŭ�������

	// 1) ������ ���� ��� ���� �� ������ ����
	void AllClear();

	// 2) �������� ��ġ�� ���� ������ �� ���� ����
	void AllCorridorClear();

	// 3) ��ġ�� �� ������ �� ��������
	void AllRoomClear();

	// 4) ��ġ�� ��/�� ������ �� ��������
	void AllWallClear();
	
public: // ������ ���� ����
	// 1. �������� �������� ����
	void CreateRandomCorridor(int _Create, int _Thickness, int _LenTileCount, int _DirCnt);
	void CreateRandomCorridorInfo(int _Create, int _Thickness, int _LenTileCount, int _DirCnt);
	bool CorridorOverlapCheck(TileIndex _TileIndex);
	bool Corridor8WaySearch(TileIndex _CheckTileIndex);
	void CorridorGridRendering();

	// 2. ������ �������� ������ ����
	void CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void SetTheFarthestRoom(int _CheckRoomIndex);
	bool RoomIntersectsCheck(const std::vector<TileIndex>& _TileList);
	bool RoomOverlapCheck(TileIndex _CenterTile);
	void CorridorOverlapTileIndexCheck(TileIndex _TileIndex);
	void RoomGridRendering();

	// 3. ����/�� ������ �̿��Ͽ� ������ ����
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

	// 4. ����<->�� or ��<->�� ���� ������ ����
	void CreateDoorInfo();
	bool Door8WaySearch(TileIndex _DoorTileIndex, RandomWallCheckDir _CheckDir);
	RandomMapTileType DoorInfoSettingCheck(TileIndex _CheckTile, int _CurRoomNo);

	// 5. ��� Ÿ��Ÿ�԰� �ؽ��ĸ�Ī�� ���� Ÿ�� ������
	void FloorTileTextureMatching();
	void WallTileTextureMatching();
	void DoorTileTextureMatching();

	// 6. Save & Load
	void RandomMapSave(const std::string& _FileName);
	void RandomMapLoad(const std::string& _FileName);
};

