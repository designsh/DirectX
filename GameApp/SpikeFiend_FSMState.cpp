#include "PreCompile.h"
#include "SpikeFiend.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

void SpikeFiend::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = SpikeFiend_TargetDir::SF_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = SpikeFiend_TargetDir::SF_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = SpikeFiend_TargetDir::SF_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = SpikeFiend_TargetDir::SF_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = SpikeFiend_TargetDir::SF_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = SpikeFiend_TargetDir::SF_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = SpikeFiend_TargetDir::SF_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = SpikeFiend_TargetDir::SF_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = SpikeFiend_TargetDir::SF_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = SpikeFiend_TargetDir::SF_B;
		}
	}

	// �ִϸ��̼� ����
	ChangeAnimationCheck(_StateName);
}

// ���⺰ �ִϸ��̼� ��ȯ
void SpikeFiend::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case SpikeFiend_TargetDir::SF_LB:
		{
			AnimationName += "_LB";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_LT:
		{
			AnimationName += "_LT";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_RT:
		{
			AnimationName += "_RT";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_RB:
		{
			AnimationName += "_RB";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_B:
		{
			AnimationName += "_B";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_L:
		{
			AnimationName += "_L";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_T:
		{
			AnimationName += "_T";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
		case SpikeFiend_TargetDir::SF_R:
		{
			AnimationName += "_R";
			SpikeFiend_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

// ���� ��Ž�� ����
void SpikeFiend::StartRoomDetect()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	ChangeAnimationCheck("Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_ROOMDETECT;
}

void SpikeFiend::UpdateRoomDetect()
{
	// �÷��̾� �� ���Խ� �����·� ��ȯ
	if (true == EnterTheRoomDetectCheck())
	{
		// ���� ��ȯ
		State_.ChangeState("Idle");
	}
}

void SpikeFiend::EndRoomDetect()
{
	// ������ ���� ���
	StateSound_->PlayAlone("SpikeFiend_Detect.wav", 0);
}

// ������
void SpikeFiend::StartIdle()
{
	// ������� üũ �� �ִϸ��̼Ǻ���
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// ���º���
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_IDLE;
}

void SpikeFiend::UpdateIdle()
{
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		State_.ChangeState("Walk");

		IdleDelayTime_ = 1.f;
	}
}

void SpikeFiend::EndIdle()
{
}

// �̵�����(����������)
void SpikeFiend::StartMove()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_WALK;

	// �÷��̾� ���� �̵���� ����
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::SpikeFiend, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void SpikeFiend::UpdateMove()
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

void SpikeFiend::EndMove()
{
}

// �⺻���ݻ���
void SpikeFiend::StartNormalAttack()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_ATTACK;

	// ���� ���� ���
	StateSound_->PlayAlone("SpikeFiend_Attack.wav", 0);
}

void SpikeFiend::UpdateNormalAttack()
{
}

void SpikeFiend::EndNormalAttack()
{
}

// �ǰݻ���
void SpikeFiend::StartGetHit()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_GETHIT;

	// �ǰ� ���� ���
	StateSound_->PlayAlone("SpikeFiend_GetHit.wav", 0);

	// Ư�� ���ݿ� ���� �ǰݽ� �ش� ������ ���� ����
	if (true == SpecialGetHit_)
	{
		SpecialGetHitTime_ = 0.2f;

		switch (CurDamageType_)
		{
			case MonsterDamageType::COLD:
			{
				SpikeFiend_->SetResultColor(float4(0.f, 0.f, 1.f, 1.f));
				break;
			}
			case MonsterDamageType::POISON:
			{
				SpikeFiend_->SetResultColor(float4(0.f, 1.f, 0.f, 1.f));
				break;
			}
		}
	}
}

void SpikeFiend::UpdateGetHit()
{
}

void SpikeFiend::EndGetHit()
{
	CurDamageType_ = MonsterDamageType::NONE;
	SpecialGetHit_ = false;
	SpikeFiend_->SetResultColor(float4::ONE);
}

// �������
void SpikeFiend::StartDeath()
{
	// ������ üũ�Ͽ� �ִϸ��̼� �� ���⼳��
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_DEATH;

	// ��� ���� ���
	StateSound_->PlayAlone("SpikeFiend_Death.wav", 0);

	// ����� ���� �÷��̾��� ����ġ�� ����
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->AddCurrentEXP(MonsterInfo_.DropEXP);
	}
}

void SpikeFiend::UpdateDeath()
{
}

void SpikeFiend::EndDeath()
{
}

// ��ü����
void SpikeFiend::StartDead()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = SpikeFiend_FSMState::SF_DEAD;
}

void SpikeFiend::UpdateDead()
{
}

void SpikeFiend::EndDead()
{
}

