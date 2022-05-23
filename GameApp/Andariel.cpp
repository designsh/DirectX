#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "MainPlayer.h"
#include "CatacombsMap.h"

int Andariel::AndarielCnt = 0;

Andariel::Andariel() :
	Andariel_(nullptr),
	BodyCollider_(nullptr),
	SpawnRoomNo_(-1),
	SpawnTile_(),
	IdleDelayTime_(1.f),
	NavigationIndex_(-1),
	State_(),
	PrevState_(Andariel_FSMState::AD_ROOMDETECT),
	CurState_(Andariel_FSMState::AD_ROOMDETECT)
{
	NavigationIndex_ = AndarielCnt;
	++AndarielCnt;
}

Andariel::~Andariel()
{
}

void Andariel::Start()
{
	// 해당 몬스터관련 초기화
	InitAndariel();
}

void Andariel::Update(float _DeltaTime)
{

}
