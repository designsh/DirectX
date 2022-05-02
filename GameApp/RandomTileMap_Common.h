#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

enum class RandomMapFloorTileType
{
	NONE = -1,							// 
	ROOM,								// ��
	DOOR,								// ��
	CORRIDOR,							// ����
};

enum class RandomMapWallTileType
{
	NONE = -1,							// ��Ÿ�Ϸ� ����ϳ� �����������ʴ� ��Ÿ��
	NORMAL,								// ������ �����ϴ� ��Ÿ��
	RT_T,								// ���ܹ��� ��(��/���� �߽ɱ��� �����ġ ��)
	RT_B,								// ���ܹ��� ��(��/���� �߽ɱ��� �ϴ���ġ ��)
	RB_L,								// ���ϴܹ��� ��(��/���� �߽ɱ��� �´���ġ ��)
	RB_R,								// ���ϴܹ��� ��(��/���� �߽ɱ��� �����ġ ��)
	BENT_SINGLE,						// ���̴� ��(�ܵ� ���)
	BENT_MULTI,							// ���̴� ��(������ 2���� �̿��� ���)
};

// �ٴ�Ÿ������
struct RandomFloorTileInfo
{
	RandomMapFloorTileType TileType;	// �ٴ�Ÿ�� Ÿ��(��, ��, ����)
	int IndexX;							// 
	int IndexY;							// 
	int TileImageIndex;					// 

	// ������ ����
	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};

// ��Ÿ������
struct RandomWallTileInfo
{
	// �ε��� �� Ÿ������
	RandomMapWallTileType TileType;		// ��Ÿ�� Ÿ��(���⺰ Ÿ��)
	int IndexX;							// 
	int IndexY;							// 
	int Tile1ImageIndex;				// 
	int Tile2ImageIndex;				// 

	// ������ ����
	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};
