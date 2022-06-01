#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

// 타겟위치별 이동방향 전환
void Tainted::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = Tainted_Dir::TT_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = Tainted_Dir::TT_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = Tainted_Dir::TT_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = Tainted_Dir::TT_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = Tainted_Dir::TT_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = Tainted_Dir::TT_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = Tainted_Dir::TT_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = Tainted_Dir::TT_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = Tainted_Dir::TT_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = Tainted_Dir::TT_B;
		}
	}

	// 애니메이션 변경
	ChangeAnimationCheck(_StateName);
}

// 방향별 애니메이션 전환
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

// 최초 적탐지 상태
void Tainted::StartRoomDetect()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_ROOMDETECT;
}

void Tainted::UpdateRoomDetect()
{
	// 플레이어 룸 진입시 대기상태로 전환
	if (true == EnterTheRoomDetectCheck())
	{
		// 상태 전환
		State_.ChangeState("Idle");
	}
}

void Tainted::EndRoomDetect()
{
	// 적발견 사운드 재생
	StateSound_->PlayAlone("Tainted_Detect.wav", 0);
}

// 대기상태
void Tainted::StartIdle()
{
	// 현재방향 체크 및 애니메이션변경
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 상태변경
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

// 이동상태(적감지상태)
void Tainted::StartMove()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_WALK;

	// 플레이어 방향 이동경로 생성
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Tainted, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void Tainted::UpdateMove()
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

void Tainted::EndMove()
{
}

// 기본공격상태
void Tainted::StartNormalAttack()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_ATTACK;

	// 공격 사운드 재생
	StateSound_->PlayAlone("Tainted_Attack.wav", 0);
}

void Tainted::UpdateNormalAttack()
{
}

void Tainted::EndNormalAttack()
{
}

// 피격상태
void Tainted::StartGetHit()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "GetHit");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_GETHIT;

	// 피격 사운드 재생
	StateSound_->PlayAlone("Tainted_GetHit.wav", 0);

	// 특정 공격에 의한 피격시 해당 몬스터의 색이 변경
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

// 사망상태
void Tainted::StartDeath()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_DEATH;

	// 사망 사운드 재생
	StateSound_->PlayAlone("Tainted_Death.wav", 0);

	// 사망시 현재 플레이어의 경험치를 증가
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

// 시체상태
void Tainted::StartDead()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::TT_DEAD;
}

void Tainted::UpdateDead()
{
}

void Tainted::EndDead()
{
}
