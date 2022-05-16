#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

Tainted::Tainted() :
	Tainted_(nullptr),
	BodyCollider_(nullptr),
	AttackCollider_(nullptr),
	State_(),
	SkillDelayTime_(20.f)
{
}

Tainted::~Tainted()
{
}

void Tainted::Start()
{
}

void Tainted::Update(float _DeltaTime)
{
}
