#include "PreCompile.h"
#include "ChaosSanctuaryLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayerInfomation.h"
#include "MainPlayer.h"
#include "MouseObject.h"

bool ChaosSanctuaryLevel::ResourceLoadEndCheck = false;

ChaosSanctuaryLevel::ChaosSanctuaryLevel() :
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
{
}

ChaosSanctuaryLevel::~ChaosSanctuaryLevel()
{
}

void ChaosSanctuaryLevel::CreateLevelActor()
{
	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());
		GlobalValue::CurPlayer = MainPlayer_;
	}

	// ���� ����

	// ���콺
	MainMouse_ = CreateActor<MouseObject>();
	MainMouse_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());

	// ���θ��콺 ����
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}

	// �����÷��̾� ���� �����Ǿ����� üũ
	if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	{
		// ���� ������ �Ǿ��ٸ� �÷��̾��� UI�� �ʿ��� ���� ����
		if (nullptr != GlobalValue::CurPlayer)
		{
			GlobalValue::CurPlayer->CreatePlayerUIInfomation();
		}
	}
}

void ChaosSanctuaryLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� Off
}

void ChaosSanctuaryLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On

	// �����÷��̾� ����
	if (GlobalValue::CurPlayer != MainPlayer_)
	{
		GlobalValue::CurPlayer = MainPlayer_;
	}

	// ���θ��콺 ����
	if (GlobalValue::CurMouse != MainMouse_)
	{
		GlobalValue::CurMouse = MainMouse_;
	}

	// �����÷��̾� ���� �����Ǿ����� üũ
	if (true == MainPlayerInfomation::GetInst().IsMainPlayerInfo())
	{
		// ���� ������ �Ǿ��ٸ� �÷��̾��� UI�� �ʿ��� ���� ����
		if (nullptr != GlobalValue::CurPlayer)
		{
			GlobalValue::CurPlayer->CreatePlayerUIInfomation();
		}
	}
}

void ChaosSanctuaryLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void ChaosSanctuaryLevel::LevelUpdate(float _DeltaTime)
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
