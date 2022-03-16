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

TitleLevel::TitleLevel() :
	StartButton_(nullptr),
	EndButton_(nullptr)
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
	// ��������� �������͵��� �ʿ��׸� ����
	StartButton_->ChangeStartReset();
	EndButton_->ChangeStartReset();

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
	StartButton_ = CreateActor<GameStartButton>();

	// �������� ��ư ����(�̹���+�ؽ�Ʈ)
	EndButton_ = CreateActor<GameEndButton>();

	// ���� ���콺 ����
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
	GlobalValue::CurMouse = MainMouse;
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
}

