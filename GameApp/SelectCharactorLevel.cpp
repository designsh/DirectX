#include "PreCompile.h"
#include "SelectCharactorLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

SelectCharactorLevel::SelectCharactorLevel()
{
}

SelectCharactorLevel::~SelectCharactorLevel()
{
}

void SelectCharactorLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void SelectCharactorLevel::LevelChangeStartEvent()
{
	// ������� On
}

void SelectCharactorLevel::LevelStart()
{
	// ������ ����(�̹���)

	// ���ӽ��۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�

	// ĳ���ͻ�����ư(�̹��� + �ؽ�Ʈ) -> ĳ���ͻ������� �̵�

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�

	// ������(�̹���)

	// ��ũ��(�̹���)

	// ������ĳ���Ϳ�����Ʈ(�ִϸ��̼�)

}

void SelectCharactorLevel::LevelUpdate(float _DeltaTime)
{
}
