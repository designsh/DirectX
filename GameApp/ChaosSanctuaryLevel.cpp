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

ChaosSanctuaryLevel::ChaosSanctuaryLevel() :
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
{
}

ChaosSanctuaryLevel::~ChaosSanctuaryLevel()
{
}

void ChaosSanctuaryLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void ChaosSanctuaryLevel::LevelChangeStartEvent()
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

void ChaosSanctuaryLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ����
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// ���� ����

	// ���콺
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("EndingLevel");
	}
}
