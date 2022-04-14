#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalValue.h"
#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

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
	InventoryView_->InitInventoryView();

	// ��������޴�â���� ���� Setting
	GameEndMenuView_->InitGameEndMenuView();
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

#pragma region �÷��̾� �κ��丮â

// �÷��̾� �κ��丮â On/Off ����
void MainPlayer::InventoryViewEnabled(bool _Enabled)
{
	if (true == _Enabled)
	{
		IsInventoryView_ = true;
		InventoryView_->On();
		InventoryView_->SetInventoryBoxTileActvie();
	}
	else
	{
		IsInventoryView_ = false;
		InventoryView_->Off();
		InventoryView_->SetInentroyBoxTileInactive();

		// ������ΰ� ��ȣ�ۿ��� ���� �Ǹ�â�� Ȱ��ȭ�Ǿ��ִ� ��� �Ǹ�â�� ��Ȱ��
		if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate())
		{
			GlobalValue::WeaponNPC->GetWeaponShop()->PublicNPCBuySellViewInactive();
		}

		// ��ȭ���ΰ� ��ȣ�ۿ��� ���� �Ǹ�â�� Ȱ��ȭ�Ǿ��ִ� ��� �Ǹ�â�� ��Ȱ��
		if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate())
		{
			GlobalValue::ChandleryNPC->GetChandleryShop()->PublicNPCBuySellViewInactive();
		}
	}
}

#pragma endregion

#pragma region �÷��̾� ����޴�â

void MainPlayer::GameEndMenuViewEnabled(bool _Enabled)
{
	if (true == _Enabled)
	{
		IsGameEndMenu_ = true;
		GameEndMenuView_->On();
	}
	else
	{
		IsGameEndMenu_ = false;
		GameEndMenuView_->Off();
	}
}

#pragma endregion

#pragma region �÷��̾� â��â

// �÷��̾� â��â On/Off ����

#pragma endregion
