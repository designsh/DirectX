#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

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
	// 스킬시전이 가능하다면 스킬공격상태로 전환
	if (true == SkillAttack_)
	{
		State_.ChangeState("SkillAttack");
		IdleDelayTime_ = 1.f;
		return;
	}

	// 아니라면 대기시간 체크하여 이동상태로 전환
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

// 이동상태
void Andariel::StartMove()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Walk");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_WALK;

	// 이동경로 생성
	MovePath_.clear();
	float4 TargetPos = GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Andariel, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
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

void Andariel::UpdateMove()
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

void Andariel::EndMove()
{
	MovePath_.clear();
}

// 기본공격상태
void Andariel::StartNormalAttack()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Attack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_ATTACK;

	// 공격 사운드 재생
	StateSound_->PlayAlone("Andariel_Attack.wav", 0);
}

void Andariel::UpdateNormalAttack()
{
}

void Andariel::EndNormalAttack()
{
	Attack_ = false;
}

// 스킬공격상태
void Andariel::StartSkillAttack()
{
	// 현재방향 체크 및 애니메이션변경
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "SkillAttack");

	// 상태변경
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_SKILLATTACK;

	// 스킬공격 사운드 재생
	StateSound_->PlayAlone("Andariel_SkillAttack.wav", 0);
}

void Andariel::UpdateSkillAttack()
{
}

void Andariel::EndSkillAttack()
{
	// 스킬 발사완료 후 스킬공격가능여부 Flag 해제
	SkillAttack_ = false;

	// 생성카운트 초기화
	ProjectileCnt_ = 0;
}

// 피격상태
void Andariel::StartGetHit()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_GETHIT;

	// 피격 사운드 재생
	StateSound_->PlayAlone("Andariel_GetHit.wav", 0);

	// 특정 공격에 의한 피격시 해당 몬스터의 색이 변경
	if (true == SpecialGetHit_)
	{
		switch (CurDamageType_)
		{
			case MonsterDamageType::COLD:
			{
				Andariel_->SetResultColor(float4(0.f, 0.f, 1.f, 1.f));
				break;
			}
			case MonsterDamageType::POISON:
			{
				Andariel_->SetResultColor(float4(0.f, 1.f, 0.f, 1.f));
				break;
			}
		}
	}
}

void Andariel::UpdateGetHit()
{
	State_.ChangeState("Idle");
}

void Andariel::EndGetHit()
{
	CurDamageType_ = MonsterDamageType::NONE;
	SpecialGetHit_ = false;
	Andariel_->SetResultColor(float4::ONE);
}

// 사망상태
void Andariel::StartDeath()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Death");

	if (nullptr == AndarielEffect_)
	{
		AndarielEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
		AndarielEffect_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		AndarielEffect_->GetTransform()->SetLocalZOrder(-1.f);
		AndarielEffect_->SetRenderingPipeLine("TextureTransDepthOff");


		// 사망상태 오버레이(Andariel_Death_Effect.png, 23x8)
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_B", 0, 22, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_LB", 23, 45, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_L", 46, 68, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_LT", 69, 91, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_T", 92, 114, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_RT", 115, 137, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_R", 138, 160, 0.1f, false);
		AndarielEffect_->CreateAnimation("Andariel_Death_Effect.png", "DeathEffect_RB", 161, 183, 0.1f, false);
	}

	switch (CurDir_)
	{
	case Andariel_TargetDir::AD_B:
		AndarielEffect_->SetChangeAnimation("DeathEffect_B");
		break;
	case Andariel_TargetDir::AD_LB:
		AndarielEffect_->SetChangeAnimation("DeathEffect_LB");
		break;
	case Andariel_TargetDir::AD_L:
		AndarielEffect_->SetChangeAnimation("DeathEffect_L");
		break;
	case Andariel_TargetDir::AD_LT:
		AndarielEffect_->SetChangeAnimation("DeathEffect_LT");
		break;
	case Andariel_TargetDir::AD_T:
		AndarielEffect_->SetChangeAnimation("DeathEffect_T");
		break;
	case Andariel_TargetDir::AD_RT:
		AndarielEffect_->SetChangeAnimation("DeathEffect_RT");
		break;
	case Andariel_TargetDir::AD_R:
		AndarielEffect_->SetChangeAnimation("DeathEffect_R");
		break;
	case Andariel_TargetDir::AD_RB:
		AndarielEffect_->SetChangeAnimation("DeathEffect_RB");
		break;
	}

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_DEATH;

	// 사망 사운드 재생
	StateSound_->PlayAlone("Andariel_Death.wav", 0);
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
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Andariel_FSMState::AD_DEAD;
}

void Andariel::UpdateDead()
{
}

void Andariel::EndDead()
{
}
