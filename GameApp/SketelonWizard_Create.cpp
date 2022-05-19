#include "PreCompile.h"
#include "SketelonWizard.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void SketelonWizard::InitSketelonWizard()
{
	// 텍스쳐 컷팅
	TextureCutting();

	// 충돌체 생성
	CreateCollision();
}

void SketelonWizard::TextureCutting()
{
#pragma region COLD TYPE
	// 소환 상태(Skeleton_Wizard(Cold)_Summons.png)
	GameEngineTexture* Cold_Spawn = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_Summons.png");
	Cold_Spawn->Cut(12, 8);

	// 대기 상태(Skeleton_Wizard(Cold)_Idle.png)
	GameEngineTexture* Cold_Idle = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_Idle.png");
	Cold_Idle->Cut(8, 8);

	// 이동 상태(Skeleton_Wizard(Cold)_Walk.png)
	GameEngineTexture* Cold_Walk = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_Walk.png");
	Cold_Walk->Cut(8, 8);

	// 공격 상태(Skeleton_Wizard(Cold)_Attack.png)
	GameEngineTexture* Cold_Attack = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_Attack.png");
	Cold_Attack->Cut(16, 8);

	// 피격 상태(Skeleton_Wizard(Cold)_GetHit.png)
	GameEngineTexture* Cold_GetHit = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_GetHit.png");
	Cold_GetHit->Cut(4, 8);

	// 사망 상태(Skeleton_Wizard(Cold)_Death.png)
	GameEngineTexture* Cold_Death = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Cold)_Death.png");
	Cold_Death->Cut(19, 8);
#pragma endregion

#pragma region FIRE TYPE
	// 소환 상태(Skeleton_Wizard(Fire)_Summons.png)
	GameEngineTexture* Fire_Spawn = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_Summons.png");
	Fire_Spawn->Cut(12, 8);

	// 대기 상태(Skeleton_Wizard(Fire)_Idle.png)
	GameEngineTexture* Fire_Idle = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_Idle.png");
	Fire_Idle->Cut(8, 8);

	// 이동 상태(Skeleton_Wizard(Fire)_Walk.png)
	GameEngineTexture* Fire_Walk = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_Walk.png");
	Fire_Walk->Cut(8, 8);

	// 공격 상태(Skeleton_Wizard(Fire)_Attack.png)
	GameEngineTexture* Fire_Attack = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_Attack.png");
	Fire_Attack->Cut(16, 8);

	// 피격 상태(Skeleton_Wizard(Fire)_GetHit.png)
	GameEngineTexture* Fire_GetHit = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_GetHit.png");
	Fire_GetHit->Cut(4, 8);

	// 사망 상태(Skeleton_Wizard(Fire)_Death.png)
	GameEngineTexture* Fire_Death = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Fire)_Death.png");
	Fire_Death->Cut(19, 8);
#pragma endregion

#pragma region LIGHTNING TYPE
	// 소환 상태(Skeleton_Wizard(Lightning)_Summons.png)
	GameEngineTexture* Lightning_Spawn = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_Summons.png");
	Lightning_Spawn->Cut(12, 8);

	// 대기 상태(Skeleton_Wizard(Lightning)_Idle.png)
	GameEngineTexture* Lightning_Idle = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_Idle.png");
	Lightning_Idle->Cut(8, 8);

	// 이동 상태(Skeleton_Wizard(Lightning)_Walk.png)
	GameEngineTexture* Lightning_Walk = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_Walk.png");
	Lightning_Walk->Cut(8, 8);

	// 공격 상태(Skeleton_Wizard(Lightning)_Attack.png)
	GameEngineTexture* Lightning_Attack = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_Attack.png");
	Lightning_Attack->Cut(16, 8);

	// 피격 상태(Skeleton_Wizard(Lightning)_GetHit.png)
	GameEngineTexture* Lightning_GetHit = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_GetHit.png");
	Lightning_GetHit->Cut(4, 8);

	// 사망 상태(Skeleton_Wizard(Lightning)_Death.png)
	GameEngineTexture* Lightning_Death = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Lightning)_Death.png");
	Lightning_Death->Cut(19, 8);
