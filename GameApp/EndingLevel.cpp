#include "PreCompile.h"
#include "EndingLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

EndingLevel::EndingLevel() :
	MainPlayer_(nullptr)
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void EndingLevel::LevelChangeStartEvent()
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
