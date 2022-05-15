#include "PreCompile.h"
#include "CatacombsLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayerInfomation.h"

#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

bool CatacombsLevel::ResourceLoadEndCheck = false;

CatacombsLevel::CatacombsLevel() :
	CatacombsMap_(nullptr),
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
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
	GlobalValue::CatacombsMap = CatacombsMap_;

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

	// 몬스터 생성

	// 마우스
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}
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
}
