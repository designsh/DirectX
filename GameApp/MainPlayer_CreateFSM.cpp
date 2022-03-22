#include "PreCompile.h"
#include "MainPlayer.h"

// STAT_A1,					// x : 19, y : 16 => ���ݸ��1
// STAT_A2,					// x : 19, y : 16 => ���ݸ��2
// STAT_BL,					// x :  6, y : 16 => �����
// STAT_DD,					// x :  1, y : 16 => ��ü���
// STAT_DT,					// x : 27, y : 16 => ������
// STAT_GH,					// x :  7, y : 16 => �ǰݸ��
// STAT_KK,					// x : 12, y : 16 => ű���
// STAT_NU,					// x :  8, y : 16 => �ʵ�_�����
// STAT_RN,					// x :  8, y : 16 => �ٱ���
// STAT_S1,					// x : 16, y : 16 => ��ų���ݸ��
// STAT_SC,					// x : 16, y : 16 => ��ųĳ���ø��
// STAT_TN,					// x : 16, y : 16 => ����_�����
// STAT_TW,					// x :  8, y : 16 => ����_�ȱ���
// STAT_WL,					// x :  8, y : 16 => �ʵ�_�ȱ���

void MainPlayer::CreatePlayerStateFSM()
{
	// �÷��̾� ���� �ִϸ��̼� ���º� FSM ����

	// ========================== ���� ���� ========================== //
	State_.CreateState("Natural_Town", std::bind(&MainPlayer::UpdateTownNatural, this), std::bind(&MainPlayer::StartTownNatural, this), std::bind(&MainPlayer::EndTownNatural, this));
	State_.CreateState("Walk_Town", std::bind(&MainPlayer::UpdateTownWalk, this), std::bind(&MainPlayer::StartTownWalk, this), std::bind(&MainPlayer::EndTownWalk, this));

	// ========================== �ʵ� ���� ========================== //
	State_.CreateState("Natural_Field", std::bind(&MainPlayer::UpdateFieldNatural, this), std::bind(&MainPlayer::StartFieldNatural, this), std::bind(&MainPlayer::EndFieldNatural, this));
	State_.CreateState("Walk_Field", std::bind(&MainPlayer::UpdateFieldWalk, this), std::bind(&MainPlayer::StartFieldWalk, this), std::bind(&MainPlayer::EndFieldWalk, this));

	// ========================== ���� ���� ========================== //
	State_.CreateState("Attack1", std::bind(&MainPlayer::UpdateAttack1, this), std::bind(&MainPlayer::StartAttack1, this), std::bind(&MainPlayer::EndAttack1, this));
	State_.CreateState("Attack2", std::bind(&MainPlayer::UpdateAttack2, this), std::bind(&MainPlayer::StartAttack2, this), std::bind(&MainPlayer::EndAttack2, this));
	State_.CreateState("Block", std::bind(&MainPlayer::UpdateBlock, this), std::bind(&MainPlayer::StartBlock, this), std::bind(&MainPlayer::EndBlock, this));
	State_.CreateState("Gethit", std::bind(&MainPlayer::UpdateGetHit, this), std::bind(&MainPlayer::StartGetHit, this), std::bind(&MainPlayer::EndGetHit, this));
	State_.CreateState("Kick", std::bind(&MainPlayer::UpdateKick, this), std::bind(&MainPlayer::StartKick, this), std::bind(&MainPlayer::EndKick, this));
	State_.CreateState("Run", std::bind(&MainPlayer::UpdateRun, this), std::bind(&MainPlayer::StartRun, this), std::bind(&MainPlayer::EndRun, this));
	State_.CreateState("Special_Attack", std::bind(&MainPlayer::UpdateSkillAttack, this), std::bind(&MainPlayer::StartSkillAttack, this), std::bind(&MainPlayer::EndSkillAttack, this));
	State_.CreateState("Special_Cast", std::bind(&MainPlayer::UpdateSkillCasting, this), std::bind(&MainPlayer::StartSkillCasting, this), std::bind(&MainPlayer::EndSkillCasting, this));
	
	// ========================== ��� ���� ========================== //
	State_.CreateState("Dead", std::bind(&MainPlayer::UpdateDead, this), std::bind(&MainPlayer::StartDead, this), std::bind(&MainPlayer::EndDead, this));
	State_.CreateState("Death", std::bind(&MainPlayer::UpdateDeath, this), std::bind(&MainPlayer::StartDeath, this), std::bind(&MainPlayer::EndDeath, this));
}


