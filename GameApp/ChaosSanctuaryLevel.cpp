#include "PreCompile.h"
#include "ChaosSanctuaryLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

ChaosSanctuaryLevel::ChaosSanctuaryLevel()
{
}

ChaosSanctuaryLevel::~ChaosSanctuaryLevel()
{
}

void ChaosSanctuaryLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void ChaosSanctuaryLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void ChaosSanctuaryLevel::LevelStart()
{
	// 맵로딩(타일맵 - 랜덤맵)

	// 플레이어 생성

	// 몬스터 생성
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
{
}
