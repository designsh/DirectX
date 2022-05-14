#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalValue.h"
#include "TownMap.h"
#include "CatacombsMap.h"

void MainPlayer::ChangeCheckProcess()
{
	// 현재 상태 전환 전이기 때문에 현재상태의 아이템 착용상태를 체크하여
	// On해야하는 렌더러를 결정한다.
	int Index = 0;
	std::map<RendererPartType, bool>::iterator StartIter = IsItemEquipState_.begin();
	std::map<RendererPartType, bool>::iterator EndIter = IsItemEquipState_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 아이템착용중이라면 HVY_ 활성화, LIT_ 비활성화
		if (true == (*StartIter).second)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
		}
		else // 위와 반대의 경우
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();
		}

		++Index;
	}
}

// ========================== 상태 변경 ========================= //
void MainPlayer::ChangeFSMState(std::string _StateName)
{
	State_.ChangeState(_StateName);

	// 이전상태와 현재상태가 다를때 체크해야하는 사항체크
	if (PrevState_ != CurState_)
	{
		// 아이템 착용 상태 체크하여 렌더러 On/Off
		ChangeCheckProcess();
	}
}

// ========================== 마을 관련 ========================= //
// ============================ 대기 ============================ //
void MainPlayer::StartTownNatural()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TN;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();

	// 관련 사운드 시작


	// 기타

}

void MainPlayer::UpdateTownNatural()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndTownNatural()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ============================ 걷기 ============================ //
void MainPlayer::StartTownWalk()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_TW;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();

	// 이동위치 결정(마을맵기준)
	if (false == MovePath_.empty())
	{
		// 다음 이동타일인덱스 Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// 타겟위치로 지정된 경로의 인덱스제거
		MovePath_.pop_front();

		// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
		// 플레이어의 이동방향을 설정한다.
		float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
		MoveTargetDir_ = DirPos.NormalizeReturn3D();
	}

	MoveSpeed_ = 200.f;
}

void MainPlayer::UpdateTownWalk()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();

	// 이동처리
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
	
	// 이동타겟 타일인덱스 도달시 이동경로가 남아있다면 타겟위치 재설정 후 재이동
	// 더이상의 이동경로가 존재하지않는다면 대기상태 돌입
	if (MoveTargetIndex_.Index_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).Index_)
	{
		if (false == MovePath_.empty())
		{
			// 타겟타일 인덱스 변경
			MoveTargetIndex_.Index_ = MovePath_.front().Index_;

			float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();
		}
		else
		{
			// 이동완료이므로 이동 Flag 해제
			IsMove_ = false;

			// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
			ChangeFSMState("Natural_Town");

			// 혹시 잔존하는 경로가 있다면 클리어
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}
}

void MainPlayer::EndTownWalk()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 필드 관련 ========================== //

// ============================ 대기 ============================ //
void MainPlayer::StartFieldNatural()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_NU;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();

	// 관련 사운드 시작


	// 기타

}

void MainPlayer::UpdateFieldNatural()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndFieldNatural()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ============================ 걷기 ============================ //
void MainPlayer::StartFieldWalk()
{	
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_WL;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();

	// 이동위치 결정(마을맵기준)
	if (false == MovePath_.empty())
	{
		// 다음 이동타일인덱스 Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// 타겟위치로 지정된 경로의 인덱스제거
		MovePath_.pop_front();

		// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
		// 플레이어의 이동방향을 설정한다.
		float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
		MoveTargetDir_ = DirPos.NormalizeReturn3D();
	}

	MoveSpeed_ = 200.f;
}

void MainPlayer::UpdateFieldWalk()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();

	// 이동처리
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// 이동타겟 타일인덱스 도달시 이동경로가 남아있다면 타겟위치 재설정 후 재이동
	// 더이상의 이동경로가 존재하지않는다면 대기상태 돌입
	if (MoveTargetIndex_.Index_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()).Index_)
	{
		if (false == MovePath_.empty())
		{
			// 타겟타일 인덱스 변경
			MoveTargetIndex_.Index_ = MovePath_.front().Index_;

			float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();
		}
		else
		{
			// 이동완료이므로 이동 Flag 해제
			IsMove_ = false;

			// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
			ChangeFSMState("Natural_Field");

			// 혹시 잔존하는 경로가 있다면 클리어
			if (false == MovePath_.empty())
			{
				MovePath_.clear();
			}

			return;
		}
	}
}

void MainPlayer::EndFieldWalk()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 공통 관련 ========================== //

