#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "StatView.h"
#include "SkillView.h"

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

// 플레이어 인벤토리창 On/Off 관련


// 플레이어 창고창 On/Off 관련


