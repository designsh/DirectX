#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

// ������ Ÿ�� Ÿ��(�ٴ�Ÿ�ϱ���)
enum class RandomMapTileType
{
	CORRIDOR,													// ����
	ROOM,														// ��
};

// �� �⺻ Ÿ��
enum class RandomWallBasicType
{
	WALL,														// �Ϲݺ�
	DOOR,														// ��
};

// ��Ÿ�� ��Ÿ��(����Ÿ��)
enum class RandomWallDetailType
{
	NONE,														// �������Ǵ��ϳ�, ����������
	NORMAL,														// �������Ǵ������ʰ�, ����������

	// �⺻Ÿ���� ���϶�
	WL_RT_T,													// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) ����
	WL_RT_T_RE,													// ���ܹ������� ������ ��(BENT�� ����Ǵ� ��)
	WL_RT_T_LE,													// ���ϴܹ������� ������ ��(BENT������ RT�� ��)
	WL_RT_B,													// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) �Ʒ���
	WL_RT_B_RE,													// ���ܹ������� �Ʒ����� ��(BENT�� ��)
	WL_RT_B_LE,													// ���ϴܹ������� �Ʒ����� ��(BENT������ RT�� ��)
	WL_RB_L,													// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) ���ʺ�
	WL_RB_L_BE,													// ���ϴܹ������� ���ʺ��� ��(BENT������ RB�� ��)
	WL_RB_L_TE,													// �»�ܹ������� ���ʺ��� ��(BENT�� ��)
	WL_RB_R,													// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) �����ʺ�
	WL_RB_R_BE,													// ���ϴܹ������� �����ʺ��� ��(BENT������ RB�� ��)
	WL_RB_R_TE,													// �»�ܹ������� �����ʺ��� ��(BENT�� ����Ǵ� ��)
	WL_BENT_MULTI1,												// ���̴º�(�������� 2�� ������) - �߽ɱ���(0,0) ���ܲ��̴º� => RT_T_RE�� RB_R_TE�� ���������ϴ� ��(��Ƽ������)
	WL_BENT_MULTI2,												// ���̴º�(�������� 2�� ������) - �߽ɱ���(0,0) ���ϴܲ��̴º� => RT_T_RE�� RB_R_TE�� ���������ϴ� ��(��Ƽ������)
	WL_BENT_SINGLE,												// ���̴º�(�������� 1�� ������) - �߽ɱ���(0,0) ���ϴܲ��̴º� => RT_B_LE�� RB_L_BE�� ���������ϴ� ��(�ܵ�������)

	// �⺻Ÿ���� ���϶�
	DR_RT_L,													// �� ���ͱ��� ��� ���ܹ��� ���� ���� �ؽ���
	DR_RT_R,													// �� ���ͱ��� ��� ���ܹ��� ���� ������ �ؽ���
	DR_RB_T,													// �� ���ͱ��� �´� ���ϴܹ��� ���� ���� �ؽ���
	DR_RB_B,													// �� ���ͱ��� �´� ���ϴܹ��� ���� �Ʒ��� �ؽ���
};

// ������ ��������
struct RandomCorridorInfo
{
	RandomMapTileType CorridorType_;							// Ÿ��Ÿ��(����)
	int TileImageIndex;											// ���� Ÿ���� �ε���
	std::vector<TileIndex> AllIndexLists_;						// ���� ������ ������ ��� Ÿ�� �ε���(�������뵵)
};

// ������ ������
struct RandomRoomInfo
{
	RandomMapTileType TileType_;								// Ÿ��Ÿ��(��)
	int RoomNo_;												// �� ��ȣ(������ȣ)

	int TileImageIndex;											// �� Ÿ���� �ε���

	int WidthIndex_;											// ���� ũ�� ����(Ÿ���� Y�ε���) �ε���
	int HeightIndex_;											// ���� ũ�� ����(Ÿ���� X�ε���) �ε���

	int minIndexX_;												// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexX_;												// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	int minIndexY_;												// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexY_;												// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	TileIndex RoomCenterIndex_;									// ���� ���� �ε���
	std::vector<TileIndex> AllIndexLists_;						// ���� ������ ���� ��� Ÿ�� �ε���
};

// ������ ������
struct RandomWallInfo
{
	// Ÿ������
	TileIndex WallTileIndex_;									// Ÿ���ε���

	// Ÿ��
	RandomWallBasicType WallBasicType_;							// �� or ��
	RandomWallDetailType WallDetailType_;						// �� or �� �� Ÿ��

	// �ؽ��� ����
	int WallTile1ImageIndex;									// �Ϲ����� ���� �Ѱ��� �������� ����
	int WallTile2ImageIndex;									// Ư���� ���� 2���� �������� ����
	std::string WallTextureName;								// ���ؽ��� �̸�
	float4 WallTileSize;										// ��Ÿ�� ũ��
	float4 WallRenderSize;										// ��Ÿ�� ������ũ��
	float4 WallRenderPivotPos;									// ��Ÿ�� ������ �ǹ�
};

// ������ ����
struct RandomMapInfo
{
	// �� �ؽ��İ���
	std::string FloorTileTextureName_;							// �ٴ�Ÿ�� �ؽ��ĸ�
	std::string WallTileTextureName_;							// ��Ÿ�� �ؽ��ĸ�

	// ���� ���� ����
	RandomCorridorInfo CorridorInfo_;							// �ش� ���� ���� ���

	// �� ���� ����
	std::vector<RandomRoomInfo> RoomInfo_;						// �ش� ���� �� ���

	// �� ���� ����(�׺���̼� ������ ���)
	std::vector<RandomWallInfo> WallInfo_;						// �ش� ���� �� ���
};
