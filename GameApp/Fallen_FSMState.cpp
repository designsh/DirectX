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
			CurDir_ = Fallen_TargetDir::FL_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = Fallen_TargetDir::FL_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = Fallen_TargetDir::FL_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = Fallen_TargetDir::FL_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = Fallen_TargetDir::FL_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = Fallen_TargetDir::FL_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = Fallen_TargetDir::FL_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = Fallen_TargetDir::FL_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = Fallen_TargetDir::FL_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = Fallen_TargetDir::FL_B;
		}
	}

	// 애니메이션 변경
	ChangeAnimationCheck(_StateName);
}

// 방향별 애니메이션 전환
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

// 최초 적탐지 상태
void Fallen::StartRoomDetect()
{
	// 현재방향 체크 및 애니메이션변경
	ChangeAnimationCheck("Idle");

	// 상태변경
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_ROOMDETECT;
}

void Fallen::UpdateRoomDetect()
{
	// 플레이어 룸 진입시 대기상태로 전환
	if (true == EnterTheRoomDetectCheck())
	{
		// 상태 전환
		State_.ChangeState("Idle");
	}
}

void Fallen::EndRoomDetect()
{
}

// 대기상태
void Fallen::StartIdle()
{
	// 현재방향 체크 및 애니메이션변경
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 상태변경
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

// 이동상태
void Fallen::StartMove()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_WALK;

	// 플레이어 방향 이동경로 생성
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Fallen, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
	if (false == MovePath_.empty())
	{
		// 다음 이동타일인덱스 Get
		MoveTargetTile_.Index_ = MovePath_.front().Index_;

		// 타겟위치로 지정된 경로의 인덱스제거
		MovePath_.pop_front();

		// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
		// 플레이어의 이동방향을 설정한다.
		float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
		MoveTargetDir_ = DirPos.NormalizeReturn3D();
	}
}

void Fallen::UpdateMove()
{
	// 생성된 이동경로 모두 소모때까지 이동
	if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
	{
		if (false == MovePath_.empty())
		{
			// 타겟타일 인덱스 변경
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// 현재 목표타일까지의 방향을 계산 후
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// 현재 이동방향 및 애니메이션 변경하고,
			float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
			TargetDirCheck(MovePos, "Walk");

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();
		}
		else // 이동완료시 
		{
			State_.ChangeState("Attack");
		}
	}

	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
}

void Fallen::EndMove()
{
}

// 기본공격상태
void Fallen::StartNormalAttack()
{	
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// 현재 상태 전환
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

// 피격상태
void Fallen::StartGetHit()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_GETHIT;
}

void Fallen::UpdateGetHit()
{
}

void Fallen::EndGetHit()
{
}

// 사망상태
void Fallen::StartDeath()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_DEATH;
}

void Fallen::UpdateDeath()
{
}

void Fallen::EndDeath()
{
}

// 시체상태
void Fallen::StartDead()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Fallen_FSMState::FL_DEAD;
}

void Fallen::UpdateDead()
{
}

void Fallen::EndDead()
{
}
