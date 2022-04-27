#include "PreCompile.h"
#include "MainPlayer.h"

// ���� ������ ���� �ؽ���, �ִϸ��̼�, FSM, ZOrder ����...
void MainPlayer::MainPlayerinitialization()
{
	// �÷��̾� �ִϸ��̼� ���� �̹��� Cut
	AllAnimationCut();

	// �÷��̾� �ִϸ��̼� ���� ����
	CreateAnimation();

	// �÷��̾� �浹ü ���� ����
	CreateCollision();

	// �÷��̾� FSM ���� ���� ����
	CreatePlayerStateFSM();
	
	// ���⺰ ������ ���� ����
	CreateDirectRenderOrderType();

	// ��� ���� �Ϸ� �� ȣ��Ǹ�, �ʱ� ���۽� �����׸� ó��
	MainPlayerStartSetting();
}

// ���� ���۽� �ʱ�ȭ �Ǿ���ϴ� �׸��....
void MainPlayer::MainPlayerStartSetting()
{
	// FSM �ʱ� ���� ����
	State_.ChangeState("Natural_Town");

	SettingRender();
}

// �ʱ� ������ ����
void MainPlayer::SettingRender()
{
	
}
