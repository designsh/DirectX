#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Tainted::InitTainted()
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

void Tainted::TextureCutting()
{
	// 대기상태(Tainted_Idle.png)
	GameEngineTexture* Tainted_Idle = GameEngineTextureManager::GetInst().Find("Tainted_Idle.png");
	Tainted_Idle->Cut(8, 8);

	// 이동상태(Tainted_Walk.png)
	GameEngineTexture* Tainted_Walk = GameEngineTextureManager::GetInst().Find("Tainted_Walk.png");
	Tainted_Walk->Cut(8, 8);

	// 기본공격상태(Tainted_NormalAttack.png)
	GameEngineTexture* Tainted_NormalAttack = GameEngineTextureManager::GetInst().Find("Tainted_NormalAttack.png");
	Tainted_NormalAttack->Cut(10, 8);

	// 스킬공격상태(Tainted_SpecialAttack.png)
	GameEngineTexture* Tainted_SpecialAttack = GameEngineTextureManager::GetInst().Find("Tainted_SpecialAttack.png");
	Tainted_SpecialAttack->Cut(10, 8);

	// 피격상태(Tainted_GetHit.png)
	GameEngineTexture* Tainted_GetHit = GameEngineTextureManager::GetInst().Find("Tainted_GetHit.png");
	Tainted_GetHit->Cut(8, 8);

	// 사망상태(Tainted_Death.png)
	GameEngineTexture* Tainted_Death = GameEngineTextureManager::GetInst().Find("Tainted_Death.png");
	Tainted_Death->Cut(19, 8);

	// 시체상태(Tainted_Dead.png)
	GameEngineTexture* Tainted_Dead = GameEngineTextureManager::GetInst().Find("Tainted_Dead.png");
	Tainted_Dead->Cut(8, 1);
}

void Tainted::CreateAnimation()
{
	Tainted_ = CreateTransformComponent<GameEngineImageRenderer>();
	Tainted_->GetTransform()->SetLocalScaling(float4(280.f, 280.f));

	// 대기상태
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_R", 56, 63, 0.1f);

	// 이동상태
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_R", 56, 63, 0.1f);

	// 기본공격상태
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_LB", 0, 9, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_LT", 10, 19, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_RT", 20, 29, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_RB", 30, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_B", 40, 49, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_L", 50, 59, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_T", 60, 69, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_R", 70, 79, 0.1f);

	// 스킬공격상태
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_LB", 0, 9, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_LT", 10, 19, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_RT", 20, 29, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_RB", 30, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_B", 40, 49, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_L", 50, 59, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_T", 60, 69, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_R", 70, 79, 0.1f);

	// 피격상태
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_R", 56, 63, 0.1f);

	// 사망상태
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LB", 0, 18, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LT", 19, 37, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RT", 38, 56, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RB", 57, 75, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_B", 76, 94, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_L", 95, 113, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_T", 114, 132, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_R", 133, 151, 0.1f);

	// 시체상태
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_R", 56, 63, 0.1f);

	// 초기상태
	Tainted_->SetChangeAnimation("Idle_B");
}

void Tainted::CreateFSMState()
{
	// 대기상태(적탐지상태)
	State_.CreateState("Tainted_IDLE", std::bind(&Tainted::UpdateIdle, this), std::bind(&Tainted::StartIdle, this), std::bind(&Tainted::EndIdle, this));

	// 적감지상태
	State_.CreateState("Tainted_DETECT", std::bind(&Tainted::UpdateEnemyDetect, this), std::bind(&Tainted::StartEnemyDetect, this), std::bind(&Tainted::EndEnemyDetect, this));

	// 이동상태
	State_.CreateState("Tainted_MOVE", std::bind(&Tainted::UpdateMove, this), std::bind(&Tainted::StartMove, this), std::bind(&Tainted::EndMove, this));

	// 기본공격상태
	State_.CreateState("Tainted_ATTACK", std::bind(&Tainted::UpdateNormalAttack, this), std::bind(&Tainted::StartNormalAttack, this), std::bind(&Tainted::EndNormalAttack, this));

	// 스킬공격상태
	State_.CreateState("Tainted_SKILL", std::bind(&Tainted::UpdateSpecialAttack, this), std::bind(&Tainted::StartSpecialAttack, this), std::bind(&Tainted::EndSpecialAttack, this));

	// 피격상태
	State_.CreateState("Tainted_GETHIT", std::bind(&Tainted::UpdateGetHit, this), std::bind(&Tainted::StartGetHit, this), std::bind(&Tainted::EndGetHit, this));

	// 사망상태
	State_.CreateState("Tainted_DEATH", std::bind(&Tainted::UpdateDeath, this), std::bind(&Tainted::StartDeath, this), std::bind(&Tainted::EndDeath, this));

	// 시체상태
	State_.CreateState("Tainted_DEATH", std::bind(&Tainted::UpdateDead, this), std::bind(&Tainted::StartDead, this), std::bind(&Tainted::EndDead, this));

	// 초기상태 지정
	State_.ChangeState("Tainted_IDLE");
}

void Tainted::CreateCollision()
{
	//// 본체 충돌체(피격판정용)
	//BodyCollider_ = CreateTransformComponent<GameEngineCollision>();
	//BodyCollider_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));

	//float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	//BodyCollider_->GetTransform()->SetLocalPosition(Tainted_->GetTransform()->GetLocalPosition() - CamPos);

	//BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);

	//// 공격 충돌체(공격판정용)
	//AttackCollider_ = CreateTransformComponent<GameEngineCollision>();
	//AttackCollider_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));

	//float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	//AttackCollider_->GetTransform()->SetLocalPosition(Tainted_->GetTransform()->GetLocalPosition() - CamPos);

	//AttackCollider_->GetTransform()->SetWorldZOrder(-99.f);
}
