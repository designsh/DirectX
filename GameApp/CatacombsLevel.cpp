#include "PreCompile.h"
#include "CatacombsLevel.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

#include "GlobalValue.h"
#include "MainPlayerInfomation.h"

#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"
#include "MonsterTopHPBar.h"
#include "SummonsEmblem.h"

bool CatacombsLevel::ResourceLoadEndCheck = false;

CatacombsLevel::CatacombsLevel() :
	CatacombsMap_(nullptr),
	MainPlayer_(nullptr),
	MainMouse_(nullptr),
	TopHPBar_(nullptr),
	SummonsEmblem_(nullptr)
{
}

CatacombsLevel::~CatacombsLevel()
{
}

void CatacombsLevel::CreateLevelActor()
{
	// 맵로딩(타일맵 - 랜덤맵)
	CatacombsMap_ = CreateActor<CatacombsMap>();
	CatacombsMap_->CatacombsMapLoad();

	// 플레이어 생성 및 메인플레이어 지정
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(MainPlayer_->GetTransform()->GetLocalPosition().x, MainPlayer_->GetTransform()->GetLocalPosition().y));
		GlobalValue::CurPlayer = MainPlayer_;

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

	// 마우스
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}

	// 상단 UI 생성(상단 HPBar)
	TopHPBar_ = CreateActor<MonsterTopHPBar>();
	GlobalValue::TopHPBar = TopHPBar_;

	// 좌상단 플레이어 소환수 엠블럼
	SummonsEmblem_ = CreateActor<SummonsEmblem>();
	GlobalValue::Emblem = SummonsEmblem_;
}

void CatacombsLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 Off
}

void CatacombsLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 배경음악 On

	// 메인플레이어의 마을진입 Flag Off
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->SetIsTown(false);
		GlobalValue::CurPlayer->GetTransform()->SetWorldPosition(float4(0.f, 0.f));
		GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(GlobalValue::CurPlayer->GetTransform()->GetLocalPosition().x, GlobalValue::CurPlayer->GetTransform()->GetLocalPosition().y));
	}
}

void CatacombsLevel::LevelStart()
{	
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -300.0f));

	// 프리카메라
	if (false == GameEngineInput::GetInst().IsKey("FREECAMERA"))
	{
		GameEngineInput::GetInst().CreateKey("FREECAMERA", 'L');
	}
}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineInput::GetInst().Down("FREECAMERA"))
	{
		// 프리 카메라 모드 실행
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	// 볼륨 Up & Down Key
	if (true == GameEngineInput::GetInst().Down("VolumeUp"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeUp();
		}
	}
	if (true == GameEngineInput::GetInst().Down("VolumeDown"))
	{
		if (nullptr != GlobalValue::BackGroundSound)
		{
			GlobalValue::BackGroundSound->VolumeDown();
		}
	}
}
