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

	// �ε� ���
	LoadingBackDrop* BackDrop = CreateActor<LoadingBackDrop>();

	// �ε�����(�ִϸ��̼�) - �ӽ�(�׽�Ʈ��)
	LoadingAnimation* Animation = CreateActor<LoadingAnimation>();
}

void LoadingLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("TownLevel");
	}
}
