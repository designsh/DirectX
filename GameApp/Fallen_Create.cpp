#include "PreCompile.h"
#include "Fallen.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Fallen::InitFallen()
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

void Fallen::TextureCutting()
{
	// 대기상태(Fallen_Idle.png, 20x8)
	GameEngineTexture* Fallen_Idle = GameEngineTextureManager::GetInst().Find("Fallen_Idle.png");
	Fallen_Idle->Cut(20, 8);

	// 이동상태(Fallen_Walk.png, 10x8)
	GameEngineTexture* Fallen_Walk = GameEngineTextureManager::GetInst().Find("Fallen_Walk.png");
	Fallen_Walk->Cut(10, 8);

	// 공격상태(Fallen_Attack.png, 10x8)
	GameEngineTexture* Fallen_Attack = GameEngineTextureManager::GetInst().Find("Fallen_Attack.png");
	Fallen_Attack->Cut(10, 8);

	// 피격상태(Fallen_GetHit.png, 7x8)
	GameEngineTexture* Fallen_GetHit = GameEngineTextureManager::GetInst().Find("Fallen_GetHit.png");
	Fallen_GetHit->Cut(7, 8);

	// 사망상태(Fallen_Death.png, 20x8)
	GameEngineTexture* Fallen_Death = GameEngineTextureManager::GetInst().Find("Fallen_Death.png");
	Fallen_Death->Cut(20, 8);

	// 시체상태(Fallen_Dead.png, 8x1)
	GameEngineTexture* Fallen_Dead = GameEngineTextureManager::GetInst().Find("Fallen_Dead.png");
	Fallen_Dead->Cut(1, 8);
}

void Fallen::CreateAnimation()
{
	Fallen_ = CreateTransformComponent<GameEngineImageRenderer>();
	Fallen_->GetTransform()->SetLocalScaling(float4(120.f, 120.f));
	Fallen_->SetRenderingPipeLine("TextureDepthOff");

	// 대기상태(Fallen_Idle.png, 20x8)
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_LB",   0,  19, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_LT",  20,  39, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_RT",  40,  59, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_RB",  60,  79, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_B" ,  80,  99, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_L" , 100, 119, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_T" , 120, 139, 0.1f);
	Fallen_->CreateAnimation("Fallen_Idle.png", "Idle_R" , 140, 159, 0.1f);

	// 이동상태(Fallen_Walk.png, 10x8)
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_LB",  0,  9, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_LT", 10, 19, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_RT", 20, 29, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_RB", 30, 39, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_B" , 40, 49, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_L" , 50, 59, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_T" , 60, 69, 0.1f);
	Fallen_->CreateAnimation("Fallen_Walk.png", "Walk_R" , 70, 79, 0.1f);

	// 공격상태(Fallen_Attack.png, 10x8)
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_LB",  0,  9, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_LT", 10, 19, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_RT", 20, 29, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_RB", 30, 39, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_B" , 40, 49, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_L" , 50, 59, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_T" , 60, 69, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Attack.png", "Attack_R" , 70, 79, 0.1f, false);

	// 피격상태(Fallen_GetHit.png, 7x8)
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_LB",  0,  6, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_LT",  7, 13, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_RT", 14, 20, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_RB", 21, 27, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_B" , 28, 34, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_L" , 35, 41, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_T" , 42, 48, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_GetHit.png", "GetHit_R" , 49, 55, 0.1f, false);

	// 사망상태(Fallen_Death.png, 20x8)
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_LB",   0,  19, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_LT",  20,  39, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_RT",  40,  59, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_RB",  60,  79, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_B" ,  80,  99, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_L" , 100, 119, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_T" , 120, 139, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Death.png", "Death_R" , 140, 159, 0.1f, false);

	// 시체상태(Fallen_Dead.png, 1x8)
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_LB", 0, 0, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_LT", 0, 1, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_RT", 0, 2, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_RB", 0, 3, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_B" , 0, 4, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_L" , 0, 5, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_T" , 0, 6, 0.1f, false);
	Fallen_->CreateAnimation("Fallen_Dead.png", "Dead_R" , 0, 7, 0.1f, false);

	// 초기상태
	Fallen_->SetChangeAnimation("Idle_B");
}

void Fallen::CreateAnimationEndFunction()
{
	// 일반공격모션 종료
	Fallen_->SetEndCallBack("Attack_LB", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_LT", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_RT", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_RB", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_B", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_L", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_T", std::bind(&Fallen::AttackEnd, this));
	Fallen_->SetEndCallBack("Attack_R", std::bind(&Fallen::AttackEnd, this));

	// 피격모션 종료
	Fallen_->SetEndCallBack("GetHit_LB", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_LT", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_RT", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_RB", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_B", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_L", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_T", std::bind(&Fallen::GetHitEnd, this));
	Fallen_->SetEndCallBack("GetHit_R", std::bind(&Fallen::GetHitEnd, this));

	// 사망모션 종료
	Fallen_->SetEndCallBack("Death_LB", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_LT", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_RT", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_RB", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_B", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_L", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_T", std::bind(&Fallen::DeathEnd, this));
	Fallen_->SetEndCallBack("Death_R", std::bind(&Fallen::DeathEnd, this));
}

void Fallen::CreateFSMState()
{
	State_.CreateState("RoomDetect", std::bind(&Fallen::UpdateRoomDetect, this), std::bind(&Fallen::StartRoomDetect, this), std::bind(&Fallen::EndRoomDetect, this));
	State_.CreateState("Idle", std::bind(&Fallen::UpdateIdle, this), std::bind(&Fallen::StartIdle, this), std::bind(&Fallen::EndIdle, this));
	State_.CreateState("Walk", std::bind(&Fallen::UpdateMove, this), std::bind(&Fallen::StartMove, this), std::bind(&Fallen::EndMove, this));
	State_.CreateState("Attack", std::bind(&Fallen::UpdateNormalAttack, this), std::bind(&Fallen::StartNormalAttack, this), std::bind(&Fallen::EndNormalAttack, this));
	State_.CreateState("GetHit", std::bind(&Fallen::UpdateGetHit, this), std::bind(&Fallen::StartGetHit, this), std::bind(&Fallen::EndGetHit, this));
	State_.CreateState("Death", std::bind(&Fallen::UpdateDeath, this), std::bind(&Fallen::StartDeath, this), std::bind(&Fallen::EndDeath, this));
	State_.CreateState("Dead", std::bind(&Fallen::UpdateDead, this), std::bind(&Fallen::StartDead, this), std::bind(&Fallen::EndDead, this));

	// 초기상태 지정
	State_.ChangeState("RoomDetect");
}

void Fallen::CreateCollision()
{
	// 본체 충돌체(피격판정용)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void Fallen::CreateInfomation()
{
	// 해당 몬스터의 정보를 생성
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::Fallen, MonsterInfo_);

	// 현재 체력 셋팅(랜덤)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// 드랍골드량 셋팅
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
}

