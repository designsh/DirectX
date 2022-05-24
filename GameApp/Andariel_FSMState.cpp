#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

void Andariel::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = Andariel_TargetDir::AD_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = Andariel_TargetDir::AD_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = Andariel_TargetDir::AD_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = Andariel_TargetDir::AD_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = Andariel_TargetDir::AD_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = Andariel_TargetDir::AD_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = Andariel_TargetDir::AD_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = Andariel_TargetDir::AD_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = Andariel_TargetDir::AD_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = Andariel_TargetDir::AD_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

void Andariel::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case Andariel_TargetDir::AD_LB:
		{
			AnimationName += "_LB";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_LT:
		{
			AnimationName += "_LT";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_RT:
		{
			AnimationName += "_RT";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_RB:
		{
			AnimationName += "_RB";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_B:
		{
			AnimationName += "_B";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_L:
		{
			AnimationName += "_L";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_T:
		{
			AnimationName += "_T";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
		case Andariel_TargetDir::AD_R:
		{
			AnimationName += "_R";
			Andariel_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

// ���� ��Ž�� ����
void Andariel::StartRoomDetect()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	ChangeAnimationCheck("Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_ROOMDETECT;
}

void Andariel::UpdateRoomDetect()
{
	// �÷��̾� �� ���Խ� �����·� ��ȯ
	if (true == EnterTheRoomDetectCheck())
	{
		// ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void Andariel::EndRoomDetect()
{
}

// ������
void Andariel::StartIdle()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_IDLE;
}

void Andariel::UpdateIdle()
{
	// ��ų������ �����ϴٸ� ��ų���ݻ��·� ��ȯ
	if (true == SkillAttack_)
	{
		State_.ChangeState("SkillAttack");
		return;
	}

	// �ƴ϶�� ���ð� üũ�Ͽ� �̵����·� ��ȯ
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		State_.ChangeState("Walk");
		IdleDelayTime_ = 1.f;
	}
}

void Andariel::EndIdle()
{
}

// �̵�����
void Andariel::StartMove()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_WALK;

	// �̵���� ����
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Andariel, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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
	}
}

void Andariel::UpdateMove()
{
	// ������ �̵���� ��� �Ҹ𶧱��� �̵�
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
			float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
			TargetDirCheck(MovePos, "Walk");

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();
		}
		else // �̵��Ϸ�� 
		{
			State_.ChangeState("Attack");
		}
	}

	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
}

void Andariel::EndMove()
{
	MovePath_.clear();
}

// �⺻���ݻ���
void Andariel::StartNormalAttack()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_ATTACK;
}

void Andariel::UpdateNormalAttack()
{
}

void Andariel::EndNormalAttack()
{
}

// ��ų���ݻ���
void Andariel::StartSkillAttack()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "SkillAttack");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_SKILLATTACK;
}

void Andariel::UpdateSkillAttack()
{
}

void Andariel::EndSkillAttack()
{
	// ��ų �߻�Ϸ� �� ��ų���ݰ��ɿ��� Flag ����
	SkillAttack_ = false;
}

// �ǰݻ���
void Andariel::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_GETHIT;
}

void Andariel::UpdateGetHit()
{
	State_.ChangeState("Idle");
}

void Andariel::EndGetHit()
{
}

// �������
void Andariel::StartDeath()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_DEATH;
}

void Andariel::UpdateDeath()
{
}

void Andariel::EndDeath()
{
}

// ��ü����
void Andariel::StartDead()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_DEAD;
}

void Andariel::UpdateDead()
{
}

void Andariel::EndDead()
{
}
