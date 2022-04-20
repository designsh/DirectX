#include "PreCompile.h"
#include "SelectCharacterLevel.h"

#include "SelectCharacterBackDrop.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

SelectCharacterLevel::SelectCharacterLevel()
{
}

SelectCharacterLevel::~SelectCharacterLevel()
{
}

void SelectCharacterLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void SelectCharacterLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void SelectCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 배경액터 생성(이미지)
	SelectCharacterBackDrop* BackDrop = CreateActor<SelectCharacterBackDrop>();

	// 게임시작버튼(이미지 + 텍스트) -> 로딩레벨 이동

	// 캐릭터생성버튼(이미지 + 텍스트) -> 캐릭터생성레벨 이동

	// 이전버튼(이미지 + 텍스트) -> 타이틀레벨 이동

	// 셀렉터(이미지)

	// 스크롤(이미지)

	// 생성된캐릭터오브젝트(애니메이션)

}

void SelectCharacterLevel::LevelUpdate(float _DeltaTime)
{
}
