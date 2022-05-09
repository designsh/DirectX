#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

// �� �����ε��� ���� ����
enum class RoomCenterDirType
{
	DIRTC_T,												// ���� ���ͱ��� ���
	DIRTC_B,												// ���� ���ͱ��� �ϴ�
	DIRTC_L,												// ���� ���ͱ��� �´�
	DIRTC_R													// ���� ���ͱ��� ���
};

// ������ Ÿ�� Ÿ��(�ٴ�Ÿ�ϱ���)
enum class RandomMapTileType
{
	NONE = -1,												// 
	ROOM,													// ��
	DOOR,													// ��
	CORRIDOR,												// ����
	WALL,													// ��
};

// ������ �� Ÿ��
enum class RandomMapDoorType
{
	NONE = -1,
	RT_T_L,													// �� ���ͱ��� ��� ���ܹ��� ���� ���� �ؽ���
	RT_T_R,													// �� ���ͱ��� ��� ���ܹ��� ���� ������ �ؽ���
	RT_B_L,													// �� ���ͱ��� �ϴ� ���ܹ��� ���� ���� �ؽ���
	RT_B_R,													// �� ���ͱ��� �ϴ� ���ܹ��� ���� ������ �ؽ���
	RB_L_T,													// �� ���ͱ��� �´� ���ϴܹ��� ���� ���� �ؽ���
	RB_L_B,													// �� ���ͱ��� �´� ���ϴܹ��� ���� �Ʒ��� �ؽ���
	RB_R_T,													// �� ���ͱ��� ��� ���ϴܹ��� ���� ���� �ؽ���
	RB_R_B,													// �� ���ͱ��� ��� ���ϴܹ��� ���� �Ʒ��� �ؽ���
};

// ������ ��������
struct RandomCorridorInfo
{
	RandomMapTileType CorridorType_;						// Ÿ��Ÿ��(����)
	std::vector<TileIndex> AllIndexLists_;					// ���� ������ ������ ��� Ÿ�� �ε���(�������뵵)
};

// ������ ������
struct RandomRoomInfo
{
	RandomMapTileType TileType_;							// Ÿ��Ÿ��(��)
	int RoomNo_;											// �� ��ȣ(������ȣ)

	int WidthIndex_;										// ���� ũ�� ����(Ÿ���� Y�ε���) �ε���
	int HeightIndex_;										// ���� ũ�� ����(Ÿ���� X�ε���) �ε���

	int minIndexX_;											// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexX_;											// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	int minIndexY_;											// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexY_;											// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	TileIndex RoomCenterIndex_;								// ���� ���� �ε���
};

// ������ ������
struct RandomDoorInfo
{
	int IndexX;												// X �ε���
	int IndexY;												// Y �ε���

	RandomMapTileType TileType_;							// Ÿ��Ÿ��(��)
	int Direction_;											// �� ���ͱ��� ������ ��ġ(��/��/��/��)
	RandomMapDoorType DoorType_;							// ���� ������ Ÿ��
};

// ������ ����
struct RandomMapInfo
{
	// ���� ���� ����
	RandomCorridorInfo CorridorInfo_;						// �ش� ���� ���� ���

	// �� ���� ����
	std::vector<RandomRoomInfo> RoomInfo_;					// �ش� ���� �� ���

	// �� ���� ����(�׺���̼� ������ ���)
	std::vector<WallTileInfo> WallInfo_;					// �ش� ���� �� ���

	// �� ���� ����
	std::vector<RandomDoorInfo> DoorInfo_;					// �ش� ���� �� ���
};

// �ٴ�Ÿ������
struct RandomFloorTileInfo
{
	RandomMapTileType TileType;								// �ٴ�Ÿ�� Ÿ��(��, ��, ����)
	int IndexX;												// 
	int IndexY;												// 
	int TileImageIndex;										// 

	std::string TextureName;								// 
	float4 TileSize;										// 
	float4 RenderSize;										// 
	float4 RenderPivotPos;									// 
};

// ��Ÿ������
struct RandomWallTileInfo
{
	// �ε��� �� Ÿ������
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
