#include "PreCompile.h"
#include "SketelonWizard.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"

#include "WizardProjectile.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

// Ÿ�� ���� üũ
void SketelonWizard::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = SketelonWizard_TargetDir::SW_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = SketelonWizard_TargetDir::SW_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = SketelonWizard_TargetDir::SW_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = SketelonWizard_TargetDir::SW_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = SketelonWizard_TargetDir::SW_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = SketelonWizard_TargetDir::SW_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = SketelonWizard_TargetDir::SW_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = SketelonWizard_TargetDir::SW_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = SketelonWizard_TargetDir::SW_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = SketelonWizard_TargetDir::SW_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ����
void SketelonWizard::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case SketelonWizard_TargetDir::SW_LB:
		{
			AnimationName += "_LB";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_LT:
		{
			AnimationName += "_LT";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_RT:
		{
			AnimationName += "_RT";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_RB:
		{
			AnimationName += "_RB";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_B:
		{
			AnimationName += "_B";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_L:
		{
			AnimationName += "_L";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_T:
		{
			AnimationName += "_T";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_R:
		{
			AnimationName += "_R";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

bool SketelonWizard::MonsterDetect()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
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

bool SketelonWizard::CheckWarpStart()
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
void SketelonWizard::StartSpawnState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::SPAWN;

	// ��ȯ ���� ���
	StateSound_->PlayAlone("SkeletonSpawn.wav", 0);
}

void SketelonWizard::UpdateSpawnState()
{
}

void SketelonWizard::EndSpawnState()
{
}

// ������
void SketelonWizard::StartIdleState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::IDLE;

	// ���� �÷��̾��� ��ġ���� ���� �̵������� �����Ѵ�.
	SetMoveRange();
}

void SketelonWizard::UpdateIdleState()
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
			if (true == CheckWarpStart())
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
				MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_SketelonWizard, WizardNavigationIndex_, GetTransform()->GetWorldPosition(), CurTargetPos);
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

void SketelonWizard::EndIdleState()
{
}

// �̵�����
void SketelonWizard::StartWalkState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::WALK;

	// ���� �̵����� �� �ִϸ��̼� ����
	TargetDirCheck(TargetPos_, "Walk");
}

void SketelonWizard::UpdateWalkState()
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

void SketelonWizard::EndWalkState()
{
	// Ȥ�� �� ���� ��� ����
	MovePath_.clear();
}

// ��������
void SketelonWizard::StartWarpState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::WARP;
}

void SketelonWizard::UpdateWarpState()
{
	// ���� �÷��̾� ��ġ�� ���� �� ������ ��ȯ
	GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	State_.ChangeState("Idle");
}

void SketelonWizard::EndWarpState()
{
}

// ���ݻ���
void SketelonWizard::StartAttackState()
{
	// ���� ������ ������ ��ġ
	TargetDirCheck(DetectMonster_->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::ATTACK;
}

void SketelonWizard::UpdateAttackState()
{
}

void SketelonWizard::EndAttackState()
{
}

// �ǰݻ���
void SketelonWizard::StartGetHitState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::GETHIT;
}

void SketelonWizard::UpdateGetHitState()
{
	// �������� �ް� �����·� ��ȯ

	State_.ChangeState("Idle");
}

void SketelonWizard::EndGetHitState()
{
}

// �������
void SketelonWizard::StartDeathState()
{
	TargetDirCheck(TargetPos_, "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::DEATH;
}

void SketelonWizard::UpdateDeathState()
{
}

void SketelonWizard::EndDeathState()
{
}

// Ư�� �ִϸ��̼� ����� ȣ�� �Լ�
void SketelonWizard::SpawnAnimationEnd()
{
	State_.ChangeState("Idle");
}

void SketelonWizard::AttackAnimationEnd()
{
	// ���� Ÿ���� ���� ����
	if (nullptr != DetectMonster_)
	{
		// �߻�ü �߻�(��, �ƹ��� �浹�� ���� 5�ʰ� �̵��ߴٸ� �ڵ��Ҹ�)
		float4 TargetPos = DetectMonster_->GetTransform()->GetWorldPosition();
		WizardProjectile* NewProjectile = GetLevel()->CreateActor<WizardProjectile>();
		NewProjectile->SkeletonWizardFire(WizardType_, GetTransform()->GetWorldPosition(), TargetPos, SketelonWizardInfo_.SkillDamage);
		NewProjectile->Release(5.f);

		DetectMonster_ = nullptr;
	}

	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void SketelonWizard::GetHitAnimationEnd()
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

void SketelonWizard::DeathAnimationEnd()
{
	// �÷��̾ ���� ��ȯ�� �����ڷ�(������) ��Ͽ��� �ش� ���͸� ã�Ƽ�
	// ���ó���� ��Ͽ��� ����
	// ��, �ִ���� �Ѿ�� �̹� ����� �����ڷ��� �̹� ��Ͽ��� ���ŵǾ��ִ�.
	GlobalValue::CurPlayer->SkeletonWizardDeath(this);
}
