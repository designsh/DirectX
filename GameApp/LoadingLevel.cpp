#include "PreCompile.h"
#include "LoadingLevel.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "LoadingBackDrop.h"
#include "LoadingAnimation.h"

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

void LoadingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 체인지
	if (std::string::npos != _NextLevel->GetName().find("TownLevel"))
	{
		// 마을배경음으로 변경
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();
			GlobalValue::BackGroundSound->PlayAlone("TownLevel.wav", 99);
		}
	}
}

void LoadingLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
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

	// 볼륨 Up & Down Key
	if (true == GameEngineInput::GetInst().Down("VolumeUp"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeUp();
		}
	}
	if (true == GameEngineInput::GetInst().Down("VolumeDown"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeDown();
		}
	}
}
