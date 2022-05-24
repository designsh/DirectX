#include "PreCompile.h"
#include "Fallen.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

void Fallen::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = Fallen_TargetDir::FL_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = Fallen_TargetDir::FL_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = Fallen_TargetDir::FL_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = Fallen_TargetDir::FL_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = Fallen_TargetDir::FL_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = Fallen_TargetDir::FL_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = Fallen_TargetDir::FL_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = Fallen_TargetDir::FL_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = Fallen_TargetDir::FL_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = Fallen_TargetDir::FL_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ��ȯ
void Fallen::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case Fallen_TargetDir::FL_LB:
		{
			AnimationName += "_LB";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_LT:
		{
			AnimationName += "_LT";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_RT:
		{
			AnimationName += "_RT";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_RB:
		{
			AnimationName += "_RB";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_B:
		{
			AnimationName += "_B";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_L:
		{
			AnimationName += "_L";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_T:
		{
			AnimationName += "_T";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
		case Fallen_TargetDir::FL_R:
		{
			AnimationName += "_R";
			Fallen_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

// ���� ��Ž�� ����
void Fallen::StartRoomDetect()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	ChangeAnimationCheck("Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_ROOMDETECT;
}

void Fallen::UpdateRoomDetect()
{
	// �÷��̾� �� ���Խ� �����·� ��ȯ
	if (true == EnterTheRoomDetectCheck())
	{
		// ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void Fallen::EndRoomDetect()
{
}

// ������
void Fallen::StartIdle()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_IDLE;
}

void Fallen::UpdateIdle()
{
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		State_.ChangeState("Walk");

		IdleDelayTime_ = 1.f;
	}
}

void Fallen::EndIdle()
{
}

// �̵�����
void Fallen::StartMove()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_WALK;

	// �÷��̾� ���� �̵���� ����
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Fallen, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void Fallen::UpdateMove()
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

void Fallen::EndMove()
{
}

// �⺻���ݻ���
void Fallen::StartNormalAttack()
{	
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_ATTACK;
}

void Fallen::UpdateNormalAttack()
{
}

void Fallen::EndNormalAttack()
{
	Attack_ = true;
}

// �ǰݻ���
void Fallen::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_GETHIT;
}

void Fallen::UpdateGetHit()
{
}

void Fallen::EndGetHit()
{
}

// �������
void Fallen::StartDeath()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_DEATH;
}

void Fallen::UpdateDeath()
{
}

void Fallen::EndDeath()
{
}

// ��ü����
void Fallen::StartDead()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_DEAD;
}

void Fallen::UpdateDead()
{
}

void Fallen::EndDead()
{
}
