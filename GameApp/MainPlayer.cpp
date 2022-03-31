#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "MouseObject.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_Stamina.h"
#include "StatView.h"
#include "SkillView.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	//IsTown_(false),
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
	CurHP_(100),
	CurMP_(100),
	PrevEXP_(0),
	CurEXP_(0),
	PrevLevel_(1),
	CurLevel_(1),
	State_(),
	RenderSize_(float4(256.f, 256.f)),
	PrevMoveTargetPos_(float4::ZERO),
	CurMoveTargetPos_(float4::ZERO),
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	BottomStateBar_(nullptr),
	StatView_(nullptr),
	SkillView_(nullptr)
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
	SkillView_ = GetLevel()->CreateActor<SkillView>();

	// ����â
	StatView_ = GetLevel()->CreateActor<StatView>();

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
}

void MainPlayer::Update(float _DeltaTime)
{
	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	// �÷��̾� ���� Űüũ
	PlayerUIActiveKeyCheck();

	// ���º� �ൿ���� ó��
	State_.Update();

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
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess();
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

			// �ϴܻ��¹��� ���¹̳� Ȱ��/��Ȱ����ư ����
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// �÷��̾ �̵����̶�� ������ȯ
			if (true == IsMove_)
			{
				// �������� �ƴ��� �Ǵ�
				if (true == IsTown_)
				{
					ChangeFSMState("Walk_Town");
				}
				else
				{
					ChangeFSMState("Walk_Field");
				}
			}
		}
		else // �ƴ϶�� Ȱ��ȭ
		{
			IsRun_ = true;

			// �ϴܻ��¹��� ���¹̳� Ȱ��/��Ȱ����ư ����
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// �÷��̾ �̵����̶�� ������ȯ
			if (true == IsMove_)
			{
				ChangeFSMState("Run");
			}
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

