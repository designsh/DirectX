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
	MainPlayerInfomation::GetInst().CreateMainPlayerInfo("test1", JobType::Necromancer);
	if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			GlobalValue::CurPlayer->CreatePlayerUIInfomation();
		}
	}
	// ============================================== �׽�Ʈ�� ============================================== //

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ����
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// NPC ����(�������)

	// NPC ����(��ȭ����)

	// â�������Ʈ(�̹���)

	// ....

	// ���콺
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CatacombsLevel");
	}
}
