#include "PreCompile.h"
#include "MainPlayer.h"

// STAT_A1,					// x : 19, y : 16 => 공격모션1
// STAT_A2,					// x : 19, y : 16 => 공격모션2
// STAT_BL,					// x :  6, y : 16 => 방어모션
// STAT_DD,					// x :  1, y : 16 => 시체모션
// STAT_DT,					// x : 27, y : 16 => 사망모션
// STAT_GH,					// x :  7, y : 16 => 피격모션
// STAT_KK,					// x : 12, y : 16 => 킥모션
// STAT_NU,					// x :  8, y : 16 => 필드_대기모션
// STAT_RN,					// x :  8, y : 16 => 뛰기모션
// STAT_S1,					// x : 16, y : 16 => 스킬공격모션
// STAT_SC,					// x : 16, y : 16 => 스킬캐스팅모션
// STAT_TN,					// x : 16, y : 16 => 마을_대기모션
// STAT_TW,					// x :  8, y : 16 => 마을_걷기모션
// STAT_WL,					// x :  8, y : 16 => 필드_걷기모션

void MainPlayer::CreatePlayerStateFSM()
{
	// 플레이어 보유 애니메이션 상태별 FSM 생성

	// ========================== 마을 관련 ========================== //
	State_.CreateState("Natural_Town", std::bind(&MainPlayer::UpdateTownNatural, this), std::bind(&MainPlayer::StartTownNatural, this), std::bind(&MainPlayer::EndTownNatural, this));
	State_.CreateState("Walk_Town", std::bind(&MainPlayer::UpdateTownWalk, this), std::bind(&MainPlayer::StartTownWalk, this), std::bind(&MainPlayer::EndTownWalk, this));

	// ========================== 필드 관련 ========================== //
	State_.CreateState("Natural_Field", std::bind(&MainPlayer::UpdateFieldNatural, this), std::bind(&MainPlayer::StartFieldNatural, this), std::bind(&MainPlayer::EndFieldNatural, this));
	State_.CreateState("Walk_Field", std::bind(&MainPlayer::UpdateFieldWalk, this), std::bind(&MainPlayer::StartFieldWalk, this), std::bind(&MainPlayer::EndFieldWalk, this));

	// ========================== 공통 관련 ========================== //
	State_.CreateState("Attack1", std::bind(&MainPlayer::UpdateAttack1, this), std::bind(&MainPlayer::StartAttack1, this), std::bind(&MainPlayer::EndAttack1, this));
	State_.CreateState("Attack2", std::bind(&MainPlayer::UpdateAttack2, this), std::bind(&MainPlayer::StartAttack2, this), std::bind(&MainPlayer::EndAttack2, this));
	State_.CreateState("Block", std::bind(&MainPlayer::UpdateBlock, this), std::bind(&MainPlayer::StartBlock, this), std::bind(&MainPlayer::EndBlock, this));
	State_.CreateState("Gethit", std::bind(&MainPlayer::UpdateGetHit, this), std::bind(&MainPlayer::StartGetHit, this), std::bind(&MainPlayer::EndGetHit, this));
	State_.CreateState("Kick", std::bind(&MainPlayer::UpdateKick, this), std::bind(&MainPlayer::StartKick, this), std::bind(&MainPlayer::EndKick, this));
	State_.CreateState("Run", std::bind(&MainPlayer::UpdateRun, this), std::bind(&MainPlayer::StartRun, this), std::bind(&MainPlayer::EndRun, this));
	State_.CreateState("Special_Attack", std::bind(&MainPlayer::UpdateSkillAttack, this), std::bind(&MainPlayer::StartSkillAttack, this), std::bind(&MainPlayer::EndSkillAttack, this));
	State_.CreateState("Special_Cast", std::bind(&MainPlayer::UpdateSkillCasting, this), std::bind(&MainPlayer::StartSkillCasting, this), std::bind(&MainPlayer::EndSkillCasting, this));
	
	// ========================== 사망 관련 ========================== //
	State_.CreateState("Dead", std::bind(&MainPlayer::UpdateDead, this), std::bind(&MainPlayer::StartDead, this), std::bind(&MainPlayer::EndDead, this));
	State_.CreateState("Death", std::bind(&MainPlayer::UpdateDeath, this), std::bind(&MainPlayer::StartDeath, this), std::bind(&MainPlayer::EndDeath, this));
}


