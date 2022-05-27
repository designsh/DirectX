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
	// 배경액터 생성(이미지)
	TitleBackDrop* BackDrop = CreateActor<TitleBackDrop>();

	// 로고액터 생성(애니메이션)
	TitleLogo* Logo = CreateActor<TitleLogo>();

	// 게임시작 버튼 생성(이미지+텍스트)
	StartButton_ = CreateActor<GameStartButton>();

	// 게임종료 버튼 생성(이미지+텍스트)
	EndButton_ = CreateActor<GameEndButton>();

	// 현재 마우스 생성
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void TitleLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 맵에디터 레벨로 전환시 배경음악 정지
	if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->Stop();

			// 글로벌 저장 취소
			GlobalValue::BackGroundSound = nullptr;
		}
	}
}

void TitleLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 레벨변경시 기존액터들의 필요항목 리셋
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

