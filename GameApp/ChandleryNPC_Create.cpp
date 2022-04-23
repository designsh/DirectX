#include "PreCompile.h"
#include "ChandleryNPC.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>


void ChandleryNPC::InitChandleryNPC()
{
	// 애니메이션 관련 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성관련
	CreateAnimation();

	// FSM 상태관련
	CreateFSMState();

	// 충돌체 생성
	CreateCollision();
}

void ChandleryNPC::TextureCutting()
{
	// 기본상태
	GameEngineTexture* ChandleryNPC_Idle = GameEngineTextureManager::GetInst().Find("Akara_Idle.png");
	ChandleryNPC_Idle->Cut(13, 8);

	// 이동상태
	GameEngineTexture* ChandleryNPC_Walk = GameEngineTextureManager::GetInst().Find("Akara_Walk.png");
	ChandleryNPC_Walk->Cut(8, 8);
}

void ChandleryNPC::CreateAnimation()
{
	ChandleryNPCRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	ChandleryNPCRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

	// 기본상태
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_T" , 0, 12, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_RT", 13, 25, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_R" , 26, 38, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_RB", 39, 51, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_B" , 52, 64, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_LB", 65, 77, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_L" , 78, 90, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Idle.png", "Akara_Idle_LT", 91, 103, 0.1f);

	// 이동상태
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_T" , 0, 7, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_RT", 8, 15, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_R" , 16, 23, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_RB", 24, 31, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_B" , 32, 39, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_LB", 40, 47, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_L" , 48, 55, 0.1f);
	ChandleryNPCRenderer_->CreateAnimation("Akara_Walk.png", "Akara_Walk_LT", 56, 63, 0.1f);

	// 초기상태
	ChandleryNPCRenderer_->SetChangeAnimation("Akara_Idle_B");
}

void ChandleryNPC::CreateFSMState()
{
	// 대기상태
	State_.CreateState("ChandleryNPC_IDLE", std::bind(&ChandleryNPC::UpdateIdle, this), std::bind(&ChandleryNPC::StartIdle, this), std::bind(&ChandleryNPC::EndIdle, this));

	// 이동상태
	State_.CreateState("ChandleryNPC_WALK", std::bind(&ChandleryNPC::UpdateWalk, this), std::bind(&ChandleryNPC::StartWalk, this), std::bind(&ChandleryNPC::EndWalk, this));

	// 상호작용대기상태
	State_.CreateState("ChandleryNPC_CONVERSATION", std::bind(&ChandleryNPC::UpdateConversation, this), std::bind(&ChandleryNPC::StartConversation, this), std::bind(&ChandleryNPC::EndConversation, this));

	// 상호작용중상태
	State_.CreateState("ChandleryNPC_INTERACTION", std::bind(&ChandleryNPC::UpdateInteraction, this), std::bind(&ChandleryNPC::StartInteraction, this), std::bind(&ChandleryNPC::EndInteraction, this));

	// 초기상태 IDLE
	State_.ChangeState("ChandleryNPC_IDLE");
}

void ChandleryNPC::CreateCollision()
{
	ChandleryNPCCollision_ = CreateTransformComponent<GameEngineCollision>();
	ChandleryNPCCollision_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));

	float4 Pos = GetTransform()->GetLocalPosition();
	ChandleryNPCCollision_->GetTransform()->SetLocalPosition(float4(Pos.x, Pos.y, -10.f));
}

