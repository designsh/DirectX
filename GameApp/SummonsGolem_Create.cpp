#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "MainPlayerInfomation.h"

void SummonsGolem::CreateClayGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region ���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(75, GolemInfo_);
#pragma endregion

#pragma region �ִϸ��̼� ����
	// ��ȯ����(ClayGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// ������(ClayGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// �̵�����(ClayGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("ClayGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// ���ݻ���(ClayGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// �������(ClayGolem_Death.png, 16x1)
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("ClayGolem_Death.png", "Death_R" , 0, 15, 0.1f, false);
#pragma endregion

	// ���� ��ġ ����
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateBloodGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region ���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(85, GolemInfo_);
#pragma endregion

#pragma region �ִϸ��̼� ����
	// ��ȯ����(BloodGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// ������(BloodGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// �̵�����(BloodGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("BloodGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// ���ݻ���(BloodGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// �������(BloodGolem_Death.png, 16x8)
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_LB",   0,  15, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_LT",  16,  31, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_RT",  32,  47, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_RB",  48,  63, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_B" ,  64,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_L" ,  80,  95, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("BloodGolem_Death.png", "Death_R" , 112, 127, 0.1f, false);
#pragma endregion

	// ���� ��ġ ����
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateIronGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));

#pragma region ���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(90, GolemInfo_);
#pragma endregion

#pragma region �ִϸ��̼� ����
	// ��ȯ����(IronGolem_Spawn.png, 15x1)
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_LB", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_LT", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_RT", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_RB", 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_B" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_L" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_T" , 0, 14, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Spawn.png", "Spawn_R" , 0, 14, 0.1f, false);

	// ������(IronGolem_Idle.png, 4x8)
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_LB",  0,  3, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_LT",  4,  7, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_RT",  8, 11, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_RB", 12, 15, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_B" , 16, 19, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_L" , 20, 23, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_T" , 24, 27, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Idle.png", "Idle_R" , 28, 31, 0.1f);

	// �̵�����(IronGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("IronGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// ���ݻ���(IronGolem_Attack.png, 16x8)
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_LB",   0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_LT",  16, 31, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_RT",  32, 47, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_RB",  48, 63, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_B" ,  64, 79, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_L" ,  80, 95, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// �������(IronGolem_Death.png, 20x8)
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_LB",   0,  19, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_LT",  20,  39, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_RT",  40,  59, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_RB",  60,  79, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_B" ,  80,  99, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_L" , 100, 119, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_T" , 120, 139, 0.1f, false);
	GolemRenderer_->CreateAnimation("IronGolem_Death.png", "Death_R" , 140, 159, 0.1f, false);
#pragma endregion

	// ���� ��ġ ����
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SummonsGolem::CreateFireGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(240.f, 240.f));

#pragma region ���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(94, GolemInfo_);
#pragma endregion

#pragma region �ִϸ��̼� ����
	// ��ȯ����(FireGolem_Spawn.png, 16x1)
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_LB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_LT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_RT", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_RB", 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_B" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_L" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_T" , 0, 15, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Spawn.png", "Spawn_R" , 0, 15, 0.1f, false);

	// ������(FireGolem_Idle.png, 8x8)
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Idle.png", "Idle_R" , 56, 63, 0.1f);

	// �̵�����(FireGolem_Walk.png, 8x8)
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_LB",  0,  7, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_LT",  8, 15, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_RT", 16, 23, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_RB", 24, 31, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_B" , 32, 39, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_L" , 40, 47, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_T" , 48, 55, 0.1f);
	GolemRenderer_->CreateAnimation("FireGolem_Walk.png", "Walk_R" , 56, 63, 0.1f);

	// ���ݻ���(FireGolem_Attack.png, 17x8)
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_LB",   0,  16, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_LT",  17,  33, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_RT",  34,  50, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_RB",  51,  67, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_B" ,  68,  84, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_L" ,  85, 101, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_T" , 102, 118, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Attack.png", "Attack_R" , 119, 135, 0.1f, false);

	// �������(FireGolem_Death.png, 19x1)
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_LB", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_LT", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_RT", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_RB", 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_B" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_L" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_T" , 0, 18, 0.1f, false);
	GolemRenderer_->CreateAnimation("FireGolem_Death.png", "Death_R" , 0, 18, 0.1f, false);
#pragma endregion

	// ���� ��ġ ����
	GetTransform()->SetLocalPosition(SpawnPos_);
}
