#include "PreCompile.h"
#include "ChaosSanctuaryLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayerInfomation.h"
#include "MainPlayer.h"
#include "MouseObject.h"

bool ChaosSanctuaryLevel::ResourceLoadEndCheck = false;

ChaosSanctuaryLevel::ChaosSanctuaryLevel() :
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
{
}

ChaosSanctuaryLevel::~ChaosSanctuaryLevel()
{
}

void ChaosSanctuaryLevel::CreateLevelActor()
{
	// 맵로딩(타일맵 - 랜덤맵)

	// 플레이어 생성 및 메인플레이어 지정
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());
		GlobalValue::CurPlayer = MainPlayer_;
	}

	// 몬스터 생성

	// 마우스
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());

	// 메인마우스 지정
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}

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

void ChaosSanctuaryLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 Off
}

void ChaosSanctuaryLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 배경음악 On

	// 메인플레이어 지정
	if (GlobalValue::CurPlayer != MainPlayer_)
	{
		GlobalValue::CurPlayer = MainPlayer_;
	}

	// 메인마우스 지정
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}

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

void ChaosSanctuaryLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion
}
