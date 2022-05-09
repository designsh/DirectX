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
	GameEngineRandom RoadRandom_;
	std::vector<float4> RandomStartPos_;

private: // ������ ��������
	RandomMapInfo MapInfo_;

public:
	int SelectFloorTileIndex_;
	int SelectWallTileIndex_;

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

private: // ������ ��������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// ����/�� ������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallTiles_;		// ��/�� ������

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

public:
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_);
	void SetWallTile(TileIndex _Index, int CurTileIndex_);

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
	void CorridorRendering();

	// 2. ������ �������� ������ ����
	void CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	void CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex);
	bool RoomOvelapCheck(TileIndex _CenterTile);
	void RoomRendering();

	// 3. ����/�� ������ �̿��Ͽ� ��/�� ���� ����
	void CreateWall();
	void CreateWallInfo();
	void WallRendering();
};

