#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

void MainPlayer::ChangeCheckProcess()
{
	// ���� ���� ��ȯ ���̱� ������ ��������� ������ ������¸� üũ�Ͽ�
	// On�ؾ��ϴ� �������� �����Ѵ�.
	int Index = 0;
	std::map<RendererPartType, bool>::iterator StartIter = IsItemEquipState_.begin();
	std::map<RendererPartType, bool>::iterator EndIter = IsItemEquipState_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// �������������̶�� HVY_ Ȱ��ȭ, LIT_ ��Ȱ��ȭ
		if (true == (*StartIter).second)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
		}
		else // ���� �ݴ��� ���
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();
		}

		++Index;
	}
}

// ========================== ���� ���� ========================= //
void MainPlayer::ChangeFSMState(std::string _StateName)
{
	// �������¿� ������°� �ٸ��� üũ�ؾ��ϴ� ����üũ
	if (PrevState_ != CurState_)
	{
		ChangeCheckProcess();
	}

	State_.ChangeState(_StateName);
}

// ========================== ���� ���� ========================= //
// ============================ ��� ============================ //
StateInfo MainPlayer::StartTownNatural(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TN;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);

	// ���� ���� ����
	

	// ��Ÿ
	
	return StateInfo();
}

StateInfo MainPlayer::UpdateTownNatural(StateInfo _state)
{
	// ���� �÷��̾ �������� �ʵ����� üũ



	// �̵� üũ





	return StateInfo();
}

// ============================ �ȱ� ============================ //
StateInfo MainPlayer::StartTownWalk(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TW;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateTownWalk(StateInfo _state)
{

	return StateInfo();
}

// ========================== �ʵ� ���� ========================== //

// ============================ ��� ============================ //
StateInfo MainPlayer::StartFieldNatural(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_NU;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateFieldNatural(StateInfo _state)
{

	return StateInfo();
}

// ============================ �ȱ� ============================ //
StateInfo MainPlayer::StartFieldWalk(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_WL;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateFieldWalk(StateInfo _state)
{

	return StateInfo();
}

// ========================== ���� ���� ========================== //

// ========================== ���ݸ��1 ========================== //
StateInfo MainPlayer::StartAttack1(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A1;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack1(StateInfo _state)
{

	return StateInfo();
}

// ========================== ���ݸ��2 ========================== //
StateInfo MainPlayer::StartAttack2(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A2;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateAttack2(StateInfo _state)
{

	return StateInfo();
}

// ========================== ����� =========================== //
StateInfo MainPlayer::StartBlock(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_BL;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateBlock(StateInfo _state)
{

	return StateInfo();
}

// ========================== �ǰݸ�� =========================== //
StateInfo MainPlayer::StartGetHit(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_GH;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateGetHit(StateInfo _state)
{

	return StateInfo();
}

// ========================== ű��� ============================ //
StateInfo MainPlayer::StartKick(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_KK;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateKick(StateInfo _state)
{

	return StateInfo();
}

// ========================== �ٱ��� =========================== //
StateInfo MainPlayer::StartRun(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_RN;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateRun(StateInfo _state)
{

	return StateInfo();
}

// ======================== ��ų���ݸ�� ========================= //
StateInfo MainPlayer::StartSkillAttack(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_S1;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateSkillAttack(StateInfo _state)
{

	return StateInfo();
}

// ======================= ��ųĳ���ø�� ======================== //
StateInfo MainPlayer::StartSkillCasting(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_SC;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateSkillCasting(StateInfo _state)
{

	return StateInfo();
}

// ========================== ��� ���� ========================== //

// ========================== ��ü��� =========================== //
StateInfo MainPlayer::StartDead(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DD;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateDead(StateInfo _state)
{

	return StateInfo();
}

// ========================== ������ =========================== //
StateInfo MainPlayer::StartDeath(StateInfo _state)
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DT;

	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateDeath(StateInfo _state)
{

	return StateInfo();
}
