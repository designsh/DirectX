#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "FixedTileMap_Common.h"
#include "CatacombsMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

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

bool SummonsGolem::MonsterDetect()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
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

// 소환상태
void SummonsGolem::StartSpawnState()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::SPAWN;
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
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::IDLE;

	// 현재 플레이어의 위치기준 골렘의 이동범위를 생성한다.
	SetMoveRange();
}

void SummonsGolem::UpdateIdleState()
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
			if (true == CheckWarpStart())
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
				MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_Golem, 0, GetTransform()->GetWorldPosition(), CurTargetPos);
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

void SummonsGolem::EndIdleState()
{
}

// 이동상태
void SummonsGolem::StartWalkState()
{
	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::WALK;

	// 현재 이동방향 및 애니메이션 변경
	TargetDirCheck(TargetPos_, "Walk");
}

void SummonsGolem::UpdateWalkState()
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

void SummonsGolem::EndWalkState()
{
	// 혹시 모를 경로를 제거
	MovePath_.clear();
}

// 워프상태
void SummonsGolem::StartWarpState()
{
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::WARP;
}

void SummonsGolem::UpdateWarpState()
{
	// 현재 플레이어 위치로 워프 후 대기상태 전환
	GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	State_.ChangeState("Idle");
}

void SummonsGolem::EndWarpState()
{
}

// 공격상태
void SummonsGolem::StartAttackState()
{
	// 현재 감지된 몬스터의 위치
	TargetDirCheck(DetectMonster_->GetTransform()->GetWorldPosition(), "Attack");

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

// 피격상태
void SummonsGolem::StartGetHitState()
{
	TargetDirCheck(TargetPos_, "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = GolemState::GETHIT;
}

void SummonsGolem::UpdateGetHitState()
{
	// 데미지를 받고 대기상태로 전환

	State_.ChangeState("Idle");
}

void SummonsGolem::EndGetHitState()
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
