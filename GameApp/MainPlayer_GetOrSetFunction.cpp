#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"

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

#pragma endregion

#pragma region UI Flag관련 (GET)

bool MainPlayer::GetIsInventory() const
{
	return IsInventory_;
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

bool MainPlayer::GetIsIsStorehouse() const
{
	return IsStorehouse_;
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
}

void MainPlayer::DelCurrentHP(int _HP)
{
	CurHP_ -= _HP;
}

void MainPlayer::AddCurrentHP(int _HP)
{
	CurHP_ += _HP;
}

// MP
void MainPlayer::SetCurrentMP(int _MP)
{
	CurMP_ = _MP;
}

void MainPlayer::DelCurrentMP(int _MP)
{
	CurMP_ -= _MP;
}

void MainPlayer::AddCurrentMP(int _MP)
{
	CurMP_ += _MP;
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
	IsInventory_ = _Flag;
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
