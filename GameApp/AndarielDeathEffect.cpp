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
	// �ش� ����Ʈ���� �ʱ�ȭ
	InitDeathEffect();
}

void AndarielDeathEffect::Update(float _DeltaTime)
{
}
