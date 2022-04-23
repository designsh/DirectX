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
