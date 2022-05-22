#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>

#include "MainPlayerInfomation.h"
#include "MouseObject.h"

// �÷��̾� ���� UI ����
#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_CurExpProgressBar.h"
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

// ����
#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// ��ü UI ����
#include "SummonsEmblem.h"

// �� ����
#include "TownMap.h"
#include "CatacombsMap.h"

// NPC ����
#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

// ������Ʈ ����
#include "Portal.h"
#include "Storehouse.h"
#include "StoreView.h"

// ��ȯ������
#include "SummonsGolem.h"
#include "SketelonWarrior.h"
#include "SketelonWizard.h"

// ��ų����
#include "BoneSpirit.h"

int MainPlayer::ArrangeRoomNo_ = -1;
int MainPlayer::CurLeftSkill_ = 0;
int MainPlayer::CurRightSkill_ = 0;

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
	SkillCastPos_(float4::ZERO),
	SummonsGolem_(nullptr),
	DeathMonster_(nullptr),
	TargetMonster_(nullptr),
	CurHP_(100),
	CurMP_(100),
	PrevEXP_(0),
	CurEXP_(0),
	PrevLevel_(1),
	CurLevel_(1),
	HaveGold_(0),
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
	if (false == GameEngineInput::GetInst().IsKey("TESTDAMAGE"))
	{
		GameEngineInput::GetInst().CreateKey("TESTDAMAGE", 'O');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// ���� ���콺 ��ġ�� ȭ���� ����� Ű�Է� �Ұ�
	if (true == GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
	{
		return;
	}

	// ���� ����ī�޶����̸� �Է�ó�� �Ұ�
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	// �÷��̾� UIȰ��ȭ���� Űüũ
	PlayerUIActiveKeyCheck();

	// �÷��̾� �̵����� Űüũ
	PlayerMoveKeyCheck();

	// �÷��̾� ��ų���� Űüũ
	PlayerSkillCastKeyCheck();

	// ���º� �ൿ���� ó��
	State_.Update();

#pragma region �׽�ƮŰ
	if (true == GameEngineInput::GetInst().Down("TESTLEVELUP"))
	{
		// �׽�Ʈ ����ġ ����
		int TestEXP = 10;
		BottomStateBar_->GetEXPProgressBarControl()->AddEXP(TestEXP);
	}

	if (true == GameEngineInput::GetInst().Down("TESTDAMAGE"))
	{
		// �׽�Ʈ�� ������
		DelCurrentHP(10);
		DelCurrentMP(10);
	}
#pragma endregion

#pragma region �÷��̾��浹ü
	if (nullptr != BodyCollider_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		// �浹ü ��ġ ����
		float4 MyPos = GetTransform()->GetLocalPosition();
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
		MyPos.z = 0.f;
		CamPos.z = 0.f;
		BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Object), std::bind(&MainPlayer::PlayerBodyCollision, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region ��ǥ���� Y�� ����
	if (false == IsTown_)
	{
		float4 CurPlayerPos = GetTransform()->GetWorldPosition();
		TileIndex CurPlayerTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(CurPlayerPos.x, CurPlayerPos.y - 53.f));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurPlayerTileIndex.X_ + CurPlayerTileIndex.Y_) + 20.f);
	}
#pragma endregion

	// ī�޶�� �÷��̾ ���� �ٴѴ�.
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y));
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
	if (std::string::npos != _NextLevel->GetName().find("TownLevel"))
	{
		// ���� �̵���� �ʱ�ȭ �� �̵� Flag ����
		MovePath_.clear();
		IsMove_ = false;
		ChangeFSMState("Natural_Town");

		GetLevel()->SetLevelActorMove(_NextLevel, this);
		_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -100.0f));
	}
	else if (std::string::npos != _NextLevel->GetName().find("CatacombsLevel"))
	{
		// ���� �̵���� �ʱ�ȭ
		MovePath_.clear();
		IsMove_ = false;
		ChangeFSMState("Natural_Field");

		GetTransform()->SetLocalZOrder(-53.f);
		GetLevel()->SetLevelActorMove(_NextLevel, this);
		_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -300.0f));
	}
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
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(2);
		}
	}
	
	// ����â ����
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(0);
		}
	}

	// �κ��丮 ����
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(1);
		}
	}

	// ��������޴� ����(�ӽú���)
	if (true == GameEngineInput::GetInst().Down("GameEndMenuActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(3);
		}
	}
}

