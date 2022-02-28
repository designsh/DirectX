#include "PreCompile.h"
#include "SelectCharactorLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

SelectCharactorLevel::SelectCharactorLevel()
{
}

SelectCharactorLevel::~SelectCharactorLevel()
{
}

void SelectCharactorLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void SelectCharactorLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void SelectCharactorLevel::LevelStart()
{
	// 배경액터 생성(이미지)

	// 게임시작버튼(이미지 + 텍스트) -> 로딩레벨 이동

	// 캐릭터생성버튼(이미지 + 텍스트) -> 캐릭터생성레벨 이동

	// 이전버튼(이미지 + 텍스트) -> 타이틀레벨 이동

	// 셀렉터(이미지)

	// 스크롤(이미지)

	// 생성된캐릭터오브젝트(애니메이션)

}

void SelectCharactorLevel::LevelUpdate(float _DeltaTime)
{
}
