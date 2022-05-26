#include "PreCompile.h"
#include "SpikeFiend.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void SpikeFiend::InitSpikeFiend()
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

void SpikeFiend::TextureCutting()
{
	// ������(SpikeFiend_Idle.png, 8x8)
	GameEngineTexture* SpikeFiend_Idle = GameEngineTextureManager::GetInst().Find("SpikeFiend_Idle.png");
	SpikeFiend_Idle->Cut(8, 8);

	// �̵�����(SpikeFiend_Walk.png, 9x8)
	GameEngineTexture* SpikeFiend_Walk = GameEngineTextureManager::GetInst().Find("SpikeFiend_Walk.png");
	SpikeFiend_Walk->Cut(9, 8);

	// ���ݻ���(SpikeFiend_Attack.png, 16x8)
	GameEngineTexture* SpikeFiend_Attack = GameEngineTextureManager::GetInst().Find("SpikeFiend_Attack.png");
	SpikeFiend_Attack->Cut(16, 8);

	// �ǰݻ���(SpikeFiend_GetHit.png, 6x8)
	GameEngineTexture* SpikeFiend_GetHit = GameEngineTextureManager::GetInst().Find("SpikeFiend_GetHit.png");
	SpikeFiend_GetHit->Cut(6, 8);

	// �������(SpikeFiend_Death.png, 14x8)
	GameEngineTexture* SpikeFiend_Death = GameEngineTextureManager::GetInst().Find("SpikeFiend_Death.png");
	SpikeFiend_Death->Cut(14, 8);

	// ��ü����(SpikeFiend_Dead.png, 8x1)
	GameEngineTexture* SpikeFiend_Dead = GameEngineTextureManager::GetInst().Find("SpikeFiend_Dead.png");
	SpikeFiend_Dead->Cut(8, 1);
}

void SpikeFiend::CreateAnimation()
{
	SpikeFiend_ = CreateTransformComponent<GameEngineImageRenderer>();
	SpikeFiend_->GetTransform()->SetLocalScaling(float4(120.f, 120.f));
	SpikeFiend_->SetRenderingPipeLine("TextureDepthOff");

	// ������(SpikeFiend_Idle.png, 8x8)
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_B" ,  0,  7, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_LB",  8, 15, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_L" , 16, 23, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_LT", 24, 31, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_T" , 32, 39, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_RT", 40, 47, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_R" , 48, 55, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Idle.png", "Idle_RB", 56, 63, 0.1f);

	// �̵�����(SpikeFiend_Walk.png, 9x8)
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_B" ,  0,  8, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_LB",  9, 17, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_L" , 18, 26, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_LT", 27, 35, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_T" , 36, 44, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_RT", 45, 53, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_R" , 54, 62, 0.1f);
	SpikeFiend_->CreateAnimation("SpikeFiend_Walk.png", "Walk_RB", 63, 71, 0.1f);

	// ���ݻ���(SpikeFiend_Attack.png, 16x8)
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_B" ,   0,  15, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_LB",  16,  31, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_L" ,  32,  47, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_LT",  48,  63, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_T" ,  64,  79, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_RT",  80,  95, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_R" ,  96, 111, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Attack.png", "Attack_RB", 112, 127, 0.1f, false);

	// �ǰݻ���(SpikeFiend_GetHit.png, 6x8)
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_B" ,  0,  5, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_LB",  6, 11, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_L" , 12, 17, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_LT", 18, 23, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_T" , 24, 29, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_RT", 30, 35, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_R" , 36, 41, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_GetHit.png", "GetHit_RB", 42, 47, 0.1f, false);

	// �������(SpikeFiend_Death.png, 14x8)
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_B" ,  0,  13, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_LB", 14,  27, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_L" , 28,  41, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_LT", 42,  55, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_T" , 56,  69, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_RT", 70,  83, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_R" , 84,  97, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Death.png", "Death_RB", 98, 111, 0.1f, false);

	// ��ü����(SpikeFiend_Dead.png, 8x1)
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_B" , 0, 0, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_LB", 1, 1, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_L" , 2, 2, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_LT", 3, 3, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_T" , 4, 4, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_RT", 5, 5, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_R" , 6, 6, 0.1f, false);
	SpikeFiend_->CreateAnimation("SpikeFiend_Dead.png", "Dead_RB", 7, 7, 0.1f, false);

	// �ʱ����
	SpikeFiend_->SetChangeAnimation("Idle_B");
}

