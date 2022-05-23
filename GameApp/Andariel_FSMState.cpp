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
			CurDir_ = Andariel_TargetDir::AD_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = Andariel_TargetDir::AD_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = Andariel_TargetDir::AD_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = Andariel_TargetDir::AD_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = Andariel_TargetDir::AD_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = Andariel_TargetDir::AD_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = Andariel_TargetDir::AD_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = Andariel_TargetDir::AD_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = Andariel_TargetDir::AD_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = Andariel_TargetDir::AD_B;
		}
	}

	// 애니메이션 변경
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

// 최초 적탐지 상태
void Andariel::StartRoomDetect()
{
	// 현재방향 체크 및 애니메이션변경
	ChangeAnimationCheck("Idle");

	// 상태변경
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_ROOMDETECT;
}

void Andariel::UpdateRoomDetect()
{
	// 플레이어 룸 진입시 대기상태로 전환
	if (true == EnterTheRoomDetectCheck())
	{
		// 상태 전환
		State_.ChangeState("Idle");
	}
}

void Andariel::EndRoomDetect()
{
}

// 대기상태
void Andariel::StartIdle()
{
	// 현재방향 체크 및 애니메이션변경
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 상태변경
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_IDLE;
}

void Andariel::UpdateIdle()
{

}

void Andariel::EndIdle()
{

}

// 이동상태
void Andariel::StartMove()
{

}

void Andariel::UpdateMove()
{

}

void Andariel::EndMove()
{

}

// 기본공격상태
void Andariel::StartNormalAttack()
{

}

void Andariel::UpdateNormalAttack()
{

}

void Andariel::EndNormalAttack()
{

}

// 스킬공격상태
void Andariel::StartSkillAttack()
{

}

void Andariel::UpdateSkillAttack()
{

}

void Andariel::EndSkillAttack()
{

}

// 피격상태
void Andariel::StartGetHit()
{

}

void Andariel::UpdateGetHit()
{

}

void Andariel::EndGetHit()
{

}

// 사망상태
void Andariel::StartDeath()
{

}

void Andariel::UpdateDeath()
{

}

void Andariel::EndDeath()
{

}

// 시체상태
void Andariel::StartDead()
{

}

void Andariel::UpdateDead()
{

}

void Andariel::EndDead()
{

}