bool MainPlayer::PlayerUIActiveConditionCheck()
{
	// �÷��̾��� �� UI���� Ȱ��ȭ/��Ȱ��ȭ ó���� �ʿ��� ����üũ

	// NPC�� �Ǹ�â�� Ȱ��ȭ �Ǿ��ְų� â��â�� Ȱ��ȭ �Ǿ��ִٸ�
	// Ű�Է��� �����Ѵ�.(��, �� ������ �÷��̾ TownLevel�� �����Ҷ��� üũ)
	if (true == IsTown_)
	{
		// ������ΰ��� ��ȣ�ۿ����� ���� �Ǹ�â Ȱ��ȭ ����
		if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate())
		{
			return true;
		}
		// ��ȭ���ΰ��� ��ȣ�ۿ����� ���� �Ǹ�â Ȱ��ȭ ����
		else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate())
		{
			return true;
		}
		// â����� ��ȣ�ۿ����� ���� â��â Ȱ���� ����
		else if (nullptr != GlobalValue::Storehouse && true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
		{
			return true;
		}
	}
	else
	{
		// �ʵ�ʿ��� üũ�� �ؾߵǳ�???

	}

	return false;
}

void MainPlayer::PlayerMoveKeyCheck()
{
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

	// ���콺 ���ʹ�ư
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

		// ���� Ȱ��ȭ�� �˾��� �浹���̶�� �̵��Ұ�
		if (true == GlobalValue::CurMouse->GetUIPopupCollision())
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

#pragma region ���콺�����۵���ִ����Ǵ�
		if (true == GlobalValue::CurMouse->IsItemHold())
		{
			// �������� ����ִٸ� ������ ��ġ or ��� ������ �̵��Ұ�ó��
			return;
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

		// ���� ���� ��ȯ
		if (true == MoveDirectCheck(MousePos))
		{
			// �̵� ����
			MoveStart(MousePos);
		}
	}
}

void MainPlayer::PlayerSkillCastKeyCheck()
{
	// ���콺 �����ʹ�ư
	if (true == GameEngineInput::GetInst().Down("MouseRButton"))
	{
#pragma region ����ȭ���� ����� ��ų���Ұ� �Ǵ�
		if (GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
		{
			return;
		}
#pragma endregion

		if (nullptr != GlobalValue::CurMouse)
		{
			// �������� ��� �Ұ�
			if (false == IsTown_)
			{
				// ��ų���� ��ġ ����
				SkillCastPos_ = GlobalValue::CurMouse->GetTransform()->GetWorldPosition();
				if (true == MoveDirectCheck(SkillCastPos_))
				{
					// ���� ���õ� ��ų�� �⺻�����̾ƴ϶�� ��ų���� ������� ��ȯ
					if (0 != CurRightSkill_)
					{
						// �����ڷ� ��ȯ ��ų�϶��� ���콺�� ������ ��ü�� �浹������ üũ�Ѵ�.
						if (70 == CurRightSkill_ || 80 == CurRightSkill_)
						{
							// ���Ϳ� ���콺�� �浹��(���� ��ü�� �浹���̿��߸� ����)
							if (true == GlobalValue::CurMouse->GetMonsterCollision())
							{
								// ����Ϸ��� ��ü�� ���͸� �������ִ´�.
								DeathMonster_ = GlobalValue::CurMouse->GetCurCollisionMonster();

								// ��ų���� ��� ����� ���� ���õ� ��ų ����
								ChangeFSMState("Special_Attack");
							}
							else
							{
								DeathMonster_ = nullptr;
							}
						}
						else if (93 == CurRightSkill_)
						{
							if (true == GlobalValue::CurMouse->GetMonsterCollision())
							{
								// Ÿ������ �����Ǹ� �߻�ü
								TargetMonster_ = GlobalValue::CurMouse->GetCurCollisionMonster();
							}
							else
							{
								TargetMonster_ = nullptr;
							}

							ChangeFSMState("Special_Attack");
						}
						else
						{
							// ��ų���� ��� ����� ���� ���õ� ��ų ����
							ChangeFSMState("Special_Attack");
						}
					}
				}
			}
		}
	}
}

void MainPlayer::GolemSummons()
{
	// ��ų�� ��ȯ ���� �޶���
	// ��, ��� Ÿ���� ���̵� �Ѱ��� �񷽸� ����
	
	// ���� ��ȯ�� ���� �����Ѵٸ� �ش� ���� ���� ���δ�.
	if (nullptr != SummonsGolem_)
	{
		SummonsGolem_->CurGolemDeath();
		SummonsGolem_ = nullptr;
	}

	switch (CurRightSkill_)
	{
		case 75: // ClayGolem ��ȯ
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::CLAY, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::CLAY);
			break;
		}
		case 85: // BloodGolem ��ȯ
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::BLOOD, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::BLOOD);
			break;
		}
		case 90: // IronGolem ��ȯ
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::IRON, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::IRON);
			break;
		}
		case 94: // FireGolem ��ȯ
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::FIRE, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::FIRE);
			break;
		}
	}
}

