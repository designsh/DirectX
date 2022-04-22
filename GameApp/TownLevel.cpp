#include "PreCompile.h"
#include "TownLevel.h"

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
	// ���ҽ� �ε��Ϸ�� ���� ����

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());
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

	// NPC ����(�������) - �׽�Ʈ ��ġ
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetLocalPosition(float4(100.f, 100.f, 10.f));
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // �ӽ�
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC ����(��ȭ����) - �׽�Ʈ ��ġ
	ChandleryNPC_ = CreateActor<ChandleryNPC>();
	ChandleryNPC_->GetTransform()->SetLocalPosition(float4(-100.f, 100.f, 10.f));
	ChandleryNPC_->SetMoveRange();
	ChandleryNPC_->SetMessageBoxText("Akara Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // �ӽ�
	ChandleryNPC_->SetUIPosition();
	ChandleryNPC_->SetTopMenu();
	GlobalValue::ChandleryNPC = ChandleryNPC_;

	// â�������Ʈ


	// ....

	// ���콺
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());

	// ���θ��콺 ����
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}

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

void TownLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� Off

}

void TownLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On

}

void TownLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion
}
