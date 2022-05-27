#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleBackDrop.h"
#include "TitleLogo.h"
#include "GameStartButton.h"
#include "GameEndButton.h"
#include "MouseObject.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

bool TitleLevel::ResourceLoadEndCheck = false;

TitleLevel::TitleLevel() :
	StartButton_(nullptr),
	EndButton_(nullptr)
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::CreateLevelActor()
{
	// ������ ����(�̹���)
	TitleBackDrop* BackDrop = CreateActor<TitleBackDrop>();

	// �ΰ���� ����(�ִϸ��̼�)
	TitleLogo* Logo = CreateActor<TitleLogo>();

	// ���ӽ��� ��ư ����(�̹���+�ؽ�Ʈ)
	StartButton_ = CreateActor<GameStartButton>();

	// �������� ��ư ����(�̹���+�ؽ�Ʈ)
	EndButton_ = CreateActor<GameEndButton>();

	// ���� ���콺 ����
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void TitleLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// �ʿ����� ������ ��ȯ�� ������� ����
	if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();

			// �۷ι� ���� ���
			GlobalValue::BackGroundSound = nullptr;
		}
	}
}

void TitleLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ��������� �������͵��� �ʿ��׸� ����
	if (nullptr != StartButton_)
	{
		StartButton_->ChangeStartReset();
	}

	if (nullptr != EndButton_)
	{
		EndButton_->ChangeStartReset();
	}

	if (nullptr == GlobalValue::BackGroundSound)
	{
		GameEngineSoundPlayer* MainSound = GameEngineSoundManager::GetInst().CreateSoundPlayer();
		MainSound->PlayAlone("Main_BackgroundSound.wav", 99);
		GlobalValue::BackGroundSound = MainSound;
	}
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void TitleLevel::LevelUpdate(float _DeltaTime)
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