void MainPlayer::SkeletonWarriorSummons()
{
	// ���� ���콺�� ���Ϳ� �浹���̰�, �ش� ���Ͱ� ��ü�����϶� ���� ���� ����

	// �����ڷ�(����) ��ȯ
	if (CurRightSkill_ == 70)
	{
		// �ִ� ��ȯ���� �ʰ��� ���� ù��° ������ �����ڷ�(������) ��� ó�� ��
		if (SummonsWarrior <= static_cast<int>(SummonsSketelonWarrior_.size()))
		{
			// ��� ó��
			SketelonWarrior* DeathSketelon = SummonsSketelonWarrior_.front();
			DeathSketelon->CurSkeletonDeath();

			// ���� ���� ����
			SketelonWarrior::WarriorCnt -= 1;
			
			// ��Ͽ��� ����
			SummonsSketelonWarrior_.pop_front();

			// ���� ��Ͽ� �����ϴ� ��ȯ������ �׺���̼� �ε����� ����
			for (auto& CurSketelon : SummonsSketelonWarrior_)
			{
				CurSketelon->DecreaseNavationIndex();
			}
		}

		// �ش� ��ų�� ���� ���ʹ� ���������� ���ó���Ǹ�, �����ڷ��� �����ȴ�.
		if (nullptr != DeathMonster_)
		{
			// ���� ���콺�� ������ ���͸� ���ó��
			DeathMonster_->GetActor()->Death();

			// ���� ���� ��Ͽ��� ����
			GlobalValue::CatacombsMap->MonsterDeathToListDelete(DeathMonster_->GetActor());

			DeathMonster_ = nullptr;

			// ���ο� �����ڷ� ���� �� ��Ͽ� �߰�
			SketelonWarrior* NewSketelon = GetLevel()->CreateActor<SketelonWarrior>();
			NewSketelon->SpawnSketelonWarrior(SkillCastPos_);
			SummonsSketelonWarrior_.push_back(NewSketelon);

			// ���� ������Ʈ
			GlobalValue::Emblem->SketelonWarriorUpdate(SketelonWarrior::WarriorCnt);
		}
	}
}

