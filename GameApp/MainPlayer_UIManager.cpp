#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "StatView.h"
#include "SkillView.h"

#pragma region �÷��̾� UI �ʱ����

// UI ���� ����
void MainPlayer::CreatePlayerUIInfomation()
{
	// �ϴܻ��¹ٰ��� ���� Setting
	BottomStateBar_->InitBottomStateBar();

	// ����â���� ���� Setting
	StatView_->InitStatView();

	// ��ųâ���� ���� Setting
	SkillView_->InitSkillView();

	// �κ��丮â���� ���� Setting

	
}

#pragma endregion

#pragma region �÷��̾� ����â

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

#pragma endregion

#pragma region �÷��̾� ��ųâ

// �÷��̾� ��ųâ On/Off ����
void MainPlayer::SkillViewEnabled(bool _Enabled)
{
	if (true == _Enabled)
	{
		IsSkillView_ = true;
		SkillView_->On();
		SkillView_->SkillIconEnabled(true);
	}
	else
	{
		IsSkillView_ = false;
		SkillView_->Off();
		SkillView_->SkillIconEnabled(false);
	}
}


#pragma endregion

// �÷��̾� �κ��丮â On/Off ����


// �÷��̾� â��â On/Off ����


