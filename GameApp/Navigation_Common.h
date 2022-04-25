#pragma once

// �ش� ���� �������� ������Ʈ������ �̿��Ͽ� ����
// �������� WALL,NONE Ÿ���̸� �̵��Ұ��������� �Ǵ�
// ������Ʈ������ OBJECT,NONE Ÿ���̸� �̵��Ұ��������� �Ǵ�
enum class NavigationType
{
	NONE = -1,	// ��������
	NOR,		// �̵���������
	WALL,		// �̵��Ұ�����
};

// ���üũ ����
enum Neighbor_Dir
{
	ND_Top,
	ND_RightTop,
	ND_Right,
	ND_RightBottom,
	ND_Bottom,
	ND_LeftBottom,
	ND_Left,
	ND_LeftTop,
	ND_End
};

// �׺���̼� ���� Ÿ��
enum class Nav_Insert_Type
{
	None,
	Open,
	Close
};

// �׺���̼� ����(�������)
struct NavNodeInfo
{
	int	IndexX;
	int	IndexY;
	Nav_Insert_Type NavType;	// �������/�������
	float Dist;

};

// �׺���̼� ������
struct NavInfoManager
{
	std::vector<NavNodeInfo> vecNavInfo;
	std::vector<NavNodeInfo*> vecOpen;
	std::vector<NavNodeInfo*> vecUse;
	int OpenCount;
	int	UseCount;
	int	CountX;
	int	CountY;

	NavNodeInfo* GetNavInfo(int _IndexX, int _IndexY)
	{
		if (_IndexX < 0 || _IndexY < 0 || _IndexX >= CountX || _IndexY >= CountY)
		{
			return nullptr;
		}

		return &vecNavInfo[_IndexY * CountX + _IndexX];
	}

	NavInfoManager()
	{
		OpenCount = 0;
		UseCount = 0;
		CountX = 0;
		CountY = 0;
	}
};
