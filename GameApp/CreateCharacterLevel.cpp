#include "PreCompile.h"
#include "CreateCharacterLevel.h"

#include "CreateCharacterBackDrop.h"
#include "CreateCharacterFireObject.h"
#include "CurPlayerGameStartButton.h"
#include "TitleLevelMoveBtn.h"
#include "CreateCharacterInputText.h"
#include "ClassSelectObject.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

CreateCharacterLevel::CreateCharacterLevel()
{
}

CreateCharacterLevel::~CreateCharacterLevel()
{
}

void CreateCharacterLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void CreateCharacterLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void CreateCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 배경액터 생성(이미지)
	CreateCharacterBackDrop* BackDrop = CreateActor<CreateCharacterBackDrop>();

	// 캠프파이어오브젝트 생성(애니메이션)
	CreateCharacterFireObject* Fire = CreateActor<CreateCharacterFireObject>();

	// ID 입력창
	CreateCharacterInputText* IDInputTextBox = CreateActor<CreateCharacterInputText>();

	// 시작버튼(이미지 + 텍스트) -> 로딩레벨 이동
	CurPlayerGameStartButton* GameStartBtn = CreateActor<CurPlayerGameStartButton>();

	// 이전버튼(이미지 + 텍스트) -> 타이틀레벨 이동
	TitleLevelMoveBtn* PrevMenuBtn = CreateActor<TitleLevelMoveBtn>();

	// 직업선택용 애니메이션

	// 네크로맨서(임시)
	ClassSelectObject* NecromancerClass = CreateActor<ClassSelectObject>();
	NecromancerClass->CreateClassRenderer(JobType::Necromancer, float4(0.f, 0.f), float4(0.f, 0.f));

	// ...

}

void CreateCharacterLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("SelectCharacterLevel");
	}
}

