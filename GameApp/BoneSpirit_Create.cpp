#include "PreCompile.h"
#include "BoneSpirit.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void BoneSpirit::InitWizardProjectile()
{
	// ÅØ½ºÃÄ ÄÆÆÃ
	TextureCutting();
}

void BoneSpirit::TextureCutting()
{
	// ¹ß»çÃ¼ ÄÆÆÃ
	GameEngineTexture* BoneSpirit_Projectile = GameEngineTextureManager::GetInst().Find("PlayerSkill_BoneSpirit.png");
	BoneSpirit_Projectile->Cut(8, 8);

	// Æø¹ßÃ¼ ÄÆÆÃ
	GameEngineTexture* BoneSpirit_Explode = GameEngineTextureManager::GetInst().Find("PlayerSkill_BoneSpirit_Explode.png");
	BoneSpirit_Explode->Cut(13, 1);
}

void BoneSpirit::CreateAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Renderer_->SetRenderingPipeLine("TextureTrans");

	// ¹ß»çÃ¼(8x8)
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_LB", 0, 7, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_LT", 8, 15, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_RT", 16, 23, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_RB", 24, 31, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_B" , 32, 39, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_L" , 40, 47, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_T" , 48, 55, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_R" , 56, 63, 0.1f);
	
	// Æø¹ßÃ¼(13,1)
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_LB", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_LT", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_RT", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_RB", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_B" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_L" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_T" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_R" , 0, 12, 0.1f);
}

void BoneSpirit::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(80.f, 80.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}
