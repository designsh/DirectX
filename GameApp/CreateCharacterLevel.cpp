#include "PreCompile.h"
#include "CreateCharacterLevel.h"

#include "CreateCharacterBackDrop.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

CreateCharacterLevel::CreateCharacterLevel()
{
}

CreateCharacterLevel::~CreateCharacterLevel()
{
}

void CreateCharacterLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void CreateCharacterLevel::LevelChangeStartEvent()
{
	// ������� On
}

void CreateCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	CreateCharacterBackDrop* BackDrop = CreateActor<CreateCharacterBackDrop>();

	// ķ�����̾������Ʈ ����(�ִϸ��̼�)

	// ���۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�
}

void CreateCharacterLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("LoadingLevel");
	}
}

