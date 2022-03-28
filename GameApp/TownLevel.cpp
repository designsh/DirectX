#include "PreCompile.h"
#include "TownLevel.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"

TownLevel::TownLevel() :
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
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


	// 메인플레이어 지정
	GlobalValue::CurPlayer = MainPlayer_;

	// 메인마우스 지정
	GlobalValue::CurMouse = MainMouse_;

	// 메인플레이어 정보 생성되었는지 체크
	if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	{
		// 정보 생성이 되었다면 플레이어의 UI에 필요한 정보 셋팅
		if (nullptr != GlobalValue::CurPlayer)
		{
			GlobalValue::CurPlayer->CreatePlayerUIInfomation();
		}
	}
}

void TownLevel::LevelStart()
{
	// ============================================== 테스트용 ============================================== //
	MainPlayerInfomation::GetInst().CreateMainPlayerInfo("test1", JobType::Necromancer);
	if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			GlobalValue::CurPlayer->CreatePlayerUIInfomation();
		}
	}
	// ============================================== 테스트용 ============================================== //

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 맵로딩(타일맵 - 마름모)

	// 플레이어 생성
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// NPC 생성(무기상인)

	// NPC 생성(잡화상인)

	// 창고오브젝트(이미지)

	// ....

	// 마우스
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CatacombsLevel");
	}
}
