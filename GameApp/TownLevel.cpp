#include "PreCompile.h"
#include "TownLevel.h"

#include "UserGame.h"

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
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// �����÷��̾� ����
	GlobalValue::CurPlayer = MainPlayer_;

	// NPC ����(�������)

	// NPC ����(��ȭ����)

	// â�������Ʈ(�̹���)

	// ....

	//=========================== Ű���� ===========================//

	// ���콺 ���ʹ�ư
	if (false == GameEngineInput::GetInst().IsKey("MouseLButton"))
	{
		GameEngineInput::GetInst().CreateKey("MouseLButton", VK_LBUTTON);
	}

	// ����Ű(Ư�� UIȰ��ȭ���� Űüũ)
	if (false == GameEngineInput::GetInst().IsKey("UP"))
	{
		GameEngineInput::GetInst().CreateKey("UP", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DOWN"))
	{
		GameEngineInput::GetInst().CreateKey("DOWN", VK_DOWN);
	}
}

void TownLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CatacombsLevel");
	}
}
