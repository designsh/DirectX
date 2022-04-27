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
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "Portal.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
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
	BodyCollider_(nullptr),
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
	GameEndMenuView_(nullptr),
	MoveSpeed_(200.f),
	MoveTargetDir_(float4::ZERO),
	MoveTargetIndex_(TileIndex())
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

#pragma region �÷��̾��浹ü
	if (nullptr != BodyCollider_)
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Object), std::bind(&MainPlayer::PlayerBodyCollision, this, std::placeholders::_1));
	}
#pragma endregion

	// ī�޶�� �÷��̾ ���� �ٴѴ�.
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

void MainPlayer::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// Ÿ��Ʋ ȭ�� or �ε�ȭ�� or ĳ���ͻ���ȭ�� or ĳ���ͼ���ȭ�� or ����ȭ�� �̵��� �����̵�����
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}

	// �ϴܻ��¹�
	if (nullptr != BottomStateBar_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, BottomStateBar_);
	}

	// ����â
	if (nullptr != StatView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, StatView_);
	}

	// ��ųâ
	if (nullptr != SkillView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, SkillView_);
	}

	// �κ��丮â
	if (nullptr != InventoryView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, InventoryView_);
	}

	// ��������޴�
	if (nullptr != GameEndMenuView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, GameEndMenuView_);
	}

	// �����÷��̾�
	GetLevel()->SetLevelActorMove(_NextLevel, this);
	_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -100.0f));
}

void MainPlayer::TownMapObjectCheck(const float4& _MousePos)
{
	// �����ʿ� �����ϴ� ��� ������Ʈ ��ȣ�ۿ� Ȱ��ȭ���� üũ

	// ��Ż
	if (nullptr != GlobalValue::Portal)
	{
		// Ȱ��ȭ�Ǿ��ִٸ� ����
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// ��, ���콺�� Ŭ���������� ��Ż�� �����ϴ� Ÿ���� �ƴѰ�쿡�� ����
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
	}

	// â��� ����
}

void MainPlayer::RandomMapObjectCheck(const float4& _MousePos)
{
	// �ʵ�ʿ� �����ϴ� ��� ������Ʈ ��ȣ�ۿ� Ȱ��ȭ���� üũ

	// �����ۻ���

	// HP�칰

	// MP�칰

	// ���¹̳��칰

	// ��Ż
	if (nullptr != GlobalValue::Portal)
	{
		// Ȱ��ȭ�Ǿ��ִٸ� ����
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// ��, ���콺�� Ŭ���������� ��Ż�� �����ϴ� Ÿ���� �ƴѰ�쿡�� ����
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
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
#pragma region ����ȭ���� ����� �̵��Ұ� �Ǵ�
		if (GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
		{
			return;
		}
#pragma endregion

#pragma region ���콺�� �̹� UI�� �浹���̶�� �̵��Ұ� �Ǵ�

#pragma region �÷��̾� UI
		// �ϴܻ��¹ٿ� �浹���̶�� Ŭ������ �̵��Ұ�
		if (true == GlobalValue::CurMouse->GetBottomStateBarCollision())
		{
			return;
		}

		// ��ųƮ��â or �κ��丮â�� �浹���̶�� Ŭ������ �̵��Ұ�
		// ��, Ŭ�������� ȭ���� ���������̶�� �̵������Ǵ�
		if (true == GlobalValue::CurMouse->GetScreenRightUIViewCollision())
		{
			return;
		}

		// ����â or NPC�� �Ǹ�â �浹���̶�� Ŭ������ �̵��Ұ�
		// ��, Ŭ�������� ȭ���� �����������̶�� �̵������Ǵ�
		if (true == GlobalValue::CurMouse->GetScreenLeftUIViewCollision())
		{
			return;
		}

		// ���ʽ�ų��ϸ���Ʈ�� �浹���̶�� �̵��Ұ�
		if (true == GlobalValue::CurMouse->GetLWeaponSkillListCollision())
		{
			return;
		}

		// �����ʽ�ų��ϸ���Ʈ�� �浹���̶�� �̵��Ұ�
		if (true == GlobalValue::CurMouse->GetRWeaponSkillListCollision())
		{
			return;
		}
#pragma endregion

#pragma region NPC UI
		if (true == IsTown_) // ������������ NPC ����
		{
			// ��ܸ޴���
			if (true == GlobalValue::CurMouse->GetTopMenuBarCollision())
			{
				return;
			}

			// �Ǹ�â
			if (true == GlobalValue::CurMouse->GetBuySellViewCollision())
			{
				return;
			}
		}
#pragma endregion

#pragma endregion

		// �̵����� üũ�� �̵��̶�� �������� ���� ����
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("���� ���콺 ������Ʈ�� ã�� ���Ͽ����ϴ�!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetWorldPosition();

#pragma region ������ƮȰ��ȭ����üũ
		if (true == IsTown_)
		{
			TownMapObjectCheck(MousePos);
		}
		else
		{
			RandomMapObjectCheck(MousePos);
		}
#pragma endregion

		// �̹� �̵����̿��ٸ� ���� ��θ� �����ϰ� Flag���� �� �÷��̾� ������ ����
		if (true == IsMove_)
		{
			MovePath_.clear();
			IsMove_ = false;

			if (true == IsTown_)
			{
				ChangeFSMState("Natural_Town");
			}
			else
			{
				ChangeFSMState("Natural_Field");
			}
		}

		// ���� ���� ��ȯ �� �̵� Flag On
		if (true == MoveDirectCheck(MousePos))
		{
			// �̵� ����
			MoveStart(MousePos);
		}
	}
}

