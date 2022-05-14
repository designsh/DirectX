#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalValue.h"
#include "TownMap.h"
#include "CatacombsMap.h"

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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �̵���ġ ����(�����ʱ���)
	if (false == MovePath_.empty())
	{
		// ���� �̵�Ÿ���ε��� Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// Ÿ����ġ�� ������ ����� �ε�������
		MovePath_.pop_front();

		// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
		// �÷��̾��� �̵������� �����Ѵ�.
		float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
		MoveTargetDir_ = DirPos.NormalizeReturn3D();
	}

	MoveSpeed_ = 200.f;
}

void MainPlayer::UpdateTownWalk()
{
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();

	// �̵�ó��
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
	
	// �̵�Ÿ�� Ÿ���ε��� ���޽� �̵���ΰ� �����ִٸ� Ÿ����ġ �缳�� �� ���̵�
	// ���̻��� �̵���ΰ� ���������ʴ´ٸ� ������ ����
	if (MoveTargetIndex_.Index_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).Index_)
	{
		if (false == MovePath_.empty())
		{
			// Ÿ��Ÿ�� �ε��� ����
			MoveTargetIndex_.Index_ = MovePath_.front().Index_;

			float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();
		}
		else
		{
			// �̵��Ϸ��̹Ƿ� �̵� Flag ����
			IsMove_ = false;

			// �� �̻� �̵��� ������ �����Ƿ� �÷��̾� ������ ����
			ChangeFSMState("Natural_Town");

			// Ȥ�� �����ϴ� ��ΰ� �ִٸ� Ŭ����
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// ���� ���� ����


	// ��Ÿ

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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �̵���ġ ����(�����ʱ���)
	if (false == MovePath_.empty())
	{
		// ���� �̵�Ÿ���ε��� Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// Ÿ����ġ�� ������ ����� �ε�������
		MovePath_.pop_front();

		// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
		// �÷��̾��� �̵������� �����Ѵ�.
		float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
		MoveTargetDir_ = DirPos.NormalizeReturn3D();
	}

	MoveSpeed_ = 200.f;
}

void MainPlayer::UpdateFieldWalk()
{
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();

	// �̵�ó��
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// �̵�Ÿ�� Ÿ���ε��� ���޽� �̵���ΰ� �����ִٸ� Ÿ����ġ �缳�� �� ���̵�
	// ���̻��� �̵���ΰ� ���������ʴ´ٸ� ������ ����
	if (MoveTargetIndex_.Index_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()).Index_)
	{
		if (false == MovePath_.empty())
		{
			// Ÿ��Ÿ�� �ε��� ����
			MoveTargetIndex_.Index_ = MovePath_.front().Index_;

			float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();
		}
		else
		{
			// �̵��Ϸ��̹Ƿ� �̵� Flag ����
			IsMove_ = false;

			// �� �̻� �̵��� ������ �����Ƿ� �÷��̾� ������ ����
			ChangeFSMState("Natural_Field");

			// Ȥ�� �����ϴ� ��ΰ� �ִٸ� Ŭ����
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();

	// �̵���ġ ����(�����ʱ���)
	if (false == MovePath_.empty())
	{
		// ���� �̵�Ÿ���ε��� Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// Ÿ����ġ�� ������ ����� �ε�������
		MovePath_.pop_front();

		if (true == IsTown_)
		{
			// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
			// �÷��̾��� �̵������� �����Ѵ�.
			float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
		else
		{
			float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}

	MoveSpeed_ = 250.f;

}

void MainPlayer::UpdateRun()
{
	// �ִϸ��̼� �����Ӹ��� ZOrder üũ�Ͽ� ZOrder ����
	AnimationFrameCheckZOrderChange();

	// �̵�ó��
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// �̵�Ÿ�� Ÿ���ε��� ���޽� �̵���ΰ� �����ִٸ� Ÿ����ġ �缳�� �� ���̵�
	// ���̻��� �̵���ΰ� ���������ʴ´ٸ� ������ ����
	if (true == IsTown_)
	{
		if (MoveTargetIndex_.Index_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).Index_)
		{
			if (false == MovePath_.empty())
			{
				// Ÿ��Ÿ�� �ε��� ����
				MoveTargetIndex_.Index_ = MovePath_.front().Index_;

				float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// Ÿ����ġ�� ������ ����� �ε�������
				MovePath_.pop_front();
			}
			else
			{
				// �̵��Ϸ��̹Ƿ� �̵� Flag ����
				IsMove_ = false;

				// �� �̻� �̵��� ������ �����Ƿ� �÷��̾� ������ ����
				ChangeFSMState("Natural_Town");

				// Ȥ�� �����ϴ� ��ΰ� �ִٸ� Ŭ����
				if (false == MovePath_.empty())
				{
					MovePath_.clear();
				}

				return;
			}
		}
	}
	else
	{
		if (MoveTargetIndex_.Index_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()).Index_)
		{
			if (false == MovePath_.empty())
			{
				// Ÿ��Ÿ�� �ε��� ����
				MoveTargetIndex_.Index_ = MovePath_.front().Index_;

				float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// Ÿ����ġ�� ������ ����� �ε�������
				MovePath_.pop_front();
			}
			else
			{
				// �̵��Ϸ��̹Ƿ� �̵� Flag ����
				IsMove_ = false;

				// �� �̻� �̵��� ������ �����Ƿ� �÷��̾� ������ ����
				ChangeFSMState("Natural_Field");

				// Ȥ�� �����ϴ� ��ΰ� �ִٸ� Ŭ����
				if (false == MovePath_.empty())
				{
					MovePath_.clear();
				}

				return;
			}
		}
	}
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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

	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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
	
	// �ִϸ��̼Ǻ���
	ChangeAnimation(State_.GetCurStateName());

	// ������°� ����Ǿ����Ƿ�
	// DirectRenderOrder_�� Default ZOrder�� ����
	StateAndDirectChangeZOrder();
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
