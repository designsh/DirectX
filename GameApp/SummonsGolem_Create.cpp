#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "MainPlayerInfomation.h"

void SummonsGolem::InitGolem()
{
	// ���Ÿ���� �񷽰��� �ʱ�ȭ

	// �ؽ��� ����
	TextureCutting();

	// �浹ü ����
	CreateCollision();
}

void SummonsGolem::TextureCutting()
{
#pragma region CLAY GOLEM
	// ��ȯ����(ClayGolem_Spawn.png)
	GameEngineTexture* ClayGolem_Spawn = GameEngineTextureManager::GetInst().Find("ClayGolem_Spawn.png");
	ClayGolem_Spawn->Cut(16, 1);

	// ������(ClayGolem_Idle.png)
	GameEngineTexture* ClayGolem_Idle = GameEngineTextureManager::GetInst().Find("ClayGolem_Idle.png");
	ClayGolem_Idle->Cut(4, 8);

	// �̵�����(ClayGolem_Walk.png)
	GameEngineTexture* ClayGolem_Walk = GameEngineTextureManager::GetInst().Find("ClayGolem_Walk.png");
	ClayGolem_Walk->Cut(8, 8);

	// ���ݻ���(ClayGolem_Attack.png)
	GameEngineTexture* ClayGolem_Attack = GameEngineTextureManager::GetInst().Find("ClayGolem_Attack.png");
	ClayGolem_Attack->Cut(16, 8);

	// �������(ClayGolem_Death.png)
	GameEngineTexture* ClayGolem_Death = GameEngineTextureManager::GetInst().Find("ClayGolem_Death.png");
	ClayGolem_Death->Cut(16, 1);
#pragma endregion

#pragma region BLOOD GOLEM
	// ��ȯ����(BloodGolem_Spawn.png)
	GameEngineTexture* BloodGolem_Spawn = GameEngineTextureManager::GetInst().Find("BloodGolem_Spawn.png");
	BloodGolem_Spawn->Cut(16, 1);

	// ������(BloodGolem_Idle.png)
	GameEngineTexture* BloodGolem_Idle = GameEngineTextureManager::GetInst().Find("BloodGolem_Idle.png");
	BloodGolem_Idle->Cut(4, 8);

	// �̵�����(BloodGolem_Walk.png)
	GameEngineTexture* BloodGolem_Walk = GameEngineTextureManager::GetInst().Find("BloodGolem_Walk.png");
	BloodGolem_Walk->Cut(8, 8);

	// ���ݻ���(BloodGolem_Attack.png)
	GameEngineTexture* BloodGolem_Attack = GameEngineTextureManager::GetInst().Find("BloodGolem_Attack.png");
	BloodGolem_Attack->Cut(16, 8);

	// �������(BloodGolem_Death.png)
	GameEngineTexture* BloodGolem_Death = GameEngineTextureManager::GetInst().Find("BloodGolem_Death.png");
	BloodGolem_Death->Cut(16, 8);
#pragma endregion

#pragma region IRON GOLEM
	// ��ȯ����(IronGolem_Spawn.png)
	GameEngineTexture* IronGolem_Spawn = GameEngineTextureManager::GetInst().Find("IronGolem_Spawn.png");
	IronGolem_Spawn->Cut(15, 1);

	// ������(IronGolem_Idle.png)
	GameEngineTexture* IronGolem_Idle = GameEngineTextureManager::GetInst().Find("IronGolem_Idle.png");
	IronGolem_Idle->Cut(4, 8);

	// �̵�����(IronGolem_Walk.png)
	GameEngineTexture* IronGolem_Walk = GameEngineTextureManager::GetInst().Find("IronGolem_Walk.png");
	IronGolem_Walk->Cut(8, 8);

	// ���ݻ���(IronGolem_Attack.png)
	GameEngineTexture* IronGolem_Attack = GameEngineTextureManager::GetInst().Find("IronGolem_Attack.png");
	IronGolem_Attack->Cut(16, 8);

	// �������(IronGolem_Death.png)
	GameEngineTexture* IronGolem_Death = GameEngineTextureManager::GetInst().Find("IronGolem_Death.png");
	IronGolem_Death->Cut(20, 8);
#pragma endregion

#pragma region FIRE GOLEM
	// ��ȯ����(FireGolem_Spawn.png)
	GameEngineTexture* FireGolem_Spawn = GameEngineTextureManager::GetInst().Find("FireGolem_Spawn.png");
	FireGolem_Spawn->Cut(16, 1);

	// ������(FireGolem_Idle.png)
	GameEngineTexture* FireGolem_Idle = GameEngineTextureManager::GetInst().Find("FireGolem_Idle.png");
	FireGolem_Idle->Cut(8, 8);

	// �̵�����(FireGolem_Walk.png)
	GameEngineTexture* FireGolem_Walk = GameEngineTextureManager::GetInst().Find("FireGolem_Walk.png");
	FireGolem_Walk->Cut(8, 8);

	// ���ݻ���(FireGolem_Attack.png)
	GameEngineTexture* FireGolem_Attack = GameEngineTextureManager::GetInst().Find("FireGolem_Attack.png");
	FireGolem_Attack->Cut(17, 8);

	// �������(FireGolem_Death.png)
	GameEngineTexture* FireGolem_Death = GameEngineTextureManager::GetInst().Find("FireGolem_Death.png");
	FireGolem_Death->Cut(19, 1);
#pragma endregion
}

void SummonsGolem::CreateCollision()
{

}

void SummonsGolem::CreateClayGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));
	GolemRenderer_->GetTransform()->SetLocalPosition(SpawnPos_);

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

#pragma region �ִϸ��̼�������� ȣ���Լ� ����
	// ��ȯ����
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// ���ݻ���
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R" , std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// �������
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM ����
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion
}

void SummonsGolem::CreateBloodGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));
	GetTransform()->SetLocalPosition(SpawnPos_);

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

#pragma region �ִϸ��̼�������� ȣ���Լ� ����
	// ��ȯ����
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// ���ݻ���
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R" , std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// �������
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM ����
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion
}

void SummonsGolem::CreateIronGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(180.f, 180.f));
	GolemRenderer_->GetTransform()->SetLocalPosition(SpawnPos_);

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

#pragma region �ִϸ��̼�������� ȣ���Լ� ����
	// ��ȯ����
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// ���ݻ���
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R" , std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// �������
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM ����
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion
}

void SummonsGolem::CreateFireGolem()
{
	// ������ ����
	GolemRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	GolemRenderer_->GetTransform()->SetLocalScaling(float4(240.f, 240.f));
	GolemRenderer_->GetTransform()->SetLocalPosition(SpawnPos_);

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

#pragma region �ִϸ��̼�������� ȣ���Լ� ����
	// ��ȯ����
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R" , std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// ���ݻ���
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T" , std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R" , std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// �������
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R" , std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM ����
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion
}
