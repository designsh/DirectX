#include "PreCompile.h"
#include "SketelonWarrior.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void SketelonWarrior::CreateAnimation()
{
	WarriorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	WarriorRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	WarriorRenderer_->SetRenderingPipeLine("TextureDepthOff");

	// 소환 상태(Skeleton_Warrior_Summons.png : 12, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_LB",  0, 11, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_LT", 12, 23, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_RT", 24, 35, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_RB", 36, 47, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_B" , 48, 59, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_L" , 60, 71, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_T" , 72, 83, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Summons.png", "Spawn_R" , 84, 95, 0.1f, false);

	// 대기 상태(Skeleton_Warrior_Idle.png : 8, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_LB",  0,  7, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_LT",  8, 15, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_RT", 16, 23, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_RB", 24, 31, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_B" , 32, 39, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_L" , 40, 47, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_T" , 48, 55, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Idle.png", "Idle_R" , 56, 63, 0.1f);

	// 이동 상태(Skeleton_Warrior_Walk.png : 8, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_LB",  0,  7, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_LT",  8, 15, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_RT", 16, 23, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_RB", 24, 31, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_B" , 32, 39, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_L" , 40, 47, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_T" , 48, 55, 0.1f);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// 공격 상태(Skeleton_Warrior_Attack.png : 16, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// 피격 상태(Skeleton_Warrior_GetHit.png : 4, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_LB",  0,  3, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_LT",  4,  7, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_RT",  8, 11, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_RB", 12, 15, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_B" , 16, 19, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_L" , 20, 23, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_T" , 24, 27, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_GetHit.png", "GetHit_R" , 28, 31, 0.1f, false);

	// 사망 상태(Skeleton_Warrior_Death.png : 19, 8)
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_LB",   0,  18, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_LT",  19,  37, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_RT",  38,  56, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_RB",  57,  75, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_B" ,  76,  94, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_L" ,  95, 113, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_T" , 114, 132, 0.1f, false);
	WarriorRenderer_->CreateAnimation("Skeleton_Warrior_Death.png", "Death_R" , 133, 151, 0.1f, false);

	// 스폰위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SketelonWarrior::CreateAnimationEndCallbackFunction()
{
	// 소환 상태
	WarriorRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_B", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_L", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_T", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Spawn_R", std::bind(&SketelonWarrior::SpawnAnimationEnd, this));

	// 공격 상태
	WarriorRenderer_->SetEndCallBack("Attack_LB", std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_LT", std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_RT", std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_RB", std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_B" , std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_L" , std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_T" , std::bind(&SketelonWarrior::AttackAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Attack_R" , std::bind(&SketelonWarrior::AttackAnimationEnd, this));

	// 피격 상태
	WarriorRenderer_->SetEndCallBack("GetHit_LB", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_LT", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_RT", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_RB", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_B", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_L", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_T", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("GetHit_R", std::bind(&SketelonWarrior::GetHitAnimationEnd, this));

	// 사망 상태
	WarriorRenderer_->SetEndCallBack("Death_LB", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_LT", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_RT", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_RB", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_B", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_L", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_T", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
	WarriorRenderer_->SetEndCallBack("Death_R", std::bind(&SketelonWarrior::DeathAnimationEnd, this));
}

void SketelonWarrior::CreateFSMState()
{
	State_.CreateState("Spawn", std::bind(&SketelonWarrior::UpdateSpawnState, this), std::bind(&SketelonWarrior::StartSpawnState, this), std::bind(&SketelonWarrior::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SketelonWarrior::UpdateIdleState, this), std::bind(&SketelonWarrior::StartIdleState, this), std::bind(&SketelonWarrior::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SketelonWarrior::UpdateWalkState, this), std::bind(&SketelonWarrior::StartWalkState, this), std::bind(&SketelonWarrior::EndWalkState, this));
	State_.CreateState("Warp", std::bind(&SketelonWarrior::UpdateWarpState, this), std::bind(&SketelonWarrior::StartWarpState, this), std::bind(&SketelonWarrior::EndWarpState, this));
	State_.CreateState("Attack", std::bind(&SketelonWarrior::UpdateAttackState, this), std::bind(&SketelonWarrior::StartAttackState, this), std::bind(&SketelonWarrior::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SketelonWarrior::UpdateDeathState, this), std::bind(&SketelonWarrior::StartDeathState, this), std::bind(&SketelonWarrior::EndDeathState, this));
	State_.ChangeState("Spawn");
}
