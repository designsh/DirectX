#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"

// ======================================================= GET FUNCTION ======================================================= //

#pragma region 상태 Flag관련(GET)

bool MainPlayer::GetIsTown() const
{
	return IsTown_;
}

bool MainPlayer::GetIsRun() const
{
	return IsRun_;
}

bool MainPlayer::GetIsMove() const
{
	return IsMove_;
}

bool MainPlayer::GetIsDefaultZOrderChangeChk() const
{
	return IsDefaultZOrderChangeChk_;
}

bool MainPlayer::GetIsFrameZOrderChangeChk() const
{
	return IsFrameZOrderChangeChk_;
}

#pragma endregion

#pragma region 상태관련(GET)

int MainPlayer::GetCurrentHP() const
{
	return CurHP_;
}

int MainPlayer::GetCurrentMP() const
{
	return CurMP_;
}

int MainPlayer::GetPrevEXP() const
{
	return PrevEXP_;
}

int MainPlayer::GetCurrentEXP() const
{
	return CurEXP_;
}

int MainPlayer::GetPrevLevel() const
{
	return PrevLevel_;
}

int MainPlayer::GetCurrentLevel() const
{
	return CurLevel_;
}

int MainPlayer::GetCurHaveGold() const
{
	return HaveGold_;
}

#pragma endregion

#pragma region UI Flag관련 (GET)

bool MainPlayer::GetIsInventory() const
{
	return IsInventoryView_;
}

bool MainPlayer::GetIsStateView() const
{
	return IsStateView_;
}

bool MainPlayer::GetIsSkillView() const
{
	return IsSkillView_;
}

bool MainPlayer::GetIsRightSkillList() const
{
	return IsRightSkillList_;
}

bool MainPlayer::GetIsLeftSkillList() const
{
	return IsLeftSkillList_;
}

bool MainPlayer::GetIsStorehouse() const
{
	return IsStorehouse_;
}

bool MainPlayer::GetIsGameEndMenu() const
{
	return IsGameEndMenu_;
}

#pragma endregion

#pragma region UI 객체관련(GET)

BottomStateBar* MainPlayer::GetBottomStateBar() const
{
	return BottomStateBar_;
}

StatView* MainPlayer::GetStatView() const
{
	return StatView_;
}

SkillView* MainPlayer::GetSkillView() const
{
	return SkillView_;
}

InventoryView* MainPlayer::GetInventoryView() const
{
	return InventoryView_;
}

GameEndMenuView* MainPlayer::GetGameEndMenuView() const
{
	return GameEndMenuView_;
}

#pragma endregion

// ======================================================= SET FUNCTION ======================================================= //

#pragma region 상태 Flag관련(SET)

void MainPlayer::SetIsTown(bool _Flag)
{
	IsTown_ = _Flag;
}

void MainPlayer::SetIsRun(bool _Flag)
{
	IsRun_ = _Flag;
}

void MainPlayer::SetIsMove(bool _Flag)
{
	IsMove_ = _Flag;
}

void MainPlayer::SetIsDefaultZOrderChangeChk(bool _Flag)
{
	IsDefaultZOrderChangeChk_ = _Flag;
}

void MainPlayer::SetIsFrameZOrderChangeChk(bool _Flag)
{
	IsFrameZOrderChangeChk_ = _Flag;
}

#pragma endregion

#pragma region 상태관련(SET)

// HP
void MainPlayer::SetCurrentHP(int _HP)
{
	CurHP_ = _HP;
	BottomStateBar_->GetHPControl()->HPConsumption(static_cast<float>(CurHP_) * 0.01f);
}

void MainPlayer::DelCurrentHP(int _HP)
{
	CurHP_ -= _HP;
	BottomStateBar_->GetHPControl()->HPConsumption(static_cast<float>(CurHP_) * 0.01f);
}

void MainPlayer::AddCurrentHP(int _HP)
{
	CurHP_ += _HP;
	BottomStateBar_->GetHPControl()->HPConsumption(static_cast<float>(CurHP_) * 0.01f);
}

void MainPlayer::AllCurrentHPRecovery()
{
	CurHP_ = 100;
	BottomStateBar_->GetHPControl()->AllHPRecovery();
}

// MP
void MainPlayer::SetCurrentMP(int _MP)
{
	CurMP_ = _MP;
	BottomStateBar_->GetMPControl()->MPConsumption(static_cast<float>(CurMP_) * 0.01f);
}

void MainPlayer::DelCurrentMP(int _MP)
{
	CurMP_ -= _MP;
	BottomStateBar_->GetMPControl()->MPConsumption(static_cast<float>(CurMP_) * 0.01f);
}

void MainPlayer::AddCurrentMP(int _MP)
{
	CurMP_ += _MP;
	BottomStateBar_->GetMPControl()->MPConsumption(static_cast<float>(CurMP_) * 0.01f);
}

void MainPlayer::AllCurrentMPRecovery()
{
	CurMP_ = 100;
	BottomStateBar_->GetMPControl()->AllMPRecovery();
}

// EXP
void MainPlayer::SetPrevEXP(int _EXP)
{
	PrevEXP_ = _EXP;
}

void MainPlayer::SetCurrentEXP(int _EXP)
{
	CurEXP_ = _EXP;
}

// LEVEL
void MainPlayer::SetPrevLevel(int _LEVEL)
{
	PrevLevel_ = _LEVEL;
}

void MainPlayer::SetCurrentLevel(int _LEVEL)
{
	CurLevel_ = _LEVEL;
}

void MainPlayer::SetLevelUP()
{
	PrevLevel_ = CurLevel_;
	CurLevel_ += 1;

	// 플레이어 정보 갱신
	MainPlayerInfomation::GetInst().PlayerLevelUP();
}

#pragma endregion

#pragma region UI Flag관련(SET)

void MainPlayer::SetIsInventory(bool _Flag)
{
	IsInventoryView_ = _Flag;
}

void MainPlayer::SetIsStateView(bool _Flag)
{
	IsStateView_ = _Flag;
}

void MainPlayer::SetIsSkillView(bool _Flag)
{
	IsSkillView_ = _Flag;
}

void MainPlayer::SetIsRightSkillList(bool _Flag)
{
	IsRightSkillList_ = _Flag;
}

void MainPlayer::SetIsLeftSkillList(bool _Flag)
{
	IsLeftSkillList_ = _Flag;
}

void MainPlayer::SetIsIsStorehouse(bool _Flag)
{
	IsStorehouse_ = _Flag;
}

#pragma endregion
