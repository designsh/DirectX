#include "PreCompile.h"
#include "EndingLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 Off
}

void EndingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 배경음악 On
}

void EndingLevel::LevelStart()
{
	// 배경

	// Fade In/Out Image

	// 텍스트

}

void EndingLevel::LevelUpdate(float _DeltaTime)
{
}
