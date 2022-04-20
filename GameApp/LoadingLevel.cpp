#include "PreCompile.h"
#include "LoadingLevel.h"

#include "LoadingBackDrop.h"
#include "LoadingAnimation.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

bool LoadingLevel::ResourceLoadEndCheck = false;

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::CreateLevelActor()
{
	// 로딩 배경
	LoadingBackDrop* BackDrop = CreateActor<LoadingBackDrop>();

	// 로딩액터(애니메이션)
	LoadingAnimation* Animation = CreateActor<LoadingAnimation>();
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
}

void LoadingLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion
}
