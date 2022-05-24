#include "PreCompile.h"
#include "AndarielDeathEffect.h"

#include <GameEngine/GameEngineImageRenderer.h>

AndarielDeathEffect::AndarielDeathEffect() :
	DeathFire_(nullptr),
	FireType_(DeathFireType::NONE),
	CamShaking_(false)
{
}

AndarielDeathEffect::~AndarielDeathEffect()
{
}

void AndarielDeathEffect::Start()
{
	// 해당 이펙트관련 초기화
	InitDeathEffect();
}

void AndarielDeathEffect::Update(float _DeltaTime)
{
}
