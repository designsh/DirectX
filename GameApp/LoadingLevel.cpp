#include "PreCompile.h"
#include "LoadingLevel.h"

#include "LoadingBackDrop.h"
#include "LoadingAnimation.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

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
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 로딩 배경
	LoadingBackDrop* BackDrop = CreateActor<LoadingBackDrop>();

	// 로딩액터(애니메이션) - 임시(테스트용)
	LoadingAnimation* Animation = CreateActor<LoadingAnimation>();
}

void LoadingLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("TownLevel");
	}
}
