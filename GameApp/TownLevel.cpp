#include "PreCompile.h"
#include "TownLevel.h"

#include "TownMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"

bool TownLevel::ResourceLoadEndCheck = false;

TownLevel::TownLevel() :
	TownMap_(nullptr),
	MainPlayer_(nullptr),
	MainMouse_(nullptr),
	WeaponNPC_(nullptr),
	ChandleryNPC_(nullptr)
{
}

TownLevel::~TownLevel()
{
}

void TownLevel::CreateLevelActor()
{
	// 리소스 로딩완료시 액터 생성

	// 맵로딩(타일맵 - 고정맵)
	TownMap_ = CreateActor<TownMap>();
	TownMap_->TownLevel_FixedMapLoad();

	// 플레이어 생성 및 메인플레이어 지정
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());
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

	// NPC 생성(무기상인) - 테스트 위치
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetLocalPosition(float4(100.f, 100.f, 10.f));
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // 임시
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC 생성(잡화상인) - 테스트 위치
	ChandleryNPC_ = CreateActor<ChandleryNPC>();
	ChandleryNPC_->GetTransform()->SetLocalPosition(float4(-100.f, 100.f, 10.f));
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // 임시
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// 창고오브젝트


	// ....

	// 마우스
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());

	// 메인마우스 지정
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}
}

void TownLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 배경음악 Off

}

void TownLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// 배경음악 On

}

void TownLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));

#pragma region 맵테스트용
	//if (false == GameEngineInput::GetInst().IsKey("MAPUP"))
	//{
	//	GameEngineInput::GetInst().CreateKey("MAPUP", VK_UP);
	//}

	//if (false == GameEngineInput::GetInst().IsKey("MAPDOWN"))
	//{
	//	GameEngineInput::GetInst().CreateKey("MAPDOWN", VK_DOWN);
	//}

	//if (false == GameEngineInput::GetInst().IsKey("MAPLEFT"))
	//{
	//	GameEngineInput::GetInst().CreateKey("MAPLEFT", VK_LEFT);
	//}

	//if (false == GameEngineInput::GetInst().IsKey("MAPRIGHT"))
	//{
	//	GameEngineInput::GetInst().CreateKey("MAPRIGHT", VK_RIGHT);
	//}
#pragma endregion
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

#pragma region 테스트키
	//if (true == GameEngineInput::GetInst().Press("MAPUP"))
	//{
	//	GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldUpVector() * _DeltaTime * 200.f);
	//}

	//if (true == GameEngineInput::GetInst().Press("MAPDOWN"))
	//{
	//	GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldDownVector() * _DeltaTime * 200.f);

	//}

	//if (true == GameEngineInput::GetInst().Press("MAPLEFT"))
	//{
	//	GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldLeftVector() * _DeltaTime * 200.f);
	//}

	//if (true == GameEngineInput::GetInst().Press("MAPRIGHT"))
	//{
	//	GetMainCameraActor()->GetTransform()->SetWorldMove(GetMainCameraActor()->GetTransform()->GetWorldRightVector() * _DeltaTime * 200.f);
	//}
#pragma endregion
}
