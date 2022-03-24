#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"
#include "MouseObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	IsRun_(false),
	IsInventory_(false),
	IsStateView_(false),
	IsSkillView_(false),
	IsRightSkillList_(false),
	IsLeftSkillList_(false),
	IsStorehouse_(false),
	IsMove_(false),
	IsDefaultZOrderChangeChk_(false),
	IsFrameZOrderChangeChk_(false),
	State_(),
	RenderSize_(float4(256.f, 256.f)),
	PrevMoveTargetPos_(float4::ZERO),
	CurMoveTargetPos_(float4::ZERO),
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	BottomStateBar_(nullptr)
{
	IsItemEquipState_.clear();
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		IsItemEquipState_.insert(std::map<RendererPartType, bool>::value_type(static_cast<RendererPartType>(i), false));
	}
}

MainPlayer::~MainPlayer()
{
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
	// �÷��̾� �ʱ�ȭ
	MainPlayerinitialization();

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
}

void MainPlayer::Update(float _DeltaTime)
{
	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	// �÷��̾� ���� Űüũ
	PlayerUIActiveKeyCheck();

	// ���º� �ൿ���� ó��
	State_.Update();

	// TEST
	if (true == GameEngineInput::GetInst().Down("NextDirect"))
	{

	}

	if (true == GameEngineInput::GetInst().Down("PrevDirect"))
	{

		int a = 0;
	}

	if (true == GameEngineInput::GetInst().Down("NextState"))
	{

		int a = 0;
	}

	if (true == GameEngineInput::GetInst().Down("PrevState"))
	{

		int a = 0;
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// ��ųâ ����
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		// �̹� Ȱ��ȭ �Ǿ��ִٸ� ��Ȱ��ȭ
		if (true == IsSkillView_)
		{
			IsSkillView_ = false;
		}
		else // �ƴ϶�� Ȱ��ȭ
		{
			IsSkillView_ = true;
		}
	}
	
	// ����â ����
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		// �̹� Ȱ��ȭ �Ǿ��ִٸ� ��Ȱ��ȭ
		if (true == IsStateView_)
		{
			IsStateView_ = false;
		}
		else // �ƴ϶�� Ȱ��ȭ
		{
			IsStateView_ = true;
		}
	}

	// �κ��丮 ����
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		// �̹� Ȱ��ȭ �Ǿ��ִٸ� ��Ȱ��ȭ
		if (true == IsInventory_)
		{
			IsInventory_ = false;
		}
		else // �ƴ϶�� Ȱ��ȭ
		{
			IsInventory_ = true;
		}
	}

	// ���¹̳� Ȱ��/��Ȱ��
	if (true == GameEngineInput::GetInst().Down("StaminaActive"))
	{
		// �̹� Ȱ��ȭ �Ǿ��ִٸ� ��Ȱ��ȭ
		if (true == IsRun_)
		{
			IsRun_ = false;
		}
		else // �ƴ϶�� Ȱ��ȭ
		{
			IsRun_ = true;
		}
	}

	// ���콺 ���ʹ�ư(���� �浹�� ȣ��� ���濹��)
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// �̵����� üũ�� �̵��̶�� �������� ���� ����
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("���� ���콺 ������Ʈ�� ã�� ���Ͽ����ϴ�!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetLocalPosition();

		// ���� ���� ��ȯ �� �̵� Flag On
		if (true == MoveDirectCheck(MousePos))
		{
			// �̵� ����
			MoveStart();
		}
	}
}

