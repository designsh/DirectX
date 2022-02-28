#include "PreCompile.h"
#include "CreateCharactorLevel.h"

#include "CreateCharactorBackDrop.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

CreateCharactorLevel::CreateCharactorLevel()
{
}

CreateCharactorLevel::~CreateCharactorLevel()
{
}

void CreateCharactorLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void CreateCharactorLevel::LevelChangeStartEvent()
{
	// ������� On
}

void CreateCharactorLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	CreateCharactorBackDrop* BackDrop = CreateActor<CreateCharactorBackDrop>();

	// ķ�����̾������Ʈ ����(�ִϸ��̼�)

	// ���۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�
}

void CreateCharactorLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("LoadingLevel");
	}
}

