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
	// 해당 이펙트관련 초기화
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
	// 카메라 쉐이킹효과 발생
	CamShakeStart_ = true;

	// 보스사망본체 불꽃 발생
	CreateAnimation();
}

void AndarielDeathEffect::NormalDeathFire1()
{
	// 애니메이션 변경
	DeathFire_->SetChangeAnimation("Fire2");
}

void AndarielDeathEffect::NormalDeathFire2()
{
	// 4방향 이동 불꽃 생성 후 자동 이동처리 시작



	DeathFire_->SetChangeAnimation("Fire3");
}

void AndarielDeathEffect::NormalDeathFire3()
{
	// 해당 애니메이션 종료시 카메라 쉐이킹 효과를 중단하며
	CamShakeStart_ = false;

	// 보스는 실질적으로 사망처리하면서 해당 자리에 포탈생성
	if (nullptr != GlobalValue::Andariel)
	{
		GlobalValue::Andariel->PortalSpawnAfterDeath();
	}

	// 사망처리
	Death();
}

void AndarielDeathEffect::DirDeathFireFrameCallback()
{
	// 이동후 새로운 불꽃 발생

}

void AndarielDeathEffect::CamShakeEffect()
{
	// 카메라 흔들림
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
		// 원래자리 복귀
		GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_);
		Shake_ = false;
	}
}
