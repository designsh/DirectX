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
	static bool FirstRandomLoad_;
	static std::vector<int> IgnoreRange;
	static std::vector<std::vector<float4>> RandomRange;
	static std::vector<std::vector<int>> RandomReversRange;
	static std::vector<std::vector<int>> RandomNextRange;

private:
	static bool Compare(std::pair<int, float>& _First, std::pair<int, float>& _Second);

private:
	GameEngineRandom RoadRandom_;
	std::vector<float4> RandomStartPos_;

private: // ������ ��������
	RandomMapInfo MapInfo_;

private: // �� ũ�����
	TileIndex MapMinIndexX_;
	TileIndex MapMaxIndexX_;
	TileIndex MapMinIndexY_;
	TileIndex MapMaxIndexY_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> MapMaxScale_;

private: // �� ��������
	GameEngineRandom RoomRandom_;
	int RoomCnt_;
	int minIndexX_;
	int minIndexY_;
	int maxIndexX_;
	int maxIndexY_;
	std::vector<RoomRender> RoomRenderer_;

private: // ���� ��������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> CorridorRenderer_;

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
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallTiles_;

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

public: // 
	void RandomRoad(int _Count, bool _Multidirectional = false);

public: // ������ ���ѹ��� ����
	void TotalMapScale(int _MaxIndexX, int _MaxIndexY);										// ���� �����Ϸ��� ���� ũ�⸦ ����
	void TotalMapRendererClear();															// ���� �����Ϸ��� ���� ũ�⸦ ��Ÿ���� ������ ��� ���ű��(�� ���ġ�Ϸ�� ȣ��)

public: // ���� ����
	void AllClear();																		// ���� ������ �����ʰ��� ���� �� ������ ����

	// ���������
	void AllRoomClear();																	// ��� �� ���� �� ������ ����
	void AllRoomInfomationClear();															// ��� ���� ���� ����
	void AllRoomRendererClear();															// ��� ���� ������ ����
	void RoomRenderClear(int _Index);														// ���� ���õ� �ε����� ������ ����

	// ������������
	void AllCorridorClear();																// ��� ���� ���� �� ������ ����
	void AllCorridorInfomationClear();														// ��� ������ ���� ����
	void AllCorridorRendererClear();														// ��� ������ ������ ����

	// ������������
	void AllRandomRoadClear();																// �������� ��ġ�� ���� ������ ����

	void RandomRoom(int _RoomCnt, int _WidthIndex, int _HeightIndex);						// ���� �����Ϸ��� ���� ���� ��ġ�ϱ� ���Ͽ� �⺻���� ����
	bool RoomArrangeCheck(int _WidthIndex, int _HeightIndex, int _RoomCnt);					// ���� �����Ϸ��� ���� ������������ üũ�Ͽ� �����ϴٸ� �ε�����ȯ

	// �� �ڵ�����
	void CreateRoomAuto(int _WidthIndex, int _HeightIndex);									// _RoomCnt�� 0�� �ƴϸ� �ڵ����� ������ŭ ����(��������)
	void RenderingAutoRoom();																// �ڵ����� ������ ���� ��� ������

	// �� ��������
	void CreateRoomManual(int _WidthIndex, int _HeightIndex);								// _RoomCnt�� 0�̸� �ش� ���� �����Ҷ����� ���� ����(��������)
	void RenderingManualRoom();																// ȭ�鿡�� Ȯ���ϱ� ���Ͽ� ������ �� ������ �̿��Ͽ� ȭ�鿡 ������

	// ���� �����Ϸ�� ���Ͽ��� ��ġ�� ���� ���� �о�� ����
	void RoomPushOut();																		// 
	bool RoomIntersectsMoveCheck(int _CurIndex, float4 _Dir = float4(0, 0));				// ���� �˻��ϴ� ��� ��� ���� üũ�Ͽ� ������������������ �̵�

	// ���� ���� �� ���ġ�Ϸ�� �������� �̿��Ͽ� ���������� �ʿ��� ���� ����
	void RoomDistanceMeasurement();															// �� ���� ���������� �̿��Ͽ� �밣�� �Ÿ��� ���� �� ���� �ָ��ִ� ���� �˾Ƴ���, ���� ����� ���� �˾Ƴ���.
	void SearchRoomDistance(int _CheckIndex);												// ������ ���ط�� �ٸ� ������ �Ÿ��� ����
	
public: // ���� ����
	void RoomConnection();																	// ������ ���� ��� ����
	void RoomConnectionStart(int _CurIndex, int _ConnectionIndex);							// �� ���� ����
	void ConnectRoomDir(int _CurIndex, int _ConnectionIndex);								// �����Ϸ��� ���� ��ġ�� �̿��Ͽ� ���� �뿡�� ������ ���� ��ġ�� ����
	void SetCorridorTile(int _CurIndex, int _ConnectionIndex);								// ���� ���� ���Ϳ��� ��ǥ ���� �����ε������� ����Ÿ�� ���� ����
	void CorridorRendering(int _Index);														// ������ ���� ������(�������� ȣ��)
	void AllCorridorRendering();															// ��� ���� ������(��ü �����Ϸ��� ȣ��)

public: // ��/���� ������
	void CreateWall();																		// 

public: // ��-����-���� ����κп� �� ����
	void CreateDoor();																		// 
};

