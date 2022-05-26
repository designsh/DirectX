#include "PreCompile.h"
#include "Zombie.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Zombie::InitZombie()
{
	// �������� ����
	CreateInfomation();

	// �ִϸ��̼� ���� �ؽ��� ����
	TextureCutting();

	// �ִϸ��̼� ��������
	CreateAnimation();

	// �ִϸ��̼� ������� ȣ���Լ� ����
	CreateAnimationEndFunction();

	// FSM ���°���
	CreateFSMState();

	// �浹ü ����
	CreateCollision();

	// ȿ���� ���� �÷��̾� ����
	StateSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void Zombie::TextureCutting()
{
	// ������(Zombie_Idle.png, 8x8)
	GameEngineTexture* Zombie_Idle = GameEngineTextureManager::GetInst().Find("Zombie_Idle.png");
	Zombie_Idle->Cut(8, 8);

	// �̵�����(Zombie_Walk.png, 12x8)
	GameEngineTexture* Zombie_Walk = GameEngineTextureManager::GetInst().Find("Zombie_Walk.png");
	Zombie_Walk->Cut(12, 8);

	// ���ݻ���(Zombie_Attack.png, 16x8)
	GameEngineTexture* Zombie_Attack = GameEngineTextureManager::GetInst().Find("Zombie_Attack.png");
	Zombie_Attack->Cut(16, 8);

	// �ǰݻ���(Zombie_GetHit.png, 5x8)
	GameEngineTexture* Zombie_GetHit = GameEngineTextureManager::GetInst().Find("Zombie_GetHit.png");
	Zombie_GetHit->Cut(5, 8);

	// �������(Zombie_Death.png, 19x8)
	GameEngineTexture* Zombie_Death = GameEngineTextureManager::GetInst().Find("Zombie_Death.png");
	Zombie_Death->Cut(19, 8);

	// ��ü����(Zombie_Dead.png, 1x8)
	GameEngineTexture* Zombie_Dead = GameEngineTextureManager::GetInst().Find("Zombie_Dead.png");
	Zombie_Dead->Cut(1, 8);
}

void Zombie::CreateAnimation()
{
	Zombie_ = CreateTransformComponent<GameEngineImageRenderer>();
	Zombie_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Zombie_->SetRenderingPipeLine("TextureDepthOff");

	// ������(Zombie_Idle.png, 8x8)
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_LB", 0, 7, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_LT", 8, 15, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_RT", 16, 23, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_RB", 24, 31, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_B" , 32, 39, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_L" , 40, 47, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_T" , 48, 55, 0.1f);
	Zombie_->CreateAnimation("Zombie_Idle.png", "Idle_R" , 56, 63, 0.1f);

	// �̵�����(Zombie_Walk.png, 12x8)
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_LB",  0, 11, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_LT", 12, 23, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_RT", 24, 35, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_RB", 36, 47, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_B" , 48, 59, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_L" , 60, 71, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_T" , 72, 83, 0.1f);
	Zombie_->CreateAnimation("Zombie_Walk.png", "Walk_R" , 84, 95, 0.1f);

	// ���ݻ���(Zombie_Attack.png, 16x8)
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_LB",   0,  15, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_LT",  16,  31, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_RT",  32,  47, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_RB",  48,  63, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_B" ,  64,  79, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_L" ,  80,  95, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_T" ,  96, 111, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Attack.png", "Attack_R" , 112, 127, 0.1f, false);

	// �ǰݻ���(Zombie_GetHit.png, 5x8)
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_LB",  0,  4, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_LT",  5,  9, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_RT", 10, 14, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_RB", 15, 19, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_B" , 20, 24, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_L" , 25, 29, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_T" , 30, 34, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_GetHit.png", "GetHit_R" , 35, 39, 0.1f, false);

	// �������(Zombie_Death.png, 19x8)
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_LB",   0,  18, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_LT",  19,  37, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_RT",  38,  56, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_RB",  57,  75, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_B" ,  76,  94, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_L" ,  95, 113, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_T" , 114, 132, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Death.png", "Death_R" , 133, 151, 0.1f, false);

	// ��ü����(Zombie_Dead.png, 1x8)
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_LB", 0, 0, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_LT", 0, 1, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_RT", 0, 2, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_RB", 0, 3, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_B" , 0, 4, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_L" , 0, 5, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_T" , 0, 6, 0.1f, false);
	Zombie_->CreateAnimation("Zombie_Dead.png", "Dead_R" , 0, 7, 0.1f, false);

	// �ʱ����
	Zombie_->SetChangeAnimation("Idle_B");
}

void Zombie::CreateAnimationEndFunction()
{
	// �Ϲݰ��ݸ�� ����
	Zombie_->SetEndCallBack("Attack_LB", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_LT", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_RT", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_RB", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_B", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_L", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_T", std::bind(&Zombie::AttackEnd, this));
	Zombie_->SetEndCallBack("Attack_R", std::bind(&Zombie::AttackEnd, this));

	// �ǰݸ�� ����
	Zombie_->SetEndCallBack("GetHit_LB", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_LT", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_RT", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_RB", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_B", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_L", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_T", std::bind(&Zombie::GetHitEnd, this));
	Zombie_->SetEndCallBack("GetHit_R", std::bind(&Zombie::GetHitEnd, this));

	// ������ ����
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

	// �ʱ���� ����
	State_.ChangeState("RoomDetect");
}

void Zombie::CreateCollision()
{
	// ��ü �浹ü(�ǰ�������)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void Zombie::CreateInfomation()
{
	// �ش� ������ ������ ����
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::Zombie, MonsterInfo_);

	// ���� ü�� ����(����)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// �����差 ����
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
}
