#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

void MainPlayer::ChangeCheckProcess()
{
	// 현재 상태 전환 전이기 때문에 현재상태의 아이템 착용상태를 체크하여
	// On해야하는 렌더러를 결정한다.
	int Index = 0;
	std::map<RendererPartType, bool>::iterator StartIter = IsItemEquipState_.begin();
	std::map<RendererPartType, bool>::iterator EndIter = IsItemEquipState_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 아이템착용중이라면 HVY_ 활성화, LIT_ 비활성화
		if (true == (*StartIter).second)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
		}
		else // 위와 반대의 경우
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();
		}

		++Index;
	}
}

// ========================== 상태 변경 ========================= //
void MainPlayer::ChangeFSMState(std::string _StateName)
{
	// 이전상태와 현재상태가 다를때 체크해야하는 사항체크
	if (PrevState_ != CurState_)
	{
		ChangeCheckProcess();
	}

	State_.ChangeState(_StateName);
}

// ========================== 마을 관련 ========================= //
// ============================ 대기 ============================ //
StateInfo MainPlayer::StartTownNatural(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TN;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);

	// 관련 사운드 시작
	

	// 기타
	
	return StateInfo();
}

StateInfo MainPlayer::UpdateTownNatural(StateInfo _state)
{
	// 현재 플레이어가 마을인지 필드인지 체크



	// 이동 체크





	return StateInfo();
}

// ============================ 걷기 ============================ //
StateInfo MainPlayer::StartTownWalk(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TW;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateTownWalk(StateInfo _state)
{

	return StateInfo();
}

// ========================== 필드 관련 ========================== //

// ============================ 대기 ============================ //
StateInfo MainPlayer::StartFieldNatural(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_NU;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateFieldNatural(StateInfo _state)
{

	return StateInfo();
}

// ============================ 걷기 ============================ //
StateInfo MainPlayer::StartFieldWalk(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_WL;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateFieldWalk(StateInfo _state)
{

	return StateInfo();
}

// ========================== 공통 관련 ========================== //

// ========================== 공격모션1 ========================== //
StateInfo MainPlayer::StartAttack1(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A1;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack1(StateInfo _state)
{

	return StateInfo();
}

// ========================== 공격모션2 ========================== //
StateInfo MainPlayer::StartAttack2(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A2;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack2(StateInfo _state)
{

	return StateInfo();
}

// ========================== 방어모션 =========================== //
StateInfo MainPlayer::StartBlock(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_BL;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateBlock(StateInfo _state)
{

	return StateInfo();
}

// ========================== 피격모션 =========================== //
StateInfo MainPlayer::StartGetHit(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_GH;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateGetHit(StateInfo _state)
{

	return StateInfo();
}

// ========================== 킥모션 ============================ //
StateInfo MainPlayer::StartKick(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_KK;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateKick(StateInfo _state)
{

	return StateInfo();
}

// ========================== 뛰기모션 =========================== //
StateInfo MainPlayer::StartRun(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_RN;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateRun(StateInfo _state)
{

	return StateInfo();
}

// ======================== 스킬공격모션 ========================= //
StateInfo MainPlayer::StartSkillAttack(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_S1;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateSkillAttack(StateInfo _state)
{

	return StateInfo();
}

// ======================= 스킬캐스팅모션 ======================== //
StateInfo MainPlayer::StartSkillCasting(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_SC;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateSkillCasting(StateInfo _state)
{

	return StateInfo();
}

// ========================== 사망 관련 ========================== //

// ========================== 시체모션 =========================== //
StateInfo MainPlayer::StartDead(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DD;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateDead(StateInfo _state)
{

	return StateInfo();
}

// ========================== 사망모션 =========================== //
StateInfo MainPlayer::StartDeath(StateInfo _state)
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DT;

	// 애니메이션변경
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateDeath(StateInfo _state)
{

	return StateInfo();
}
