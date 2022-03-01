#include "PreCompile.h"
#include "CatacombsLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

CatacombsLevel::CatacombsLevel() :
	MainPlayer_(nullptr)
{
}

CatacombsLevel::~CatacombsLevel()
{
}

void CatacombsLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void CatacombsLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void CatacombsLevel::LevelStart()
{	
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 맵로딩(타일맵 - 랜덤맵)

	// 플레이어 생성
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// 메인플레이어 지정
	GlobalValue::CurPlayer = MainPlayer_;

	// 몬스터 생성

}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("ChaosSanctuaryLevel");
	}
}
