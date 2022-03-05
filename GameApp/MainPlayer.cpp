#include "PreCompile.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PrevDirect_(TargetDirect::None),
	CurDirect_(TargetDirect::None),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	StateName_(),
	PlayerInfomation_(nullptr),
	BottomStateBar_(nullptr),
	PlayerSize_(float4::ZERO)
{
}

MainPlayer::~MainPlayer()
{
	if (!StateName_.empty())
	{
		StateName_.clear();
	}
}

void MainPlayer::Start()
{
	// �÷��̾� ���¸��� ����
	CreateStateName();

	// �÷��̾� �ִϸ��̼� ���� �̹��� Cut
	AllAnimationCut();

	// �÷��̾� �ִϸ��̼� ���� ����
	CreateAnimation();

	// �ϴ� ���¹�
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// ��ųâ


	// ����â

	// �κ��丮â


	// TEST
	if (false == GameEngineInput::GetInst().IsKey("NextAnimation"))
	{
		GameEngineInput::GetInst().CreateKey("NextAnimation", '1');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// TEST
	if (true == GameEngineInput::GetInst().Down("NextAnimation"))
	{
		ChangePlayerAnimation(PlayerState::STAT_TN, static_cast<TargetDirect>(Test));
		++Test;
		if (Test >= static_cast<int>(TargetDirect::DIR_MAX))
		{
			Test = 0;
		}
	}

	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

