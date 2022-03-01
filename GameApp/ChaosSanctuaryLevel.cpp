#include "PreCompile.h"
#include "ChaosSanctuaryLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

ChaosSanctuaryLevel::ChaosSanctuaryLevel() :
	MainPlayer_(nullptr)
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
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("EndingLevel");
	}
}
