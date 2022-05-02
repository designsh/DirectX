#pragma once
#include "FixedTileMap_Common.h"

// 랜덤맵 공통 정보 헤더

enum class RandomMapFloorTileType
{
	NONE = -1,							// 
	ROOM,								// 방
	DOOR,								// 문
	CORRIDOR,							// 복도
};

enum class RandomMapWallTileType
{
	NONE = -1,							// 벽타일로 취급하나 렌더링하지않는 벽타일
	NORMAL,								// 정보만 존재하는 벽타일
	RT_T,								// 우상단방향 벽(룸/복도 중심기준 상단위치 벽)
	RT_B,								// 우상단방향 벽(룸/복도 중심기준 하단위치 벽)
	RB_L,								// 우하단방향 벽(룸/복도 중심기준 좌단위치 벽)
	RB_R,								// 우하단방향 벽(룸/복도 중심기준 우단위치 벽)
	BENT_SINGLE,						// 꺽이는 벽(단독 기둥)
	BENT_MULTI,							// 꺽이는 벽(렌더러 2개를 이용한 기둥)
};

// 바닥타일정보
struct RandomFloorTileInfo
{
	RandomMapFloorTileType TileType;	// 바닥타일 타입(방, 문, 복도)
	int IndexX;							// 
	int IndexY;							// 
	int TileImageIndex;					// 

	// 렌더링 정보
	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};

// 벽타일정보
struct RandomWallTileInfo
{
	// 인덱스 및 타입정보
	RandomMapWallTileType TileType;		// 벽타일 타입(방향별 타입)
	int IndexX;							// 
	int IndexY;							// 
	int Tile1ImageIndex;				// 
	int Tile2ImageIndex;				// 

	// 렌더링 정보
	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};
