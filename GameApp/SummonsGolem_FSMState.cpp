#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "FixedTileMap_Common.h"
#include "CatacombsMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

// Ÿ�� ���� üũ �� �ִϸ��̼� ����
void SummonsGolem::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = GolemTargetDir::GL_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = GolemTargetDir::GL_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = GolemTargetDir::GL_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = GolemTargetDir::GL_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = GolemTargetDir::GL_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = GolemTargetDir::GL_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = GolemTargetDir::GL_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = GolemTargetDir::GL_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = GolemTargetDir::GL_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = GolemTargetDir::GL_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

void SummonsGolem::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case GolemTargetDir::GL_LB:
		{
			AnimationName += "_LB";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_LT:
		{
			AnimationName += "_LT";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_RT:
		{
			AnimationName += "_RT";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_RB:
		{
			AnimationName += "_RB";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_B:
		{
			AnimationName += "_B";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_L:
		{
			AnimationName += "_L";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_T:
		{
			AnimationName += "_T";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case GolemTargetDir::GL_R:
		{
			AnimationName += "_R";
			GolemRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

bool SummonsGolem::MonsterDetect()
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

// ��ȯ����
void SummonsGolem::StartSpawnState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::SPAWN;
}

void SummonsGolem::UpdateSpawnState()
{
}

void SummonsGolem::EndSpawnState() 
{
}

// ������
void SummonsGolem::StartIdleState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::IDLE;

	// ���� �÷��̾��� ��ġ���� ���� �̵������� �����Ѵ�.
	SetMoveRange();
}

void SummonsGolem::UpdateIdleState()
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
				MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_Golem, 0, GetTransform()->GetWorldPosition(), CurTargetPos);
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

void SummonsGolem::EndIdleState()
{
}

// �̵�����
void SummonsGolem::StartWalkState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::WALK;

	// ���� �̵����� �� �ִϸ��̼� ����
	TargetDirCheck(TargetPos_, "Walk");
}

void SummonsGolem::UpdateWalkState()
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

void SummonsGolem::EndWalkState()
{
	// Ȥ�� �� ��θ� ����
	MovePath_.clear();
}

// ��������
void SummonsGolem::StartWarpState()
{
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::WARP;
}

void SummonsGolem::UpdateWarpState()
{
	// ���� �÷��̾� ��ġ�� ���� �� ������ ��ȯ
	GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	State_.ChangeState("Idle");
}

void SummonsGolem::EndWarpState()
{
}

// ���ݻ���
void SummonsGolem::StartAttackState()
{
	// ���� ������ ������ ��ġ
	TargetDirCheck(DetectMonster_->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::ATTACK;
}

void SummonsGolem::UpdateAttackState()
{
}

void SummonsGolem::EndAttackState()
{
}

// �ǰݻ���
void SummonsGolem::StartGetHitState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::GETHIT;
}

void SummonsGolem::UpdateGetHitState()
{
	// �������� �ް� �����·� ��ȯ

	State_.ChangeState("Idle");
}

void SummonsGolem::EndGetHitState()
{
}

// �������
void SummonsGolem::StartDeathState()
{
	TargetDirCheck(TargetPos_, "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::DEATH;
}

void SummonsGolem::UpdateDeathState()
{
}

void SummonsGolem::EndDeathState()
{
}