#pragma endregion

#pragma region POISON TYPE
	// 소환 상태(Skeleton_Wizard(Poison)_Summons.png)
	GameEngineTexture* Poison_Spawn = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_Summons.png");
	Poison_Spawn->Cut(12, 8);

	// 대기 상태(Skeleton_Wizard(Poison)_Idle.png)
	GameEngineTexture* Poison_Idle = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_Idle.png");
	Poison_Idle->Cut(8, 8);

	// 이동 상태(Skeleton_Wizard(Poison)_Walk.png)
	GameEngineTexture* Poison_Walk = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_Walk.png");
	Poison_Walk->Cut(8, 8);

	// 공격 상태(Skeleton_Wizard(Poison)_Attack.png)
	GameEngineTexture* Poison_Attack = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_Attack.png");
	Poison_Attack->Cut(16, 8);

	// 피격 상태(Skeleton_Wizard(Poison)_GetHit.png)
	GameEngineTexture* Poison_GetHit = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_GetHit.png");
	Poison_GetHit->Cut(4, 8);

	// 사망 상태(Skeleton_Wizard(Poison)_Death.png)
	GameEngineTexture* Poison_Death = GameEngineTextureManager::GetInst().Find("Skeleton_Wizard(Poison)_Death.png");
	Poison_Death->Cut(19, 8);
#pragma endregion
}

void SketelonWizard::CreateCollision()
{
}

void SketelonWizard::CreateAnimation()
{
	WizardRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	WizardRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

	switch (WizardType_)
	{
		case SkeletonWizardType::COLD:
		{
			CreateWizardColdType();
			break;
		}
		case SkeletonWizardType::FIRE:
		{
			CreateWizardFireType();
			break;
		}
		case SkeletonWizardType::LIGHTNING:
		{
			CreateWizardLightningType();
			break;
		}
		case SkeletonWizardType::POISON:
		{
			CreateWizardPoisonType();
			break;
		}
	}

	// 스폰위치 셋팅
	GetTransform()->SetLocalPosition(SpawnPos_);
}

void SketelonWizard::CreateWizardColdType()
{
	// 소환 상태(Skeleton_Wizard(Cold)_Summons.png : 12, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_LB", 0, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_LT", 12, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_RT", 24, 35, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_RB", 36, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_B", 48, 59, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_L", 60, 71, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_T", 72, 83, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Summons.png", "Spawn_R", 84, 95, 0.1f, false);

	// 대기 상태(Skeleton_Wizard(Cold)_Idle.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Idle.png", "Idle_R", 56, 63, 0.1f);

	// 이동 상태(Skeleton_Wizard(Cold)_Walk.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Walk.png", "Walk_R", 56, 63, 0.1f);

	// 공격 상태(Skeleton_Wizard(Cold)_Attack.png : 16, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_LB", 0, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_LT", 16, 31, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_RT", 32, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_RB", 48, 63, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_B", 64, 79, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_L", 80, 95, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_T", 96, 111, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Attack.png", "Attack_R", 112, 127, 0.1f, false);

	// 피격 상태(Skeleton_Wizard(Cold)_GetHit.png : 4, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_LB", 0, 3, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_LT", 4, 7, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_RT", 8, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_RB", 12, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_B", 16, 19, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_L", 20, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_T", 24, 27, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_GetHit.png", "GetHit_R", 28, 31, 0.1f, false);

	// 사망 상태(Skeleton_Wizard(Cold)_Death.png : 19, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_LB", 0, 18, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_LT", 19, 37, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_RT", 38, 56, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_RB", 57, 75, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_B", 76, 94, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_L", 95, 113, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_T", 114, 132, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Cold)_Death.png", "Death_R", 133, 151, 0.1f, false);
}

