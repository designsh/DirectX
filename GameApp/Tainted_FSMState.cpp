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
	// 타겟위치 저장
	TargetPos_ = _TargetPos;

	// 현재위치 저장
	CurPos_ = GetTransform()->GetWorldPosition();

	// 현재 이동방향 저장
	// 이전 방향 셋팅
	PrevDir_ = CurDir_;

	// 현재 방향 전환처리
	// => 타겟위치로 방향 전환
	float4 Direct = TargetPos_ - CurPos_;
	Direct.Normalize3D();

	// 월드의 y축기준 방향벡터를 얻어온다.
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

// 해당 몬스터 상태전환용 체크타일리스트 셋팅
void Tainted::SetCheckTileList(TileIndex _CurTileIndex)
{
	// 기존 체크타일목록 삭제
	CheckTileList_.clear();

	// 적감지 체크타일목록 작성(현재타일의 +- 8)
	for (int i = 1; i <= 10; ++i)
	{
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( 0,  i)).Index_, Tainted_TileCheckType::MOVE));		// 좌단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i,  i)).Index_, Tainted_TileCheckType::MOVE));		// 좌상단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i,  0)).Index_, Tainted_TileCheckType::MOVE));		// 상단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex(-i, -i)).Index_, Tainted_TileCheckType::MOVE));		// 우상단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( 0, -i)).Index_, Tainted_TileCheckType::MOVE));		// 우단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i, -i)).Index_, Tainted_TileCheckType::MOVE));		// 우하단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i,  0)).Index_, Tainted_TileCheckType::MOVE));		// 하단
		CheckTileList_.insert(std::make_pair((_CurTileIndex + TileIndex( i,  i)).Index_, Tainted_TileCheckType::MOVE));		// 좌하단
	}
}

// 적이 체크리스트에 들어오는지 체크 후 상태전환
void Tainted::CheckChangeState(TileIndex _PlayerTileIndex)
{
	if (CheckTileList_.end() == CheckTileList_.find(_PlayerTileIndex.Index_))
	{
		return;
	}

	if (CurState_ == Tainted_FSMState::ST_WALK)
	{
		if (Tainted_TileCheckType::ATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
		{
			State_.ChangeState("Tainted_ATTACK");
		}
	}
	else
	{
		if (Tainted_TileCheckType::MOVE == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
		{
			State_.ChangeState("Tainted_MOVE");
		}
		else if (Tainted_TileCheckType::ATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
		{
			State_.ChangeState("Tainted_ATTACK");
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
	CurState_ = Tainted_FSMState::ST_ROOMDETECT;
}

void Tainted::UpdateRoomDetect()
{
	// 적 최초 룸진입시점 감지
	if (false == RoomDetect_)
	{
		for (auto& DetectTile : RoomDetectList_)
		{
			// 플레이어가 존재할때
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 
				TileIndex PlayerTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
				if (PlayerTileIndex == DetectTile)
				{
					// 대기상태 전환
					State_.ChangeState("Tainted_IDLE");

					// 룸진입 Flag On
					RoomDetect_ = true;
				}
			}
		}
	}
}

void Tainted::EndRoomDetect()
{

}

// 대기상태
void Tainted::StartIdle()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "Idle");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_IDLE;

	// 현재위치에서의 체크리스트 작성
	SetCheckTileList(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()));
}

void Tainted::UpdateIdle()
{
	// 적이 룸진입을 한번이라도 했을 경우
	if (true == RoomDetect_)
	{
		// 적의 위치 타일인덱스 체크
		CheckChangeState(GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition()));
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

	// 이동 경로 생성
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
	MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Tainted, NavigationIndex_, CurPos_, TargetPos_ - CamPos);
	if(false == MovePath_.empty())
	{
		// 다음 이동타일인덱스 Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// 타겟위치로 지정된 경로의 인덱스제거
		MovePath_.pop_front();

		// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
		// 플레이어의 이동방향을 설정한다.
		MoveTargetDir_ = (GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetIndex_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y)).NormalizeReturn3D();
	}
}

void Tainted::UpdateMove()
{
	// 현재 경로 타겟위치까지 이동 완료시
	if (MoveTargetIndex_.Index_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()).Index_)
	{
		if (false == MovePath_.empty())
		{
			// 타겟타일 인덱스 변경
			MoveTargetIndex_.Index_ = MovePath_.front().Index_;

			// 현재 위치의 체크리스트 갱신
			SetCheckTileList(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()));

			MoveTargetDir_ = (GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetIndex_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y)).NormalizeReturn3D();

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();
		}
		else
		{
			// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
			State_.ChangeState("Tainted_IDLE");

			// 혹시 잔존하는 경로가 있다면 클리어
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}

	// 현재 타겟위치까지 이동
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

	// 타겟의 본체 충돌체와 나의 공격충돌체가 충돌하고있었다면 타겟에게 데미지를 입힌다.
	
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
	// 공격모션 종료시 적의 충돌체와 충돌중이라면 적에게 데미지를 입힌다.
	if (true == EnemyCol_)
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