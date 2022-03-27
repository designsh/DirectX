#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"

#include "BottomStateBar.h"
#include "StatView.h"

// UI 정보 생성
void MainPlayer::CreatePlayerUIInfomation()
{
	// 하단상태바관련 정보 Setting
	//BottomStateBar_

	// 스탯창관련 정보 Setting
	StatView_->SetInfomationString();

	// 스킬창관련 정보 Setting


	// 인벤토리창관련 정보 Setting

	
}

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
