#include "PreCompile.h"
#include "CatacombsLevel.h"

#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "GlobalValue.h"
#include "MainPlayerInfomation.h"
#include "MainPlayer.h"
#include "MouseObject.h"

bool CatacombsLevel::ResourceLoadEndCheck = false;

CatacombsLevel::CatacombsLevel() :
	MainPlayer_(nullptr),
	MainMouse_(nullptr)
{
}

CatacombsLevel::~CatacombsLevel()
{
}

void CatacombsLevel::CreateLevelActor()
{
	// �ʷε�(Ÿ�ϸ� - ������)

	// �÷��̾� ���� �� �����÷��̾� ����
	if (nullptr == GlobalValue::CurPlayer)
	{
		MainPlayer_ = CreateActor<MainPlayer>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(MainPlayer_->GetTransform()->GetLocalPosition());
		GlobalValue::CurPlayer = MainPlayer_;

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

void CatacombsLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ������� Off
}

void CatacombsLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	// ������� On

}

void CatacombsLevel::LevelStart()
{	
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void CatacombsLevel::LevelUpdate(float _DeltaTime)
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
