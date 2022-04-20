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
	// ������� Off
}

void EndingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On
}

void EndingLevel::LevelStart()
{
	// ���

	// Fade In/Out Image

	// �ؽ�Ʈ

}

void EndingLevel::LevelUpdate(float _DeltaTime)
{
}
