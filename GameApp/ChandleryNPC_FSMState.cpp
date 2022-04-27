#include "PreCompile.h"
#include "ChandleryNPC.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "MainPlayer.h"
#include "TownMap.h"

#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"

#pragma region ����/���� üũ�Ͽ� �ִϸ��̼� ����
void ChandleryNPC::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurMoveDir_)
	{
		case ChandleryNPC_MoveDir::DIR_B:
		{
			AnimationName += "_B";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_LB:
		{
			AnimationName += "_LB";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_L:
		{
			AnimationName += "_L";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_LT:
		{
			AnimationName += "_LT";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_T:
		{
			AnimationName += "_T";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_RT:
		{
			AnimationName += "_RT";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_R:
		{
			AnimationName += "_R";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case ChandleryNPC_MoveDir::DIR_RB:
		{
			AnimationName += "_RB";
			ChandleryNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}
#pragma endregion

// ������
void ChandleryNPC::StartIdle()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Akara_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = ChandleryNPC_FSMState::ST_IDLE;
}

void ChandleryNPC::UpdateIdle()
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
		int RandomDir = rand() % static_cast<int>(ChandleryNPC_MoveDir::MAX);

		// ��������� �ٸ��� �����̵������� �����ϰ�, �̵����·� ����
		if (PrevMoveDir_ != static_cast<ChandleryNPC_MoveDir>(RandomDir))
		{
			CurMoveDir_ = static_cast<ChandleryNPC_MoveDir>(RandomDir);

			State_.ChangeState("ChandleryNPC_WALK");
		}

		MoveDelayTime_ = 5.f;
	}
}

void ChandleryNPC::EndIdle()
{
}

// �̵�����
void ChandleryNPC::StartWalk()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Akara_Walk");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = ChandleryNPC_FSMState::ST_WALK;

	// �̵��� ��ġ ����
	MoveStartPos_ = GetTransform()->GetWorldPosition();
	MoveCurPos_ = GetTransform()->GetWorldPosition();
}

void ChandleryNPC::UpdateWalk()
{
	// �÷��̾�� ��ȣ�ۿ���°� �ƴҶ� �ڵ��̵�
	// �ִ� �̵��Ÿ� �̵��Ϸ�� �����·� ����
	switch (CurMoveDir_)
	{
		case ChandleryNPC_MoveDir::DIR_B:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_LB:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_L:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_LT:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_T:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_RT:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_R:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
			}
			break;
		}
		case ChandleryNPC_MoveDir::DIR_RB:
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
				State_.ChangeState("ChandleryNPC_IDLE");
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
		State_.ChangeState("ChandleryNPC_IDLE");
		return;
	}
}

void ChandleryNPC::EndWalk()
{
	MoveCurPos_ = float4::ZERO;
}

// ��ȣ�ۿ��� ����
void ChandleryNPC::StartConversation()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Akara_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = ChandleryNPC_FSMState::ST_CONV;
}

void ChandleryNPC::UpdateConversation()
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
			State_.ChangeState("ChandleryNPC_INTERACTION");
			return;
		}
	}
}

void ChandleryNPC::EndConversation()
{

}

// ��ȣ�ۿ��� ����
void ChandleryNPC::StartInteraction()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Akara_Idle");

	// ���°� ����
	PrevState_ = CurState_;
	CurState_ = ChandleryNPC_FSMState::ST_INTER;

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

void ChandleryNPC::UpdateInteraction()
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

void ChandleryNPC::EndInteraction()
{
	// ��ȣ�ۿ� ��ȿ�Ÿ� üũ Flag ����
	InteractionFlag = false;
}
