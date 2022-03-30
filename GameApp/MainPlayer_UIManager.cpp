#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "StatView.h"

// UI ���� ����
void MainPlayer::CreatePlayerUIInfomation()
{
	// �ϴܻ��¹ٰ��� ���� Setting
	BottomStateBar_->InitBottomStateBar();

	// ����â���� ���� Setting
	StatView_->InitStatView();

	// ��ųâ���� ���� Setting


	// �κ��丮â���� ���� Setting

	
}

// �÷��̾� ����â On/Off ����
void MainPlayer::StateViewEnabled(bool _Enabled)
{
	if (true == _Enabled)
	{
		IsStateView_ = true;
		StatView_->On();
	}
	else
	{
		IsStateView_ = false;
		StatView_->Off();
	}
}
