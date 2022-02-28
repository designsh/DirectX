#include "PreCompile.h"
#include "LoadingLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void LoadingLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void LoadingLevel::LevelStart()
{
	// 로딩액터(애니메이션)

}

void LoadingLevel::LevelUpdate(float _DeltaTime)
{
}
