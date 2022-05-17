#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

#include "CatacombsMap.h"

// Ÿ����ġ�� �̵����� ��ȯ
void Tainted::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
{
	// Ÿ����ġ ����
	TargetPos_ = _TargetPos;

	// ������ġ ����
	CurPos_ = GetTransform()->GetWorldPosition();

	// ���� �̵����� ����
	// ���� ���� ����
	PrevDir_ = CurDir_;

	// ���� ���� ��ȯó��
	// => Ÿ����ġ�� ���� ��ȯ
	float4 Direct = TargetPos_ - CurPos_;
	Direct.Normalize3D();

	// ������ y����� ���⺤�͸� ���´�.
	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // ������
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// ����
			CurDir_ = Tainted_Dir::TT_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = Tainted_Dir::TT_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = Tainted_Dir::TT_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = Tainted_Dir::TT_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = Tainted_Dir::TT_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = Tainted_Dir::TT_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = Tainted_Dir::TT_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = Tainted_Dir::TT_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = Tainted_Dir::TT_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = Tainted_Dir::TT_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ��ȯ
void Tainted::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case Tainted_Dir::TT_LB:
		{
			AnimationName += "_LB";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_LT:
		{
			AnimationName += "_LT";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_LT;

			break;
		}
		case Tainted_Dir::TT_RT:
		{
			AnimationName += "_RT";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_RT;

			break;
		}
		case Tainted_Dir::TT_RB:
		{
			AnimationName += "_RB";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_RB;

			break;
		}
		case Tainted_Dir::TT_B:
		{
			AnimationName += "_B";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_B;

			break;
		}
		case Tainted_Dir::TT_L:
		{
			AnimationName += "_L";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_L;

			break;
		}
		case Tainted_Dir::TT_T:
		{
			AnimationName += "_T";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_T;

			break;
		}
		case Tainted_Dir::TT_R:
		{
			AnimationName += "_R";
			Tainted_->SetChangeAnimation(AnimationName);

			// ���� ��ȯ
			CurDir_ = Tainted_Dir::TT_R;

			break;
		}
	}
}

