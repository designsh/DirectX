#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "MainPlayer.h"
#include "CatacombsMap.h"

Andariel::Andariel() :
	Andariel_(nullptr),
	BodyCollider_(nullptr),
	AttackCollider_(nullptr)
{
}

Andariel::~Andariel()
{
}

void Andariel::Start()
{
	// Texture Cutting

}

void Andariel::Update(float _DeltaTime)
{
}
