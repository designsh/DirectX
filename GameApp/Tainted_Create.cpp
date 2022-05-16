#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Tainted::InitTainted()
{
	// �ִϸ��̼� ���� �ؽ��� ����
	TextureCutting();

	// �ִϸ��̼� ��������
	CreateAnimation();

	// �浹ü ����
	CreateCollision();

	// FSM ���°���
	CreateFSMState();
}

void Tainted::TextureCutting()
{
	// ������(Tainted_Idle.png)
	GameEngineTexture* Tainted_Idle = GameEngineTextureManager::GetInst().Find("Tainted_Idle.png");
	Tainted_Idle->Cut(8, 8);

	// �̵�����(Tainted_Walk.png)
	GameEngineTexture* Tainted_Walk = GameEngineTextureManager::GetInst().Find("Tainted_Walk.png");
	Tainted_Walk->Cut(8, 8);

	// �⺻���ݻ���(Tainted_NormalAttack.png)
	GameEngineTexture* Tainted_NormalAttack = GameEngineTextureManager::GetInst().Find("Tainted_NormalAttack.png");
	Tainted_NormalAttack->Cut(10, 8);

	// ��ų���ݻ���(Tainted_SpecialAttack.png)
	GameEngineTexture* Tainted_SpecialAttack = GameEngineTextureManager::GetInst().Find("Tainted_SpecialAttack.png");
	Tainted_SpecialAttack->Cut(10, 8);

	// �ǰݻ���(Tainted_GetHit.png)
	GameEngineTexture* Tainted_GetHit = GameEngineTextureManager::GetInst().Find("Tainted_GetHit.png");
	Tainted_GetHit->Cut(8, 8);

	// �������(Tainted_Death.png)
	GameEngineTexture* Tainted_Death = GameEngineTextureManager::GetInst().Find("Tainted_Death.png");
	Tainted_Death->Cut(19, 8);

	// ��ü����(Tainted_Dead.png)
	GameEngineTexture* Tainted_Dead = GameEngineTextureManager::GetInst().Find("Tainted_Dead.png");
	Tainted_Dead->Cut(8, 1);
}

void Tainted::CreateAnimation()
{
	Tainted_ = CreateTransformComponent<GameEngineImageRenderer>();
	Tainted_->GetTransform()->SetLocalScaling(float4(280.f, 280.f));

	// ������
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Idle.png", "Idle_R", 56, 63, 0.1f);

	// �̵�����
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Walk.png", "Walk_R", 56, 63, 0.1f);

	// �⺻���ݻ���
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_LB", 0, 9, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_LT", 10, 19, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_RT", 20, 29, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_RB", 30, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_B", 40, 49, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_L", 50, 59, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_T", 60, 69, 0.1f);
	Tainted_->CreateAnimation("Tainted_NormalAttack.png", "NormalAttack_R", 70, 79, 0.1f);

	// ��ų���ݻ���
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_LB", 0, 9, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_LT", 10, 19, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_RT", 20, 29, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_RB", 30, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_B", 40, 49, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_L", 50, 59, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_T", 60, 69, 0.1f);
	Tainted_->CreateAnimation("Tainted_SpecialAttack.png", "SpecialAttack_R", 70, 79, 0.1f);

	// �ǰݻ���
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_GetHit.png", "GetHit_R", 56, 63, 0.1f);

	// �������
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LB", 0, 18, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_LT", 19, 37, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RT", 38, 56, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_RB", 57, 75, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_B", 76, 94, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_L", 95, 113, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_T", 114, 132, 0.1f);
	Tainted_->CreateAnimation("Tainted_Death.png", "Death_R", 133, 151, 0.1f);

	// ��ü����
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LB", 0, 7, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_LT", 8, 15, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RT", 16, 23, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_RB", 24, 31, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_B", 32, 39, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_L", 40, 47, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_T", 48, 55, 0.1f);
	Tainted_->CreateAnimation("Tainted_Dead.png", "Dead_R", 56, 63, 0.1f);

	// �ʱ����
	Tainted_->SetChangeAnimation("Idle_B");
}

void Tainted::CreateFSMState()
{
	// ������(��Ž������)
	State_.CreateState("Tainted_IDLE", std::bind(&Tainted::UpdateIdle, this), std::bind(&Tainted::StartIdle, this), std::bind(&Tainted::EndIdle, this));

	// ����������
	State_.CreateState("Tainted_DETECT", std::bind(&Tainted::UpdateEnemyDetect, this), std::bind(&Tainted::StartEnemyDetect, this), std::bind(&Tainted::EndEnemyDetect, this));

	// �̵�����
	State_.CreateState("Tainted_MOVE", std::bind(&Tainted::UpdateMove, this), std::bind(&Tainted::StartMove, this), std::bind(&Tainted::EndMove, this));

	// �⺻���ݻ���
	State_.CreateState("Tainted_ATTACK", std::bind(&Tainted::UpdateNormalAttack, this), std::bind(&Tainted::StartNormalAttack, this), std::bind(&Tainted::EndNormalAttack, this));

	// ��ų���ݻ���
	State_.CreateState("Tainted_SKILL", std::bind(&Tainted::UpdateSpecialAttack, this), std::bind(&Tainted::StartSpecialAttack, this), std::bind(&Tainted::EndSpecialAttack, this));

	// �ǰݻ���
	State_.CreateState("Tainted_GETHIT", std::bind(&Tainted::UpdateGetHit, this), std::bind(&Tainted::StartGetHit, this), std::bind(&Tainted::EndGetHit, this));

	// �������
	State_.CreateState("Tainted_DEATH", std::bind(&Tainted::UpdateDeath, this), std::bind(&Tainted::StartDeath, this), std::bind(&Tainted::EndDeath, this));

	// ��ü����
	State_.CreateState("Tainted_DEATH", std::bind(&Tainted::UpdateDead, this), std::bind(&Tainted::StartDead, this), std::bind(&Tainted::EndDead, this));

	// �ʱ���� ����
	State_.ChangeState("Tainted_IDLE");
}

void Tainted::CreateCollision()
{
	//// ��ü �浹ü(�ǰ�������)
	//BodyCollider_ = CreateTransformComponent<GameEngineCollision>();
	//BodyCollider_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));

	//float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	//BodyCollider_->GetTransform()->SetLocalPosition(Tainted_->GetTransform()->GetLocalPosition() - CamPos);

	//BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);

	//// ���� �浹ü(����������)
	//AttackCollider_ = CreateTransformComponent<GameEngineCollision>();
	//AttackCollider_->GetTransform()->SetLocalScaling(float4(32.f, 75.f));

	//float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	//AttackCollider_->GetTransform()->SetLocalPosition(Tainted_->GetTransform()->GetLocalPosition() - CamPos);

	//AttackCollider_->GetTransform()->SetWorldZOrder(-99.f);
}
