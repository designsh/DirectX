#include "PreCompile.h"
#include "CreateCharactorLevel.h"

#include "CreateCharactorBackDrop.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

CreateCharactorLevel::CreateCharactorLevel()
{
}

CreateCharactorLevel::~CreateCharactorLevel()
{
}

void CreateCharactorLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void CreateCharactorLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void CreateCharactorLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 배경액터 생성(이미지)
	CreateCharactorBackDrop* BackDrop = CreateActor<CreateCharactorBackDrop>();

	// 캠프파이어오브젝트 생성(애니메이션)

	// 시작버튼(이미지 + 텍스트) -> 로딩레벨 이동

	// 이전버튼(이미지 + 텍스트) -> 타이틀레벨 이동
}

void CreateCharactorLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("LoadingLevel");
	}
}

