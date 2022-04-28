#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalValue.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

#include "Storehouse.h"
#include "StoreView.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

#pragma region 플레이어 UI 초기셋팅

// UI 정보 생성
void MainPlayer::CreatePlayerUIInfomation()
{
	// 하단상태바관련 정보 Setting
	BottomStateBar_->InitBottomStateBar();

	// 스탯창관련 정보 Setting
	StatView_->InitStatView();

	// 스킬창관련 정보 Setting
	SkillView_->InitSkillView();

	// 인벤토리창관련 정보 Setting
	InventoryView_->InitInventoryView();

	// 게임종료메뉴창관련 정보 Setting
	GameEndMenuView_->InitGameEndMenuView();
}

#pragma endregion

#pragma region 플레이어 상태창

// 플레이어 상태창 On/Off 관련
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

#pragma region 플레이어 스킬창

// 플레이어 스킬창 On/Off 관련
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

#pragma region 플레이어 인벤토리창

// 플레이어 인벤토리창 On/Off 관련
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

		// 현재 플레이어가 속한 레벨이 Town레벨일때
		if (true == IsTown_)
		{
			// 무기상인과 상호작용을 통해 판매창이 활성화되어있는 경우 판매창도 비활성
			if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate())
			{
				GlobalValue::WeaponNPC->GetWeaponShop()->PublicNPCBuySellViewInactive();
			}

			// 잡화상인과 상호작용을 통해 판매창이 활성화되어있는 경우 판매창도 비활성
			if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate())
			{
				GlobalValue::ChandleryNPC->GetChandleryShop()->PublicNPCBuySellViewInactive();
			}

			// 창고와 상호작용을 통해 창고창이 활성화되어있는 경우 창고창도 비활성
			if (nullptr != GlobalValue::Storehouse && true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
			{
				GlobalValue::Storehouse->GetStoreView()->StoreViewOff();
			}
		}
	}
}

#pragma endregion

#pragma region 플레이어 종료메뉴창

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

#pragma region 플레이어 창고창

// 플레이어 창고창 On/Off 관련

#pragma endregion

#pragma region 인벤토리창 아이템배치 체크
// 외부접근 인벤토리체크하여 해당 아이템 배치가능한지 체크
bool MainPlayer::InventoryViewItemArrageCheckOn(const float4& _ItemScale, const std::string& _ItemName)
{
	return InventoryView_->InventoryArrangeTileCheckOn(_ItemScale, _ItemName);
}

#pragma endregion
