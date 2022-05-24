#include "PreCompile.h"
#include "AndarielProjectile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void AndarielProjectile::InitProjectile()
{
	// 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성
	CreateAnimation();

	// 충돌체 생성
	CreateCollision();
}

void AndarielProjectile::TextureCutting()
{
	// 이동모션(Andariel_Projetile.png, 18x8)
	GameEngineTexture* Andariel_Projetile = GameEngineTextureManager::GetInst().Find("Andariel_Projetile.png");
	Andariel_Projetile->Cut(18, 8);
}

void AndarielProjectile::CreateAnimation()
{
	// 이동모션(Andariel_Projetile.png, 18x8)
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

	// 렌더링 파이프라인 변경
	Renderer_->SetRenderingPipeLine("TextureTransDepthOff");

	// 애니메이션 생성(Andariel_Projetile.png, 18x8)
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_B" ,   0,  17, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_LB",  18,  35, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_L" ,  36,  53, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_LT",  54,  71, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_T" ,  72,  89, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_RT",  90, 107, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_R" , 108, 125, 0.1f);
	Renderer_->CreateAnimation("Andariel_Projetile.png", "Move_RB", 126, 143, 0.1f);
}

void AndarielProjectile::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}
