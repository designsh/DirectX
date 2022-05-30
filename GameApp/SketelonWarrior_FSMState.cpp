#include "PreCompile.h"
#include "SketelonWarrior.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "CatacombsMap.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

// Ÿ�� ���� üũ
void SketelonWarrior::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
{	
	// ��������� �������⿡ ����
	PrevDir_ = CurDir_;

	// ���� ��ġ�� Ÿ����ġ�� ������ ���
	float4 Direct = _TargetPos - GetTransform()->GetWorldPosition();
	Direct.Normalize3D();

	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // ������
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// ����
			CurDir_ = SketelonWarrior_TargetDir::SW_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = SketelonWarrior_TargetDir::SW_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = SketelonWarrior_TargetDir::SW_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = SketelonWarrior_TargetDir::SW_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = SketelonWarrior_TargetDir::SW_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = SketelonWarrior_TargetDir::SW_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = SketelonWarrior_TargetDir::SW_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = SketelonWarrior_TargetDir::SW_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = SketelonWarrior_TargetDir::SW_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = SketelonWarrior_TargetDir::SW_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ����
void SketelonWarrior::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case SketelonWarrior_TargetDir::SW_LB:
		{
			AnimationName += "_LB";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_LT:
		{
			AnimationName += "_LT";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_RT:
		{
			AnimationName += "_RT";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_RB:
		{
			AnimationName += "_RB";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_B:
		{
			AnimationName += "_B";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_L:
		{
			AnimationName += "_L";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_T:
		{
			AnimationName += "_T";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWarrior_TargetDir::SW_R:
		{
			AnimationName += "_R";
			WarriorRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

bool SketelonWarrior::MonsterDetect()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			TileIndex CheckTileIndex = CurTileIndex + TileIndex(x, y);
			DetectMonster_ = GlobalValue::CatacombsMap->MonsterTileIndexCheck(CheckTileIndex);
			if (nullptr != DetectMonster_)
			{
				return true;
			}
		}
	}

	return false;
}

bool SketelonWarrior::CheckWarpStart()
{
	// �ش� ������ ����� �÷��̾�Է� ������Ų��.
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	for (auto& MoveabledTile : MaxMoveRange_)
	{
		if (CurTileIndex == MoveabledTile)
		{
			return false;
		}
	}

	return true;
}

// ��ȯ����
void SketelonWarrior::StartSpawnState()
{	
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::SPAWN;

	// ��ȯ ���� ���
	StateSound_->PlayAlone("SkeletonSpawn.wav", 0);
}

void SketelonWarrior::UpdateSpawnState()
{
}

void SketelonWarrior::EndSpawnState()
{
}

// ������
void SketelonWarrior::StartIdleState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::IDLE;

	// ���� �÷��̾��� ��ġ���� ���� �̵������� �����Ѵ�.
	SetMoveRange();
}

void SketelonWarrior::UpdateIdleState()
{
	// �ֺ����� ���� ���翩�� �Ǵ�
	CheckTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= CheckTime_)
	{
		// 1. ���Ͱ� �����Ѵٸ� ���� ���� �������� Ÿ�ٱ��� �̵�����
		if (true == MonsterDetect())
		{
			// ���ݻ��·� ��ȯ
			State_.ChangeState("Attack");
		}
		// 2. ���Ͱ� �������������� �̵� or ����
		else
		{
			// �÷��̾��ֺ� 6x6Ÿ�ϳ��� ���������ʴ´ٸ� �������·� ��ȯ
			// ��, �÷��̾ �̵��߿��� ���� �Ұ���
			if (true == CheckWarpStart() && false == GlobalValue::CurPlayer->GetIsMove())
			{
				State_.ChangeState("Warp");
			}
			// �ƴ϶�� �̵����·� ��ȯ
			else
			{
				// �̵�Ÿ�� Ÿ�� ����
				GameEngineRandom Random;
				MoveTargetTile_ = MaxMoveRange_[Random.RandomInt(0, static_cast<int>(MaxMoveRange_.size()) - 1)];
				TargetPos_ = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);

				MovePath_.clear();
				float4 CurTargetPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
				MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_SketelonWarrior, WarriorNavigationIndex_, GetTransform()->GetWorldPosition(), CurTargetPos);
				if (false == MovePath_.empty())
				{
					// ���� �̵�Ÿ���ε��� Get
					MoveTargetTile_.Index_ = MovePath_.front().Index_;

					// Ÿ����ġ�� ������ ����� �ε�������
					MovePath_.pop_front();

					// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
					// �÷��̾��� �̵������� �����Ѵ�.
					float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
					MoveTargetDir_ = DirPos.NormalizeReturn3D();

					State_.ChangeState("Walk");
				}
			}
		}

		CheckTime_ = 1.5f;
	}
}

void SketelonWarrior::EndIdleState()
{
}

// �̵�����
void SketelonWarrior::StartWalkState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::WALK;

	// ���� �̵����� �� �ִϸ��̼� ����
	TargetDirCheck(TargetPos_, "Walk");
}

void SketelonWarrior::UpdateWalkState()
{
	// �̵�
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// �̵� �� �������� ����
	if (true == MonsterDetect())
	{
		// ���ݻ��·� ��ȯ
		State_.ChangeState("Attack");
		return;
	}

	if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
	{
		if (false == MovePath_.empty())
		{
			// Ÿ��Ÿ�� �ε��� ����
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// ���� ��ǥŸ�ϱ����� ������ ��� ��
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// ���� �̵����� �� �ִϸ��̼� �����ϰ�,
			TargetPos_ = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
			TargetDirCheck(TargetPos_, "Walk");

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();
		}
		else
		{
			// �� �̻� �̵��� ������ �����Ƿ� �÷��̾� ������ ����
			State_.ChangeState("Idle");

			// Ȥ�� �����ϴ� ��ΰ� �ִٸ� Ŭ����
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}
}

void SketelonWarrior::EndWalkState()
{
	// Ȥ�� �� ���� ��� ����
	MovePath_.clear();
}

// ��������
void SketelonWarrior::StartWarpState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::WARP;
}

void SketelonWarrior::UpdateWarpState()
{
	// ���� �÷��̾� ��ġ�� ���� �� ������ ��ȯ
	GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	State_.ChangeState("Idle");
}

void SketelonWarrior::EndWarpState()
{
}

// ���ݻ���
void SketelonWarrior::StartAttackState()
{
	// ���� ������ ������ ��ġ
	TargetDirCheck(DetectMonster_->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::ATTACK;
}

void SketelonWarrior::UpdateAttackState()
{
}

void SketelonWarrior::EndAttackState()
{
}

// �ǰݻ���
void SketelonWarrior::StartGetHitState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::GETHIT;
}

void SketelonWarrior::UpdateGetHitState()
{
	// �������� �ް� �����·� ��ȯ

	State_.ChangeState("Idle");
}

void SketelonWarrior::EndGetHitState()
{
}

// �������
void SketelonWarrior::StartDeathState()
{
	TargetDirCheck(TargetPos_, "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWarriorState::DEATH;
}

void SketelonWarrior::UpdateDeathState()
{
}

void SketelonWarrior::EndDeathState()
{
}

// Ư�� �ִϸ��̼� ����� ȣ�� �Լ�
void SketelonWarrior::SpawnAnimationEnd()
{
	State_.ChangeState("Idle");
}

void SketelonWarrior::AttackAnimationEnd()
{
	// ���� Ÿ���� ���� ����
	if (nullptr != DetectMonster_)
	{
		std::string DetectActor = DetectMonster_->GetName();
		if (std::string::npos != DetectActor.find("Fallen"))
		{
			Fallen* CurAttackMonster = (Fallen*)DetectMonster_;
			if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
				Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->HitDamage(SketelonWarriorInfo_.SkillDamage);
			}
		}
		else if (std::string::npos != DetectActor.find("SpikeFiend"))
		{
			SpikeFiend* CurAttackMonster = (SpikeFiend*)DetectMonster_;
			if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
				SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->HitDamage(SketelonWarriorInfo_.SkillDamage);
			}
		}
		else if (std::string::npos != DetectActor.find("Tainted"))
		{
			Tainted* CurAttackMonster = (Tainted*)DetectMonster_;
			if (Tainted_FSMState::TT_DEAD != CurAttackMonster->GetCurState() &&
				Tainted_FSMState::TT_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->HitDamage(SketelonWarriorInfo_.SkillDamage);
			}
		}
		else if (std::string::npos != DetectActor.find("Zombie"))
		{
			Zombie* CurAttackMonster = (Zombie*)DetectMonster_;
			if (Zombie_FSMState::ZB_DEAD != CurAttackMonster->GetCurState() &&
				Zombie_FSMState::ZB_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->HitDamage(SketelonWarriorInfo_.SkillDamage);
			}
		}
		else if (std::string::npos != DetectActor.find("Andariel"))
		{
			Andariel* CurAttackMonster = (Andariel*)DetectMonster_;
			if (Andariel_FSMState::AD_DEAD != CurAttackMonster->GetCurState() &&
				Andariel_FSMState::AD_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->HitDamage(SketelonWarriorInfo_.SkillDamage);
			}
		}

		DetectMonster_ = nullptr;
	}

	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void SketelonWarrior::GetHitAnimationEnd()
{
	// ������ HP �Ҹ�
	CurHP_ -= 10;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Death");
	}
	else
	{
		// ��� ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void SketelonWarrior::DeathAnimationEnd()
{
	// �÷��̾ ���� ��ȯ�� �����ڷ�(������) ��Ͽ��� �ش� ���͸� ã�Ƽ�
	// ���ó���� ��Ͽ��� ����
	// ��, �ִ���� �Ѿ�� �̹� ����� �����ڷ��� �̹� ��Ͽ��� ���ŵǾ��ִ�.
	GlobalValue::CurPlayer->SkeletonWarriorDeath(this);
}
