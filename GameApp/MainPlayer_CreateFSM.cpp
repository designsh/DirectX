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
	State_.CreateState("Natural_Town", &MainPlayer::StartTownNatural, &MainPlayer::UpdateTownNatural);
	State_.CreateState("Walk_Town", &MainPlayer::StartTownWalk, &MainPlayer::UpdateTownWalk);

	// ========================== �ʵ� ���� ========================== //
	State_.CreateState("Natural_Field", &MainPlayer::StartFieldNatural, &MainPlayer::UpdateFieldNatural);
	State_.CreateState("Walk_Field", &MainPlayer::StartFieldWalk, &MainPlayer::UpdateFieldWalk);

	// ========================== ���� ���� ========================== //
	State_.CreateState("Attack1", &MainPlayer::StartAttack1, &MainPlayer::UpdateAttack1);
	State_.CreateState("Attack2", &MainPlayer::StartAttack2, &MainPlayer::UpdateAttack2);
	State_.CreateState("Block", &MainPlayer::StartBlock, &MainPlayer::UpdateBlock);
	State_.CreateState("Gethit", &MainPlayer::StartGetHit, &MainPlayer::UpdateGetHit);
	State_.CreateState("Kick", &MainPlayer::StartKick, &MainPlayer::UpdateKick);	
	State_.CreateState("Run", &MainPlayer::StartRun, &MainPlayer::UpdateRun);
	State_.CreateState("Special_Attack", &MainPlayer::StartSkillAttack, &MainPlayer::UpdateSkillAttack);
	State_.CreateState("Special_Cast", &MainPlayer::StartSkillCasting, &MainPlayer::UpdateSkillCasting);
	
	// ========================== ��� ���� ========================== //
	State_.CreateState("Dead", &MainPlayer::StartDead, &MainPlayer::UpdateDead);
	State_.CreateState("Death", &MainPlayer::StartDeath, &MainPlayer::UpdateDeath);
}


