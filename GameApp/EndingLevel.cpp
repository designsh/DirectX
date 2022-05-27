#include "PreCompile.h"
#include "EndingLevel.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

#include "GlobalValue.h"

#include "EndingBackDrop.h"
#include "EndingCredit.h"

bool EndingLevel::ResourceLoadEndCheck = false;

EndingLevel::EndingLevel() :
	BackDrop_(nullptr),
	Credit_(nullptr)
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
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void EndingLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	// ���� Up & Down Key
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

void EndingLevel::CreateLevelActor()
{
	// ���
	BackDrop_ = CreateActor<EndingBackDrop>();

	// ũ���� �ؽ�Ʈ
	//Credit_ = CreateActor<EndingCredit>();
}
