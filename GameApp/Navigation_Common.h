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

struct NavigationInfo
{
	NavigationType NaviType;
	int IndexX;
	int IndexY;


};
