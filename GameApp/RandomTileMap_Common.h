#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

// ������ �� ��ġ Ÿ��(�뼾�ͱ���)
enum class DoorPositionType
{
	DIRTC_T,										// ���� ���ͱ��� ���
	DIRTC_B,										// ���� ���ͱ��� �ϴ�
	DIRTC_L,										// ���� ���ͱ��� �´�
	DIRTC_R											// ���� ���ͱ��� ���
};

// ������ ���� ����
enum class CorridorDirType
{
	RT,
	RB
};

// ������ Ÿ�� Ÿ��(�ٴ�Ÿ�ϱ���)
enum class RandomMapTileType
{
	NONE = -1,										// 
	ROOM,											// ��
	DOOR,											// ��
	CORRIDOR,										// ����
	WALL,											// ��
};

// ������ �� Ÿ��
enum class RandomMapDoorType
{
	NONE = -1,
	RT_T_L,											// �� ���ͱ��� ��� ���ܹ��� ���� ���� �ؽ���
	RT_T_R,											// �� ���ͱ��� ��� ���ܹ��� ���� ������ �ؽ���
	RT_B_L,											// �� ���ͱ��� �ϴ� ���ܹ��� ���� ���� �ؽ���
	RT_B_R,											// �� ���ͱ��� �ϴ� ���ܹ��� ���� ������ �ؽ���
	RB_L_T,											// �� ���ͱ��� �´� ���ϴܹ��� ���� ���� �ؽ���
	RB_L_B,											// �� ���ͱ��� �´� ���ϴܹ��� ���� �Ʒ��� �ؽ���
	RB_R_T,											// �� ���ͱ��� ��� ���ϴܹ��� ���� ���� �ؽ���
	RB_R_B,											// �� ���ͱ��� ��� ���ϴܹ��� ���� �Ʒ��� �ؽ���
};

// ������ ��������
struct RandomCorridorInfo
{
	CorridorDirType DirType_;						// ���� �������(����/���ϴ�)
};

// ������ ������
struct RandomDoorInfo
{
	int IndexX;										// X �ε���
	int IndexY;										// Y �ε���

	RandomMapTileType TileType_;					// Ÿ��Ÿ��(��)
	int Direction_;									// �� ���ͱ��� ������ ��ġ(��/��/��/��)
	RandomMapDoorType DoorType_;					// ���� ������ Ÿ��
};

// ������ ������
struct RandomRoomInfo
{
	RandomMapTileType TileType_;					// Ÿ��Ÿ��(��)
	int RoomNo_;									// �� ��ȣ(������ȣ)

	// ���� ������ ���� ����
	int minIndexX_;									// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexX_;									// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	int minIndexY_;									// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexY_;									// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	TileIndex RoomCenterIndex_;						// ���� ���� �ε���
	int WidthIndex_;								// ���� ũ�� ����(Ÿ���� Y�ε���) �ε���
	int HeightIndex_;								// ���� ũ�� ����(Ÿ���� X�ε���) �ε���
	
	//std::vector<DoorPositionType> DoorInfo_;		// ���� ������ �� ����
};

// ������ ����
struct RandomMapInfo
{
	// ������
	int minIndexX_;									// �������� �ּ� X�ε���
	int maxIndexX_;									// �������� �ִ� X�ε���
	int minIndexY_;									// �������� �ּ� Y�ε���
	int maxIndexY_;									// �������� �ִ� Y�ε���

	// �� ���� ����
	std::vector<RandomRoomInfo> RoomInfo_;			// �ش� ���� �� ���

	// ���� ���� ����


	// �� ���� ����
	// => ��ũ���Ǻ����� -> ���Ǻ��������� -> �����Ǻ���������
	std::vector<WallTileInfo> WallInfo_;			// �ش� ���� ��üũ�⸸ŭ �����Ǵ� ������

	// �� ���� ����

};

// �ٴ�Ÿ������
struct RandomFloorTileInfo
{
	RandomMapTileType TileType;			// �ٴ�Ÿ�� Ÿ��(��, ��, ����)
	int IndexX;							// 
	int IndexY;							// 
	int TileImageIndex;					// 

	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};

// ��Ÿ������
struct RandomWallTileInfo
{
	// �ε��� �� Ÿ������
	WallBasicType BasicType;			// 
	WallDetailType DetailType;			// 
	int IndexX;							// 
	int IndexY;							// 
	int Tile1ImageIndex;				// 
	int Tile2ImageIndex;				// 

	std::string TextureName;			// 
	float4 TileSize;					// 
	float4 RenderSize;					// 
	float4 RenderPivotPos;				// 
};
