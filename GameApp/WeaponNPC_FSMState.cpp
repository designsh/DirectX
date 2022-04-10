#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

#pragma region 방향/상태 체크하여 애니메이션 변경
void WeaponNPC::ChangeAnimationCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;
	
	switch (CurMoveDir_)
	{
		case WeaponNPC_MoveDir::DIR_B:
		{
			AnimationName += "_B";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_LB:
		{
			AnimationName += "_LB";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_L:
		{
			AnimationName += "_L";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_LT:
		{
			AnimationName += "_LT";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_T:
		{
			AnimationName += "_T";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_RT:
		{
			AnimationName += "_RT";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_R:
		{
			AnimationName += "_R";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WeaponNPC_MoveDir::DIR_RB:
		{
			AnimationName += "_RB";
			WeaponNPCRenderer_->SetChangeAnimation(AnimationName);
			break;
		}	
	}
}
#pragma endregion

// 대기상태
void WeaponNPC::StartIdle()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Idle");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_IDLE;
}

void WeaponNPC::UpdateIdle()
{
	// 플레이어와 상호작용상태가 아닐때 자동이동방향결정
	MoveDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
	if (0.f >= MoveDelayTime_)
	{
		// 랜덤결정
		srand((unsigned int)time(0));
		int RandomDir = rand() % static_cast<int>(WeaponNPC_MoveDir::MAX);

		// 이전방향과 다를때 현재이동방향을 결정하고,
		// 이동상태로 변경
		if (PrevMoveDir_ != static_cast<WeaponNPC_MoveDir>(RandomDir))
		{
			PrevMoveDir_ = CurMoveDir_;
			CurMoveDir_ = static_cast<WeaponNPC_MoveDir>(RandomDir);

			State_.ChangeState("WeaponNPC_WALK");
		}

		MoveDelayTime_ = 3.f;
	}
}

void WeaponNPC::EndIdle()
{
	MoveDelayTime_ = 3.f;
}

// 이동상태
void WeaponNPC::StartWalk()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Walk");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_WALK;
}

void WeaponNPC::UpdateWalk()
{
	// 플레이어와 상호작용상태가 아닐때 자동이동
	// 최대 이동거리 이동완료시 대기상태로 돌입

}

void WeaponNPC::EndWalk()
{

}

// 대화상태
void WeaponNPC::StartConversation()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Idle");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_CONV;

	// 상호작용 시작시 플레이어와의 거리체크 해제
	InteractionFlag = false;
}

void WeaponNPC::UpdateConversation()
{
	// 최초 대화시도시 메세지뷰 로드
	if (false == FirstInteraction)
	{
		// 상호작용 Flag On
		FirstInteraction = true;

		// 메세지뷰 로드

	}
	// 두번째 대화시도시 메뉴 도출
	else
	{
		// 상단메뉴 도출

	}
}

void WeaponNPC::EndConversation()
{

}
