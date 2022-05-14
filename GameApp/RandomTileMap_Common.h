#pragma once
#include "FixedTileMap_Common.h"

// ������ ���� ���� ���

// ������ ��Ÿ�� �˻����
enum class RandomWallCheckDir
{
	CHK_T,		// X-1 ������ Ÿ��
	CHK_R,		// Y-1 ������ Ÿ��
	CHK_B,		// X+1 ������ Ÿ��
	CHK_L		// Y+1 ������ Ÿ��
};

// ������ Ÿ�� Ÿ��(�ٴ�Ÿ�ϱ���)
enum class RandomMapTileType
{
	NONE,														// Ÿ�Ͼ���
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
	WL_BENT_MULTI,												// ���̴º�(�������� 2�� ������) - �߽ɱ���(0,0) ���ܲ��̴º� => RT_T_RE�� RB_R_TE�� ���������ϴ� ��(��Ƽ������)
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
	// �⺻ ����
	RandomMapTileType TileType_;								// Ÿ��Ÿ��(��)
	int RoomNo_;												// �� ��ȣ(������ȣ)

	// �ؽ��� ����
	int TileImageIndex;											// �� Ÿ���� �ε���

	// �ε��� ����
	int WidthIndex_;											// ���� ũ�� ����(Ÿ���� Y�ε���) �ε���
	int HeightIndex_;											// ���� ũ�� ����(Ÿ���� X�ε���) �ε���
	int minIndexX_;												// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexX_;												// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	int minIndexY_;												// ���� �����ϴ� �ε��� X�� �ּ� �ε���
	int maxIndexY_;												// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
	TileIndex RoomCenterIndex_;									// ���� ���� �ε���
	std::vector<TileIndex> AllIndexLists_;						// ���� ������ ���� ��� Ÿ�� �ε���

	// �Ÿ� ���� ����
	int TheFarthestRoomNo_;										// ���� ��� ���� �ָ� �������ִ� ���ȣ
																// �÷��̾� ������ġ�� ����ָ� �������ִ� ���� ���������� ���� ����
};

// ������ ������
struct RandomWallInfo
{
	// Ÿ�� �⺻����
	TileIndex WallTileIndex_;									// Ÿ���ε���

	// Ÿ�� Ÿ�԰���(T,R,B,L)
	std::vector<bool> SearchTileFlag_;							// ���� ���� Ÿ�ϱ��� 4���� Ÿ���� üũ�Ͽ� 
																// �ٴ�Ÿ�� ���翩�ο� ���� Flag�� ����

	RandomWallBasicType WallBasicType_;							// �� or ��
	RandomWallDetailType WallDetailType_;						// �� or �� �� Ÿ��

	// Ÿ�� �ؽ��� ����
	bool WallMultiRender_;
	int WallTile1ImageIndex_;									// �Ϲ����� ���� �Ѱ��� �������� ����
	int WallTile2ImageIndex_;									// Ư���� ���� 2���� �������� ����
	std::string WallTextureName_;								// ���ؽ��� �̸�
	float4 WallTileSize_;										// ��Ÿ�� ũ��
	float4 WallRenderSize_;										// ��Ÿ�� ������ũ��
	float4 WallRenderPivotPos_;									// ��Ÿ�� ������ �ǹ�
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
