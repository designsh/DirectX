#include "PreCompile.h"
#include "SelectCharacterLevel.h"

#include "SelectCharacterBackDrop.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

SelectCharacterLevel::SelectCharacterLevel()
{
}

SelectCharacterLevel::~SelectCharacterLevel()
{
}

void SelectCharacterLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void SelectCharacterLevel::LevelChangeStartEvent()
{
	// ������� On
}

void SelectCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	SelectCharacterBackDrop* BackDrop = CreateActor<SelectCharacterBackDrop>();

	// ���ӽ��۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�

	// ĳ���ͻ�����ư(�̹��� + �ؽ�Ʈ) -> ĳ���ͻ������� �̵�

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�

	// ������(�̹���)

	// ��ũ��(�̹���)

	// ������ĳ���Ϳ�����Ʈ(�ִϸ��̼�)

}

void SelectCharacterLevel::LevelUpdate(float _DeltaTime)
{
}
