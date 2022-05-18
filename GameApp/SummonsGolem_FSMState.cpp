#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>

// 타겟 방향 체크 후 애니메이션 변경
void SummonsGolem::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
{
	// 현재방향을 이전방향에 저장
	PrevDir_ = CurDir_;

	// 현재 위치와 타겟위치의 각도를 계산
	float4 Direct = _TargetPos - GetTransform()->GetWorldPosition();
	Direct.Normalize3D();

	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // 오른쪽
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// 우상단
			CurDir_ = GolemTargetDir::GL_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = GolemTargetDir::GL_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = GolemTargetDir::GL_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = GolemTargetDir::GL_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = GolemTargetDir::GL_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = GolemTargetDir::GL_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = GolemTargetDir::GL_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = GolemTargetDir::GL_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = GolemTargetDir::GL_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = GolemTargetDir::GL_B;
		}
	}

	// 애니메이션 변경
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

// 소환상태
void SummonsGolem::StartSpawnState()
{
	// 현재 상태 전환
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

// 대기상태
void SummonsGolem::StartIdleState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::IDLE;
}

void SummonsGolem::UpdateIdleState()
{
	// 골렘의 이동제한범위의 타일중 랜덤한타일을 목표타일로 설정 후 
	// 이동상태로 전환



}

void SummonsGolem::EndIdleState()
{

}

// 이동상태
void SummonsGolem::StartWalkState()
{
	TargetDirCheck(TargetPos_, "Walk");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::WALK;

	// 

}

void SummonsGolem::UpdateWalkState()
{
	// 플레이어 주변 일정범위내에서 이동



	// 이동 중 적감지시 적을 공격
	// 단, 이동범위를 벗어났다면 플레이어 자리로 워프






	
}

void SummonsGolem::EndWalkState()
{

}

// 공격상태
void SummonsGolem::StartAttackState()
{
	TargetDirCheck(TargetPos_, "Attack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::ATTACK;
}

void SummonsGolem::UpdateAttackState()
{
	
}

void SummonsGolem::EndAttackState()
{

}

// 사망상태
void SummonsGolem::StartDeathState()
{
	TargetDirCheck(TargetPos_, "Death");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::DEATH;
}

void SummonsGolem::UpdateDeathState()
{

}

void SummonsGolem::EndDeathState()
{

}