void SpikeFiend::CreateAnimationEndFunction()
{
	// �Ϲݰ��ݸ�� ����
	SpikeFiend_->SetEndCallBack("Attack_LB", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_LT", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_RT", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_RB", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_B", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_L", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_T", std::bind(&SpikeFiend::AttackEnd, this));
	SpikeFiend_->SetEndCallBack("Attack_R", std::bind(&SpikeFiend::AttackEnd, this));

	// �ǰݸ�� ����
	SpikeFiend_->SetEndCallBack("GetHit_LB", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_LT", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_RT", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_RB", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_B", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_L", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_T", std::bind(&SpikeFiend::GetHitEnd, this));
	SpikeFiend_->SetEndCallBack("GetHit_R", std::bind(&SpikeFiend::GetHitEnd, this));

	// ������ ����
	SpikeFiend_->SetEndCallBack("Death_LB", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_LT", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_RT", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_RB", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_B", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_L", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_T", std::bind(&SpikeFiend::DeathEnd, this));
	SpikeFiend_->SetEndCallBack("Death_R", std::bind(&SpikeFiend::DeathEnd, this));
}

void SpikeFiend::CreateFSMState()
{
	State_.CreateState("RoomDetect", std::bind(&SpikeFiend::UpdateRoomDetect, this), std::bind(&SpikeFiend::StartRoomDetect, this), std::bind(&SpikeFiend::EndRoomDetect, this));
	State_.CreateState("Idle", std::bind(&SpikeFiend::UpdateIdle, this), std::bind(&SpikeFiend::StartIdle, this), std::bind(&SpikeFiend::EndIdle, this));
	State_.CreateState("Walk", std::bind(&SpikeFiend::UpdateMove, this), std::bind(&SpikeFiend::StartMove, this), std::bind(&SpikeFiend::EndMove, this));
	State_.CreateState("Attack", std::bind(&SpikeFiend::UpdateNormalAttack, this), std::bind(&SpikeFiend::StartNormalAttack, this), std::bind(&SpikeFiend::EndNormalAttack, this));
	State_.CreateState("GetHit", std::bind(&SpikeFiend::UpdateGetHit, this), std::bind(&SpikeFiend::StartGetHit, this), std::bind(&SpikeFiend::EndGetHit, this));
	State_.CreateState("Death", std::bind(&SpikeFiend::UpdateDeath, this), std::bind(&SpikeFiend::StartDeath, this), std::bind(&SpikeFiend::EndDeath, this));
	State_.CreateState("Dead", std::bind(&SpikeFiend::UpdateDead, this), std::bind(&SpikeFiend::StartDead, this), std::bind(&SpikeFiend::EndDead, this));

	// �ʱ���� ����
	State_.ChangeState("RoomDetect");
}

void SpikeFiend::CreateCollision()
{
	// ��ü �浹ü(�ǰ�������)
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Monster));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void SpikeFiend::CreateInfomation()
{
	// �ش� ������ ������ ����
	AllMonsterInfomation::GetInst().MonsterInfoFind(MonsterClassType::SpikeFiend, MonsterInfo_);

	// ���� ü�� ����(����)
	GameEngineRandom HPRandom;
	CurHP_ = HPRandom.RandomInt(MonsterInfo_.MinHP, MonsterInfo_.MaxHP);
	MapHP_ = CurHP_;

	// �����差 ����
	GameEngineRandom GoldRandom;
	DropGold_ = GoldRandom.RandomInt(MonsterInfo_.DropGoldMin, MonsterInfo_.DropGoldMax);
}
