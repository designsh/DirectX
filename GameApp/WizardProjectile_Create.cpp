#include "PreCompile.h"
#include "WizardProjectile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

void WizardProjectile::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(80.f, 80.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}

void WizardProjectile::CreateAnimation()
{
	switch (ProjectileType_)
	{
		case SkeletonWizardType::COLD:
		{
			CreateColdTypeAnimation();
			break;
		}
		case SkeletonWizardType::FIRE:
		{
			CreateFireTypeAnimation();
			break;
		}
		case SkeletonWizardType::LIGHTNING:
		{
			CreateLightingTypeAnimation();
			break;
		}
		case SkeletonWizardType::POISON:
		{
			CreatePoisonTypeAnimation();
			break;
		}
	}
}

void WizardProjectile::CreateColdTypeAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(128.f, 128.f));
	Renderer_->SetRenderingPipeLine("TextureTrans");

	// 애니메이션 생성
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_LB",  0,  5, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_LT",  6, 11, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_RT", 12, 17, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_RB", 18, 23, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_B" , 24, 29, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_L" , 30, 35, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_T" , 36, 47, 0.1f);
	Renderer_->CreateAnimation("Wizard_Cold.png", "Move_R" , 48, 53, 0.1f);

	// 생성위치 셋팅
	GetTransform()->SetLocalPosition(StartPos_);
}

void WizardProjectile::CreateFireTypeAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(128.f, 128.f));
	Renderer_->SetRenderingPipeLine("TextureTrans");

	// 애니메이션 생성
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_LB",  0,  4, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_LT",  5,  9, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_RT", 10, 14, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_RB", 15, 19, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_B" , 20, 24, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_L" , 25, 29, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_T" , 30, 34, 0.1f);
	Renderer_->CreateAnimation("Wizard_Fire.png", "Move_R" , 35, 39, 0.1f);

	// 생성위치 셋팅
	GetTransform()->SetLocalPosition(StartPos_);
}

void WizardProjectile::CreateLightingTypeAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Renderer_->SetRenderingPipeLine("TextureTrans");

	// 애니메이션 생성
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_LB",  0,  7, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_LT",  8, 15, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_RT", 16, 23, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_RB", 24, 31, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_B" , 32, 39, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_L" , 40, 47, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_T" , 48, 55, 0.1f);
	Renderer_->CreateAnimation("Wizard_Lighting.png", "Move_R" , 56, 63, 0.1f);

	// 생성위치 셋팅
	GetTransform()->SetLocalPosition(StartPos_);
}

void WizardProjectile::CreatePoisonTypeAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Renderer_->SetRenderingPipeLine("TextureTrans");

	// 애니메이션 생성
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_LB",   0,  29, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_LT",  30,  59, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_RT",  60,  89, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_RB",  90, 119, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_B" , 120, 149, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_L" , 150, 179, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_T" , 180, 209, 0.1f);
	Renderer_->CreateAnimation("Wizard_Poison.png", "Move_R" , 210, 239, 0.1f);

	// 생성위치 셋팅
	GetTransform()->SetLocalPosition(StartPos_);
}
