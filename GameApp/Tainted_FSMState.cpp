#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

#include "CatacombsMap.h"

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

void Tainted::SetEnterTheRoomDetectList(int _SpawnRoomNo)
{
	// 적(플레이어)의 룸진입 체크용 타일목록
	// => 자신이 소환된 룸이 가지는 모든 바닥타일인덱스목록 기준 벽타일목록을 생성하여 체크리스트 작성

	// 생성관련 기본정보 저장
	SpawnRoomNo_ = _SpawnRoomNo;
	if (-1 != SpawnRoomNo_)
	{
		SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

		// 현재 내가 생성된 룸의 바닥타일 기준 벽타일을 모두 감지 목록으로 작성
		int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
		RoomTileList_.clear();
		for (int i = 0; i < RoomTileListCnt; ++i)
		{
			// 바닥타일의 위치 Get
			float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

			// 바닥타일 1개 기준 3x3의 벽타일을 가진다.
			TileIndex WallTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					RoomTileList_.push_back(WallTileIndex);
					WallTileIndex.X_ += 1;
				}

				WallTileIndex.X_ = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos).X_;
				WallTileIndex.Y_ += 1;
			}
		}
	}
}

bool Tainted::EnterTheRoomDetect()
{
	// 룸진입체크는 플레이어의 위치 타일인덱스 체크
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	for (auto& CheckTile : RoomTileList_)
	{
		if (CheckTile == PlayerTile)
		{
			return true;
		}
	}

	return false;
}

// 최초 적탐지 상태
void Tainted::StartRoomDetect()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_ROOMDETECT;
}

void Tainted::UpdateRoomDetect()
{
	// 플레이어(적)의 룸 진입을 체크
	if (true == EnterTheRoomDetect())
	{
		// 진입성공시 대기상태 전환
		State_.ChangeState("Tainted_IDLE");
	}
}

void Tainted::EndRoomDetect()
{
}

void Tainted::SetEnterTheDetectRangeList()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	for (int y = -9; y <= 9; ++y)
	{
		for (int x = -9; x <= 9; ++x)
		{
			DetetTileList_.push_back(CurTileIndex + TileIndex(x, y));
		}
	}
}

bool Tainted::EnterTheDetectRange()
{
	for (auto& DetectTile : DetetTileList_)
	{
		// 플레이어 감지 체크
		if (DetectTile == GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition()))
		{
			return true;
		}
	}

	return false;
}

// 대기상태
void Tainted::StartIdle()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_IDLE;

	// 타겟 지정 목록 생성
	SetEnterTheDetectRangeList();

	TargetCol_ = false;
}

void Tainted::UpdateIdle()
{
	// 다음 상태 전환을 위해 대기시간 소모
	IdleDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= IdleDelayTime_)
	{
		// 적감지를 통한 타겟지정 완료시 이동상태 전환
		if (true == EnterTheDetectRange())
		{
			State_.ChangeState("Tainted_MOVE");
		}

		IdleDelayTime_ = 1.5f;
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
	CurState_ = Tainted_FSMState::ST_WALK;

	// 타겟 위치까지의 이동경로 작성
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
	// 타겟방향으로 이동중 공격범위 진입한 적 체크
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
			State_.ChangeState("Tainted_IDLE");
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
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "NormalAttack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_NORMALATTACK;
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
	CurState_ = Tainted_FSMState::ST_GETHIT;
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
	CurState_ = Tainted_FSMState::ST_DEATH;
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
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Dead");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_DEAD;
}

void Tainted::UpdateDead()
{
}

void Tainted::EndDead()
{
}

#pragma region 애니메이션종료시점호출함수

void Tainted::NormalAttackEnd()
{
	// 플레이어에게 데미지
	// 단, 충돌중이여야만 데미지를 입힌다.
	if (true == TargetCol_)
	{
		GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
	}

	// 대기상태로 전환
	State_.ChangeState("Tainted_IDLE");
}

void Tainted::GetHitEnd()
{
	// 대기상태로 전환
	State_.ChangeState("Tainted_IDLE");
}

void Tainted::DeathEnd()
{
	// 시체상태로 전환
	State_.ChangeState("Tainted_DEAD");
}

#pragma endregion