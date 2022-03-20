#include "PreCompile.h"
#include "MainPlayer.h"

// ========================== 상태 변경 ========================= //
void MainPlayer::ChangeFSMState(std::string _StateName)
{
	State_.ChangeState(_StateName);
}

// ========================== 마을 관련 ========================= //
// ============================ 대기 ============================ //
StateInfo MainPlayer::StartTownNatural(StateInfo _state)
{
	// 애니메이션변경을 위한 이름 편집


	//ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));


	//std::string AniName = 


	int a = 0;


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

	return StateInfo();
}

StateInfo MainPlayer::UpdateFieldNatural(StateInfo _state)
{

	return StateInfo();
}

// ============================ 걷기 ============================ //
StateInfo MainPlayer::StartFieldWalk(StateInfo _state)
{

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

	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack1(StateInfo _state)
{

	return StateInfo();
}

// ========================== 공격모션2 ========================== //
StateInfo MainPlayer::StartAttack2(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack2(StateInfo _state)
{

	return StateInfo();
}

// ========================== 방어모션 =========================== //
StateInfo MainPlayer::StartBlock(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateBlock(StateInfo _state)
{

	return StateInfo();
}

// ========================== 피격모션 =========================== //
StateInfo MainPlayer::StartGetHit(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateGetHit(StateInfo _state)
{

	return StateInfo();
}

// ========================== 킥모션 ============================ //
StateInfo MainPlayer::StartKick(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateKick(StateInfo _state)
{

	return StateInfo();
}

// ========================== 뛰기모션 =========================== //
StateInfo MainPlayer::StartRun(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateRun(StateInfo _state)
{

	return StateInfo();
}

// ======================== 스킬공격모션 ========================= //
StateInfo MainPlayer::StartSkillAttack(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateSkillAttack(StateInfo _state)
{

	return StateInfo();
}

// ======================= 스킬캐스팅모션 ======================== //
StateInfo MainPlayer::StartSkillCasting(StateInfo _state)
{

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

	return StateInfo();
}

StateInfo MainPlayer::UpdateDead(StateInfo _state)
{

	return StateInfo();
}

// ========================== 사망모션 =========================== //
StateInfo MainPlayer::StartDeath(StateInfo _state)
{

	return StateInfo();
}

StateInfo MainPlayer::UpdateDeath(StateInfo _state)
{

	return StateInfo();
}
