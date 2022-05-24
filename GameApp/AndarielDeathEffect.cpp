#include "PreCompile.h"
#include "AndarielDeathEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "Andariel.h"

AndarielDeathEffect::AndarielDeathEffect() :
	DeathFire_(nullptr),
	CamShakeStart_(false),
	Shake_(false),
	ShakeDelayTime_(0.001f),
	InitCamPos_(float4::ZERO),
	DirFireCnt{0,}
{
}

AndarielDeathEffect::~AndarielDeathEffect()
{
}

void AndarielDeathEffect::Start()
{
	// �ش� ����Ʈ���� �ʱ�ȭ
	InitDeathEffect();

	InitCamPos_ = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
}

void AndarielDeathEffect::Update(float _DeltaTime)
{
	if (true == CamShakeStart_)
	{
		ShakeDelayTime_ -= _DeltaTime;
		if (0.f >= ShakeDelayTime_)
		{
			CamShakeEffect();
			ShakeDelayTime_ = 0.001f;
		}
	}
}

void AndarielDeathEffect::CreateDeathFire()
{
	// ī�޶� ����ŷȿ�� �߻�
	CamShakeStart_ = true;

	// ���������ü �Ҳ� �߻�
	CreateAnimation();
}

void AndarielDeathEffect::NormalDeathFire1()
{
	// �ִϸ��̼� ����
	DeathFire_->SetChangeAnimation("Fire2");
}

void AndarielDeathEffect::NormalDeathFire2()
{
	// 4���� �̵� �Ҳ� ���� �� �ڵ� �̵�ó�� ����



	DeathFire_->SetChangeAnimation("Fire3");
}

void AndarielDeathEffect::NormalDeathFire3()
{
	// �ش� �ִϸ��̼� ����� ī�޶� ����ŷ ȿ���� �ߴ��ϸ�
	CamShakeStart_ = false;

	// ������ ���������� ���ó���ϸ鼭 �ش� �ڸ��� ��Ż����
	if (nullptr != GlobalValue::Andariel)
	{
		GlobalValue::Andariel->PortalSpawnAfterDeath();
	}

	// ���ó��
	Death();
}

void AndarielDeathEffect::DirDeathFireFrameCallback()
{
	// �̵��� ���ο� �Ҳ� �߻�

}

void AndarielDeathEffect::CamShakeEffect()
{
	// ī�޶� ��鸲
	if (false == Shake_)
	{
		GameEngineRandom ShakeRandom;
		CamShakeDir Dir = static_cast<CamShakeDir>(ShakeRandom.RandomInt(0, 7));
		switch (Dir)
		{
		case CamShakeDir::CS_B:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(0.f, -10.f));
			break;
		case CamShakeDir::CS_LB:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, -10.f));
			break;
		case CamShakeDir::CS_L:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, 0.f));
			break;
		case CamShakeDir::CS_LT:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, 10.f));
			break;
		case CamShakeDir::CS_T:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(0.f, 10.f));
			break;
		case CamShakeDir::CS_RT:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, 10.f));
			break;
		case CamShakeDir::CS_R:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, 0.f));
			break;
		case CamShakeDir::CS_RB:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, -10.f));
			break;
		}
		Shake_ = true;
	}
	else
	{
		// �����ڸ� ����
		GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_);
		Shake_ = false;
	}
}
