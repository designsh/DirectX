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

bool TitleLevel::ResourceLoadEndCheck = false;

TitleLevel::TitleLevel() :
	StartButton_(nullptr),
	EndButton_(nullptr)
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::CreateLevelActor()
{
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

void TitleLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void TitleLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ��������� �������͵��� �ʿ��׸� ����
	if (nullptr != StartButton_)
	{
		StartButton_->ChangeStartReset();
	}

	if (nullptr != EndButton_)
	{
		EndButton_->ChangeStartReset();
	}

	// ���� ù ���۽� ������� ���
	


}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
#pragma region ResourceLoadingEndCheck
	// �̹��� �ε��� �Ϸ�Ǹ� ���ͻ���
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion
}

