#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "MainPlayerInfomation.h"

void SummonsGolem::CreateClayGolem()
{
	// 렌더러 생성
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region 정보 저장
	MainPlayerInfomation::GetInst().GetSkillInfo(75, GolemInfo_);
#pragma endregion

#pragma region 애니메이션 생성
	// 소환상태(ClayGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// 대기상태(ClayGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// 이동상태(ClayGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// 공격상태(ClayGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// 사망상태(ClayGolem_Death.png, 16x1)
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_R" , 0, 15, 0.1f, false);
#pragma endregion

	// 액터 위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateBloodGolem()
{
	// 렌더러 생성
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region 정보 저장
	MainPlayerInfomation::GetInst().GetSkillInfo(85, GolemInfo_);
#pragma endregion

#pragma region 애니메이션 생성
	// 소환상태(BloodGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// 대기상태(BloodGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// 이동상태(BloodGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// 공격상태(BloodGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// 사망상태(BloodGolem_Death.png, 16x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_R" , 112, 127, 0.1f, false);
#pragma endregion

	// 액터 위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateIronGolem()
{
	// 렌더러 생성
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region 정보 저장
	MainPlayerInfomation::GetInst().GetSkillInfo(90, GolemInfo_);
#pragma endregion

#pragma region 애니메이션 생성
	// 소환상태(IronGolem_Spawn.png, 15x1)
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_LB", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_LT", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_RT", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_RB", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_B" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_L" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_T" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_R" , 0, 14, 0.1f, false);

	// 대기상태(IronGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// 이동상태(IronGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// 공격상태(IronGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_LB",   0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_LT",  16, 31, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_RT",  32, 47, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_RB",  48, 63, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_B" ,  64, 79, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_L" ,  80, 95, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// 사망상태(IronGolem_Death.png, 20x8)
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_LB",   0,  19, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_LT",  20,  39, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_RT",  40,  59, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_RB",  60,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_B" ,  80,  99, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_L" , 100, 119, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_T" , 120, 139, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_R" , 140, 159, 0.1f, false);
#pragma endregion

	// 액터 위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateFireGolem()
{
	// 렌더러 생성
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(240.f, 240.f));

#pragma region 정보 저장
	MainPlayerInfomation::GetInst().GetSkillInfo(94, GolemInfo_);
#pragma endregion

#pragma region 애니메이션 생성
	// 소환상태(FireGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// 대기상태(FireGolem_Idle.png, 8x8)
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_R" , 56, 63, 0.1f);

	// 이동상태(FireGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// 공격상태(FireGolem_Attack.png, 17x8)
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_LB",   0,  16, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_LT",  17,  33, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_RT",  34,  50, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_RB",  51,  67, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_B" ,  68,  84, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_L" ,  85, 101, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_T" , 102, 118, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_R" , 119, 135, 0.1f, false);

	// 사망상태(FireGolem_Death.png, 19x1)
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_LB", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_LT", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_RT", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_RB", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_B" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_L" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_T" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_R" , 0, 18, 0.1f, false);
#pragma endregion

	// 액터 위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}
