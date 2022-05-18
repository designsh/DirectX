#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>

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

// ��ȯ����
void SummonsGolem::StartSpawnState()
{
	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::SPAWN;

	// 
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
	TargetDirCheck(TargetPos_, "Idle");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::IDLE;
}

void SummonsGolem::UpdateIdleState()
{
	// ���� �̵����ѹ����� Ÿ���� ������Ÿ���� ��ǥŸ�Ϸ� ���� �� 
	// �̵����·� ��ȯ



}

void SummonsGolem::EndIdleState()
{

}

// �̵�����
void SummonsGolem::StartWalkState()
{
	TargetDirCheck(TargetPos_, "Walk");

	// ���� ���� ��ȯ
	PrevState_ = CurState_;
	CurState_ = GolemState::WALK;

	// 

}

void SummonsGolem::UpdateWalkState()
{
	// �÷��̾� �ֺ� �������������� �̵�



	// �̵� �� �������� ���� ����
	// ��, �̵������� ����ٸ� �÷��̾� �ڸ��� ����






	
}

void SummonsGolem::EndWalkState()
{

}

// ���ݻ���
void SummonsGolem::StartAttackState()
{
	TargetDirCheck(TargetPos_, "Attack");

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
