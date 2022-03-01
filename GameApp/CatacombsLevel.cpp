#include "PreCompile.h"
#include "CatacombsLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayer.h"

CatacombsLevel::CatacombsLevel() :
	MainPlayer_(nullptr)
{
}

CatacombsLevel::~CatacombsLevel()
{
}

void CatacombsLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void CatacombsLevel::LevelChangeStartEvent()
{
	// ������� On
}

void CatacombsLevel::LevelStart()
{	
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ����
	MainPlayer_ = CreateActor<MainPlayer>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());

	// �����÷��̾� ����
	GlobalValue::CurPlayer = MainPlayer_;

	// ���� ����

}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("ChaosSanctuaryLevel");
	}
}