// �ش� ���� ������ȯ�� üũŸ�ϸ���Ʈ ����
void Tainted::SetCheckTileList(TileIndex _CurTileIndex)
{
	// ���� üũŸ�ϸ�� ����
	std::map<__int64, Tainted_TileCheckType>::iterator StartIter = CheckTileList_.begin();
	std::map<__int64, Tainted_TileCheckType>::iterator EndIter = CheckTileList_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		CheckTileList_.erase(StartIter);
	}
	CheckTileList_.clear();

	// ������ üũŸ�ϸ�� �ۼ�(����Ÿ���� +- 6)
	for (int i = 1; i <= 6; ++i)
	{
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( 0,  i)).Index_, Tainted_TileCheckType::MOVE));		// �´�
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i,  i)).Index_, Tainted_TileCheckType::MOVE));		// �»��
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i,  0)).Index_, Tainted_TileCheckType::MOVE));		// ���
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i, -i)).Index_, Tainted_TileCheckType::MOVE));		// ����
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( 0, -i)).Index_, Tainted_TileCheckType::MOVE));		// ���
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i, -i)).Index_, Tainted_TileCheckType::MOVE));		// ���ϴ�
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i,  0)).Index_, Tainted_TileCheckType::MOVE));		// �ϴ�
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i,  i)).Index_, Tainted_TileCheckType::MOVE));		// ���ϴ�
	}

	// ��ų���� üũŸ�ϸ�� �ۼ�(����Ÿ���� +- 2)
	for (int i = 1; i <= 2; ++i)
	{
		CheckTileList_.find((_CurTileIndex + TileIndex( 0,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// �´�
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// �»��
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  0)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// ���
		CheckTileList_.find((_CurTileIndex + TileIndex(-i, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// ����
		CheckTileList_.find((_CurTileIndex + TileIndex( 0, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// ���
		CheckTileList_.find((_CurTileIndex + TileIndex( i, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// ���ϴ�
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  0)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// �ϴ�
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// ���ϴ�
	}

	// �Ϲݰ��� üũŸ�ϸ�� �ۼ�(����Ÿ���� +- 1)
	for (int i = 1; i <= 1; ++i)
	{
		CheckTileList_.find((_CurTileIndex + TileIndex( 0,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// �´�
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// �»��
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  0)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// ���
		CheckTileList_.find((_CurTileIndex + TileIndex(-i, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// ����
		CheckTileList_.find((_CurTileIndex + TileIndex( 0, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// ���
		CheckTileList_.find((_CurTileIndex + TileIndex( i, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// ���ϴ�
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  0)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// �ϴ�
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// ���ϴ�
	}
}

// ���� üũ����Ʈ�� �������� üũ �� ������ȯ
void Tainted::CheckChangeState(TileIndex _PlayerTileIndex)
{
	if (CheckTileList_.end() == CheckTileList_.find(_PlayerTileIndex.Index_))
	{
		return;
	}

	if (Tainted_TileCheckType::MOVE == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_MOVE");
	}
	else if (Tainted_TileCheckType::NORMALATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_ATTACK");
	}
	else if (Tainted_TileCheckType::SKILLATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_SKILL");
	}
}

// ���� ��Ž�� ����
void Tainted::StartRoomDetect()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_ROOMDETECT;
}

void Tainted::UpdateRoomDetect()
{
	// �� ���� �����Խ��� ����
	if (false == RoomDetect_)
	{
		for (auto& DetectTile : RoomDetectList_)
		{
			// �÷��̾ �����Ҷ�
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 
				TileIndex PlayerTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
				if (PlayerTileIndex == DetectTile)
				{
					// ������ ��ȯ
					State_.ChangeState("Tainted_IDLE");

					// ������ Flag On
					RoomDetect_ = true;
				}
			}
		}
	}
}

void Tainted::EndRoomDetect()
{

}

// ������
void Tainted::StartIdle()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_IDLE;

	// ������ġ������ üũ����Ʈ �ۼ�
	SetCheckTileList(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()));
}

void Tainted::UpdateIdle()
{
	// ���� �������� �ѹ��̶� ���� ���
	if (true == RoomDetect_)
	{
		// ���� ��ġ Ÿ���ε��� üũ
		CheckChangeState(GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition()));
	}
}

void Tainted::EndIdle()
{

}

// �̵�����(����������)
void Tainted::StartMove()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_WALK;

	// �÷��̾��� ���� Ÿ���� Ÿ����ġ�� ����


	// Ÿ���� ���� �������� �ִϸ��̼� ����


	// 

}

void Tainted::UpdateMove()
{
	// �Ϲݰ��� �������� �÷��̾� ���Խ� �Ϲݰ��ݻ��·� ��ȯ



	// ��ų���� �������� �÷��̾� ���԰� ���ÿ� ��Ÿ�� �ʱ�ȭ�� ��ų���ݻ��·� ��ȯ



}

void Tainted::EndMove()
{

}

// �⺻���ݻ���
void Tainted::StartNormalAttack()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "NormalAttack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_NORMALATTACK;
}

void Tainted::UpdateNormalAttack()
{

}

void Tainted::EndNormalAttack()
{

}

// ��ų���ݻ���
void Tainted::StartSpecialAttack()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "SpecialAttack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_SKILLATTACK;
}

void Tainted::UpdateSpecialAttack()
{

}

void Tainted::EndSpecialAttack()
{

}

// �ǰݻ���
void Tainted::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_GETHIT;
}

void Tainted::UpdateGetHit()
{

}

void Tainted::EndGetHit()
{

}

// �������
void Tainted::StartDeath()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_DEATH;
}

void Tainted::UpdateDeath()
{
	// ������ ����� ��ü���·� ��ȯ

}

void Tainted::EndDeath()
{

}

// ��ü����
void Tainted::StartDead()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Dead");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_DEAD;
}

void Tainted::UpdateDead()
{
	// ���콺�� �浹�����̸�, �÷��̾ �ش� ��ü�� ��ȯ��ų ������ �ش� ���ʹ� ������ ���

}

void Tainted::EndDead()
{

}