void SketelonWizard::CreateWizardFireType()
{
	// 소환 상태(Skeleton_Wizard(Fire)_Summons.png : 12, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_LB", 0, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_LT", 12, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_RT", 24, 35, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_RB", 36, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_B", 48, 59, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_L", 60, 71, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_T", 72, 83, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Summons.png", "Spawn_R", 84, 95, 0.1f, false);

	// 대기 상태(Skeleton_Wizard(Fire)_Idle.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Idle.png", "Idle_R", 56, 63, 0.1f);

	// 이동 상태(Skeleton_Wizard(Fire)_Walk.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Walk.png", "Walk_R", 56, 63, 0.1f);

	// 공격 상태(Skeleton_Wizard(Fire)_Attack.png : 16, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_LB", 0, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_LT", 16, 31, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_RT", 32, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_RB", 48, 63, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_B", 64, 79, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_L", 80, 95, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_T", 96, 111, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Attack.png", "Attack_R", 112, 127, 0.1f, false);

	// 피격 상태(Skeleton_Wizard(Fire)_GetHit.png : 4, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_LB", 0, 3, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_LT", 4, 7, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_RT", 8, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_RB", 12, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_B", 16, 19, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_L", 20, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_T", 24, 27, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_GetHit.png", "GetHit_R", 28, 31, 0.1f, false);

	// 사망 상태(Skeleton_Wizard(Fire)_Death.png : 19, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_LB", 0, 18, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_LT", 19, 37, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_RT", 38, 56, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_RB", 57, 75, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_B", 76, 94, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_L", 95, 113, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_T", 114, 132, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Fire)_Death.png", "Death_R", 133, 151, 0.1f, false);
}

void SketelonWizard::CreateWizardLightningType()
{
	// 소환 상태(Skeleton_Wizard(Lightning)_Summons.png : 12, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_LB", 0, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_LT", 12, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_RT", 24, 35, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_RB", 36, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_B", 48, 59, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_L", 60, 71, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_T", 72, 83, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Summons.png", "Spawn_R", 84, 95, 0.1f, false);

	// 대기 상태(Skeleton_Wizard(Lightning)_Idle.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Idle.png", "Idle_R", 56, 63, 0.1f);

	// 이동 상태(Skeleton_Wizard(Lightning)_Walk.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Walk.png", "Walk_R", 56, 63, 0.1f);

	// 공격 상태(Skeleton_Wizard(Lightning)_Attack.png : 16, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_LB", 0, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_LT", 16, 31, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_RT", 32, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_RB", 48, 63, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_B", 64, 79, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_L", 80, 95, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_T", 96, 111, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Attack.png", "Attack_R", 112, 127, 0.1f, false);

	// 피격 상태(Skeleton_Wizard(Lightning)_GetHit.png : 4, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_LB", 0, 3, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_LT", 4, 7, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_RT", 8, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_RB", 12, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_B", 16, 19, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_L", 20, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_T", 24, 27, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_GetHit.png", "GetHit_R", 28, 31, 0.1f, false);

	// 사망 상태(Skeleton_Wizard(Lightning)_Death.png : 19, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_LB", 0, 18, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_LT", 19, 37, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_RT", 38, 56, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_RB", 57, 75, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_B", 76, 94, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_L", 95, 113, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_T", 114, 132, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Lightning)_Death.png", "Death_R", 133, 151, 0.1f, false);
}

