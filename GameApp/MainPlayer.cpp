#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_A1),
	CurState_(PlayerState::STAT_A1),
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

	if (!PartRenderer_.empty())
	{
		PartRenderer_.clear();
	}

	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		DirectRenderOrder_[i].clear();
	}
}

void MainPlayer::Start()
{
	// �÷��̾� ���¸��� ����
	CreateStateName();

	// ���⺰ ������ ���� ����
	CreateDirectRenderOrderType();

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

	// ���¹̳� Ȱ��/��Ȱ��
	if (false == GameEngineInput::GetInst().IsKey("StaminaActive"))
	{
		GameEngineInput::GetInst().CreateKey("StaminaActive", 'R');
	}

	// TEST ��
	if (false == GameEngineInput::GetInst().IsKey("NextDirect"))
	{
		GameEngineInput::GetInst().CreateKey("NextDirect", '1');
	}

	if (false == GameEngineInput::GetInst().IsKey("PrevDirect"))
	{
		GameEngineInput::GetInst().CreateKey("PrevDirect", '2');
	}

	if (false == GameEngineInput::GetInst().IsKey("NextState"))
	{
		GameEngineInput::GetInst().CreateKey("NextState", '3');
	}

	if (false == GameEngineInput::GetInst().IsKey("PrevState"))
	{
		GameEngineInput::GetInst().CreateKey("PrevState", '4');
	}

	//DirectText = static_cast<int>(CurDirect_);
	StateTest = static_cast<int>(PlayerState::STAT_A1);
}

void MainPlayer::Update(float _DeltaTime)
{
	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	// �÷��̾� ���� Űüũ
	PlayerUIActiveKeyCheck();






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

	if (true == GameEngineInput::GetInst().Down("PrevDirect"))
	{
		ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));
		--DirectText;

		if (DirectText <= 0)
		{
			DirectText = static_cast<int>(TargetDirect::DIR_MAX) - 1;
		}
	}

	if (true == GameEngineInput::GetInst().Down("NextState"))
	{
		DirectText = 4;
		++StateTest;
		if (StateTest >= static_cast<int>(PlayerState::STAT_MAX))
		{
			StateTest = 0;
		}
		ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));
	}

	if (true == GameEngineInput::GetInst().Down("PrevState"))
	{
		DirectText = 4;
		--StateTest;
		if (StateTest < 0)
		{
			StateTest = static_cast<int>(PlayerState::STAT_MAX) - 1;
		}
		ChangePlayerAnimation(static_cast<PlayerState>(StateTest), static_cast<TargetDirect>(DirectText));
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// ��ųâ ����
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		int a = 0;
	}
	
	// ����â ����
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		int a = 0;
	}

	// �κ��丮 ����
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		int a = 0;
	}

	// ���¹̳� Ȱ��/��Ȱ��
	if (true == GameEngineInput::GetInst().Down("StaminaActive"))
	{
		int a = 0;
	}
}

