#pragma once
#include "FixedTileMap_Common.h"

// 랜덤맵 공통 정보 헤더

// 랜덤맵 타일 타입(바닥타일기준)
enum class RandomMapTileType
{
	CORRIDOR,													// 복도
	ROOM,														// 방
};

// 벽 기본 타입(
enum class RandomWallBasicType
{
	WALL,														// 일반벽
	DOOR,														// 문
};

// 벽타일 상세타입(방향타입)
enum class RandomWallDetailType
{
	NONE,														// 벽으로판단하나, 렌더링없음
	NORMAL,														// 벽으로판단하지않고, 렌더링없음

	// 기본타입이 벽일때
	WL_RT_T,													// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 윗벽
	WL_RT_T_RE,													// 우상단방향으로 윗벽의 끝(BENT와 연결되는 벽)
	WL_RT_T_LE,													// 좌하단방향으로 윗벽의 끝(BENT직전에 RT가 끝)
	WL_RT_B,													// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 아랫벽
	WL_RT_B_RE,													// 우상단방향으로 아랫벽의 끝(BENT가 끝)
	WL_RT_B_LE,													// 좌하단방향으로 아랫벽의 끝(BENT직전에 RT가 끝)
	WL_RB_L,													// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 왼쪽벽
	WL_RB_L_BE,													// 우하단방향으로 왼쪽벽의 끝(BENT직전에 RB가 끝)
	WL_RB_L_TE,													// 좌상단방향으로 왼쪽벽의 끝(BENT가 끝)
	WL_RB_R,													// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 오른쪽벽
	WL_RB_R_BE,													// 우하단방향으로 오른쪽벽의 끝(BENT직전에 RB가 끝)
	WL_RB_R_TE,													// 좌상단방향으로 오른쪽벽의 끝(BENT와 연결되는 벽)
	WL_BENT_MULTI,												// 꺽이는벽(렌더러를 2개 가진다) - 중심기준(0,0) 우상단꺽이는벽 => RT_T_RE와 RB_R_TE가 만나려고하는 벽(멀티렌더러)
	WL_BENT_SINGLE,												// 꺽이는벽(렌더러를 1개 가진다) - 중심기준(0,0) 좌하단꺽이는벽 => RT_B_LE와 RB_L_BE가 만나려고하는 벽(단독렌더러)

	// 기본타입이 문일때
	DR_RT_T_L,													// 룸 센터기준 상단 우상단방향 문의 왼쪽 텍스쳐
	DR_RT_T_R,													// 룸 센터기준 상단 우상단방향 문의 오른쪽 텍스쳐
	DR_RT_B_L,													// 룸 센터기준 하단 우상단방향 문의 왼쪽 텍스쳐
	DR_RT_B_R,													// 룸 센터기준 하단 우상단방향 문의 오른쪽 텍스쳐
	DR_RB_L_T,													// 룸 센터기준 좌단 우하단방향 문의 위쪽 텍스쳐
	DR_RB_L_B,													// 룸 센터기준 좌단 우하단방향 문의 아래쪽 텍스쳐
	DR_RB_R_T,													// 룸 센터기준 우단 우하단방향 문의 위쪽 텍스쳐
	DR_RB_R_B,													// 룸 센터기준 우단 우하단방향 문의 아래쪽 텍스쳐
};

// 랜덤맵 복도정보
struct RandomCorridorInfo
{
	RandomMapTileType CorridorType_;							// 타일타입(복도)
	std::vector<TileIndex> AllIndexLists_;						// 현재 생성된 복도의 모든 타일 인덱스(렌더링용도)
};

// 랜덤맵 룸정보
struct RandomRoomInfo
{
	RandomMapTileType TileType_;								// 타일타입(룸)
	int RoomNo_;												// 룸 번호(생성번호)

	int WidthIndex_;											// 룸의 크기 가로(타일의 Y인덱스) 인덱스
	int HeightIndex_;											// 룸의 크기 세로(타일의 X인덱스) 인덱스

	int minIndexX_;												// 룸이 차지하는 인덱스 X의 최소 인덱스
	int maxIndexX_;												// 룸이 차지하는 인덱스 Y의 최대 인덱스
	int minIndexY_;												// 룸이 차지하는 인덱스 X의 최소 인덱스
	int maxIndexY_;												// 룸이 차지하는 인덱스 Y의 최대 인덱스
	TileIndex RoomCenterIndex_;									// 룸의 센터 인덱스
	std::vector<TileIndex> AllIndexLists_;						// 현재 생성된 룸의 모든 타일 인덱스
};

// 랜덤맵 벽정보
struct RandomWallInfo
{
	// 타일정보
	TileIndex WallTileIndex_;									// 타일인덱스

	// 타입
	RandomWallBasicType WallBasicType_;							// 벽 or 문
	RandomWallDetailType WallDetailType_;						// 벽 or 문 상세 타입

	// 텍스쳐 정보
	int WallTile1ImageIndex;									// 일반적인 벽은 한개의 렌더링만 가짐
	int WallTile2ImageIndex;									// 특수한 벽은 2개의 렌더링을 가짐
	std::string WallTextureName;								// 벽텍스쳐 이름
	float4 WallTileSize;										// 벽타일 크기
	float4 WallRenderSize;										// 벽타일 렌더링크기
	float4 WallRenderPivotPos;									// 벽타일 렌더링 피벗
};

// 랜덤맵 정보
struct RandomMapInfo
{
	// 복도 관련 정보
	RandomCorridorInfo CorridorInfo_;							// 해당 맵의 복도 목록

	// 룸 관련 정보
	std::vector<RandomRoomInfo> RoomInfo_;						// 해당 맵의 룸 목록

	// 벽 관련 정보(네비게이션 정보로 사용)
	std::vector<RandomWallInfo> WallInfo_;						// 해당 맵의 벽 목록
};
