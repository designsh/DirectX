#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalValue.h"
#include "TownMap.h"
#include "RandomMap.h"

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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndTownNatural()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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

	// �̵���ġ ����
	if (false == MovePath_.empty())
	{
		if (true == IsTown_)
		{
			// ���� �̵�Ÿ���ε��� Get
			PathIndex TargetTileIndex = MovePath_.front();
			MoveTargetIndex_ = TileIndex(TargetTileIndex.X_, TargetTileIndex.Y_);

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();
		}
		else
		{
			// �����ʿ��� ã�Ƴ���.

		}
	}
}

void MainPlayer::UpdateTownWalk()
{
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();
	
	// �̵�Ÿ�� Ÿ���ε��� ���޽� �̵���ΰ� �����ִٸ� Ÿ����ġ �缳�� �� ���̵�
	// ���̻��� �̵���ΰ� ���������ʴ´ٸ� ������ ����
	if (MoveTargetIndex_.X_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).X_ && 
		MoveTargetIndex_.Y_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).Y_)
	{
		if (false == MovePath_.empty())
		{

		}
		else
		{

		}

		// �̵� ����

	}
}

void MainPlayer::EndTownWalk()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndFieldNatural()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndFieldWalk()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndAttack1()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndAttack2()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndBlock()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndGetHit()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndKick()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndRun()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndSkillAttack()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndSkillCasting()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndDead()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
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
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndDeath()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}
