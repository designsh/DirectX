#include "PreCompile.h"
#include "BoneSpirit.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void BoneSpirit::CreateAnimation()
{
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Renderer_->SetRenderingPipeLine("TextureTransDepthOff");

	// 발사체(8x8)
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_LB", 0, 7, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_LT", 8, 15, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_RT", 16, 23, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_RB", 24, 31, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_B" , 32, 39, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_L" , 40, 47, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_T" , 48, 55, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit.png", "Move_R" , 56, 63, 0.1f);
	
	// 폭발체(13,1)
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_LB", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_LT", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_RT", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_RB", 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_B" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_L" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_T" , 0, 12, 0.1f);
	Renderer_->CreateAnimation("PlayerSkill_BoneSpirit_Explode.png", "Explode_R" , 0, 12, 0.1f);

	// 폭발체 애니메이션 종료시 호출함수 등록
	Renderer_->SetEndCallBack("Explode_LB", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_LT", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_RT", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_RB", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_B", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_L", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_T", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));
	Renderer_->SetEndCallBack("Explode_R", std::bind(&BoneSpirit::ExplodeAnimationEnd, this));

	// 초기값셋팅
	Renderer_->SetChangeAnimation("Move_B");
}

void BoneSpirit::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(80.f, 80.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}

void BoneSpirit::CreateFSMState()
{
	State_.CreateState("Move", std::bind(&BoneSpirit::UpdateMoveState, this), std::bind(&BoneSpirit::StartMoveState, this), std::bind(&BoneSpirit::EndMoveState, this));
	State_.CreateState("Search", std::bind(&BoneSpirit::UpdateSearchState, this), std::bind(&BoneSpirit::StartSearchState, this), std::bind(&BoneSpirit::EndSearchState, this));
	State_.CreateState("Fire", std::bind(&BoneSpirit::UpdateFireState, this), std::bind(&BoneSpirit::StartFireState, this), std::bind(&BoneSpirit::EndFireState, this));
	State_.CreateState("Explode", std::bind(&BoneSpirit::UpdateExplodeState, this), std::bind(&BoneSpirit::StartExplodeState, this), std::bind(&BoneSpirit::EndExplodeState, this));
}
