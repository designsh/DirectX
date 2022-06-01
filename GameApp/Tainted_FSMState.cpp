#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

// Ÿ����ġ�� �̵����� ��ȯ
void Tainted::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			break;
		}
		case Tainted_Dir::TT_RT:
		{
			AnimationName += "_RT";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_RB:
		{
			AnimationName += "_RB";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_B:
		{
			AnimationName += "_B";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_L:
		{
			AnimationName += "_L";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_T:
		{
			AnimationName += "_T";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
		case Tainted_Dir::TT_R:
		{
			AnimationName += "_R";
			Tainted_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

// ���� ��Ž�� ����
void Tainted::StartRoomDetect()
{
	// �ִϸ��̼� ����
	ChangeAnimationCheck("Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_ROOMDETECT;
}

void Tainted::UpdateRoomDetect()
{
	// �÷��̾� �� ���Խ� �����·� ��ȯ
	if (true == EnterTheRoomDetectCheck())
	{
		// ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void Tainted::EndRoomDetect()
{
	// ���߰� ���� ���
	StateSound_->PlayAlone("Tainted_Detect.wav", 0);
}

// ������
void Tainted::StartIdle()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_IDLE;
}

void Tainted::UpdateIdle()
{
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		State_.ChangeState("Walk");

		IdleDelayTime_ = 1.f;
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
	CurState_ = Tainted_FSMState::TT_WALK;

	// �÷��̾� ���� �̵���� ����
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Tainted, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void Tainted::UpdateMove()
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

void Tainted::EndMove()
{
}

// �⺻���ݻ���
void Tainted::StartNormalAttack()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_ATTACK;

	// ���� ���� ���
	StateSound_->PlayAlone("Tainted_Attack.wav", 0);
}

void Tainted::UpdateNormalAttack()
{
}

void Tainted::EndNormalAttack()
{
}

// �ǰݻ���
void Tainted::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_GETHIT;

	// �ǰ� ���� ���
	StateSound_->PlayAlone("Tainted_GetHit.wav", 0);

	// Ư�� ���ݿ� ���� �ǰݽ� �ش� ������ ���� ����
	if (true == SpecialGetHit_)
	{
		SpecialGetHitTime_ = 0.2f;

		switch (CurDamageType_)
		{
			case MonsterDamageType::COLD:
			{
				Tainted_->SetResultColor(float4(0.f, 0.f, 1.f, 1.f));
				break;
			}
			case MonsterDamageType::POISON:
			{
				Tainted_->SetResultColor(float4(0.f, 1.f, 0.f, 1.f));
				break;
			}
		}
	}
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
	CurState_ = Tainted_FSMState::TT_DEATH;

	// ��� ���� ���
	StateSound_->PlayAlone("Tainted_Death.wav", 0);

	// ����� ���� �÷��̾��� ����ġ�� ����
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->AddCurrentEXP(MonsterInfo_.DropEXP);
	}
}

void Tainted::UpdateDeath()
{
}

void Tainted::EndDeath()
{
}

// ��ü����
void Tainted::StartDead()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_DEAD;
}

void Tainted::UpdateDead()
{
}

void Tainted::EndDead()
{
}
