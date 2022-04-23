#include "PreCompile.h"
#include "TownMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

TownMap::TownMap() :
	MapType_(MapType::FIXED)
{
}

TownMap::~TownMap()
{
}

void TownMap::Start()
{
}

void TownMap::Update(float _DeltaTime)
{
}

bool TownMap::TownLevel_FixedMapLoad()
{
	return false;
}
