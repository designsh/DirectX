#include "PreCompile.h"
#include "SummonsGolem.h"

// 타겟 방향 체크 후 애니메이션 변경
void SummonsGolem::TargetDirCheck()
{
	// 현재방향을 이전방향에 저장
	PrevDir_ = CurDir_;

	// 현재 위치와 
	float4 MyPos = GetTransform()->GetWorldPosition();


}

// 소환상태
void SummonsGolem::StartSpawnState()
{

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

}

void SummonsGolem::UpdateIdleState()
{

}

void SummonsGolem::EndIdleState()
{

}

// 이동상태
void SummonsGolem::StartWalkState()
{

}

void SummonsGolem::UpdateWalkState()
{

}

void SummonsGolem::EndWalkState()
{

}

// 공격상태
void SummonsGolem::StartAttackState()
{

}

void SummonsGolem::UpdateAttackState()
{

}

void SummonsGolem::EndAttackState()
{

}

// 사망상태
void SummonsGolem::StartDeathState()
{

}

void SummonsGolem::UpdateDeathState()
{

}

void SummonsGolem::EndDeathState()
{

}
