#include "PreCompile.h"
#include "MainPlayer.h"

bool MainPlayer::MoveDirectCheck()
{
	// ���콺 Ŭ�� ���� Get



	// UI Ȱ��ȭ ���� üũ





	// ���콺 Ŭ�������� �̿��Ͽ� �̵������� ���ͼ� ���� �̵����� ����
	PrevDirect_ = CurDirect_;

	return true;
}

void MainPlayer::MoveStart()
{
	// �̵������� �����̹Ƿ� ������ �̿��Ͽ� ���� �� �ִϸ��̼� ����
	// ��, ���� �÷��̾ �������� �ʵ����� üũ�Ѵ�.
	// ����, �ٱ� �������� üũ
	if (true == IsRun_)
	{
		ChangeFSMState("Run");
	}
	else
	{
		if (true == IsTown_)
		{
			ChangeFSMState("Walk_Town");
		}
		else
		{
			ChangeFSMState("Walk_Field");
		}
	}
}
