#include "PreCompile.h"
#include "Zombie.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

void Zombie::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = Zombie_TargetDir::ZB_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = Zombie_TargetDir::ZB_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = Zombie_TargetDir::ZB_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = Zombie_TargetDir::ZB_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = Zombie_TargetDir::ZB_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = Zombie_TargetDir::ZB_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = Zombie_TargetDir::ZB_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = Zombie_TargetDir::ZB_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = Zombie_TargetDir::ZB_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = Zombie_TargetDir::ZB_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ��ȯ
void Zombie::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
	case Zombie_TargetDir::ZB_LB:
	{
		AnimationName += "_LB";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_LT:
	{
		AnimationName += "_LT";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_RT:
	{
		AnimationName += "_RT";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_RB:
	{
		AnimationName += "_RB";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_B:
	{
		AnimationName += "_B";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_L:
	{
		AnimationName += "_L";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_T:
	{
		AnimationName += "_T";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	case Zombie_TargetDir::ZB_R:
	{
		AnimationName += "_R";
		Zombie_->SetChangeAnimation(AnimationName);
		break;
	}
	}
}

// ���� ��Ž�� ����
void Zombie::StartRoomDetect()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	ChangeAnimationCheck("Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_ROOMDETECT;
}

void Zombie::UpdateRoomDetect()
{
	// �÷��̾� �� ���Խ� �����·� ��ȯ
	if (true == EnterTheRoomDetectCheck())
	{
		// ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void Zombie::EndRoomDetect()
{
	// ���߰� ���� ���
	StateSound_->PlayAlone("Zombie_Detect.wav", 0);
}

// ������
void Zombie::StartIdle()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_IDLE;
}

void Zombie::UpdateIdle()
{
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		State_.ChangeState("Walk");

		IdleDelayTime_ = 1.f;
	}
}

void Zombie::EndIdle()
{
}

// �̵�����(����������)
void Zombie::StartMove()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_WALK;

	// �÷��̾� ���� �̵���� ����
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Zombie, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void Zombie::UpdateMove()
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

void Zombie::EndMove()
{
}

// �⺻���ݻ���
void Zombie::StartNormalAttack()
{	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_ATTACK;

	// ���� ���� ���
	StateSound_->PlayAlone("Zombie_Attack.wav", 0);
}

void Zombie::UpdateNormalAttack()
{
}

void Zombie::EndNormalAttack()
{
	Attack_ = false;
}

// �ǰݻ���
void Zombie::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_GETHIT;

	// �ǰ� ���� ���
	StateSound_->PlayAlone("Zombie_GetHit.wav", 0);

	// Ư�� ���ݿ� ���� �ǰݽ� �ش� ������ ���� ����
	if (true == SpecialGetHit_)
	{
		switch (CurDamageType_)
		{
			case MonsterDamageType::COLD:
			{
				Zombie_->SetResultColor(float4(0.f, 0.f, 1.f, 1.f));
				break;
			}
			case MonsterDamageType::POISON:
			{
				Zombie_->SetResultColor(float4(0.f, 1.f, 0.f, 1.f));
				break;
			}
		}
	}
}

void Zombie::UpdateGetHit()
{
}

void Zombie::EndGetHit()
{
	CurDamageType_ = MonsterDamageType::NONE;
	SpecialGetHit_ = false;
	Zombie_->SetResultColor(float4::ONE);
}

// �������
void Zombie::StartDeath()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_DEATH;

	// ��� ���� ���
	StateSound_->PlayAlone("Zombie_Death.wav", 0);

	// ����� ���� �÷��̾��� ����ġ�� ����
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->AddCurrentEXP(MonsterInfo_.DropEXP);
	}
}

void Zombie::UpdateDeath()
{
}

void Zombie::EndDeath()
{
}

// ��ü����
void Zombie::StartDead()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Zombie_FSMState::ZB_DEAD;
}

void Zombie::UpdateDead()
{
}

void Zombie::EndDead()
{
}
