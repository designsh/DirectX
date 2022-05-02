#pragma once
#include "FixedTileMap_Common.h"

// 랜덤맵 공통 정보 헤더

enum class RandomMapFloorTileType
{
	NONE = -1,					// 
	ROOM,						// 던전내 방
	DOOR,						// 문
	CORRIDOR,					// 복도
};

enum class RandomMapWallTileType
{
	NONE = -1,					// 렌더링없는 벽
	NORMAL,						// 정보만 존재하는 타일
	RT_T,						// 우상단방향 벽(룸/복도 중심기준 상단위치 벽)
	RT_B,						// 우상단방향 벽(룸/복도 중심기준 하단위치 벽)
	RB_L,						// 우하단방향 벽(룸/복도 중심기준 좌단위치 벽)
	RB_R,						// 우하단방향 벽(룸/복도 중심기준 우단위치 벽)
	BENT_SINGLE,				// 꺽이는 벽(단독 기둥)
	BENT_MULTI,					// 꺽이는 벽(렌더러 2개를 이용한 기둥)
};
