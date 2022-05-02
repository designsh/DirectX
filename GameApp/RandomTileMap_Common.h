#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

enum class RandomMapFloorTileType
{
	NONE = -1,					// 
	ROOM,						// ������ ��
	DOOR,						// ��
	CORRIDOR,					// ����
};

enum class RandomMapWallTileType
{
	NONE = -1,					// ���������� ��
	NORMAL,						// ������ �����ϴ� Ÿ��
	RT_T,						// ���ܹ��� ��(��/���� �߽ɱ��� �����ġ ��)
	RT_B,						// ���ܹ��� ��(��/���� �߽ɱ��� �ϴ���ġ ��)
	RB_L,						// ���ϴܹ��� ��(��/���� �߽ɱ��� �´���ġ ��)
	RB_R,						// ���ϴܹ��� ��(��/���� �߽ɱ��� �����ġ ��)
	BENT_SINGLE,				// ���̴� ��(�ܵ� ���)
	BENT_MULTI,					// ���̴� ��(������ 2���� �̿��� ���)
};