void MainPlayer::SkeletonWizardSummons()
{
	// ���� ���콺�� ���Ϳ� �浹���̰�, �ش� ���Ͱ� ��ü�����϶� ���� ���� ����

	// �����ڷ�(������) ��ȯ
	if (CurRightSkill_ == 80)
	{
		// �ִ� ��ȯ���� �ʰ��� ���� ù��° ������ �����ڷ�(������) ��� ó�� ��
		if (SummonsWizard <= static_cast<int>(SummonsSketelonWizard_.size()))
		{
			// ��� ó��
			SketelonWizard* DeathSketelon = SummonsSketelonWizard_.front();
			DeathSketelon->CurSkeletonDeath();

			// ���� ���� ����
			SketelonWizard::WizardCnt -= 1;

			// ��Ͽ��� ����
			SummonsSketelonWizard_.pop_front();

			// ���� ��Ͽ� �����ϴ� ��ȯ������ �׺���̼� �ε����� ����
			for (auto& CurSketelon : SummonsSketelonWizard_)
			{
				CurSketelon->DecreaseNavationIndex();
			}
		}

		// �ش� ��ų�� ���� ���ʹ� ���������� ���ó���Ǹ�, �����ڷ��� �����ȴ�.
		if (nullptr != DeathMonster_)
		{
			// ���� ���콺�� ������ ���͸� ���ó��
			DeathMonster_->GetActor()->Death();

			// ���� ���� ��Ͽ��� ����
			GlobalValue::CatacombsMap->MonsterDeathToListDelete(DeathMonster_->GetActor());

			DeathMonster_ = nullptr;

			// ���ο� ���̷��� ���� �� ��Ͽ� �߰�
			// ��, �����Ǵ� ���̷����� Ÿ���� �����ϰ� �����ȴ�.
			GameEngineRandom TypeRandom;
			SkeletonWizardType RandType = static_cast<SkeletonWizardType>(TypeRandom.RandomInt(0, 3));
			SketelonWizard* NewSketelon = GetLevel()->CreateActor<SketelonWizard>();
			NewSketelon->SpawnSketelonWizard(RandType, SkillCastPos_);
			SummonsSketelonWizard_.push_back(NewSketelon);

			// ���� ������Ʈ
			GlobalValue::Emblem->SketelonWizardUpdate(SketelonWizard::WizardCnt);
		}
	}
}

void MainPlayer::SkeletonWarriorDeath(SketelonWarrior* _DeathWarrior)
{
	std::list<SketelonWarrior*>::iterator StartIter = SummonsSketelonWarrior_.begin();
	std::list<SketelonWarrior*>::iterator EndIter = SummonsSketelonWarrior_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == _DeathWarrior)
		{
			SummonsSketelonWarrior_.erase(StartIter);
			_DeathWarrior->Death();
			return;
		}
	}

	if (nullptr != _DeathWarrior)
	{
		_DeathWarrior->Death();
	}
}

void MainPlayer::SkeletonWizardDeath(SketelonWizard* _DeathWizard)
{
	std::list<SketelonWizard*>::iterator StartIter = SummonsSketelonWizard_.begin();
	std::list<SketelonWizard*>::iterator EndIter = SummonsSketelonWizard_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == _DeathWizard)
		{
			SummonsSketelonWizard_.erase(StartIter);
			_DeathWizard->Death();
			break;
		}
	}
}

SummonsGolem* MainPlayer::SummonsGolemTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap && nullptr != SummonsGolem_)
	{
		TileIndex CurGolemIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SummonsGolem_->GetTransform()->GetWorldPosition());
		if (CurGolemIndex == _CheckTile)
		{
			return SummonsGolem_;
		}
	}

	return nullptr;
}

SketelonWarrior* MainPlayer::SummonsSkeletonWarriorTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap)
	{
		for (auto& SketelonWarrior : SummonsSketelonWarrior_)
		{
			if (nullptr != SketelonWarrior)
			{
				TileIndex CurWarriorIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SketelonWarrior->GetTransform()->GetWorldPosition());
				if (CurWarriorIndex == _CheckTile)
				{
					return SketelonWarrior;
				}
			}
		}
	}

	return nullptr;
}

SketelonWizard* MainPlayer::SummonsSkeletonWizardTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap)
	{
		for (auto& SketelonWizard : SummonsSketelonWizard_)
		{
			if (nullptr != SketelonWizard)
			{
				TileIndex CurWizardIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SketelonWizard->GetTransform()->GetWorldPosition());
				if (CurWizardIndex == _CheckTile)
				{
					return SketelonWizard;
				}
			}
		}
	}

	return nullptr;
}

void MainPlayer::BoneSpiritFire()
{
	if (CurRightSkill_ == 93)
	{
		// �߻�ü ����
		BoneSpirit* NewBoneSpirit = GetLevel()->CreateActor<BoneSpirit>();

		// Ÿ�������� �߻�ü
		if (nullptr != TargetMonster_)
		{
			NewBoneSpirit->BoneSpiritFire(GetTransform()->GetWorldPosition(), SkillCastPos_, TargetMonster_->GetActor());
		}
		// Ÿ�������� �ȵ� �߻�ü
		else
		{
			NewBoneSpirit->BoneSpiritFire(GetTransform()->GetWorldPosition(), SkillCastPos_);
		}
	}
}
