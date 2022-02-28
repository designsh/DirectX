#include "PreCompile.h"
#include "CatacombsLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

CatacombsLevel::CatacombsLevel()
{
}

CatacombsLevel::~CatacombsLevel()
{
}

void CatacombsLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void CatacombsLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void CatacombsLevel::LevelStart()
{	
	// 맵로딩(타일맵 - 랜덤맵)

	// 플레이어 생성

	// 몬스터 생성

}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
{
}
