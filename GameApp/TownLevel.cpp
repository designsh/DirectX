#include "PreCompile.h"
#include "TownLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

TownLevel::TownLevel() :
	MainPlayer_(nullptr)
{
}

TownLevel::~TownLevel()
{
}

void TownLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void TownLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void TownLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 맵로딩(타일맵 - 마름모)

	// 플레이어 생성
	MainPlayer_ = CreateActor<MainPlayer>();

	// 메인플레이어 지정
	GlobalValue::CurPlayer = MainPlayer_;

	// NPC 생성(무기상인)

	// NPC 생성(잡화상인)

	// 창고오브젝트(이미지)

	// ....
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
}