void SketelonWizard::CreateWizardPoisonType()
{
	// 소환 상태(Skeleton_Wizard(Poison)_Summons.png : 12, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_LB", 0, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_LT", 12, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_RT", 24, 35, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_RB", 36, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_B", 48, 59, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_L", 60, 71, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_T", 72, 83, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Summons.png", "Spawn_R", 84, 95, 0.1f, false);

	// 대기 상태(Skeleton_Wizard(Poison)_Idle.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Idle.png", "Idle_R", 56, 63, 0.1f);

	// 이동 상태(Skeleton_Wizard(Poison)_Walk.png : 8, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_LB", 0, 7, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_LT", 8, 15, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_RT", 16, 23, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_RB", 24, 31, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_B", 32, 39, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_L", 40, 47, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_T", 48, 55, 0.1f);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Walk.png", "Walk_R", 56, 63, 0.1f);

	// 공격 상태(Skeleton_Wizard(Poison)_Attack.png : 16, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_LB", 0, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_LT", 16, 31, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_RT", 32, 47, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_RB", 48, 63, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_B", 64, 79, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_L", 80, 95, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_T", 96, 111, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Attack.png", "Attack_R", 112, 127, 0.1f, false);

	// 피격 상태(Skeleton_Wizard(Poison)_GetHit.png : 4, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_LB", 0, 3, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_LT", 4, 7, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_RT", 8, 11, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_RB", 12, 15, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_B", 16, 19, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_L", 20, 23, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_T", 24, 27, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_GetHit.png", "GetHit_R", 28, 31, 0.1f, false);

	// 사망 상태(Skeleton_Wizard(Poison)_Death.png : 19, 8)
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_LB", 0, 18, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_LT", 19, 37, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_RT", 38, 56, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_RB", 57, 75, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_B", 76, 94, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_L", 95, 113, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_T", 114, 132, 0.1f, false);
	WizardRenderer_->CreateAnimation("Skeleton_Wizard(Poison)_Death.png", "Death_R", 133, 151, 0.1f, false);
}

void SketelonWizard::CreateAnimationEndCallbackFunction()
{
	// 소환 상태
	WizardRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_B", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_L", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_T", std::bind(&SketelonWizard::SpawnAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Spawn_R", std::bind(&SketelonWizard::SpawnAnimationEnd, this));

	// 공격 상태
	WizardRenderer_->SetEndCallBack("Attack_LB", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_LT", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_RT", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_RB", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_B", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_L", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_T", std::bind(&SketelonWizard::AttackAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Attack_R", std::bind(&SketelonWizard::AttackAnimationEnd, this));

	// 피격 상태
	WizardRenderer_->SetEndCallBack("GetHit_LB", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_LT", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_RT", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_RB", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_B", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_L", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_T", std::bind(&SketelonWizard::GetHitAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("GetHit_R", std::bind(&SketelonWizard::GetHitAnimationEnd, this));

	// 사망 상태
	WizardRenderer_->SetEndCallBack("Death_LB", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_LT", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_RT", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_RB", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_B", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_L", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_T", std::bind(&SketelonWizard::DeathAnimationEnd, this));
	WizardRenderer_->SetEndCallBack("Death_R", std::bind(&SketelonWizard::DeathAnimationEnd, this));
}

void SketelonWizard::CreateFSMState()
{
	State_.CreateState("Spawn", std::bind(&SketelonWizard::UpdateSpawnState, this), std::bind(&SketelonWizard::StartSpawnState, this), std::bind(&SketelonWizard::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SketelonWizard::UpdateIdleState, this), std::bind(&SketelonWizard::StartIdleState, this), std::bind(&SketelonWizard::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SketelonWizard::UpdateWalkState, this), std::bind(&SketelonWizard::StartWalkState, this), std::bind(&SketelonWizard::EndWalkState, this));
	State_.CreateState("Warp", std::bind(&SketelonWizard::UpdateWarpState, this), std::bind(&SketelonWizard::StartWarpState, this), std::bind(&SketelonWizard::EndWarpState, this));
	State_.CreateState("Attack", std::bind(&SketelonWizard::UpdateAttackState, this), std::bind(&SketelonWizard::StartAttackState, this), std::bind(&SketelonWizard::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SketelonWizard::UpdateDeathState, this), std::bind(&SketelonWizard::StartDeathState, this), std::bind(&SketelonWizard::EndDeathState, this));
	State_.ChangeState("Spawn");
}
