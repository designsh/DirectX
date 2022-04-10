#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "MouseObject.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_CurExpProgressBar.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	//IsTown_(false),
	IsRun_(false),
	IsInventoryView_(false),
	IsStateView_(false),
	IsSkillView_(false),
	IsRightSkillList_(false),
	IsLeftSkillList_(false),
	IsStorehouse_(false),
	IsGameEndMenu_(false),
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
	SkillView_(nullptr),
	InventoryView_(nullptr),
	GameEndMenuView_(nullptr)
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
	InventoryView_ = GetLevel()->CreateActor<InventoryView>();

	// ��������޴� â
	GameEndMenuView_ = GetLevel()->CreateActor<GameEndMenuView>();

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

	// ��������޴� ����
	if (false == GameEngineInput::GetInst().IsKey("GameEndMenuActive"))
	{
		GameEngineInput::GetInst().CreateKey("GameEndMenuActive", VK_ESCAPE);
	}

	// ���¹̳� Ȱ��/��Ȱ��
	if (false == GameEngineInput::GetInst().IsKey("StaminaActive"))
	{
		GameEngineInput::GetInst().CreateKey("StaminaActive", 'R');
	}

	// ============================================ �׽�Ʈ�� ============================================ //
	if (false == GameEngineInput::GetInst().IsKey("TESTLEVELUP"))
	{
		GameEngineInput::GetInst().CreateKey("TESTLEVELUP", 'P');
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

	if (true == GameEngineInput::GetInst().Down("TESTLEVELUP"))
	{
		// �׽�Ʈ ����ġ ����
		int TextEXP = 10;
		BottomStateBar_->GetEXPProgressBarControl()->AddEXP(TextEXP);
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// ��ųâ ����
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(2);
	}
	
	// ����â ����
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(0);
	}

	// �κ��丮 ����
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(1);
	}

	// ��������޴� ����(�ӽú���)
	if (true == GameEngineInput::GetInst().Down("GameEndMenuActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(3);
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
		// UI �浹�� ���ÿ� Ŭ���Ͻ� ����ó��(�̵��Ұ�ó��)



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

