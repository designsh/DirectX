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
void MainPlayer::StartTownNatural()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TN;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 관련 사운드 시작


	// 기타
}

void MainPlayer::UpdateTownNatural()
{




}

void MainPlayer::EndTownNatural()
{

}

// ============================ 걷기 ============================ //
void MainPlayer::StartTownWalk()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TW;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateTownWalk()
{
}

void MainPlayer::EndTownWalk()
{
}

// ========================== 필드 관련 ========================== //

// ============================ 대기 ============================ //
void MainPlayer::StartFieldNatural()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_NU;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateFieldNatural()
{

}

void MainPlayer::EndFieldNatural()
{

}

// ============================ 걷기 ============================ //
void MainPlayer::StartFieldWalk()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_WL;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateFieldWalk()
{

}

void MainPlayer::EndFieldWalk()
{

}

// ========================== 공통 관련 ========================== //

// ========================== 공격모션1 ========================== //
void MainPlayer::StartAttack1()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A1;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateAttack1()
{

}

void MainPlayer::EndAttack1()
{

}

// ========================== 공격모션2 ========================== //
void MainPlayer::StartAttack2()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A2;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateAttack2()
{

}

void MainPlayer::EndAttack2()
{

}

// ========================== 방어모션 =========================== //
void MainPlayer::StartBlock()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_BL;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateBlock()
{

}

void MainPlayer::EndBlock()
{

}

// ========================== 피격모션 =========================== //
void MainPlayer::StartGetHit()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_GH;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateGetHit()
{

}

void MainPlayer::EndGetHit()
{

}

// ========================== 킥모션 ============================ //
void MainPlayer::StartKick()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_KK;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateKick()
{

}

void MainPlayer::EndKick()
{

}

// ========================== 뛰기모션 =========================== //
void MainPlayer::StartRun()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_RN;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateRun()
{

}

void MainPlayer::EndRun()
{

}

// ======================== 스킬공격모션 ========================= //
void MainPlayer::StartSkillAttack()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_S1;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateSkillAttack()
{

}

void MainPlayer::EndSkillAttack()
{

}

// ======================= 스킬캐스팅모션 ======================== //
void MainPlayer::StartSkillCasting()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_SC;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateSkillCasting()
{

}

void MainPlayer::EndSkillCasting()
{

}

// ========================== 사망 관련 ========================== //

// ========================== 시체모션 =========================== //
void MainPlayer::StartDead()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DD;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateDead()
{

}

void MainPlayer::EndDead()
{

}

// ========================== 사망모션 =========================== //
void MainPlayer::StartDeath()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DT;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateDeath()
{

}

void MainPlayer::EndDeath()
{

}
