#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PrevDirect_(TargetDirect::None),
	CurDirect_(TargetDirect::None),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	StateName_(),
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



	// ================================== Ű���� ================================== //
	// ��ųâ ����
	if (false == GameEngineInput::GetInst().IsKey("SkillViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("SkillViewActive", 'T');
	}

	// ����â ����
	if (false == GameEngineInput::GetInst().IsKey("StatViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("StatViewActive", 'A');
	}

	// �κ��丮 ����
	if (false == GameEngineInput::GetInst().IsKey("InventoryActive"))
	{
		GameEngineInput::GetInst().CreateKey("InventoryActive", 'I');
	}

	// TEST ��
	//MainPlayerInfomation::GetInst().CreateMainPlayerInfo("aaaa", JobType::Necromancer);
	if (false == GameEngineInput::GetInst().IsKey("NextDirect"))
	{
		GameEngineInput::GetInst().CreateKey("NextDirect", '1');
	}

	if (false == GameEngineInput::GetInst().IsKey("NextState"))
	{
		GameEngineInput::GetInst().CreateKey("NextState", '2');
	}

	//DirectText = static_cast<int>(CurDirect_);
	StateTest = static_cast<int>(PlayerState::STAT_TN);
}

void MainPlayer::Update(float _DeltaTime)
{
	// TEST
	if (true == GameEngineInput::GetInst().Down("NextDirect"))
	{
		ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));
		++DirectText;

		if (DirectText >= static_cast<int>(TargetDirect::DIR_MAX))
		{
			DirectText = 0;
		}
	}

	if (true == GameEngineInput::GetInst().Down("NextState"))
	{
		DirectText = 0;
		++StateTest;
		if (StateTest >= static_cast<int>(PlayerState::STAT_MAX))
		{
			StateTest = 0;
		}
		ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));
	}

	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

