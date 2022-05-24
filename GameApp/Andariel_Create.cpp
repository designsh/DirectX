#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Andariel::InitAndariel()
{
	// 몬스터정보 생성
	CreateInfomation();

	// 애니메이션 관련 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성관련
	CreateAnimation();

	// 애니메이션 종료시점 호출함수 관련
	CreateAnimationEndFunction();

	// 애니메이션 특정프레임시점 호출함수 관련
	CreateSpecificFrameFunction();

	// FSM 상태관련
	CreateFSMState();

	// 충돌체 생성
	CreateCollision();
}

void Andariel::TextureCutting()
{
	// 대기상태(Andariel_Idle.png, 16x8)
	GameEngineTexture* Andariel_Idle = GameEngineTextureManager::GetInst().Find("Andariel_Idle.png");
	Andariel_Idle->Cut(16, 8);

	// 이동상태(Andariel_Walk.png, 12x8)
	GameEngineTexture* Andariel_Walk = GameEngineTextureManager::GetInst().Find("Andariel_Walk.png");
	Andariel_Walk->Cut(12, 8);

	// 공격상태(Andariel_Attack.png, 16x8)
	GameEngineTexture* Andariel_Attack = GameEngineTextureManager::GetInst().Find("Andariel_Attack.png");
	Andariel_Attack->Cut(16, 8);

	// 스킬공격상태(Andariel_SpecialCast.png, 18x8)
	GameEngineTexture* Andariel_SpecialCast = GameEngineTextureManager::GetInst().Find("Andariel_SpecialCast.png");
	Andariel_SpecialCast->Cut(18, 8);

	// 사망상태(Andariel_Death.png, 23x8)
	GameEngineTexture* Andariel_Death = GameEngineTextureManager::GetInst().Find("Andariel_Death.png");
	Andariel_Death->Cut(23, 8);

	// 사망상태 오버레이(Andariel_Death_Effect.png, 23x8)
	GameEngineTexture* Andariel_Death_Effect = GameEngineTextureManager::GetInst().Find("Andariel_Death_Effect.png");
	Andariel_Death_Effect->Cut(23, 8);

	// 시체상태(Andariel_Dead.png, 8x1)
	GameEngineTexture* Andariel_Dead = GameEngineTextureManager::GetInst().Find("Andariel_Dead.png");
	Andariel_Dead->Cut(1, 8);
}

void Andariel::CreateAnimation()
{
	Andariel_ = CreateTransformComponent<GameEngineImageRenderer>();
	Andariel_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Andariel_->SetRenderingPipeLine("TextureDepthOff");

	// 대기상태(Andariel_Idle.png, 16x8)
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_B" , 0, 15, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_LB", 16, 31, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_L" , 32, 47, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_LT", 48, 63, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_T" , 64, 79, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_RT", 80, 95, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_R" , 96, 111, 0.1f);
	Andariel_->CreateAnimation("Andariel_Idle.png", "Idle_RB", 112, 127, 0.1f);

	// 이동상태(Andariel_Walk.png, 12x8)
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_B" ,  0, 11, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_LB", 12, 23, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_L" , 24, 35, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_LT", 36, 47, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_T" , 48, 59, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_RT", 60, 71, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_R" , 72, 83, 0.1f);
	Andariel_->CreateAnimation("Andariel_Walk.png", "Walk_RB", 84, 95, 0.1f);

	// 공격상태(Andariel_Attack.png, 16x8)
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_B" ,   0,  15, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_LB",  16,  31, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_L" ,  32,  47, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_LT",  48,  63, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_T" ,  64,  79, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_RT",  80,  95, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_R" ,  96, 111, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Attack.png", "Attack_RB", 112, 127, 0.1f, false);

	// 스킬공격상태(Andariel_SpecialCast.png, 18x8)
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_B" ,   0,  17, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_LB",  18,  35, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_L" ,  36,  53, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_LT",  54,  71, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_T" ,  72,  89, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_RT",  90, 107, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_R" , 108, 125, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_SpecialCast.png", "SkillAttack_RB", 126, 143, 0.1f, false);

	// 사망상태(Andariel_Death.png, 23x8)
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_B" ,   0,  22, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_LB",  23,  45, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_L" ,  46,  68, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_LT",  69,  91, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_T" ,  92, 114, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_RT", 115, 137, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_R" , 138, 160, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Death.png", "Death_RB", 161, 183, 0.1f, false);

	// 시체상태(Andariel_Dead.png, 8x1)
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_B" , 0, 0, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_LB", 0, 1, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_L" , 0, 2, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_LT", 0, 3, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_T" , 0, 4, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_RT", 0, 5, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_R" , 0, 6, 0.1f, false);
	Andariel_->CreateAnimation("Andariel_Dead.png", "Dead_RB", 0, 7, 0.1f, false);

	// 초기애니메이션 셋팅
	Andariel_->SetChangeAnimation("Idle_B");
}

