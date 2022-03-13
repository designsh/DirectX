#include "PreCompile.h"
#include "CreateCharacterLevel.h"

#include "CreateCharacterBackDrop.h"
#include "CreateCharacterFireObject.h"
#include "CurPlayerGameStartButton.h"
#include "TitleLevelMoveBtn.h"
#include "CreateCharacterInputText.h"
#include "ClassSelectObject.h"

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
	CreateCharacterFireObject* Fire = CreateActor<CreateCharacterFireObject>();

	// ID �Է�â
	CreateCharacterInputText* IDInputTextBox = CreateActor<CreateCharacterInputText>();

	// ���۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�
	CurPlayerGameStartButton* GameStartBtn = CreateActor<CurPlayerGameStartButton>();

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�
	TitleLevelMoveBtn* PrevMenuBtn = CreateActor<TitleLevelMoveBtn>();

	// �������ÿ� �ִϸ��̼�

	// ��ũ�θǼ�(�ӽ�)
	ClassSelectObject* NecromancerClass = CreateActor<ClassSelectObject>();
	NecromancerClass->CreateClassRenderer(JobType::Necromancer, float4(0.f, 0.f), float4(0.f, 0.f));

	// ...

}

void CreateCharacterLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("SelectCharacterLevel");
	}
}

