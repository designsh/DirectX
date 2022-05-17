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

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_LT;

			break;
		}
		case Tainted_Dir::TT_RT:
		{
			AnimationName += "_RT";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_RT;

			break;
		}
		case Tainted_Dir::TT_RB:
		{
			AnimationName += "_RB";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_RB;

			break;
		}
		case Tainted_Dir::TT_B:
		{
			AnimationName += "_B";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_B;

			break;
		}
		case Tainted_Dir::TT_L:
		{
			AnimationName += "_L";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_L;

			break;
		}
		case Tainted_Dir::TT_T:
		{
			AnimationName += "_T";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_T;

			break;
		}
		case Tainted_Dir::TT_R:
		{
			AnimationName += "_R";
			Tainted_->SetChangeAnimation(AnimationName);

			// 방향 전환
			CurDir_ = Tainted_Dir::TT_R;

			break;
		}
	}
}

// 해당 몬스터 상태전환용 체크타일리스트 셋팅
void Tainted::SetCheckTileList(TileIndex _CurTileIndex)
{
	// 기존 체크타일목록 삭제
	std::map<__int64, Tainted_TileCheckType>::iterator StartIter = CheckTileList_.begin();
	std::map<__int64, Tainted_TileCheckType>::iterator EndIter = CheckTileList_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		CheckTileList_.erase(StartIter);
	}
	CheckTileList_.clear();

	// 적감지 체크타일목록 작성(현재타일의 +- 6)
	for (int i = 1; i <= 6; ++i)
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

	// 스킬공격 체크타일목록 작성(현재타일의 +- 2)
	for (int i = 1; i <= 2; ++i)
	{
		CheckTileList_.find((_CurTileIndex + TileIndex( 0,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 좌단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 좌상단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  0)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 상단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 우상단
		CheckTileList_.find((_CurTileIndex + TileIndex( 0, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 우단
		CheckTileList_.find((_CurTileIndex + TileIndex( i, -i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 우하단
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  0)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 하단
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  i)).Index_)->second = Tainted_TileCheckType::SKILLATTACK;		// 좌하단
	}

	// 일반공격 체크타일목록 작성(현재타일의 +- 1)
	for (int i = 1; i <= 1; ++i)
	{
		CheckTileList_.find((_CurTileIndex + TileIndex( 0,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 좌단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 좌상단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i,  0)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 상단
		CheckTileList_.find((_CurTileIndex + TileIndex(-i, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 우상단
		CheckTileList_.find((_CurTileIndex + TileIndex( 0, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 우단
		CheckTileList_.find((_CurTileIndex + TileIndex( i, -i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 우하단
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  0)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 하단
		CheckTileList_.find((_CurTileIndex + TileIndex( i,  i)).Index_)->second = Tainted_TileCheckType::NORMALATTACK;		// 좌하단
	}
}

// 적이 체크리스트에 들어오는지 체크 후 상태전환
void Tainted::CheckChangeState(TileIndex _PlayerTileIndex)
{
	if (CheckTileList_.end() == CheckTileList_.find(_PlayerTileIndex.Index_))
	{
		return;
	}

	if (Tainted_TileCheckType::MOVE == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_MOVE");
	}
	else if (Tainted_TileCheckType::NORMALATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_ATTACK");
	}
	else if (Tainted_TileCheckType::SKILLATTACK == CheckTileList_.find(_PlayerTileIndex.Index_)->second)
	{
		State_.ChangeState("Tainted_SKILL");
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

	// 플레이어의 현재 타일을 타겟위치로 설정


	// 타겟을 향한 방향으로 애니메이션 변경


	// 

}

void Tainted::UpdateMove()
{
	// 일반공격 범위내에 플레이어 진입시 일반공격상태로 전환



	// 스킬공격 범위내에 플레이어 진입과 동시에 쿨타임 초기화시 스킬공격상태로 전환



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

// 스킬공격상태
void Tainted::StartSpecialAttack()
{
	// 적방향 체크하여 애니메이션 및 방향설정
	TargetDirCheck(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition(), "SpecialAttack");

	// 현재 상태 전환
	PrevState_ = CurState_;
	CurState_ = Tainted_FSMState::ST_SKILLATTACK;
}

void Tainted::UpdateSpecialAttack()
{

}

void Tainted::EndSpecialAttack()
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
	// 사망모션 종료시 시체상태로 전환

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
	// 마우스와 충돌상태이며, 플레이어가 해당 시체에 소환스킬 시전시 해당 몬스터는 완전한 사망

}

void Tainted::EndDead()
{

}