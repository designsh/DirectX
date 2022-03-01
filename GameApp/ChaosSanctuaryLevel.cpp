#include "PreCompile.h"
#include "ChaosSanctuaryLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

ChaosSanctuaryLevel::ChaosSanctuaryLevel() :
	MainPlayer_(nullptr)
{
}

ChaosSanctuaryLevel::~ChaosSanctuaryLevel()
{
}

void ChaosSanctuaryLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void ChaosSanctuaryLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void ChaosSanctuaryLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 맵로딩(타일맵 - 랜덤맵)

	// 플레이어 생성
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// 몬스터 생성
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("EndingLevel");
	}
}
