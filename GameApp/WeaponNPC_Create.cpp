#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void WeaponNPC::InitWeaponNPC()
{
	// 애니메이션 관련 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성관련
	CreateAnimation();

	// 충돌체 생성
	CreateCollision();

	// FSM 상태관련
	CreateFSMState();
}

void WeaponNPC::TextureCutting()
{
	// 기본상태
	GameEngineTexture* WeaponNPC_Idle = GameEngineTextureManager::GetInst().Find("Charsi_Idle.png");
	WeaponNPC_Idle->Cut(13, 8);

	// 이동상태
	GameEngineTexture* WeaponNPC_Walk = GameEngineTextureManager::GetInst().Find("Charsi_Walk.png");
	WeaponNPC_Walk->Cut(8, 8);
}

void WeaponNPC::CreateAnimation()
{
	WeaponNPCRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	WeaponNPCRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	WeaponNPCRenderer_->GetTransform()->SetLocalZOrder(11.f);

	// 기본상태
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_B",   0,  12, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_LB", 13,  25, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_L",  26,  38, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_LT", 39,  51, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_T",  52,  64, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_RT", 65,  77, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_R",  78,  90, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Idle.png", "Charsi_Idle_RB", 91, 103, 0.1f);

	// 이동상태
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_B",   0,   7, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_LB",  8,  15, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_L",  16,  23, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_LT", 24,  31, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_T",  32,  39, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_RT", 40,  47, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_R",  48,  55, 0.1f);
	WeaponNPCRenderer_->CreateAnimation("Charsi_Walk.png", "Charsi_Walk_RB", 56,  63, 0.1f);

	// 초기상태
	WeaponNPCRenderer_->SetChangeAnimation("Charsi_Idle_B");
}

void WeaponNPC::CreateFSMState()
{
	// 대기상태
	State_.CreateState("WeaponNPC_IDLE", std::bind(&WeaponNPC::UpdateIdle, this), std::bind(&WeaponNPC::StartIdle, this), std::bind(&WeaponNPC::EndIdle, this));

	// 이동상태
	State_.CreateState("WeaponNPC_WALK", std::bind(&WeaponNPC::UpdateWalk, this), std::bind(&WeaponNPC::StartWalk, this), std::bind(&WeaponNPC::EndWalk, this));

	// 상호작용대기상태
	State_.CreateState("WeaponNPC_CONVERSATION", std::bind(&WeaponNPC::UpdateConversation, this), std::bind(&WeaponNPC::StartConversation, this), std::bind(&WeaponNPC::EndConversation, this));

	// 상호작용중상태
	State_.CreateState("WeaponNPC_INTERACTION", std::bind(&WeaponNPC::UpdateInteraction, this), std::bind(&WeaponNPC::StartInteraction, this), std::bind(&WeaponNPC::EndInteraction, this));

	// 초기상태 IDLE
	State_.ChangeState("WeaponNPC_IDLE");
}

void WeaponNPC::CreateCollision()
{
	WeaponNPCCollision_ = CreateTransformComponent<GameEngineCollision>();
	WeaponNPCCollision_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	WeaponNPCCollision_->GetTransform()->SetLocalPosition(WeaponNPCRenderer_->GetTransform()->GetLocalPosition() - CamPos);
	WeaponNPCCollision_->GetTransform()->SetWorldZOrder(-99.f);
}
