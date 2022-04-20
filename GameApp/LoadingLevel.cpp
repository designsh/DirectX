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
	// �ε� ���
	LoadingBackDrop* BackDrop = CreateActor<LoadingBackDrop>();

	// �ε�����(�ִϸ��̼�)
	LoadingAnimation* Animation = CreateActor<LoadingAnimation>();
}

void LoadingLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void LoadingLevel::LevelChangeStartEvent()
{
	// ������� On
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
