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

void TownLevel::LevelChangeEndEvent()
{
	// ������� Off

}

void TownLevel::LevelChangeStartEvent()
{
	// ������� On


	// �����÷��̾� ����
	GlobalValue::CurPlayer = MainPlayer_;

	// ���θ��콺 ����
	GlobalValue::CurMouse = MainMouse_;

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

void TownLevel::LevelStart()
{
	// ============================================== �׽�Ʈ�� ============================================== //
	//MainPlayerInfomation::GetInst().CreateMainPlayerInfo("test1", JobType::Necromancer);
	//if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	//{
	//	if (nullptr != GlobalValue::CurPlayer)
	//	{
	//		GlobalValue::CurPlayer->CreatePlayerUIInfomation();
	//	}
	//}
	// ============================================== �׽�Ʈ�� ============================================== //

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ����
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// NPC ����(�������) - �׽�Ʈ ��ġ
	WeaponNPC_ = CreateActor<WeaponNPC>();
	WeaponNPC_->GetTransform()->SetLocalPosition(float4(100.f, 100.f, 10.f));
	WeaponNPC_->SetMoveRange();
	WeaponNPC_->SetMessageBoxText("Charsi Testing is currently underway!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); // �ӽ�
	WeaponNPC_->SetUIPosition();
	WeaponNPC_->SetTopMenu();
	GlobalValue::WeaponNPC = WeaponNPC_;

	// NPC ����(��ȭ����)
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

#pragma region �׽�ƮŰ
	// �׽�ƮŰ ����
	if (false == GameEngineInput::GetInst().IsKey("FreeCamera"))
	{
		GameEngineInput::GetInst().CreateKey("FreeCamera", 'o');
	}
#pragma endregion
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
#pragma region �׽�ƮŰ
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CatacombsLevel");
	}

	if (true == GameEngineInput::GetInst().Down("FreeCamera"))
	{
		GetMainCameraActor()->FreeCameraModeSwitch();
	}
#pragma endregion
}
