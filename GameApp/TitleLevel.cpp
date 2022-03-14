#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleBackDrop.h"
#include "TitleLogo.h"
#include "GameStartButton.h"
#include "GameEndButton.h"
#include "MouseObject.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelChangeEndEvent()
{
}

void TitleLevel::LevelChangeStartEvent()
{
	// ���� ù ���۽� ������� ���
	
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	TitleBackDrop* BackDrop = CreateActor<TitleBackDrop>();

	// �ΰ���� ����(�ִϸ��̼�)
	TitleLogo* Logo = CreateActor<TitleLogo>();

	// ���ӽ��� ��ư ����(�̹���+�ؽ�Ʈ)
	GameStartButton* StartButton = CreateActor<GameStartButton>();

	// �������� ��ư ����(�̹���+�ؽ�Ʈ)
	GameEndButton* EndButton = CreateActor<GameEndButton>();

	// ���� ���콺 ���� - �̹��� ���� �� ��������(���������ؾ���)
	//MouseObject* MainMouse = CreateActor<MouseObject>();
	//GlobalValue::CurMouse = MainMouse;
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("CreateCharacterLevel");
	}
}

