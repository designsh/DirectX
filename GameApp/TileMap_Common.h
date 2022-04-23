#pragma once

// ��Ÿ��
enum class MapType
{
	FIXED,		// ������(��������)
	RANDOM,		// ������(īŸ�޷���, ī������������)
};

union TileIndex
{
public:
	struct
	{
		int X_;
		int Y_;
	};

	__int64 Index_;

	TileIndex()
		: X_(0), Y_(0)
	{

	}

	TileIndex(int _X, int _Y)
		: X_(_X), Y_(_Y)
	{

	}
};

// �ٴ�Ÿ�� ������Ÿ��
enum class FloorRenderingType
{
	TILE,		// Ÿ�ϸ��
	GRID		// �׸�����
};

// ��Ÿ�� ������Ÿ��
enum class WallRenderingType
{
	TILE1,				// Ÿ�ϸ��(Ÿ��1������ ��ü)
	TILE2,				// Ÿ�ϸ��(Ÿ��2������ ��ü)
	GRID_NOR,			// �׸���(���� �ƴϸ鼭 ���������ϴ� Ÿ��)
	GRID_NONE,			// �׸���(���̸鼭 ���������ϴ� Ÿ��)
	GRID_RT_T,			// �׸�����(RT_T)
	GRID_RT_T_LE,		// �׸�����(RT_T_LE)
	GRID_RT_T_RE,		// �׸�����(RT_T_RE)
	GRID_RT_B,			// �׸�����(RT_B)
	GRID_RT_B_LE,		// �׸�����(RT_B_LE)
	GRID_RT_B_RE,		// �׸�����(RT_B_RE)
	GRID_RB_L,			// �׸�����(RB_L)
	GRID_RB_L_TE,		// �׸�����(RB_L_TE)
	GRID_RB_L_BE,		// �׸�����(RB_L_BE)
	GRID_RB_R,			// �׸�����(RB_R)
	GRID_RB_R_TE,		// �׸�����(RB_R_TE)
	GRID_RB_R_BE,		// �׸�����(RB_R_BE)
	GRID_BENT_SINGLE,	// �׸�����(BENT_SINGLE)
	GRID_BENT_MULTI1,	// �׸�����(BENT_MULTI1)
	GRID_BENT_MULTI2,	// �׸�����(BENT_MULTI2)
};

// ������ƮŸ�� ������Ÿ��(������ ���)
enum class ObjectRenderingType
{
	TILE,				// �ܼ� Ÿ��(�̹����ε����� ����)
	GRID_WALL,			// ��Ÿ���� NONEŸ�԰� ����(������Ʈ �⺻Ÿ�Կ� ����)
	GRID_NORMAL,		// �ƹ��͵� �������������� Ÿ��(������Ʈ �⺻Ÿ�Կ� ����)
	GRID_OBJECT,		// ������Ʈ�� �������Ǿ��ִ� Ÿ��(������Ʈ �⺻Ÿ�Կ� ����)
};

// ��Ÿ�� �⺻Ÿ��(���ⱸ��)
enum class WallBasicType
{
	NONE,		// �������Ǵ��ϳ�, ����������
	NORMAL,		// �������Ǵ������ʰ�, ����������

	// RT_T
	RT_T,			// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) ����
	RT_T_RE,		// ���ܹ������� ������ ��(BENT�� ����Ǵ� ��)
	RT_T_LE,		// ���ϴܹ������� ������ ��(BENT������ RT�� ��)

	// RT_B
	RT_B,			// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) �Ʒ���
	RT_B_RE,		// ���ܹ������� �Ʒ����� ��(BENT�� ��)
	RT_B_LE,		// ���ϴܹ������� �Ʒ����� ��(BENT������ RT�� ��)

	// RB_L
	RB_L,			// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) ���ʺ�
	RB_L_BE,		// ���ϴܹ������� ���ʺ��� ��(BENT������ RB�� ��)
	RB_L_TE,		// �»�ܹ������� ���ʺ��� ��(BENT�� ��)

	// RB_R
	RB_R,			// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) �����ʺ�
	RB_R_BE,		// ���ϴܹ������� �����ʺ��� ��(BENT������ RB�� ��)
	RB_R_TE,		// �»�ܹ������� �����ʺ��� ��(BENT�� ����Ǵ� ��)

	// BENT
	BENT_MULTI,		// ���̴º�(�������� 2�� ������) - �߽ɱ���(0,0) ���ܲ��̴º� => RT_T_RE�� RB_R_TE�� ���������ϴ� ��(��Ƽ������)
	BENT_SINGLE,	// ���̴º�(�������� 1�� ������) - �߽ɱ���(0,0) ���ϴܲ��̴º� => RT_B_LE�� RB_L_BE�� ���������ϴ� ��(�ܵ�������)
};

// ��Ÿ�� ��Ÿ��(���ұ���)
enum class WallDetailType
{
	NORMAL,		// �Ϲݺ�
	DOOR,		// ��
};

// ������ƮŸ�� �⺻Ÿ��
enum class ObjectBasicType
{
	NORMAL,		// ����������
	WALL,		// ������ �Ǵ��ϹǷ� ������Ʈ ��ġ�Ұ�
	OBJECT,		// ������Ʈ�� ��ġ�Ǿ�����
};

// �ٴ�Ÿ�� ����
struct FloorTileInfo
{
	// �ε�������
	int FloorIndexX;
	int FloorIndexY;
	int FloorImageIndex;

	// ������ ����
	std::string FloorTextureName;
	float4 FloorTileSize;
	float4 FloorRenderSize;
	float4 FloorRenderPivotPos;
};

// ��Ÿ�� ����
struct WallTileInfo
{
	// �ε��� �� Ÿ������
	int WallIndexX;
	int WallIndexY;
	int WallTile1ImageIndex;
	int WallTile2ImageIndex;
	WallBasicType WallBasicType;
	WallDetailType WallDetailType;

	// ������ ����
	std::string WallTextureName;
	float4 WallTileSize;
	float4 WallRenderSize;
	float4 WallRenderPivotPos;
};

// ������ƮŸ�� ����
struct ObjectTileInfo
{
	// �ε��� �� Ÿ������
	int ObjectIndexX;
	int ObjectIndexY;
	int ObjectImageIndex;
	ObjectBasicType ObjectBasicType;

	// ������ ����
	std::string ObjectTextureName;
	float4 ObjectTileSize;
	float4 ObjectRenderSize;
	float4 ObjectRenderPivotPos;
};
