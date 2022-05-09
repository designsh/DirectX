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

private: // 랜덤맵 정보관련
	RandomMapInfo MapInfo_;

private: // 맵 크기관련
	TileIndex MapMinIndexX_;
	TileIndex MapMaxIndexX_;
	TileIndex MapMinIndexY_;
	TileIndex MapMaxIndexY_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> MapMaxScale_;

private: // 룸 생성관련
	GameEngineRandom RoomRandom_;
	int RoomCnt_;
	int minIndexX_;
	int minIndexY_;
	int maxIndexX_;
	int maxIndexY_;
	std::vector<RoomRender> RoomRenderer_;

private: // 복도 생성관련
	std::unordered_map<__int64, GameEngineTileMapRenderer*> CorridorRenderer_;

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

public: // 
	void RandomRoad(int _Count, bool _Multidirectional = false);

public: // 랜덤맵 제한범위 관련
	void TotalMapScale(int _MaxIndexX, int _MaxIndexY);										// 현재 생성하려는 맵의 크기를 결정
	void TotalMapRendererClear();															// 현재 생성하려는 맵의 크기를 나타내는 렌더러 목록 제거기능(룸 재배치완료시 호출)

public: // 정리 관련
	void AllClear();																		// 현재 생성된 랜덤맵관련 정보 및 렌더러 제거

	// 룸관련정보
	void AllRoomClear();																	// 모든 룸 정보 및 렌더러 제거
	void AllRoomInfomationClear();															// 모든 룸의 정보 제거
	void AllRoomRendererClear();															// 모든 룸의 렌더러 제거
	void RoomRenderClear(int _Index);														// 현재 선택된 인덱스의 렌더러 제거

	// 복도관련정보
	void AllCorridorClear();																// 모든 복도 정보 및 렌더러 제거
	void AllCorridorInfomationClear();														// 모든 복도의 정보 제거
	void AllCorridorRendererClear();														// 모든 복도의 렌더러 제거

	// 랜덤복도관련
	void AllRandomRoadClear();																// 랜덤으로 설치한 복도 렌더러 제거

	void RandomRoom(int _RoomCnt, int _WidthIndex, int _HeightIndex);						// 현재 생성하려는 맵의 방을 배치하기 위하여 기본정보 저장
	bool RoomArrangeCheck(int _WidthIndex, int _HeightIndex, int _RoomCnt);					// 현재 생성하려는 룸이 생성가능한지 체크하여 가능하다면 인덱스반환

	// 룸 자동생성
	void CreateRoomAuto(int _WidthIndex, int _HeightIndex);									// _RoomCnt가 0이 아니면 자동으로 갯수만큼 생성(정보생성)
	void RenderingAutoRoom();																// 자동으로 생성된 룸을 모두 렌더링

	// 룸 수동생성
	void CreateRoomManual(int _WidthIndex, int _HeightIndex);								// _RoomCnt가 0이면 해당 동작 수행할때마다 룸을 생성(정보생성)
	void RenderingManualRoom();																// 화면에서 확인하기 위하여 생성된 룸 정보를 이용하여 화면에 렌더링

	// 현재 생성완료된 룸목록에서 겹치는 룸을 서로 밀어내는 구문
	void RoomPushOut();																		// 
	bool RoomIntersectsMoveCheck(int _CurIndex, float4 _Dir = float4(0, 0));				// 현재 검사하는 방과 모든 룸을 체크하여 겹쳐지지않을때까지 이동

	// 현재 생성 및 재배치완료된 룸정보를 이용하여 복도생성에 필요한 정보 셋팅
	void RoomDistanceMeasurement();															// 각 룸의 센터정보를 이용하여 룸간의 거리를 측정 후 가장 멀리있는 룸을 알아내고, 가장 가까운 룸을 알아낸다.
	void SearchRoomDistance(int _CheckIndex);												// 각각의 기준룸과 다른 모든룸의 거리를 측정
	
public: // 복도 연결
	void RoomConnection();																	// 생성된 룸을 모두 연결
	void RoomConnectionStart(int _CurIndex, int _ConnectionIndex);							// 룸 연결 시작
	void ConnectRoomDir(int _CurIndex, int _ConnectionIndex);								// 연결하려는 룸의 위치를 이용하여 현재 룸에서 복도를 뚫을 위치를 결정
	void SetCorridorTile(int _CurIndex, int _ConnectionIndex);								// 현재 룸의 센터에서 목표 룸의 센터인덱스까지 복도타일 정보 생성
	void CorridorRendering(int _Index);														// 생성된 복도 렌더링(생성마다 호출)
	void AllCorridorRendering();															// 모든 복도 렌더링(전체 생성완료후 호출)

public: // 룸/복도 벽생성
	void CreateWall();																		// 

public: // 룸-복도-룸의 연결부분에 문 생성
	void CreateDoor();																		// 
};