void Andariel::CreateAnimationEndFunction()
{
	// 공격모션 종료
	Andariel_->SetEndCallBack("Attack_LB", std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_LT", std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_RT", std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_RB", std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_B" , std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_L" , std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_T" , std::bind(&Andariel::AttackEnd, this));
	Andariel_->SetEndCallBack("Attack_R" , std::bind(&Andariel::AttackEnd, this));

	// 스킬공격모션 종료
	Andariel_->SetEndCallBack("SkillAttack_LB", std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_LT", std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_RT", std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_RB", std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_B" , std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_L" , std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_T" , std::bind(&Andariel::SkillAttackEnd, this));
	Andariel_->SetEndCallBack("SkillAttack_R" , std::bind(&Andariel::SkillAttackEnd, this));

	// 사망모션 종료
	Andariel_->SetEndCallBack("Death_LB", std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_LT", std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_RT", std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_RB", std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_B" , std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_L" , std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_T" , std::bind(&Andariel::DeathEnd, this));
	Andariel_->SetEndCallBack("Death_R" , std::bind(&Andariel::DeathEnd, this));
}

void Andariel::CreateSpecificFrameFunction()
{
	// Bottom SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_B", 0 + 13, std::bind(&Andariel::ProjectileFire, this));

	// LeftBottom SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LB", 18 + 13, std::bind(&Andariel::ProjectileFire, this));

	// Left SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_L", 36 + 13, std::bind(&Andariel::ProjectileFire, this));

	// LeftTop SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_LT", 54 + 13, std::bind(&Andariel::ProjectileFire, this));
	
	// Top SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_T", 72 + 13, std::bind(&Andariel::ProjectileFire, this));
	
	// RightTop SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RT", 90 + 13, std::bind(&Andariel::ProjectileFire, this));

	// Right SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_R", 108 + 13, std::bind(&Andariel::ProjectileFire, this));

	// Right SkillAttack Animation
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 4, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 5, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 6, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 7, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 8, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 9, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 10, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 11, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 12, std::bind(&Andariel::ProjectileFire, this));
	Andariel_->SetFrameCallBack("SkillAttack_RB", 126 + 13, std::bind(&Andariel::ProjectileFire, this));
}

void Andariel::CreateFSMState()
{
	State_.CreateState("RoomDetect", std::bind(&Andariel::UpdateRoomDetect, this), std::bind(&Andariel::StartRoomDetect, this), std::bind(&Andariel::EndRoomDetect, this));
	State_.CreateState("Idle", std::bind(&Andariel::UpdateIdle, this), std::bind(&Andariel::StartIdle, this), std::bind(&Andariel::EndIdle, this));
	State_.CreateState("Walk", std::bind(&Andariel::UpdateMove, this), std::bind(&Andariel::StartMove, this), std::bind(&Andariel::EndMove, this));
	State_.CreateState("Attack", std::bind(&Andariel::UpdateNormalAttack, this), std::bind(&Andariel::StartNormalAttack, this), std::bind(&Andariel::EndNormalAttack, this));
	State_.CreateState("SkillAttack", std::bind(&Andariel::UpdateSkillAttack, this), std::bind(&Andariel::StartSkillAttack, this), std::bind(&Andariel::EndSkillAttack, this));
	State_.CreateState("GetHit", std::bind(&Andariel::UpdateGetHit, this), std::bind(&Andariel::StartGetHit, this), std::bind(&Andariel::EndGetHit, this));
	State_.CreateState("Death", std::bind(&Andariel::UpdateDeath, this), std::bind(&Andariel::StartDeath, this), std::bind(&Andariel::EndDeath, this));
	State_.CreateState("Dead", std::bind(&Andariel::UpdateDead, this), std::bind(&Andariel::StartDead, this), std::bind(&Andariel::EndDead, this));

	// 초기상태 지정
	State_.ChangeState("RoomDetect");
}

void Andariel::CreateCollision()
{
	// 본체 충돌체(피격판정용)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void Andariel::CreateInfomation()
{
	// 해당 몬스터의 정보를 생성
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::Andariel, MonsterInfo_);

	// 현재 체력 셋팅(랜덤)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// 드랍골드량 셋팅
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
}