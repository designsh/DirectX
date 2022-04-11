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
		// 이동방향 결정
		// 이전방향을 체크하여 현재방향이 결정된다.
		// 즉, 아래로 이동한뒤 다시 대기상태가 되었다면 위로 이동한다.
		// 원래자리로 복귀후 방향이 전환되며, 위와같은 동작을 반복처리하게된다.
		
		// 이전방향과 현재방향이 반대방향이면 랜덤으로 방향 재결정
		srand((unsigned int)time(0));
		int RandomDir = rand() % static_cast<int>(WeaponNPC_MoveDir::MAX);

		// 이전방향과 다를때 현재이동방향을 결정하고, 이동상태로 변경
		if (PrevMoveDir_ != static_cast<WeaponNPC_MoveDir>(RandomDir))
		{
			CurMoveDir_ = static_cast<WeaponNPC_MoveDir>(RandomDir);

			State_.ChangeState("WeaponNPC_WALK");
		}

		MoveDelayTime_ = 3.f;
	}
}

void WeaponNPC::EndIdle()
{
}

// 이동상태
void WeaponNPC::StartWalk()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Walk");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_WALK;

	// 이동전 위치 저장
	MoveStartPos_ = GetTransform()->GetLocalPosition();
	MoveCurPos_ = GetTransform()->GetLocalPosition();
}

void WeaponNPC::UpdateWalk()
{
	// 이동처리중 최대이동범위를 넘어가면 현재이동방향을 저장하고 바로 상태전환
	if ((MoveCurPos_.x < MoveMinRange_.x && MoveCurPos_.y < MoveMinRange_.y) ||
		(MoveCurPos_.x > MoveMaxRange_.x && MoveCurPos_.y > MoveMaxRange_.y))
	{
		// 현재이동방향 저장
		PrevMoveDir_ = CurMoveDir_;

		// 상태 전환
		State_.ChangeState("WeaponNPC_IDLE");
		return;
	}

	// 플레이어와 상호작용상태가 아닐때 자동이동
	// 최대 이동거리 이동완료시 대기상태로 돌입
	switch (CurMoveDir_)
	{
		case WeaponNPC_MoveDir::DIR_B:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(0.0f, -1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.f <= MoveDist.y)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_LB:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, -1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.y && 150.0f <= MoveDist.x)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_L:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, 0.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.x)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_LT:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(-1.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.y && 150.0f <= MoveDist.x)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_T:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(0.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.y)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_RT:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, 1.0f) * MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.y && 150.0f <= MoveDist.x)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_R:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, 0.0f)* MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.x)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
		case WeaponNPC_MoveDir::DIR_RB:
		{
			// 이동 및 현재 이동위치 갱신
			GetTransform()->SetLocalDeltaTimeMove(float4(1.0f, -1.0f)* MoveSpeed_);
			MoveCurPos_ = GetTransform()->GetLocalPosition();

			// 이동중 이동시작위치와 현재위치를 비교하여 320 이상 거리가 벌어지면 이동 종료
			float4 MoveDist = MoveStartPos_ - MoveCurPos_;
			MoveDist = float4(std::abs(MoveDist.x), std::abs(MoveDist.y));
			if (150.0f <= MoveDist.x && 150.f <= MoveDist.y)
			{
				// 현재이동방향 저장
				PrevMoveDir_ = CurMoveDir_;

				// 상태 전환
				State_.ChangeState("WeaponNPC_IDLE");
			}
			break;
		}
	}
}

void WeaponNPC::EndWalk()
{
	MoveCurPos_ = float4::ZERO;
}

// 상호작용대기 상태
void WeaponNPC::StartConversation()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Idle");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_CONV;
}

void WeaponNPC::UpdateConversation()
{
	// 플레이어와 상호작용가능범위 체크
	// 상호작용가능범위 진입시 상태전환


}

void WeaponNPC::EndConversation()
{

}

// 상호작용중 상태
void WeaponNPC::StartInteraction()
{
	// 애니메이션 변경
	ChangeAnimationCheck("Charsi_Idle");

	// 상태값 저장
	PrevState_ = CurState_;
	CurState_ = WeaponNPC_FSMState::ST_INTER;

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

void WeaponNPC::UpdateInteraction()
{
	// 플레이어에 의해 상호작용 종료시 대기상태로 전환



}

void WeaponNPC::EndInteraction()
{
	// 상호작용 유효거리 체크 Flag 해제
	InteractionFlag = false;
}
