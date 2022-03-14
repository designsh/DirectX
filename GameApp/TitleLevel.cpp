#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleBackDrop.h"
#include "TitleLogo.h"
#include "GameStartButton.h"
#include "GameEndButton.h"
#include "MouseObject.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelChangeEndEvent()
{
}

void TitleLevel::LevelChangeStartEvent()
{
	// 레벨 첫 시작시 배경음악 재생
	
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 배경액터 생성(이미지)
	TitleBackDrop* BackDrop = CreateActor<TitleBackDrop>();

	// 로고액터 생성(애니메이션)
	TitleLogo* Logo = CreateActor<TitleLogo>();

	// 게임시작 버튼 생성(이미지+텍스트)
	GameStartButton* StartButton = CreateActor<GameStartButton>();

	// 게임종료 버튼 생성(이미지+텍스트)
	GameEndButton* EndButton = CreateActor<GameEndButton>();

	// 현재 마우스 생성 - 이미지 편집 후 생성예정(집에가서해야지)
	//MouseObject* MainMouse = CreateActor<MouseObject>();
	//GlobalValue::CurMouse = MainMouse;
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CreateCharacterLevel");
	}
}

