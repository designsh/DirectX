#pragma once
#include "FixedTileMap_Common.h"

// 랜덤맵 공통 정보 헤더

// 룸 센터인덱스 기준 방향
enum class RoomCenterDirType
{
	DIRTC_T,												// 룸의 센터기준 상단
	DIRTC_B,												// 룸의 센터기준 하단
	DIRTC_L,												// 룸의 센터기준 좌단
	DIRTC_R													// 룸의 센터기준 우단
};

// 랜덤맵 타일 타입(바닥타일기준)
enum class RandomMapTileType
{
	NONE = -1,												// 
	ROOM,													// 방
	DOOR,													// 문
	CORRIDOR,												// 복도
	WALL,													// 벽
};

// 랜덤맵 문 타입
enum class RandomMapDoorType
{
	NONE = -1,
	RT_T_L,													// 룸 센터기준 상단 우상단방향 문의 왼쪽 텍스쳐
	RT_T_R,													// 룸 센터기준 상단 우상단방향 문의 오른쪽 텍스쳐
	RT_B_L,													// 룸 센터기준 하단 우상단방향 문의 왼쪽 텍스쳐
	RT_B_R,													// 룸 센터기준 하단 우상단방향 문의 오른쪽 텍스쳐
	RB_L_T,													// 룸 센터기준 좌단 우하단방향 문의 위쪽 텍스쳐
	RB_L_B,													// 룸 센터기준 좌단 우하단방향 문의 아래쪽 텍스쳐
	RB_R_T,													// 룸 센터기준 우단 우하단방향 문의 위쪽 텍스쳐
	RB_R_B,													// 룸 센터기준 우단 우하단방향 문의 아래쪽 텍스쳐
};

// 랜덤맵 복도정보
struct RandomCorridorInfo
{
	RandomMapTileType CorridorType_;						// 타일타입(복도)
	std::vector<TileIndex> AllIndexLists_;					// 현재 생성된 복도의 모든 타일 인덱스(렌더링용도)
};

// 랜덤맵 룸정보
struct RandomRoomInfo
{
	RandomMapTileType TileType_;							// 타일타입(룸)
	int RoomNo_;											// 룸 번호(생성번호)

	int WidthIndex_;										// 룸의 크기 가로(타일의 Y인덱스) 인덱스
	int HeightIndex_;										// 룸의 크기 세로(타일의 X인덱스) 인덱스

	int minIndexX_;											// 룸이 차지하는 인덱스 X의 최소 인덱스
	int maxIndexX_;											// 룸이 차지하는 인덱스 Y의 최대 인덱스
	int minIndexY_;											// 룸이 차지하는 인덱스 X의 최소 인덱스
	int maxIndexY_;											// 룸이 차지하는 인덱스 Y의 최대 인덱스
	TileIndex RoomCenterIndex_;								// 룸의 센터 인덱스
};

// 랜덤맵 문정보
struct RandomDoorInfo
{
	int IndexX;												// X 인덱스
	int IndexY;												// Y 인덱스

	RandomMapTileType TileType_;							// 타일타입(문)
	int Direction_;											// 룸 센터기준 생성된 위치(상/하/좌/우)
	RandomMapDoorType DoorType_;							// 문의 렌더링 타입
};

// 랜덤맵 정보
struct RandomMapInfo
{
	// 복도 관련 정보
	RandomCorridorInfo CorridorInfo_;						// 해당 맵의 복도 목록

	// 룸 관련 정보
	std::vector<RandomRoomInfo> RoomInfo_;					// 해당 맵의 룸 목록

	// 벽 관련 정보(네비게이션 정보로 사용)
	std::vector<WallTileInfo> WallInfo_;					// 해당 맵의 벽 목록

	// 문 관련 정보
	std::vector<RandomDoorInfo> DoorInfo_;					// 해당 맵의 문 목록
};

// 바닥타일정보
struct RandomFloorTileInfo
{
	RandomMapTileType TileType;								// 바닥타일 타입(방, 문, 복도)
	int IndexX;												// 
	int IndexY;												// 
	int TileImageIndex;										// 

	std::string TextureName;								// 
	float4 TileSize;										// 
	float4 RenderSize;										// 
	float4 RenderPivotPos;									// 
};

// 벽타일정보
struct RandomWallTileInfo
{
	// 인덱스 및 타입정보
	WallBasicType BasicType;								// 
	WallDetailType DetailType;								// 
	int IndexX;												// 
	int IndexY;												// 
	int Tile1ImageIndex;									// 
	int Tile2ImageIndex;									// 

	std::string TextureName;								// 
	float4 TileSize;										// 
	float4 RenderSize;										// 
	float4 RenderPivotPos;									// 
};
