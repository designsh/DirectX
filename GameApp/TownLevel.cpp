#include "PreCompile.h"
#include "TownLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

TownLevel::TownLevel() :
	MainPlayer_(nullptr)
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
}

void TownLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ����
	MainPlayer_ = CreateActor<MainPlayer>();

	// �����÷��̾� ����
	GlobalValue::CurPlayer = MainPlayer_;

	// NPC ����(�������)

	// NPC ����(��ȭ����)

	// â�������Ʈ(�̹���)

	// ....
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
}
