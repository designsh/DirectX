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
	State_.CreateState("Natural_Town", &MainPlayer::StartTownNatural, &MainPlayer::UpdateTownNatural);
	State_.CreateState("Walk_Town", &MainPlayer::StartTownWalk, &MainPlayer::UpdateTownWalk);

	// ========================== 필드 관련 ========================== //
	State_.CreateState("Natural_Field", &MainPlayer::StartFieldNatural, &MainPlayer::UpdateFieldNatural);
	State_.CreateState("Walk_Field", &MainPlayer::StartFieldWalk, &MainPlayer::UpdateFieldWalk);

	// ========================== 공통 관련 ========================== //
	State_.CreateState("Attack1", &MainPlayer::StartAttack1, &MainPlayer::UpdateAttack1);
	State_.CreateState("Attack2", &MainPlayer::StartAttack2, &MainPlayer::UpdateAttack2);
	State_.CreateState("Block", &MainPlayer::StartBlock, &MainPlayer::UpdateBlock);
	State_.CreateState("Gethit", &MainPlayer::StartGetHit, &MainPlayer::UpdateGetHit);
	State_.CreateState("Kick", &MainPlayer::StartKick, &MainPlayer::UpdateKick);	
	State_.CreateState("Run", &MainPlayer::StartRun, &MainPlayer::UpdateRun);
	State_.CreateState("Special_Attack", &MainPlayer::StartSkillAttack, &MainPlayer::UpdateSkillAttack);
	State_.CreateState("Special_Cast", &MainPlayer::StartSkillCasting, &MainPlayer::UpdateSkillCasting);
	
	// ========================== 사망 관련 ========================== //
	State_.CreateState("Dead", &MainPlayer::StartDead, &MainPlayer::UpdateDead);
	State_.CreateState("Death", &MainPlayer::StartDeath, &MainPlayer::UpdateDeath);
}


