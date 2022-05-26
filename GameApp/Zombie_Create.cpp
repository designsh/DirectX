#include "PreCompile.h"
#include "Zombie.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Zombie::InitZombie()
{
	// 몬스터정보 생성
	CreateInfomation();

	// 애니메이션 관련 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성관련
	CreateAnimation();

	// 애니메이션 종료시점 호출함수 관련
	CreateAnimationEndFunction();

	// FSM 상태관련
	CreateFSMState();

	// 충돌체 생성
	CreateCollision();

	// 효과음 사운드 플레이어 생성
	StateSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void Zombie::TextureCutting()
{
	// 대기상태(Zombie_Idle.png, 8x8)
	GameEngineTexture* Zombie_Idle = GameEngineTextureManager::GetInst().Find("Zombie_Idle.png");
	Zombie_Idle->Cut(8, 8);

	// 이동상태(Zombie_Walk.png, 12x8)
	GameEngineTexture* Zombie_Walk = GameEngineTextureManager::GetInst().Find("Zombie_Walk.png");
	Zombie_Walk->Cut(12, 8);

	// 공격상태(Zombie_Attack.png, 16x8)
	GameEngineTexture* Zombie_Attack = GameEngineTextureManager::GetInst().Find("Zombie_Attack.png");
	Zombie_Attack->Cut(16, 8);

	// 피격상태(Zombie_GetHit.png, 5x8)
	GameEngineTexture* Zombie_GetHit = GameEngineTextureManager::GetInst().Find("Zombie_GetHit.png");
	Zombie_GetHit->Cut(5, 8);

	// 사망상태(Zombie_Death.png, 19x8)
	GameEngineTexture* Zombie_Death = GameEngineTextureManager::GetInst().Find("Zombie_Death.png");
	Zombie_Death->Cut(19, 8);

	// 시체상태(Zombie_Dead.png, 1x8)
	GameEngineTexture* Zombie_Dead = GameEngineTextureManager::GetInst().Find("Zombie_Dead.png");
	Zombie_Dead->Cut(1, 8);
}

void Zombie::CreateAnimation()
{
	Zombie_ = CreateTransformComponent<GameEngineImageRenderer>();
	Zombie_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Zombie_->SetRenderingPipeLine("TextureDepthOff");

	// 대기상태(Zombie_Idle.png, 8x8)
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_LB", 0, 7, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_LT", 8, 15, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_RT", 16, 23, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_RB", 24, 31, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_B" , 32, 39, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_L" , 40, 47, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_T" , 48, 55, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_R" , 56, 63, 0.1f);

	// 이동상태(Zombie_Walk.png, 12x8)
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_LB",  0, 11, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_LT", 12, 23, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_RT", 24, 35, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_RB", 36, 47, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_B" , 48, 59, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_L" , 60, 71, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_T" , 72, 83, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_R" , 84, 95, 0.1f);

	// 공격상태(Zombie_Attack.png, 16x8)
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// 피격상태(Zombie_GetHit.png, 5x8)
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_LB",  0,  4, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_LT",  5,  9, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_RT", 10, 14, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_RB", 15, 19, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_B" , 20, 24, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_L" , 25, 29, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_T" , 30, 34, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_R" , 35, 39, 0.1f, false);

	// 사망상태(Zombie_Death.png, 19x8)
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_LB",   0,  18, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_LT",  19,  37, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_RT",  38,  56, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_RB",  57,  75, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_B" ,  76,  94, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_L" ,  95, 113, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_T" , 114, 132, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_R" , 133, 151, 0.1f, false);

	// 시체상태(Zombie_Dead.png, 1x8)
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_LB", 0, 0, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_LT", 0, 1, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_RT", 0, 2, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_RB", 0, 3, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_B" , 0, 4, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_L" , 0, 5, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_T" , 0, 6, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_R" , 0, 7, 0.1f, false);

	// 초기상태
	Zombie_->SetChangeAnimation("Idle_B");
}

void Zombie::CreateAnimationEndFunction()
{
	// 일반공격모션 종료
	Zombie_->SetEndCallBack("Attack_LB", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_LT", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_RT", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_RB", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_B", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_L", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_T", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_R", std::bind(&Zombie::AttackEnd, this));

	// 피격모션 종료
	Zombie_->SetEndCallBack("GetHit_LB", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_LT", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_RT", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_RB", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_B", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_L", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_T", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_R", std::bind(&Zombie::GetHitEnd, this));

	// 사망모션 종료
	Zombie_->SetEndCallBack("Death_LB", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_LT", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_RT", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_RB", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_B", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_L", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_T", std::bind(&Zombie::DeathEnd, this));
	Zombie_->SetEndCallBack("Death_R", std::bind(&Zombie::DeathEnd, this));
}

void Zombie::CreateFSMState()
{
	State_.CreateState("RoomDetect", std::bind(&Zombie::UpdateRoomDetect, this), std::bind(&Zombie::StartRoomDetect, this), std::bind(&Zombie::EndRoomDetect, this));
	State_.CreateState("Idle", std::bind(&Zombie::UpdateIdle, this), std::bind(&Zombie::StartIdle, this), std::bind(&Zombie::EndIdle, this));
	State_.CreateState("Walk", std::bind(&Zombie::UpdateMove, this), std::bind(&Zombie::StartMove, this), std::bind(&Zombie::EndMove, this));
	State_.CreateState("Attack", std::bind(&Zombie::UpdateNormalAttack, this), std::bind(&Zombie::StartNormalAttack, this), std::bind(&Zombie::EndNormalAttack, this));
	State_.CreateState("GetHit", std::bind(&Zombie::UpdateGetHit, this), std::bind(&Zombie::StartGetHit, this), std::bind(&Zombie::EndGetHit, this));
	State_.CreateState("Death", std::bind(&Zombie::UpdateDeath, this), std::bind(&Zombie::StartDeath, this), std::bind(&Zombie::EndDeath, this));
	State_.CreateState("Dead", std::bind(&Zombie::UpdateDead, this), std::bind(&Zombie::StartDead, this), std::bind(&Zombie::EndDead, this));

	// 초기상태 지정
	State_.ChangeState("RoomDetect");
}

void Zombie::CreateCollision()
{
	// 본체 충돌체(피격판정용)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void Zombie::CreateInfomation()
{
	// 해당 몬스터의 정보를 생성
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::Zombie, MonsterInfo_);

	// 현재 체력 셋팅(랜덤)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// 드랍골드량 셋팅
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
}
