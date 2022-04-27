#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GlobalValue.h"
#include "MainPlayer.h"
#include "TownMap.h"

#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"

#pragma region ��ǥ��ġ���Ž��
std::list<PathIndex> WeaponNPC::SearchMovePath(WeaponNPC_MoveDir _MoveDir)
{
	// Ÿ����ġ ����
	float4 MoveTargetPos = float4::ZERO;

	// �̵����⿡ �´� Ÿ����ġ ����
	TileIndex TargetTile = TileIndex();
	switch (_MoveDir)
	{
		case WeaponNPC_MoveDir::DIR_B:
		{
			TargetTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()) + TileIndex(0, -2);
			MoveTargetPos = GlobalValue::TownMap->GetTileIndexToPos(TargetTile);
			break;
		}
		case WeaponNPC_MoveDir::DIR_L:
		{
			TargetTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()) + TileIndex(-2, 0);
			MoveTargetPos = GlobalValue::TownMap->GetTileIndexToPos(TargetTile);
			break;
		}
		case WeaponNPC_MoveDir::DIR_T:
		{
			TargetTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()) + TileIndex(0, 2);
			MoveTargetPos = GlobalValue::TownMap->GetTileIndexToPos(TargetTile);
			break;
		}
		case WeaponNPC_MoveDir::DIR_R:
		{
			TargetTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()) + TileIndex(2, 0);
			MoveTargetPos = GlobalValue::TownMap->GetTileIndexToPos(TargetTile);
			break;
		}
	}

	if (float4::ZERO != MoveTargetPos)
	{
		return GlobalValue::TownMap->NavgationFind4Way(GetTransform()->GetWorldPosition(), MoveTargetPos);
	}

	return std::list<PathIndex>();
}
#pragma endregion

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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(1, 1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(0.0f, -1.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(0, 1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(-1.0f, -1.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(-1, 1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(-1.0f, 0.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(-1, 0);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(-1.0f, 1.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(-1, -1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(0.0f, 1.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(0, -1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(1.0f, 1.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(1, -1);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(1.0f, 0.0f) * MoveSpeed_);
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
			// �̵��� ���� Ÿ���ε������� �̵��Ϸ��� Ÿ���� Ÿ���� ���̸� �̵��� �ߴ��ϰ�
			// �����·� ��ȯ�Ѵ�.
			TileIndex CurTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
			CurTile = CurTile + TileIndex(1, 0);
			if (NavigationType::WALL == GlobalValue::TownMap->GetTileToNaviType(GlobalValue::TownMap->GetTileIndexToPos(CurTile)))
			{
				// �����̵����� ����
				PrevMoveDir_ = CurMoveDir_;

				// ���� ��ȯ
				State_.ChangeState("WeaponNPC_IDLE");
				return;
			}

			// �̵� �� ���� �̵���ġ ����
			GetTransform()->SetWorldDeltaTimeMove(float4(1.0f, -1.0f) * MoveSpeed_);
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
	TileIndex SearchTile[9] = { {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

	// �÷��̾�� ��ȣ�ۿ밡�ɹ��� üũ
	// �÷��̾��� ��ġ(Ÿ����ġ)�� NPC�� ��ġ�ϴ� Ÿ�Ͽ����� +-1 ���̿� �����ϴ� Ÿ���̸�
	// ��ȣ�ۿ밡��ó��
	TileIndex PlayerTile = GlobalValue::TownMap->GetPosToTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	TileIndex MyTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
	for (int i = 0; i < 9; ++i)
	{
		// ���� NPC�� Ÿ�Ͽ��� �̿����(8����) �˻��Ͽ� �÷��̾ ã�Ƴ���.
		TileIndex FindTile = MyTile + SearchTile[i];

		// �÷��̾ ã�Ƴ´ٸ� ��ȣ�ۿ� ���·� ��ȯ
		if (PlayerTile == FindTile)
		{
			// ���Լ������� ���� ������ȯ
			State_.ChangeState("WeaponNPC_INTERACTION");
			return;
		}
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
		MessageView_->InteractionActive();
	}
	// �ι�° ��ȭ�õ��� �޴� ����
	else
	{
		if (false == TopMenuBar_->IsUpdate())
		{
			// ��ܸ޴� ����
			TopMenuBar_->NPCTopMenuActive();
		}
	}
}

void WeaponNPC::UpdateInteraction()
{
	// ��ܸ޴����� or �Ǹ�â���� or ��ȭ����� npc�� �����·� ��ȯ

	// 1. NPC�� ��ȣ�ۿ�(����)
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
			TopMenuBar_->NPCTopMenuActive();
		}
	}
}

void WeaponNPC::EndInteraction()
{
	// ��ȣ�ۿ� ��ȿ�Ÿ� üũ Flag ����
	InteractionFlag = false;
}
