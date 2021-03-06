#include "PreCompile.h"
#include "SketelonWizard.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"

#include "WizardProjectile.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

// 타겟 방향 체크
void SketelonWizard::TargetDirCheck(const float4& _TargetPos, const std::string& _StateName)
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
			CurDir_ = SketelonWizard_TargetDir::SW_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = SketelonWizard_TargetDir::SW_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = SketelonWizard_TargetDir::SW_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = SketelonWizard_TargetDir::SW_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = SketelonWizard_TargetDir::SW_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = SketelonWizard_TargetDir::SW_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = SketelonWizard_TargetDir::SW_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = SketelonWizard_TargetDir::SW_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = SketelonWizard_TargetDir::SW_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = SketelonWizard_TargetDir::SW_B;
		}
	}

	// 애니메이션 변경
	ChangeAnimationCheck(_StateName);
}

// 방향별 애니메이션 변경
void SketelonWizard::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case SketelonWizard_TargetDir::SW_LB:
		{
			AnimationName += "_LB";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_LT:
		{
			AnimationName += "_LT";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_RT:
		{
			AnimationName += "_RT";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_RB:
		{
			AnimationName += "_RB";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_B:
		{
			AnimationName += "_B";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_L:
		{
			AnimationName += "_L";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_T:
		{
			AnimationName += "_T";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case SketelonWizard_TargetDir::SW_R:
		{
			AnimationName += "_R";
			WizardRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

bool SketelonWizard::MonsterDetect()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{
			TileIndex CheckTileIndex = CurTileIndex + TileIndex(x, y);
			DetectMonster_ = GlobalValue::CatacombsMap->MonsterTileIndexCheck(CheckTileIndex);
			if (nullptr != DetectMonster_)
			{
				return true;
			}
		}
	}

	return false;
}

bool SketelonWizard::CheckWarpStart()
{
	// 해당 범위를 벗어나면 플레이어에게로 워프시킨다.
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	for (auto& MoveabledTile : MaxMoveRange_)
	{
		if (CurTileIndex == MoveabledTile)
		{
			return false;
		}
	}

	return true;
}

// 소환상태
void SketelonWizard::StartSpawnState()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::SPAWN;

	// 소환 사운드 재생
	StateSound_->PlayAlone("SkeletonSpawn.wav", 0);
}

void SketelonWizard::UpdateSpawnState()
{
}

void SketelonWizard::EndSpawnState()
{
}

// 대기상태
void SketelonWizard::StartIdleState()
{
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::IDLE;

	// 현재 플레이어의 위치기준 골렘의 이동범위를 생성한다.
	SetMoveRange();
}

void SketelonWizard::UpdateIdleState()
{
	// 주변내에 몬스터 존재여부 판단
	CheckTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= CheckTime_)
	{
		// 1. 몬스터가 존재한다면 몬스터 감지 성공으로 타겟까지 이동시작
		if (true == MonsterDetect())
		{
			// 공격상태로 전환
			State_.ChangeState("Attack");
		}
		// 2. 몬스터가 존재하지않을때 이동 or 워프
		else
		{
			// 플레이어주변 6x6타일내에 존재하지않는다면 워프상태로 전환
			// 단, 플레이어가 이동중에는 워프 불가능
			if (true == CheckWarpStart() && false == GlobalValue::CurPlayer->GetIsMove())
			{
				State_.ChangeState("Warp");
			}
			// 아니라면 이동상태로 전환
			else
			{
				// 이동타겟 타일 결정
				GameEngineRandom Random;
				MoveTargetTile_ = MaxMoveRange_[Random.RandomInt(0, static_cast<int>(MaxMoveRange_.size()) - 1)];
				TargetPos_ = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);

				MovePath_.clear();
				float4 CurTargetPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
				MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_SketelonWizard, WizardNavigationIndex_, GetTransform()->GetWorldPosition(), CurTargetPos);
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

					State_.ChangeState("Walk");
				}
			}
		}

		CheckTime_ = 1.5f;
	}
}

void SketelonWizard::EndIdleState()
{
}

// 이동상태
void SketelonWizard::StartWalkState()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::WALK;

	// 현재 이동방향 및 애니메이션 변경
	TargetDirCheck(TargetPos_, "Walk");
}

void SketelonWizard::UpdateWalkState()
{
	// 이동
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// 이동 중 적감지시 공격
	if (true == MonsterDetect())
	{
		// 공격상태로 전환
		State_.ChangeState("Attack");
		return;
	}

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
			TargetPos_ = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
			TargetDirCheck(TargetPos_, "Walk");

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();
		}
		else
		{
			// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
			State_.ChangeState("Idle");

			// 혹시 잔존하는 경로가 있다면 클리어
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}
}

void SketelonWizard::EndWalkState()
{
	// 혹시 모를 남은 경로 제거
	MovePath_.clear();
}

// 워프상태
void SketelonWizard::StartWarpState()
{
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::WARP;
}

void SketelonWizard::UpdateWarpState()
{
	// 현재 플레이어 위치로 워프 후 대기상태 전환
	GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	State_.ChangeState("Idle");
}

void SketelonWizard::EndWarpState()
{
}

// 공격상태
void SketelonWizard::StartAttackState()
{
	// 현재 감지된 몬스터의 위치
	TargetDirCheck(DetectMonster_->GetTransform()->GetWorldPosition(), "Attack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::ATTACK;
}

void SketelonWizard::UpdateAttackState()
{
}

void SketelonWizard::EndAttackState()
{
}

// 피격상태
void SketelonWizard::StartGetHitState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::GETHIT;
}

void SketelonWizard::UpdateGetHitState()
{
	// 데미지를 받고 대기상태로 전환

	State_.ChangeState("Idle");
}

void SketelonWizard::EndGetHitState()
{
}

// 사망상태
void SketelonWizard::StartDeathState()
{
	TargetDirCheck(TargetPos_, "Death");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = SketelonWizardState::DEATH;
}

void SketelonWizard::UpdateDeathState()
{
}

void SketelonWizard::EndDeathState()
{
}

// 특정 애니메이션 종료시 호출 함수
void SketelonWizard::SpawnAnimationEnd()
{
	State_.ChangeState("Idle");
}

void SketelonWizard::AttackAnimationEnd()
{
	// 현재 타겟팅 몬스터 공격
	if (nullptr != DetectMonster_)
	{
		// 발사체 발사(단, 아무런 충돌도 없이 5초간 이동했다면 자동소멸)
		float4 TargetPos = DetectMonster_->GetTransform()->GetWorldPosition();
		WizardProjectile* NewProjectile = GetLevel()->CreateActor<WizardProjectile>();
		NewProjectile->SkeletonWizardFire(WizardType_, GetTransform()->GetWorldPosition(), TargetPos, SketelonWizardInfo_.SkillDamage);
		NewProjectile->Release(5.f);

		DetectMonster_ = nullptr;
	}

	// 대기상태 전환
	State_.ChangeState("Idle");
}

void SketelonWizard::GetHitAnimationEnd()
{
	// 본인의 HP 소모
	CurHP_ -= 10;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Death");
	}
	else
	{
		// 대기 상태 전환
		State_.ChangeState("Idle");
	}
}

void SketelonWizard::DeathAnimationEnd()
{
	// 플레이어가 현재 소환한 스켈텔론(전사형) 목록에서 해당 액터를 찾아서
	// 사망처리후 목록에서 제거
	// 단, 최대수를 넘어가서 이미 사망한 스켈텔론은 이미 목록에서 제거되어있다.
	GlobalValue::CurPlayer->SkeletonWizardDeath(this);
}
