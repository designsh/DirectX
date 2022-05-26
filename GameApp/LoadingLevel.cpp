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
	// �ε� ���
	LoadingBackDrop* BackDrop = CreateActor<LoadingBackDrop>();

	// �ε�����(�ִϸ��̼�)
	LoadingAnimation* Animation = CreateActor<LoadingAnimation>();
}

void LoadingLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� ü����
	if (std::string::npos != _NextLevel->GetName().find("TownLevel"))
	{
		// ������������� ����
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();
			GlobalValue::BackGroundSound->PlayAlone("TownLevel.wav");
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
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion
}
