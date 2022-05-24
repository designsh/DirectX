#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Tainted::InitTainted()
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
}

void Tainted::CreateInfomation()
{
	// 해당 몬스터의 정보를 생성
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::Tainted, MonsterInfo_);

	// 현재 체력 셋팅(랜덤)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// 드랍골드량 셋팅
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
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
	Tainted_->SetRenderingPipeLine("TextureDepthOff");

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
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_LB", 0, 9, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_LT", 10, 19, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_RT", 20, 29, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_RB", 30, 39, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_B", 40, 49, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_L", 50, 59, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_T", 60, 69, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "Attack_R", 70, 79, 0.1f, false);
	
	// 피격상태
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LB", 0, 7, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LT", 8, 15, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RT", 16, 23, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RB", 24, 31, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_B", 32, 39, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_L", 40, 47, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_T", 48, 55, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_R", 56, 63, 0.1f, false);

	// 사망상태
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LB", 0, 18, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LT", 19, 37, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RT", 38, 56, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RB", 57, 75, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_B", 76, 94, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_L", 95, 113, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_T", 114, 132, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_R", 133, 151, 0.1f, false);

	// 시체상태
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LB", 0, 0, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LT", 1, 1, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RT", 2, 2, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RB", 3, 3, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_B", 4, 4, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_L", 5, 5, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_T", 6, 6, 0.1f, false);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_R", 7, 7, 0.1f, false);

	// 초기상태
	Tainted_->SetChangeAnimation("Idle_B");
}

void Tainted::CreateAnimationEndFunction()
{
	// 일반공격모션 종료
	Tainted_->SetEndCallBack("Attack_LB", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_LT", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_RT", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_RB", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_B", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_L", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_T", std::bind(&Tainted::AttackEnd, this));
	Tainted_->SetEndCallBack("Attack_R", std::bind(&Tainted::AttackEnd, this));

	// 피격모션 종료
	Tainted_->SetEndCallBack("GetHit_LB", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_LT", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_RT", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_RB", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_B", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_L", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_T", std::bind(&Tainted::GetHitEnd, this));
	Tainted_->SetEndCallBack("GetHit_R", std::bind(&Tainted::GetHitEnd, this));

	// 사망모션 종료
	Tainted_->SetEndCallBack("Death_LB", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_LT", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_RT", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_RB", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_B", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_L", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_T", std::bind(&Tainted::DeathEnd, this));
	Tainted_->SetEndCallBack("Death_R", std::bind(&Tainted::DeathEnd, this));
}

void Tainted::CreateFSMState()
{
	State_.CreateState("RoomDetect", std::bind(&Tainted::UpdateRoomDetect, this), std::bind(&Tainted::StartRoomDetect, this), std::bind(&Tainted::EndRoomDetect, this));
	State_.CreateState("Idle", std::bind(&Tainted::UpdateIdle, this), std::bind(&Tainted::StartIdle, this), std::bind(&Tainted::EndIdle, this));
	State_.CreateState("Walk", std::bind(&Tainted::UpdateMove, this), std::bind(&Tainted::StartMove, this), std::bind(&Tainted::EndMove, this));
	State_.CreateState("Attack", std::bind(&Tainted::UpdateNormalAttack, this), std::bind(&Tainted::StartNormalAttack, this), std::bind(&Tainted::EndNormalAttack, this));
	State_.CreateState("GetHit", std::bind(&Tainted::UpdateGetHit, this), std::bind(&Tainted::StartGetHit, this), std::bind(&Tainted::EndGetHit, this));
	State_.CreateState("Death", std::bind(&Tainted::UpdateDeath, this), std::bind(&Tainted::StartDeath, this), std::bind(&Tainted::EndDeath, this));
	State_.CreateState("Dead", std::bind(&Tainted::UpdateDead, this), std::bind(&Tainted::StartDead, this), std::bind(&Tainted::EndDead, this));

	// 초기상태 지정
	State_.ChangeState("RoomDetect");
}

void Tainted::CreateCollision()
{
	// 본체 충돌체(피격판정용)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}
