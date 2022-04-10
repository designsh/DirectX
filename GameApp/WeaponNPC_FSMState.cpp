#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#pragma region ����/���� üũ�Ͽ� �ִϸ��̼� ����
void WeaponNPC::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;
	
	switch (CurMoveDir_)
	{
		case WeaponNPC_MoveDir::DIR_B:
		{
			AnimationName += "_B";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_LB:
		{
			AnimationName += "_LB";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_L:
		{
			AnimationName += "_L";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_LT:
		{
			AnimationName += "_LT";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_T:
		{
			AnimationName += "_T";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_RT:
		{
			AnimationName += "_RT";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_R:
		{
			AnimationName += "_R";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_RB:
		{
			AnimationName += "_RB";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}	
	}
}
#pragma endregion

// ������
void WeaponNPC::StartIdle()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_IDLE;
}

void WeaponNPC::UpdateIdle()
{
	// �÷��̾�� ��ȣ�ۿ���°� �ƴҶ� �ڵ��̵��������
	MoveDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= MoveDelayTime_)
	{
		// ��������
		srand((unsigned int)time(0));
		int RandomDir = rand() % static_cast<int>(WeaponNPC_MoveDir::MAX);

		// ��������� �ٸ��� �����̵������� �����ϰ�,
		// �̵����·� ����
		if (PrevMoveDir_ != static_cast<WeaponNPC_MoveDir>(RandomDir))
		{
			PrevMoveDir_ = CurMoveDir_;
			CurMoveDir_ = static_cast<WeaponNPC_MoveDir>(RandomDir);

			State_.ChangeState("WeaponNPC_WALK");
		}

		MoveDelayTime_ = 3.f;
	}
}

void WeaponNPC::EndIdle()
{
	MoveDelayTime_ = 3.f;
}

// �̵�����
void WeaponNPC::StartWalk()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Walk");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_WALK;
}

void WeaponNPC::UpdateWalk()
{
	// �÷��̾�� ��ȣ�ۿ���°� �ƴҶ� �ڵ��̵�
	// �ִ� �̵��Ÿ� �̵��Ϸ�� �����·� ����

}

void WeaponNPC::EndWalk()
{

}

// ��ȭ����
void WeaponNPC::StartConversation()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_CONV;

	// ��ȣ�ۿ� ���۽� �÷��̾���� �Ÿ�üũ ����
	InteractionFlag = false;
}

void WeaponNPC::UpdateConversation()
{
	// ���� ��ȭ�õ��� �޼����� �ε�
	if (false == FirstInteraction)
	{
		// ��ȣ�ۿ� Flag On
		FirstInteraction = true;

		// �޼����� �ε�

	}
	// �ι�° ��ȭ�õ��� �޴� ����
	else
	{
		// ��ܸ޴� ����

	}
}

void WeaponNPC::EndConversation()
{

}
