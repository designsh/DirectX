#include "PreCompile.h"
#include "MainPlayer.h"

// ========================== ���� ���� ========================= //
void MainPlayer::ChangeFSMState(std::string _StateName)
{
	State_.ChangeState(_StateName);
}

// ========================== ���� ���� ========================= //
// ============================ ��� ============================ //
StateInfo MainPlayer::StartTownNatural(StateInfo _state)
{
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
	// �ִϸ��̼Ǻ���
	ChangeAnimation(_state._NextState);



	return StateInfo();
}

StateInfo MainPlayer::UpdateDeath(StateInfo _state)
{

	return StateInfo();
}