// ========================== 공격모션1 ========================== //
void MainPlayer::StartAttack1()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A1;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateAttack1()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndAttack1()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 공격모션2 ========================== //
void MainPlayer::StartAttack2()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_A2;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateAttack2()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndAttack2()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 방어모션 =========================== //
void MainPlayer::StartBlock()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_BL;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateBlock()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndBlock()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 피격모션 =========================== //
void MainPlayer::StartGetHit()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_GH;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateGetHit()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndGetHit()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 킥모션 ============================ //
void MainPlayer::StartKick()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_KK;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateKick()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndKick()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 뛰기모션 =========================== //
void MainPlayer::StartRun()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_RN;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();

	// 이동위치 결정(마을맵기준)
	if (false == MovePath_.empty())
	{
		// 다음 이동타일인덱스 Get
		MoveTargetIndex_.Index_ = MovePath_.front().Index_;

		// 타겟위치로 지정된 경로의 인덱스제거
		MovePath_.pop_front();

		if (true == IsTown_)
		{
			// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
			// 플레이어의 이동방향을 설정한다.
			float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
		else
		{
			float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}

	MoveSpeed_ = 250.f;

}

void MainPlayer::UpdateRun()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();

	// 이동처리
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// 이동타겟 타일인덱스 도달시 이동경로가 남아있다면 타겟위치 재설정 후 재이동
	// 더이상의 이동경로가 존재하지않는다면 대기상태 돌입
	if (true == IsTown_)
	{
		if (MoveTargetIndex_.Index_ == GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition()).Index_)
		{
			if (false == MovePath_.empty())
			{
				// 타겟타일 인덱스 변경
				MoveTargetIndex_.Index_ = MovePath_.front().Index_;

				float4 DirPos = GlobalValue::TownMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// 타겟위치로 지정된 경로의 인덱스제거
				MovePath_.pop_front();
			}
			else
			{
				// 이동완료이므로 이동 Flag 해제
				IsMove_ = false;

				// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
				ChangeFSMState("Natural_Town");

				// 혹시 잔존하는 경로가 있다면 클리어
				if (false == MovePath_.empty())
				{
					MovePath_.clear();
				}

				return;
			}
		}
	}
	else
	{
		if (MoveTargetIndex_.Index_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()).Index_)
		{
			if (false == MovePath_.empty())
			{
				// 타겟타일 인덱스 변경
				MoveTargetIndex_.Index_ = MovePath_.front().Index_;

				float4 DirPos = GlobalValue::CatacombsMap->GetTileIndexToPos(MoveTargetIndex_) - GetTransform()->GetWorldPosition();
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// 타겟위치로 지정된 경로의 인덱스제거
				MovePath_.pop_front();
			}
			else
			{
				// 이동완료이므로 이동 Flag 해제
				IsMove_ = false;

				// 더 이상 이동할 이유가 없으므로 플레이어 대기상태 돌입
				ChangeFSMState("Natural_Field");

				// 혹시 잔존하는 경로가 있다면 클리어
				if (false == MovePath_.empty())
				{
					MovePath_.clear();
				}

				return;
			}
		}
	}
}

void MainPlayer::EndRun()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ======================== 스킬공격모션 ========================= //
void MainPlayer::StartSkillAttack()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_S1;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateSkillAttack()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndSkillAttack()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ======================= 스킬캐스팅모션 ======================== //
void MainPlayer::StartSkillCasting()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_SC;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateSkillCasting()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndSkillCasting()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 사망 관련 ========================== //

// ========================== 시체모션 =========================== //
void MainPlayer::StartDead()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DD;

	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateDead()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndDead()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}

// ========================== 사망모션 =========================== //
void MainPlayer::StartDeath()
{
	// 현재 상태 저장
	PrevState_ = CurState_;
	CurState_ = PlayerState::STAT_DT;
	
	// 애니메이션변경
	ChangeAnimation(State_.GetCurStateName());

	// 현재상태가 변경되었으므로
	// DirectRenderOrder_의 Default ZOrder가 셋팅
	StateAndDirectChangeZOrder();
}

void MainPlayer::UpdateDeath()
{
	// 애니메이션 프레임마다 ZOrder 체크하여 ZOrder 갱신
	AnimationFrameCheckZOrderChange();



}

void MainPlayer::EndDeath()
{
	// Animation Frame Check ZOrder Change Flag Off
	IsDefaultZOrderChangeChk_ = false;
}
