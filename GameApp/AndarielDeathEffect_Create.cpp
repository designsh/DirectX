#include "PreCompile.h"
#include "AndarielDeathEffect.h"

#include <GameEngine/GameEngineImageRenderer.h>

void AndarielDeathEffect::InitDeathEffect()
{
	// ���� �ؽ��� ����
	TextureCutting();
}

void AndarielDeathEffect::TextureCutting()
{
	// �̵�������� �Ҳ�(20x1)
	GameEngineTexture* DeathFire1 = GameEngineTextureManager::GetInst().Find("DeathFire1.png");
	DeathFire1->Cut(20, 1);
	GameEngineTexture* DeathFire2 = GameEngineTextureManager::GetInst().Find("DeathFire2.png");
	DeathFire2->Cut(20, 1);
	GameEngineTexture* DeathFire3 = GameEngineTextureManager::GetInst().Find("DeathFire3.png");
	DeathFire3->Cut(20, 1);
	//GameEngineTexture* DeathFire1 = GameEngineTextureManager::GetInst().Find("DeathFire1.png");
	//DeathFire1->Cut(37, 1);
	//GameEngineTexture* DeathFire2 = GameEngineTextureManager::GetInst().Find("DeathFire2.png");
	//DeathFire2->Cut(37, 1);
	//GameEngineTexture* DeathFire3 = GameEngineTextureManager::GetInst().Find("DeathFire3.png");
	//DeathFire3->Cut(37, 1);

	// �̵������� �����ϴ� �Ҳ�(20x1)
	GameEngineTexture* DeathFireDir = GameEngineTextureManager::GetInst().Find("DeathFireDir.png");
	DeathFireDir->Cut(20, 1);
}

void AndarielDeathEffect::CreateAnimation()
{
	DeathFire_ = CreateTransformComponent<GameEngineImageRenderer>();
	DeathFire_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	DeathFire_->SetRenderingPipeLine("TextureTrans");

	DeathFire_->CreateAnimation("DeathFire1.png", "Fire1", 0, 19, 0.2f, false);
	DeathFire_->CreateAnimation("DeathFire2.png", "Fire2", 0, 19, 0.2f, false);
	DeathFire_->CreateAnimation("DeathFire3.png", "Fire3", 0, 19, 0.2f, false);
	//DeathFire_->CreateAnimation("DeathFire1.png", "Fire1", 0, 36, 0.1f, false);
	//DeathFire_->CreateAnimation("DeathFire2.png", "Fire2", 0, 36, 0.1f, false);
	//DeathFire_->CreateAnimation("DeathFire3.png", "Fire3", 0, 36, 0.1f, false);
	DeathFire_->SetChangeAnimation("Fire1");

	// ����� ȣ���Լ� ���
	DeathFire_->SetEndCallBack("Fire1", std::bind(&AndarielDeathEffect::NormalDeathFire1, this));
	DeathFire_->SetEndCallBack("Fire2", std::bind(&AndarielDeathEffect::NormalDeathFire2, this));
	DeathFire_->SetEndCallBack("Fire3", std::bind(&AndarielDeathEffect::NormalDeathFire3, this));
}
