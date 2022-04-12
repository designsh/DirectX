#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"

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
		// �̵����� ����
		// ���������� üũ�Ͽ� ��������� �����ȴ�.
		// ��, �Ʒ��� �̵��ѵ� �ٽ� �����°� �Ǿ��ٸ� ���� �̵��Ѵ�.
		// �����ڸ��� ������ ������ ��ȯ�Ǹ�, ���Ͱ��� ������ �ݺ�ó���ϰԵȴ�.
		
		// ��������� ��������� �ݴ�����̸� �������� ���� �����
		srand((unsigned int)time(0));
		int RandomDir = rand() % static_cast<int>(WeaponNPC_MoveDir::MAX);

		// ��������� �ٸ��� �����̵������� �����ϰ�, �̵����·� ����
		if (PrevMoveDir_ != static_cast<WeaponNPC_MoveDir>(RandomDir))
		{
			CurMoveDir_ = static_cast<WeaponNPC_MoveDir>(RandomDir);

			State_.ChangeState("WeaponNPC_WALK");
		}

		MoveDelayTime_ = 5.f;
	}
}

void WeaponNPC::EndIdle()
{
}

// �̵�����
void WeaponNPC::StartWalk()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Walk");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_WALK;

	// �̵��� ��ġ ����
	MoveStartPos_ = GetTransform()->GetLocalPosition();
	MoveCurPos_ = GetTransform()->GetLocalPosition();
}

void WeaponNPC::UpdateWalk()
{
	// �÷��̾�� ��ȣ�ۿ���°� �ƴҶ� �ڵ��̵�
	// �ִ� �̵��Ÿ� �̵��Ϸ�� �����·� ����
	switch (CurMoveDir_)
	{
		case WeaponNPC_MoveDir::DIR_B:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(0.0f, -1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.y)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_LB:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, -1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.y && 100.0f <= MoveDist.x)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_L:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, 0.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.x)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_LT:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.y && 100.0f <= MoveDist.x)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_T:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(0.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.y)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_RT:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.y && 100.0f <= MoveDist.x)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_R:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, 0.0f)* MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.x)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_RB:
		{
			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, -1.0f)* MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// �̵��� �̵�������ġ�� ������ġ�� ���Ͽ� 320 �̻� �Ÿ��� �������� �̵� ����
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (100.0f <= MoveDist.x && 100.0f <= MoveDist.y)
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
	}

	// �̵�ó���� �ִ��̵������� �Ѿ�� �����̵������� �����ϰ� �ٷ� ������ȯ
	if (!((MoveMinRange_.x <= MoveCurPos_.x && MoveMinRange_.y <= MoveCurPos_.y) && (MoveMaxRange_.x >= MoveCurPos_.x && MoveMaxRange_.y >= MoveCurPos_.y)))
	{
		// �����̵����� ����
		PrevMoveDir_ = CurMoveDir_;

		// ���� ��ȯ
		State_.ChangeState("WeaponNPC_IDLE");
		return;
	}
}

void WeaponNPC::EndWalk()
{
	MoveCurPos_ = float4::ZERO;
}

// ��ȣ�ۿ��� ����
void WeaponNPC::StartConversation()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_CONV;
}

void WeaponNPC::UpdateConversation()
{
	// �÷��̾�� ��ȣ�ۿ밡�ɹ��� üũ
	// ��ȣ�ۿ밡�ɹ��� ���Խ� ������ȯ
	float4 PlayerPos = GlobalValue::CurPlayer->GetTransform()->GetLocalPosition();
	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 InteactionDist = MyPos - PlayerPos;
	InteactionDist = float4(std::abs(InteactionDist.x), std::abs(InteactionDist.y));
	//if (InteractionDistance_ >= InteactionDist.x || InteractionDistance_ >= InteactionDist.y) // �ӽ��ּ�
	if (500.f >= InteactionDist.x || 500.f >= InteactionDist.y) // �׽�Ʈ��
	{
		// ���Լ������� ���� ������ȯ
		State_.ChangeState("WeaponNPC_INTERACTION");
	}
}

void WeaponNPC::EndConversation()
{

}

// ��ȣ�ۿ��� ����
void WeaponNPC::StartInteraction()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Charsi_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_INTER;

	// ���� ��ȭ�õ��� �޼����� �ε�
	if (false == FirstInteraction)
	{
		// �޼����� �ε�
		MessageView_->FirstInteractionActive();
	}
	// �ι�° ��ȭ�õ��� �޴� ����
	else
	{
		// ��ܸ޴� ����
		TopMenuBar_->On();
	}
}

void WeaponNPC::UpdateInteraction()
{
	// ��ܸ޴����� or �Ǹ�â���� or ��ȭ����� npc�� �����·� ��ȯ

	// 1. ��ȭâ �޼��� ����üũ
	if (false == FirstInteraction)
	{
		// ������ ������ �ؽ�Ʈ ��� �����
		if (true == MessageView_->GetMessageLoadEnd())
		{
			// ���ʻ�ȣ�ۿ� Flag On
			FirstInteraction = true;

			// �޼���â ���� ��
			MessageView_->Off();

			// ��ܸ޴� ����
			TopMenuBar_->On();
		}
	}

	// 2. ��ܸ޴� �����ư Ŭ��üũ



	// 3. �ش� NPC �Ǹ�â �����ư Ŭ��üũ



	// ����� ���� ��ȯ
	//State_.ChangeState("WeaponNPC_IDLE");
}

void WeaponNPC::EndInteraction()
{
	// ��ȣ�ۿ� ��ȿ�Ÿ� üũ Flag ����
	InteractionFlag = false;
}
