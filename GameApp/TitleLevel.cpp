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

TitleLevel::TitleLevel() :
	StartButton_(nullptr),
	EndButton_(nullptr)
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
	// 레벨변경시 기존액터들의 필요항목 리셋
	StartButton_->ChangeStartReset();
	EndButton_->ChangeStartReset();

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
	StartButton_ = CreateActor<GameStartButton>();

	// 게임종료 버튼 생성(이미지+텍스트)
	EndButton_ = CreateActor<GameEndButton>();

	// 현재 마우스 생성
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
	GlobalValue::CurMouse = MainMouse;
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
}

