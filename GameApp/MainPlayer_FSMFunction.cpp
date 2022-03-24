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
	State_.ChangeState(_StateName);

	// �������¿� ������°� �ٸ��� üũ�ؾ��ϴ� ����üũ
	if (PrevState_ != CurState_)
	{
		// ������ ���� ���� üũ�Ͽ� ������ On/Off
		ChangeCheckProcess();
	}
}

// ========================== ���� ���� ========================= //
// ============================ ��� ============================ //
void MainPlayer::StartTownNatural()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TN;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ���� ���� ����


	// ��Ÿ
}

void MainPlayer::UpdateTownNatural()
{




}

void MainPlayer::EndTownNatural()
{

}

// ============================ �ȱ� ============================ //
void MainPlayer::StartTownWalk()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TW;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateTownWalk()
{
}

void MainPlayer::EndTownWalk()
{
}

// ========================== �ʵ� ���� ========================== //

// ============================ ��� ============================ //
void MainPlayer::StartFieldNatural()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_NU;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();


	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateFieldNatural()
{

}

void MainPlayer::EndFieldNatural()
{

}

// ============================ �ȱ� ============================ //
void MainPlayer::StartFieldWalk()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_WL;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateFieldWalk()
{

}

void MainPlayer::EndFieldWalk()
{

}

// ========================== ���� ���� ========================== //

// ========================== ���ݸ��1 ========================== //
void MainPlayer::StartAttack1()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A1;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateAttack1()
{

}

void MainPlayer::EndAttack1()
{

}

// ========================== ���ݸ��2 ========================== //
void MainPlayer::StartAttack2()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A2;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateAttack2()
{

}

void MainPlayer::EndAttack2()
{

}

// ========================== ����� =========================== //
void MainPlayer::StartBlock()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_BL;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateBlock()
{

}

void MainPlayer::EndBlock()
{

}

// ========================== �ǰݸ�� =========================== //
void MainPlayer::StartGetHit()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_GH;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateGetHit()
{

}

void MainPlayer::EndGetHit()
{

}

// ========================== ű��� ============================ //
void MainPlayer::StartKick()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_KK;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateKick()
{

}

void MainPlayer::EndKick()
{

}

// ========================== �ٱ��� =========================== //
void MainPlayer::StartRun()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_RN;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateRun()
{

}

void MainPlayer::EndRun()
{

}

// ======================== ��ų���ݸ�� ========================= //
void MainPlayer::StartSkillAttack()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_S1;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateSkillAttack()
{

}

void MainPlayer::EndSkillAttack()
{

}

// ======================= ��ųĳ���ø�� ======================== //
void MainPlayer::StartSkillCasting()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_SC;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateSkillCasting()
{

}

void MainPlayer::EndSkillCasting()
{

}

// ========================== ��� ���� ========================== //

// ========================== ��ü��� =========================== //
void MainPlayer::StartDead()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DD;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateDead()
{

}

void MainPlayer::EndDead()
{

}

// ========================== ������ =========================== //
void MainPlayer::StartDeath()
{
	// ���� ���� ����
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DT;

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());
}

void MainPlayer::UpdateDeath()
{

}

void MainPlayer::EndDeath()
{

}
