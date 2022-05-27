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
	// �ʷε�(Ÿ�ϸ� - ������)
	CatacombsMap_ = CreateActor<CatacombsMap>();
	CatacombsMap_->CatacombsMapLoad();

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(MainPlayer_->GetTransform()->GetLocalPosition().x, MainPlayer_->GetTransform()->GetLocalPosition().y));
		GlobalValue::CurPlayer = MainPlayer_;

		// �����÷��̾� ���� �����Ǿ����� üũ
		if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
		{
			// ���� ������ �Ǿ��ٸ� �÷��̾��� UI�� �ʿ��� ���� ����
			if (nullptr != GlobalValue::CurPlayer)
			{
				GlobalValue::CurPlayer->CreatePlayerUIInfomation();
			}
		}
	}

	// ���콺
	if (nullptr == GlobalValue::CurMouse)
	{
		MainMouse_ = CreateActor<MouseObject>();
		MainMouse_->GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
		GlobalValue::CurMouse = MainMouse_;
	}

	// ��� UI ����(��� HPBar)
	TopHPBar_ = CreateActor<MonsterTopHPBar>();
	GlobalValue::TopHPBar = TopHPBar_;

	// �»�� �÷��̾� ��ȯ�� ����
	SummonsEmblem_ = CreateActor<SummonsEmblem>();
	GlobalValue::Emblem = SummonsEmblem_;
}

void CatacombsLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� Off
}

void CatacombsLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On

	// �����÷��̾��� �������� Flag Off
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

	// ����ī�޶�
	if (false == GameEngineInput::GetInst().IsKey("FREECAMERA"))
	{
		GameEngineInput::GetInst().CreateKey("FREECAMERA", 'L');
	}
}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineInput::GetInst().Down("FREECAMERA"))
	{
		// ���� ī�޶� ��� ����
		GetMainCameraActor()->FreeCameraModeSwitch();
	}

	// ���� Up & Down Key
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
