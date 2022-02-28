#include "PreCompile.h"
#include "TownLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

TownLevel::TownLevel()
{
}

TownLevel::~TownLevel()
{
}

void TownLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void TownLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void TownLevel::LevelStart()
{
	// 맵로딩(타일맵 - 마름모)

	// 플레이어 생성

	// NPC 생성(무기상인)

	// NPC 생성(잡화상인)

	// 창고오브젝트(이미지)

	// ....
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
}
