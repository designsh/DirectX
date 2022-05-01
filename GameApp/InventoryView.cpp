#include "PreCompile.h"
#include "InventoryView.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "AllItemInfomation.h"
#include "InventoryTileBox.h"
#include "InvArrangementItemInfo.h"

#include "GlobalValue.h"

#include "MouseObject.h"
#include "MainPlayer.h"
#include "Storehouse.h"
#include "StoreView.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"

#include "TakeInOutGoldPopup.h"

InventoryView::InventoryView() :
	InventoryPanel_(nullptr),
	PanelCol_(nullptr),
	CloseButton_(nullptr),
	CloseButtonCollider_(nullptr),
	CloseButtonState_(Button_State::Normal),
	InvTabType_(InvTabType::NONE),
	GoldTakeInPopup_(nullptr),
	GoldDropPopup_(nullptr),
	GoldButton_(nullptr),
	GoldButtonCol_(nullptr),
	GoldButtonState_(Button_State::Normal),
	CurHaveGoldText_(nullptr)
{
}

InventoryView::~InventoryView()
{

}

void InventoryView::CloseButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Click");

		CloseButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Default");
	}
}

void InventoryView::EquipTileBoxClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		InvTabType_ = InvTabType::EQUIP;

		// ���� ���콺�� Ŀ������ üũ
		
		if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState()) // ���콺 �Ǹ�Ŀ������
		{
			// �ش� Ÿ���� �������� ��������� ó������
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag())
			{
				// �Ǹ�Ŀ�� Ȱ��ȭ �����϶� �����ǿ� �������� �����Ѵٸ� ���� ��ȣ�ۿ����� NPC�� �Ǹ�â�� �ش� ������ �Ǹ�
				// 1. ���� Ȱ��ȭ�� �Ǹ�â�� �Ÿ���� �Ǹ�â���� �˾Ƴ���.
				// 2. �ش� �Ǹ�â�� �ŷ��� �õ�(�ŷ����� üũ)
				// 3. �ŷ��Ϸ�� ó��
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // �����Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // ��ȭ�Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::PotionShop);
				}
			}
		}
		else if (MouseState::Repair == GlobalValue::CurMouse->GetMouseState()) // ���콺 ����Ŀ������
		{
			// �ش� Ÿ���� �������� ����ְ� ���� Ȱ��ȭ�Ǿ��ִ� �Ǹ�â�� ��������� �Ǹ�â�϶�
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() &&
				(nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()))
			{
				ItemRepairProcess(_Index, InvTabType_);
			}
		}
		else if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() || MouseState::Move == GlobalValue::CurMouse->GetMouseState()) // ���콺 �⺻Ŀ������
		{
			// �ش� Ÿ���� �������� �������ְ�, ���콺�� �������� ��������ʴٸ�
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOff(_Index, InvTabType_);
			}
			// �ش� Ÿ���� �������� �����������ʰ�, ���콺�� �������� ����ִٸ�
			else if (false == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOn(_Index, InvTabType_);
			}
			else
			{
				// �� ���ǿ� �������� �ʴٸ� ���� ���

			}
		}
	}
}

void InventoryView::StoreTileBoxClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		InvTabType_ = InvTabType::NORMAL;

		// ���� ���콺�� Ŀ������ üũ
		if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState()) // ���콺 �Ǹ�Ŀ������
		{
			// �ش� Ÿ���� �������� ��������� �ŷ�����
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag())
			{
				// �Ǹ�Ŀ�� Ȱ��ȭ �����϶� �����ǿ� �������� �����Ѵٸ� ���� ��ȣ�ۿ����� NPC�� �Ǹ�â�� �ش� ������ �Ǹ�
				// 1. ���� Ȱ��ȭ�� �Ǹ�â�� �Ÿ���� �Ǹ�â���� �˾Ƴ���.
				// 2. �ش� �Ǹ�â�� �ŷ��� �õ�(�ŷ����� üũ)
				// 3. �ŷ��Ϸ�� ó��
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // �����Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // ��ȭ�Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::PotionShop);
				}
			}
		}
		else if (MouseState::Repair == GlobalValue::CurMouse->GetMouseState()) // ���콺 ����Ŀ������
		{
			// �ش� Ÿ���� �������� ����ְ� ���� Ȱ��ȭ�Ǿ��ִ� �Ǹ�â�� ��������� �Ǹ�â�϶�
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && 
				(nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()))
			{
				ItemRepairProcess(_Index, InvTabType_);
			}
		}
		else if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() || MouseState::Move == GlobalValue::CurMouse->GetMouseState()) // ���콺 �⺻Ŀ������
		{
			// �ش� Ÿ���� �������� �������ְ�, ���콺�� �������� ��������ʴٸ�
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOff(_Index, InvTabType_);
			}
			// �ش� Ÿ���� �������� �����������ʰ�, ���콺�� �������� ����ִٸ�
			else if (false == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOn(_Index, InvTabType_);
			}
			else
			{
				// �� ���ǿ� �������� �ʴٸ� ���� ���

			}
		}
	}
}

void InventoryView::Start()
{
	// GetScreen Harf Size
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// Create Panel Renderer
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Inventory_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	InventoryPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	InventoryPanel_->SetImage("Inventory_Panel.png");
	InventoryPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x, 24.f));

	// �÷��̾� �̵��Ұ�ó���� ���� �浹ü ����
	PanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	PanelCol_->SetName("Player_InventoryView");
	PanelCol_->GetTransform()->SetLocalScaling(InventoryPanel_->GetTransform()->GetLocalScaling());
	PanelCol_->GetTransform()->SetLocalPosition(InventoryPanel_->GetTransform()->GetLocalPosition());

	// Button Image Cutting
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);
	GameEngineTexture* GoldCoinButtonDefault = GameEngineTextureManager::GetInst().Find("GoldIconBtn_Default.png");
	GoldCoinButtonDefault->Cut(1, 1);
	GameEngineTexture* GoldCoinButtonClick = GameEngineTextureManager::GetInst().Find("GoldIconBtn_Click.png");
	GoldCoinButtonClick->Cut(1, 1);


	// Create Button Renderer
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(35.f, -161.f));
	CloseButton_->SetChangeAnimation("Default");

	// Create Button Collision
	CloseButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	CloseButtonCollider_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.0f));
	CloseButtonCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// �÷��̾� ���� ��� ����
	GoldTakeInPopup_ = GetLevel()->CreateActor<TakeInOutGoldPopup>();
	GoldTakeInPopup_->CreateTakePopup(TakeInOutPopupType::TakeIn, TakeInOutPopCreateType::PLAYER, float4(-100.f, 50.f), 0);

	GoldDropPopup_ = GetLevel()->CreateActor<TakeInOutGoldPopup>();
	GoldDropPopup_->CreateTakePopup(TakeInOutPopupType::Drop, TakeInOutPopCreateType::PLAYER, float4(-100.f, 50.f), 0);

	GoldButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	GoldButton_->CreateAnimation("GoldIconBtn_Default.png", "Default", 0, 0, 0.1f, false);
	GoldButton_->CreateAnimation("GoldIconBtn_Click.png", "Click", 0, 0, 0.1f, false);
	GoldButton_->GetTransform()->SetLocalScaling(float4(20.f, 18.f));
	GoldButton_->GetTransform()->SetLocalPosition(float4(95.f, -160.f));
	GoldButton_->SetChangeAnimation("Default");

	GoldButtonCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	GoldButtonCol_->GetTransform()->SetLocalScaling(GoldButton_->GetTransform()->GetLocalScaling());
	GoldButtonCol_->GetTransform()->SetLocalPosition(GoldButton_->GetTransform()->GetLocalPosition());

	CurHaveGoldText_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	CurHaveGoldText_->SetImage("InvTestTileImage.png");
	CurHaveGoldText_->TextSetting("diablo", std::to_string(0), 12.f, FW1_LEFT | FW1_VCENTER, float4::WHITE, float4(-42.f, 0.f));
	CurHaveGoldText_->GetTransform()->SetLocalScaling(float4(90.f, 15.f));
	CurHaveGoldText_->GetTransform()->SetLocalPosition(float4(152.f, -160.f));
	CurHaveGoldText_->SetAlpha(0.f);

	Off();
}

void InventoryView::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(PanelCol_->GetTransform(), CollisionType::Rect);

	GetLevel()->UIPushDebugRender(CloseButtonCollider_->GetTransform(), CollisionType::Rect);

	for (int i = 0; i < static_cast<int>(InvEquipCol_.size()); ++i)
	{
		GetLevel()->UIPushDebugRender(InvEquipCol_[i]->GetTransform(), CollisionType::Rect);
	}

	for (int i = 0; i < static_cast<int>(InvStoreCol_.size()); ++i)
	{
		GetLevel()->UIPushDebugRender(InvStoreCol_[i]->GetTransform(), CollisionType::Rect);
	}

	GetLevel()->UIPushDebugRender(GoldButtonCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

#pragma region �����ư�浹 �� Ŭ��üũ
	// �κ�â �����ư üũ
	if (CloseButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// �̴ϸ޴� �����ڸ� ����
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// ��ųâ ��Ȱ��ȭ
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(1);
			}

			// ����˾��� �����ִٸ� ����˾��� ��Ȱ��ȭ�Ѵ�.
			if (true == GoldTakeInPopup_->IsUpdate())
			{
				GoldTakeInPopup_->TakeInOutGoldPopupInactive();
			}
			if (true == GoldDropPopup_->IsUpdate())
			{
				GoldDropPopup_->TakeInOutGoldPopupInactive();
			}

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// �̺�â �����ư �浹üũ
	CloseButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::CloseButtonClick, this, std::placeholders::_1));

#pragma endregion

#pragma region �κ�â ���/�ϴ� Ÿ�Ϲڽ� �浹üũ
	for (int i = 0; i < static_cast<int>(InvEquipCol_.size()); ++i)
	{
		InvEquipCol_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::EquipTileBoxClick, this, std::placeholders::_1, i));
	}

	for (int i = 0; i < static_cast<int>(InvStoreCol_.size()); ++i)
	{
		InvStoreCol_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::StoreTileBoxClick, this, std::placeholders::_1, i));
	}
#pragma endregion

#pragma region ����˾�Ȱ��ȭ��ư �浹üũ
	if (GoldButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ����˾� Ȱ��ȭ ó��
			GoldPopupActive();

			GoldButtonState_ = Button_State::Normal;
			GoldButton_->SetChangeAnimation("Default");
		}
	}

	GoldButtonCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::GoldPopupButtonClick, this, std::placeholders::_1));
#pragma endregion
}

void InventoryView::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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

	// �κ��丮�� ����ִ� ��� ���͸� �ѱ�

	// ������(����, ��, ...) �������
	if (false == InvEquipInfo_.empty())
	{
		int InvEquipInfoCnt = static_cast<int>(InvEquipInfo_.size());
		for (int i = 0; i < InvEquipInfoCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvEquipInfo_[i]);
		}
	}

	// ������ �������
	if (false == InvStoreInfo_.empty())
	{
		int InvStoreInfoCnt = static_cast<int>(InvStoreInfo_.size());
		for (int i = 0; i < InvStoreInfoCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvStoreInfo_[i]);
		}
	}

	// �κ�â�� ��ġ�Ǿ��ִ� ���������� ���
	if (false == InvArrItemList_.empty())
	{
		int InvArrItemCnt = static_cast<int>(InvArrItemList_.size());
		for (int i = 0; i < InvArrItemCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvArrItemList_[i]);
		}
	}

	// ����˾�
	if (nullptr != GoldTakeInPopup_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, GoldTakeInPopup_);
	}

	if (nullptr != GoldDropPopup_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, GoldDropPopup_);
	}
}

void InventoryView::GoldPopupButtonClick(GameEngineCollision* _Other)
{
	// 
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		GoldButton_->SetChangeAnimation("Click");

		GoldButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		GoldButton_->SetChangeAnimation("Default");
	}
}

void InventoryView::GoldPopupActive()
{
	// â�������Ʈ���� ��ȣ�ۿ��� ���� â��â�� Ȱ��ȭ ���¶�� ����� GoldTakeInPopup_ Ȱ��ȭ
	if (nullptr != GlobalValue::Storehouse)
	{
		// â��â�� Ȱ��ȭ�Ǿ�������
		if (true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
		{
			// ��� ����� �˾��� �����ִٸ� ��Ȱ��ȭ
			if (true == GoldDropPopup_->IsUpdate())
			{
				GoldDropPopup_->TakeInOutGoldPopupInactive();
			}

			// â��â�� ��� ������� �˾��� �����ִٸ� ��Ȱ��ȭ
			if (true == GlobalValue::Storehouse->GetStoreView()->GetTakeOutGoldPopup()->IsUpdate())
			{
				GlobalValue::Storehouse->GetStoreView()->GetTakeOutGoldPopup()->TakeInOutGoldPopupInactive();
			}

			// ��� ����� �˾�â Ȱ��ȭ
			GoldTakeInPopup_->TakeInOutGoldPopupActive(GlobalValue::CurPlayer->GetCurHaveGold());
		}
		// â��â�� ��Ȱ���Ǿ�������
		else
		{
			// ��� ����� �˾��� �����ִٸ� ��Ȱ�� ��
			if (true == GoldTakeInPopup_->IsUpdate())
			{
				GoldTakeInPopup_->TakeInOutGoldPopupInactive();
			}

			// ��� ����� �˾� Ȱ��ȭ
			GoldDropPopup_->TakeInOutGoldPopupActive(GlobalValue::CurPlayer->GetCurHaveGold());
		}
	}
	// â��â�� ���������ʴٸ�
	else
	{
		// ��� ����� �˾��� �����ִٸ� ��Ȱ��ȭ ��
		if (true == GoldTakeInPopup_->IsUpdate())
		{
			GoldTakeInPopup_->TakeInOutGoldPopupInactive();
		}

		// ��� ����� �˾��� Ȱ��ȭ
		GoldDropPopup_->TakeInOutGoldPopupActive(GlobalValue::CurPlayer->GetCurHaveGold());
	}
}

void InventoryView::HaveGoldUpdate(int _CurGold)
{
	CurHaveGoldText_->SetPrintText(std::to_string(_CurGold));
}

TakeInOutGoldPopup* InventoryView::GetTakeInGoldPopup() const
{
	return GoldTakeInPopup_;
}

TakeInOutGoldPopup* InventoryView::GetDropGoldPopup() const
{
	return GoldDropPopup_;
}

bool InventoryView::GetInvenCurEquipState(ItemLocType _LocType)
{
	// ���� �κ�â �����ǿ� ������ �������� ������ false
	// �׹ݴ��� ����� true
	return InvEquipInfo_[static_cast<int>(_LocType)]->GetIsItemArrangeFlag();
}

void InventoryView::SetInventoryBoxTileActvie()
{
	// �κ�â Ȱ��ȭ�� ȣ��

	// 1. �ϴ���
	int BotTabTileInfoCnt = static_cast<int>(InvStoreInfo_.size());
	for (int i = 0; i < BotTabTileInfoCnt; ++i)
	{
		InvStoreInfo_[i]->TileBoxActive();
	}

	int BotTabTileColCnt = static_cast<int>(InvStoreCol_.size());
	for (int i = 0; i < BotTabTileColCnt; ++i)
	{
		InvStoreCol_[i]->On();
	}

	// 2. �����
	int TopTabTileInfoCnt = static_cast<int>(InvEquipInfo_.size());
	for (int i = 0; i < TopTabTileInfoCnt; ++i)
	{
		InvEquipInfo_[i]->TileBoxActive();
	}

	int TopTablTileColCnt = static_cast<int>(InvEquipCol_.size());
	for (int i = 0; i < TopTablTileColCnt; ++i)
	{
		InvEquipCol_[i]->On();
	}

	// 3. ��ġ�� ������ ���
	int ArrItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ArrItemListCnt; ++i)
	{
		InvArrItemList_[i]->On();
	}
}

void InventoryView::SetInentroyBoxTileInactive()
{
	// �κ�â ��Ȱ��ȭ�� ȣ��

	// 1. �ϴ���
	int BotTabTileInfoCnt = static_cast<int>(InvStoreInfo_.size());
	for (int i = 0; i < BotTabTileInfoCnt; ++i)
	{
		InvStoreInfo_[i]->TileBoxInactive();
	}

	int BotTabTileColCnt = static_cast<int>(InvStoreCol_.size());
	for (int i = 0; i < BotTabTileColCnt; ++i)
	{
		InvStoreCol_[i]->Off();
	}

	// 2. �����
	int TopTabTileInfoCnt = static_cast<int>(InvEquipInfo_.size());
	for (int i = 0; i < TopTabTileInfoCnt; ++i)
	{
		InvEquipInfo_[i]->TileBoxInactive();
	}

	int TopTablTileColCnt = static_cast<int>(InvEquipCol_.size());
	for (int i = 0; i < TopTablTileColCnt; ++i)
	{
		InvEquipCol_[i]->Off();
	}

	// 3. ��ġ�� ������ ���
	int ArrItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ArrItemListCnt; ++i)
	{
		InvArrItemList_[i]->Off();
	}
}

void InventoryView::InitInventoryView()
{
	// �κ�â �ʱ� ����

	// 1. �κ�â �ϴ�&��� Ÿ�Ϲڽ� ���� ���� �� �浹ü ����
	CreateInvTile();

	// 2. ���� �����Ǵ� ������ �����÷��̾������� �̿��Ͽ�
	//    �����ϰ��ִ� ������ ����� �κ�â�� ��ġ
	PlayerItemListArrangement();

	// 3. ���� �÷��̾� ��差 ����
	if (nullptr != CurHaveGoldText_)
	{
		CurHaveGoldText_->SetPrintText(std::to_string(GlobalValue::CurPlayer->GetCurHaveGold()));
	}
}

void InventoryView::CreateInvTile()
{
	// �κ�â �ϴ�&��� Ÿ�Ϲڽ� ���� ����
	CreateInvTileInfo();

	// �κ�â �ϴ�&��� Ÿ�Ϲڽ� �浹ü ����
	CreateInvTileCol();
}

void InventoryView::CreateInvTileInfo()
{
	// �κ�â �ϴ�&��� Ÿ�Ϲڽ� ���� ����

	// 1. �ϴ� �÷��̾� ������
	// x : 10, y : 4 => 40ĭ
	InvStoreInfo_.resize(4 * 10);
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			int Index = (x * 1) + (y * 10);
			InventoryTileBox* NewTileBox = GetLevel()->CreateActor<InventoryTileBox>();
			NewTileBox->CreateNormalTileBox(false, ItemLocType::Inven_Bottom, x, y, Index);
			InvStoreInfo_[Index] = NewTileBox;
		}
	}

	// 2. ��� �÷��̾� ������
	// ����(0) ~ �����(9)
	InvEquipInfo_.resize(static_cast<size_t>(10));

	// WEAPON(����)
	InventoryTileBox* NewWeaponTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewWeaponTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Weapon, 0, float4(49.f, 136.f), float4(57.f, 113.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Weapon)] = NewWeaponTileBox;

	// SHIELD(����)
	InventoryTileBox* NewShieldTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewShieldTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Shield, 1, float4(280.f, 137.f), float4(57.f, 114.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Shield)] = NewShieldTileBox;

	// HELM(����)
	InventoryTileBox* NewHelmTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewHelmTileBox->CreatePlayerEquipTileBox("Helm.png", false, ItemLocType::Inven_Helm, 2, float4(164.f, 208.f), float4(57.f, 57.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Helm)] = NewHelmTileBox;

	// ARMOR(����)
	InventoryTileBox* NewArmorTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewArmorTileBox->CreatePlayerEquipTileBox("Armor.png", false, ItemLocType::Inven_Armor, 3, float4(164.f, 123.f), float4(57.f, 86.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Armor)] = NewArmorTileBox;

	// GLOVES(�尩)
	InventoryTileBox* NewGlovesTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewGlovesTileBox->CreatePlayerEquipTileBox("Gloves.png", false, ItemLocType::Inven_Gloves, 4, float4(48.f, 36.f), float4(57.f, 58.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Gloves)] = NewGlovesTileBox;

	// BELT(��Ʈ)
	InventoryTileBox* NewBeltTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBeltTileBox->CreatePlayerEquipTileBox("Belt.png", false, ItemLocType::Inven_Belt, 5, float4(164.f, 50.f), float4(57.f, 25.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Belt)] = NewBeltTileBox;

	// BOOTS(����)
	InventoryTileBox* NewBootsTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBootsTileBox->CreatePlayerEquipTileBox("Boots.png", false, ItemLocType::Inven_Boots, 6, float4(280.f, 36.f), float4(57.f, 58.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Boots)] = NewBootsTileBox;

	// LRING(���ʸ�)
	InventoryTileBox* NewLRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewLRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_LRing, 7, float4(108.f, 50.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_LRing)] = NewLRingTileBox;

	// RRING(�����ʸ�)
	InventoryTileBox* NewRRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewRRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_RRing, 8, float4(222.f, 50.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_RRing)] = NewRRingTileBox;

	// AMULET(�����)
	InventoryTileBox* NewAmuletTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewAmuletTileBox->CreatePlayerEquipTileBox("Amulet.png", false, ItemLocType::Inven_Amulet, 9, float4(222.f, 194.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Amulet)] = NewAmuletTileBox;
}

void InventoryView::CreateInvTileCol()
{
	// �κ�â �ϴ�&��� Ÿ�Ϲڽ� �浹ü ����

	// 1. �ϴ� �÷��̾� ������
	// x : 10, y : 4 => 40ĭ
	InvStoreCol_.resize(4 * 10);
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			int Index = (x * 1) + (y * 10);

			// Position Calc
			float4 ColPosition = float4::ZERO;
			ColPosition.x = 33.f + (x * 28.f) + (x * 1.f);
			ColPosition.y = -116.f + (y * 28.f) + (y * 1.f);;

			GameEngineCollision* NewTileCol = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			NewTileCol->GetTransform()->SetLocalPosition(ColPosition);
			NewTileCol->GetTransform()->SetLocalScaling(float4(28.f, 28.f, 1.f));
			NewTileCol->Off();
			InvStoreCol_[Index] = NewTileCol;
		}
	}

	// 2. ��� �÷��̾� ������
	InvEquipCol_.resize(10);

	// WEAPON(����)
	GameEngineCollision* NewWeaponTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewWeaponTileBox->GetTransform()->SetLocalPosition(float4(49.f, 136.f));
	NewWeaponTileBox->GetTransform()->SetLocalScaling(float4(57.f, 113.f));
	NewWeaponTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Weapon)] = NewWeaponTileBox;

	// SHIELD(����)
	GameEngineCollision* NewShieldTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewShieldTileBox->GetTransform()->SetLocalPosition(float4(280.f, 137.f));
	NewShieldTileBox->GetTransform()->SetLocalScaling(float4(57.f, 114.f));
	NewShieldTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Shield)] = NewShieldTileBox;

	// HELM(����)
	GameEngineCollision* NewHelmTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewHelmTileBox->GetTransform()->SetLocalPosition(float4(164.f, 208.f));
	NewHelmTileBox->GetTransform()->SetLocalScaling(float4(57.f, 57.f));
	NewHelmTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Helm)] = NewHelmTileBox;

	// ARMOR(����)
	GameEngineCollision* NewArmorTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewArmorTileBox->GetTransform()->SetLocalPosition(float4(164.f, 123.f));
	NewArmorTileBox->GetTransform()->SetLocalScaling(float4(57.f, 86.f));
	NewArmorTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Armor)] = NewArmorTileBox;

	// GLOVES(�尩)
	GameEngineCollision* NewGlovesTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewGlovesTileBox->GetTransform()->SetLocalPosition(float4(48.f, 36.f));
	NewGlovesTileBox->GetTransform()->SetLocalScaling(float4(57.f, 58.f));
	NewGlovesTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Gloves)] = NewGlovesTileBox;

	// BELT(��Ʈ)
	GameEngineCollision* NewBeltTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewBeltTileBox->GetTransform()->SetLocalPosition(float4(164.f, 50.f));
	NewBeltTileBox->GetTransform()->SetLocalScaling(float4(57.f, 25.f));
	NewBeltTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Belt)] = NewBeltTileBox;

	// BOOTS(����)
	GameEngineCollision* NewBootsTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewBootsTileBox->GetTransform()->SetLocalPosition(float4(280.f, 36.f));
	NewBootsTileBox->GetTransform()->SetLocalScaling(float4(57.f, 58.f));
	NewBootsTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Boots)] = NewBootsTileBox;

	// LRING(���ʸ�)
	GameEngineCollision* NewLRingTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewLRingTileBox->GetTransform()->SetLocalPosition(float4(108.f, 50.f));
	NewLRingTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewLRingTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_LRing)] = NewLRingTileBox;

	// RRING(�����ʸ�)
	GameEngineCollision* NewRRingTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewRRingTileBox->GetTransform()->SetLocalPosition(float4(222.f, 50.f));
	NewRRingTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewRRingTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_RRing)] = NewRRingTileBox;

	// AMULET(�����)
	GameEngineCollision* NewAmuletTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewAmuletTileBox->GetTransform()->SetLocalPosition(float4(222.f, 194.f));
	NewAmuletTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewAmuletTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Amulet)] = NewAmuletTileBox;
}

void InventoryView::PlayerItemListArrangement()
{
	// ���� ���۵Ǵ� ������ �÷��̾ ����ִ� ������ ��ġ
	MainPlayerInfo CurPlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	int ItemCnt = static_cast<int>(CurPlayerInfo.ItemInfo.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		// ���������� ������ ���� ���� Get
		int TileIndex = CurPlayerInfo.ItemInfo[i].StartPosition;
		ItemLocType LocType = CurPlayerInfo.ItemInfo[i].ItemLocType;
		std::string ItemName = CurPlayerInfo.ItemInfo[i].ItemName_abbreviation;

		// �ϴ� �������̸�
		if (ItemLocType::Inven_Bottom == LocType)
		{
			// �ش� Ÿ���� �������ϱ� ���� Ÿ�Ϲڽ� ��ġ Get
			float4 RenderPos = InvStoreInfo_[TileIndex]->GetTilePos();

			// Ÿ���ε����� ���״�� ��ġ���� ��ȯ�� Ÿ���ε����� ����
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(i, TileIndex, LocType, ItemName, RenderPos))
			{
				// ������ �������� ũ�⿡ ���� �κ� �ϴ� �������� ĭ(Ÿ��)�� Flag On
				float4 ArrangeSize = NewItemInfo->GetArrangeItemSize();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1ĭ�� �����ϹǷ� �ش� Ÿ���ε����� Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOn();

					// ��Ͽ� �ش� ������ �߰�
					InvArrItemList_.push_back(NewItemInfo);
				}
				else
				{
					// ĭ���� ���� Ÿ���ε������� �����ؼ� ����� Ÿ�ϰ�����ŭ ��� Flag Onó��

					// ����Ÿ�ϱ��� �����۹�ġ
					int WidthSize = CurPlayerInfo.ItemInfo[i].WidthSize;
					int HeightSize = CurPlayerInfo.ItemInfo[i].HeightSize;

					std::vector<int> TileArrIndexList;
					TileArrIndexList.clear();

					for (int k = 0; k < HeightSize; ++k)
					{
						for (int l = 0; l < WidthSize; ++l)
						{
							int CalcIndex = TileIndex + l + (k * 10);
							if (0 <= CalcIndex && CalcIndex < 40)
							{
								TileArrIndexList.push_back(CalcIndex);
							}
						}
					}

					// ��ġ��� ����
					std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

					// ������ ��ġ ��ġ ���� �� ������
					float4 ReRenderPos = float4(33.f, -116.f);	// �ʱⰪ ����(0���ε����ΰ��)

					// �����ϰ��ִ� ĭ�� �߾� ��ġ�� ����Ѵ�.
					// ù��° Ÿ���� ��ġ�� ��������° Ÿ���� ��ġ�� Get
					int IndexCnt = static_cast<int>(TileArrIndexList.size());
					float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
					float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

					// �� Ÿ�� ��ġ�� ��
					if (BeginTilePos.x == EndTilePos.x) // �ش� �������� �ʺ� 1
					{
						ReRenderPos.x = BeginTilePos.x;
					}
					else
					{
						BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
						ReRenderPos.x = BeginTilePos.x;
					}

					if (BeginTilePos.y == EndTilePos.y) // �ش� �������� ���� 1
					{
						ReRenderPos.y = BeginTilePos.y;
					}
					else
					{
						BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
						ReRenderPos.y = BeginTilePos.y;
					}

					NewItemInfo->SetItemRenderPos(ReRenderPos);

					// ������ ���� Flag On
					for (int l = 0; l < IndexCnt; ++l)
					{
						InvStoreInfo_[TileArrIndexList[l]]->SetItemArrangeFlagOn();
					}
					NewItemInfo->SetTileIndexList(TileArrIndexList);
					
					// ��Ͽ� �ش� ������ �߰�
					InvArrItemList_.push_back(NewItemInfo);
				}
			}
			else // ���� ���н� �ٷ� ����
			{
				NewItemInfo->Death();
			}
		}
		else // ��� �������̸�
		{
			// �ش� Ÿ���� �������ϱ� ���� Ÿ�Ϲڽ� ��ġ Get
			float4 RenderPos = InvEquipInfo_[static_cast<int>(LocType)]->GetTilePos();

			// Ÿ���ε����� ����ĭ�� ��ġ ������ ����
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(i, static_cast<int>(LocType), LocType, ItemName, RenderPos))
			{
				InvArrItemList_.push_back(NewItemInfo);

				// �κ� ��� �������� ĭ(Ÿ��)�� Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();
			}
			else // ���� ���н� �ٷ� ����
			{
				NewItemInfo->Death();
			}
		}
	}
}

void InventoryView::ItemArrangementOn(int _TileIndex, InvTabType _InvTabType)
{
	// ���콺�� �����Ǿ� �����۷����� ���� �� ��ġ�� ����

	// 1. ���� ���콺�� ����ִ� �������� �ؽ��ĸ��� �����´�.
	std::string InvItemName = GlobalValue::CurMouse->GetHoldItemName();
	size_t DotFindIndex = InvItemName.find('.');
	InvItemName = InvItemName.substr(0, DotFindIndex);

	// 2. ��� ������ �������� �ش� ������������ ã�Ƴ���.
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(InvItemName, CurItemInfo))
	{
		// 3. ã�Ҵٸ� ���� �������� ������ �ǿ� ���� ó������
		if (InvTabType::EQUIP == _InvTabType)
		{
			// ��ġ�Ϸ��� �������� �κ� ��� ������ �����̶��
			int Cnt = static_cast<int>(InvArrItemList_.size());

			// 1) ��ġ�Ϸ��� ���������� ���� �� ������Ͽ� �߰�
			// ��, �������� ���������� �ǰ� �ٸ��� "~�� �� ����" ���� ��� �� ����
			//   Ex) ���� �������ε� ����â�� �����Ϸ����ϸ� ������ �����ʾƾ���
			ItemLocType LocType = static_cast<ItemLocType>(_TileIndex);
			if (LocType != CurItemInfo.ItemLocType)
			{
				// ���� ��� - "~�� �� ����"



				return;
			}

			std::string ItemName = CurItemInfo.ItemName_abbreviation;
			float4 RenderPos = InvEquipInfo_[static_cast<int>(LocType)]->GetTilePos();

			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(Cnt, static_cast<int>(LocType), LocType, ItemName, RenderPos, true))
			{
				// ������� �߰�
				InvArrItemList_.push_back(NewItemInfo);

				// 2) ���콺 Put Down(�����۳�������)
				GlobalValue::CurMouse->ItemPutDown();

				// 3) ��ġ�Ϸ��� ĭ(Ÿ��)�� Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();
				NewItemInfo->On();

				// 4) ������ �������¿� ���� �÷��̾� ��Ʈ�� ������ ����
				EquipItemCheck(LocType, ItemName, true);
			}
			else
			{
				// ���� ���� ���н� �ٷ� ���δ�.
				NewItemInfo->Death();
			}
		}
		else
		{
			// ��ġ�Ϸ��� �������� �κ� �ϴ� ������ �����̶��
			int Cnt = static_cast<int>(InvArrItemList_.size());

			// �ش� �������� �����ϴ� ĭ��(Ÿ�� �ε���(����/����))�� üũ�Ѵ�.
			int StartIndex = _TileIndex;
			int WidthSize = CurItemInfo.WidthSize;
			int HeightSize = CurItemInfo.HeightSize;

			// ������ ��ġŸ�� ����(�ϴ� ������Ÿ������ ����)
			CurItemInfo.ItemLocType = ItemLocType::Inven_Bottom;

			if (1 == WidthSize && 1 == HeightSize)
			{
				// �����۷����� ũ�Ⱑ 1x1�̸� �ش� Ÿ���ε����� Ȱ��ȭ�Ǹ鼭 ������ ��ġ
				std::string ItemName = CurItemInfo.ItemName_abbreviation;

				ItemLocType LocType = CurItemInfo.ItemLocType;
				float4 RenderPos = InvStoreInfo_[_TileIndex]->GetTilePos();
				InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
				if (true == NewItemInfo->CreateItemInfo(Cnt, _TileIndex, LocType, ItemName, RenderPos, true))
				{
					// ���� ���� ������ 

					// ������Ͽ� �ش� ���������� �߰�
					InvArrItemList_.push_back(NewItemInfo);

					// ���콺 Put Down(�����۳�������)
					GlobalValue::CurMouse->ItemPutDown();

					// �ش� �������� ������ũ��(�����ϴ�Ÿ��ĭ��)�� ���� �ش��ϴ� ��� Ÿ��(ĭ)�� Flag On
					InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOn();

					NewItemInfo->On();
				}
				else
				{
					// ���� ���� ���н� �ٷ� ���δ�.
					NewItemInfo->Death();
				}
			}
			else
			{
				// �������� �����ϴ� ĭ���� ���� 1��, ���� 1���� �ƴ϶��
				// �浹�� Ÿ���ε��� ���� ��ġ������ Ÿ���� �����ϴ��� Ž���Ͽ�
				// ��ġ������ Ÿ���� �����Ѵٸ� �ش� Ÿ�ϸ���� �����Ѵ�.
				// ��, ��ġ������ Ÿ���� ���������ʴٸ� �ش� �������� ��ġ��ų�� ����.

				// ��ȿī��Ʈ�� �̿��Ͽ� �����۹�ġ �ε������ ����
				// ��, ���� ���н� ������ ��ġ�Ұ�
				std::vector<int> TileArrIndexList;
				TileArrIndexList.clear();

				// �ش� �������� �ʺ�/���� �ε����� �����´�.
				int StartIndex = _TileIndex;
				int WidthSize = CurItemInfo.WidthSize;
				int HeightSize = CurItemInfo.HeightSize;
				int InvTileCnt = static_cast<int>(InvStoreInfo_.size());

				// ����Ÿ���� ���� Ÿ���ΰ��
				if (StartIndex % 10 == 0)
				{
					// ���� �����̸鼭 ��� Ÿ���ΰ��
					if (30 <= StartIndex && StartIndex <= 39)
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l - (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex + l - (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
					}
					// ���� �����̸鼭 �ϴ� Ÿ���ΰ��
					else if (0 <= StartIndex && StartIndex <= 9)
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex + l + (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}

					}
					// ���� �����϶� ��� Ÿ�ϰ˻�
					else
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = -1; k < HeightSize - 1; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = -1; k < HeightSize - 1; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex + l + (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
					}
				}
				// ����Ÿ���� ���� Ÿ���ΰ��
				else if (StartIndex % 10 == 9)
				{
					// ���� �����̸鼭 ��� Ÿ���ΰ��
					if (30 <= StartIndex && StartIndex <= 39)
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l - (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex - l - (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
					}
					// ���� �����̸鼭 �ϴ� Ÿ���ΰ��
					else if (0 <= StartIndex && StartIndex <= 9)
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex - l + (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
					}
					// ���� �����϶� �´� Ÿ�ϰ˻�
					else
					{
						// ���� �ε��� ��� �˻�
						bool ChkFlag = false;
						for (int k = -1; k < HeightSize - 1; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == ChkFlag)
						{
							for (int k = -1; k < HeightSize - 1; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex - l + (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
					}
				}
				// �� ��찡 �ƴѰ��
				else
				{
					// �»�� �˻�
					// StartIndex�� ���� ���ϴ� Ÿ���ε����� �ȴ�.
					bool LeftTop = false;
					for (int k = 0; k < HeightSize; ++k)
					{
						for (int l = 0; l < WidthSize; ++l)
						{
							int CalcIndex = StartIndex - l + (k * 10);
							if (0 <= CalcIndex && CalcIndex < 40)
							{
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
									LeftTop = true;
									break;
								}
							}
							else
							{
								LeftTop = true;
								break;
							}
						}

						if (true == LeftTop)
						{
							break;
						}
					}

					// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
					if (false == LeftTop)
					{
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l + (k * 10);
								TileArrIndexList.push_back(CalcIndex);
							}
						}
					}
					else // �»�� ���н�
					{
						// ��� �˻�
						// StartIndex�� �߾��ϴ� Ÿ���ε����� �ȴ�.
						bool Top = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = -1; l < WidthSize - 1; ++l)
							{
								int CalcIndex = StartIndex + l + (k * 10);
								if (0 <= CalcIndex && CalcIndex < 40)
								{
									if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
									{
										// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
										Top = true;
										break;
									}
								}
								else
								{
									Top = true;
									break;
								}
							}

							if (true == Top)
							{
								break;
							}
						}

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
						if (false == Top)
						{
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = -1; l < WidthSize - 1; ++l)
								{
									int CalcIndex = StartIndex + l + (k * 10);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
						else // ��ܹ�ġ ���н�
						{
							// ���� �˻�
							// StartIndex�� ���� ���ϴ� Ÿ���ε����� �ȴ�.
							bool RightTop = false;
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = 0; l < WidthSize; ++l)
								{
									int CalcIndex = StartIndex + l + (k * 10);
									if (0 <= CalcIndex && CalcIndex < 40)
									{
										if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
										{
											// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
											RightTop = true;
											break;
										}
									}
									else
									{
										RightTop = true;
										break;
									}
								}

								if (true == RightTop)
								{
									break;
								}
							}

							// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
							if (false == RightTop)
							{
								for (int k = 0; k < HeightSize; ++k)
								{
									for (int l = 0; l < WidthSize; ++l)
									{
										int CalcIndex = StartIndex + l + (k * 10);
										TileArrIndexList.push_back(CalcIndex);
									}
								}
							}
							else // ���� ���н�
							{
								// ��� �˻�
								// StartIndex�� �����´� Ÿ���ε����� �ȴ�.
								bool Right = false;
								for (int k = -1; k < HeightSize - 1; ++k)
								{
									for (int l = 0; l < WidthSize; ++l)
									{
										int CalcIndex = StartIndex + l + (k * 10);
										if (0 <= CalcIndex && CalcIndex < 40)
										{
											if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
											{
												// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
												Right = true;
												break;
											}
										}
										else
										{
											Right = true;
											break;
										}
									}

									if (true == Right)
									{
										break;
									}
								}

								// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
								if (false == Right)
								{
									for (int k = -1; k < HeightSize - 1; ++k)
									{
										for (int l = 0; l < WidthSize; ++l)
										{
											int CalcIndex = StartIndex + l + (k * 10);
											TileArrIndexList.push_back(CalcIndex);
										}
									}
								}
								else // ��� ���н�
								{
									// ���ϴ� �˻�
									// StartIndex�� ���� �»�� Ÿ���ε����� �ȴ�.
									bool RightBot = false;
									for (int k = 0; k < HeightSize; ++k)
									{
										for (int l = 0; l < WidthSize; ++l)
										{
											int CalcIndex = StartIndex + l - (k * 10);
											if (0 <= CalcIndex && CalcIndex < 40)
											{
												if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
												{
													// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
													RightBot = true;
													break;
												}
											}
											else
											{
												RightBot = true;
												break;
											}
										}

										if (true == RightBot)
										{
											break;
										}
									}

									// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
									if (false == RightBot)
									{
										for (int k = 0; k < HeightSize; ++k)
										{
											for (int l = 0; l < WidthSize; ++l)
											{
												int CalcIndex = StartIndex + l - (k * 10);
												TileArrIndexList.push_back(CalcIndex);
											}
										}
									}
									else // ���ϴ� ���н�
									{
										// �ϴ� �˻�
										// StartIndex�� ���� ���ͻ�� Ÿ���ε����� �ȴ�.
										bool Bot = false;
										for (int k = 0; k < HeightSize; ++k)
										{
											for (int l = -1; l < WidthSize - 1; ++l)
											{
												int CalcIndex = StartIndex + l - (k * 10);
												if (0 <= CalcIndex && CalcIndex < 40)
												{
													if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
													{
														// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
														Bot = true;
														break;
													}
												}
												else
												{
													Bot = true;
													break;
												}
											}

											if (true == Bot)
											{
												break;
											}
										}

										// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
										if (false == Bot)
										{
											for (int k = 0; k < HeightSize; ++k)
											{
												for (int l = -1; l < WidthSize - 1; ++l)
												{
													int CalcIndex = StartIndex + l - (k * 10);
													TileArrIndexList.push_back(CalcIndex);
												}
											}
										}
										else // �ϴܽ��н�
										{
											// ���ϴ� �˻�
											// StartIndex�� ���� ���� Ÿ���ε����� �ȴ�.
											bool LeftBot = false;
											for (int k = 0; k < HeightSize; ++k)
											{
												for (int l = 0; l < WidthSize; ++l)
												{
													int CalcIndex = StartIndex - l - (k * 10);
													if (0 <= CalcIndex && CalcIndex < 40)
													{
														if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
														{
															// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
															LeftBot = true;
															break;
														}
													}
													else
													{
														LeftBot = true;
														break;
													}
												}

												if (true == LeftBot)
												{
													break;
												}
											}

											// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
											if (false == LeftBot)
											{
												for (int k = 0; k < HeightSize; ++k)
												{
													for (int l = 0; l < WidthSize; ++l)
													{
														int CalcIndex = StartIndex - l - (k * 10);
														TileArrIndexList.push_back(CalcIndex);
													}
												}
											}
											else // ���ϴܽ��н�
											{
												// �´� �˻�
												// StartIndex�� ���� ���Ϳ�� Ÿ���ε����� �ȴ�.
												bool Left = false;
												for (int k = 0; k < HeightSize; ++k)
												{
													for (int l = 0; l < WidthSize; ++l)
													{
														int CalcIndex = StartIndex - l - (k * 10);
														if (0 <= CalcIndex && CalcIndex < 40)
														{
															if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
															{
																// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
																Left = true;
																break;
															}
														}
														else
														{
															Left = true;
															break;
														}
													}

													if (true == Left)
													{
														break;
													}
												}

												// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
												if (false == Left)
												{
													for (int k = 0; k < HeightSize; ++k)
													{
														for (int l = 0; l < WidthSize; ++l)
														{
															int CalcIndex = StartIndex - l - (k * 10);
															TileArrIndexList.push_back(CalcIndex);
														}
													}
												}
												else // �´ܽ��н�
												{
													// ����
													// StartIndex�� ���� Ÿ���ε����� �ȴ�.
													bool Center = false;
													for (int k = -1; k < HeightSize - 1; ++k)
													{
														for (int l = -1; l < WidthSize - 1; ++l)
														{
															int CalcIndex = StartIndex + l + (k * 10);
															if (0 <= CalcIndex && CalcIndex < 40)
															{
																if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
																{
																	// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
																	Center = true;
																	break;
																}
															}
															else
															{
																Center = true;
																break;
															}
														}

														if (true == Center)
														{
															break;
														}
													}

													// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
													if (false == Center)
													{
														for (int k = -1; k < HeightSize - 1; ++k)
														{
															for (int l = -1; l < WidthSize - 1; ++l)
															{
																int CalcIndex = StartIndex + l + (k * 10);
																TileArrIndexList.push_back(CalcIndex);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
				
				// ��ġ������ Ÿ���� �����Ͽ� �ε��� ����� �����Ǿ��ٸ�
				if (false == TileArrIndexList.empty())
				{
					// ���������� ���� ����
					InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();

					// ��ġ �ε��� ��� ����
					std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

					// ������ ��ġ �ε������ ������������ ����
					NewItemInfo->SetTileIndexList(TileArrIndexList);

					// �������� ������ ���� ����
					std::string ItemName = CurItemInfo.ItemName_abbreviation;
					ItemLocType LocType = ItemLocType::Inven_Bottom;

					// ���������� Ÿ�������� �̿��Ͽ� ������ ����

					float4 RenderPos = InvStoreInfo_[_TileIndex]->GetTilePos();
					if (true == NewItemInfo->CreateItemInfo(Cnt, _TileIndex, LocType, ItemName, RenderPos, true))
					{
						// ���� ���� ������
						
						// 1. �ε�������� �ݺ��ϸ�, �����۹�ġ Flag On
						int IndexCnt = static_cast<int>(TileArrIndexList.size());
						for (int i = 0; i < IndexCnt; ++i)
						{
							InvStoreInfo_[TileArrIndexList[i]]->SetItemArrangeFlagOn();
						}

						// 2. ������ ��ġ ��ġ ���� �� ������
						float4 ReRenderPos = float4(33.f, -116.f);	// �ʱⰪ ����(0���ε����ΰ��)

						// �����ϰ��ִ� ĭ�� �߾� ��ġ�� ����Ѵ�.
						// ù��° Ÿ���� ��ġ�� ��������° Ÿ���� ��ġ�� Get
						float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
						float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

						// �� Ÿ�� ��ġ�� ��
						if (BeginTilePos.x == EndTilePos.x) // �ش� �������� �ʺ� 1
						{
							ReRenderPos.x = BeginTilePos.x;
						}
						else
						{
							BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
							ReRenderPos.x = BeginTilePos.x;
						}

						if (BeginTilePos.y == EndTilePos.y) // �ش� �������� ���� 1
						{
							ReRenderPos.y = BeginTilePos.y;
						}
						else
						{
							BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
							ReRenderPos.y = BeginTilePos.y;
						}

						NewItemInfo->SetItemRenderPos(ReRenderPos);
						NewItemInfo->On();

						// ��� ���� ���� ������ ������Ͽ� �ش� ���������� �߰�
						InvArrItemList_.push_back(NewItemInfo);

						// ���콺 Put Down(�����۳�������)
						GlobalValue::CurMouse->ItemPutDown();
					}
					else
					{
						// �������� ���н� �������������� �ٷ� ����
						NewItemInfo->Death();
						return;
					}
				}
				else
				{
					// ������ ����� ���ٸ� �ٷ� Ŭ����
					TileArrIndexList.clear();
				}
			}
		}
	}
}

void InventoryView::ItemArrangementOff(int _TileIndex, InvTabType _InvTabType)
{
	// ���콺�� �����Ǿ� �����۷����� ���� �� ��ġ���� ��������

	// 1. �����۸�Ͽ��� �ش� �������� ã�Ƴ���.
	int ItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ItemListCnt; ++i)
	{
		if (InvTabType::EQUIP == _InvTabType)
		{
			// �������� ����ĭ�� ��ġ(ItemLocType)�ε����� ã�Ƴ�
			if (_TileIndex == InvArrItemList_[i]->GetLocTypeInt())
			{
				// �������� �ش� ĭ�� Flag ����
				int Index = InvArrItemList_[i]->GetLocTypeInt();
				InvEquipInfo_[Index]->SetItemArrangeFlagOff();

				// ���� �÷��̾��� �ִϸ��̼��� LIT_ ������ ������ ������Ȳ�� �ƴ϶��
				// �ش� ������Ʈ�� �÷��̾� �ִϸ��̼��� HVY_ -> LIT_ ���·� ��ȯ
				std::string ItemName = InvArrItemList_[i]->GetItemName();
				ItemLocType LocType = InvArrItemList_[i]->GetLocType();
				EquipItemCheck(LocType, ItemName, false);

				// ���콺 ����
				std::string TextureName = InvArrItemList_[i]->GetTextureName();
				float4 RenderScale = InvArrItemList_[i]->GetRenderScale();
				GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

				// �÷��̾��� ������ ������Ͽ��� �ش� ������ ����
				MainPlayerInfomation::GetInst().PlayerItemDel(ItemName, LocType, _TileIndex);

				// �ش� ������ Death ó��
				InvArrItemList_[i]->Death();

				// ��ġ�����۸�Ͽ��� �ش� ������ ����
				std::vector<InvArrangementItemInfo*>::iterator DelIter = InvArrItemList_.begin() + i;
				if (InvArrItemList_.end() != DelIter)
				{
					InvArrItemList_.erase(DelIter);
					break;
				}

				break;
			}
		}
		else
		{
			// �κ�â �ϴ� �������϶�
			// Ÿ���ε���
			if (false == InvArrItemList_[i]->GetItemIndexListEmpty())
			{
				// �ε��� ����� ������ ��� : �ش� �������� �ε��� ����� �˻� true�̰�, �ش� ������ ��ġ�� �κ� �ϴ� �����ǿ� �־�����
				if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex) && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
				{
					// �����Ѵٸ� �ش� �������� �����ϴ� ��� Ÿ��(ĭ)�� Flag Off ó��
					std::vector<int> IndexList = InvArrItemList_[i]->GetItemArrIndexList();
					int ListCnt = static_cast<int>(IndexList.size());
					for (int i = 0; i < ListCnt; ++i)
					{
						InvStoreInfo_[IndexList[i]]->SetItemArrangeFlagOff();
					}

					// �ش� �������� ã�Ҵٸ� �κ�â�� �����ϴ� �����۸�Ͽ��� ���ŵǰ�,
					// ���� ���θ��콺�� �������� ��������.
					std::string TextureName = InvArrItemList_[i]->GetTextureName();
					float4 RenderScale = InvArrItemList_[i]->GetRenderScale();

					// ���콺�� �ش� �������� ���
					GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

					// �÷��̾��� ������ ������Ͽ��� �ش� ������ ����
					MainPlayerInfomation::GetInst().PlayerItemDel(InvArrItemList_[i]->GetItemName(), InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

					// �ش� ������ Death ó��
					InvArrItemList_[i]->Death();

					// ��ġ�����۸�Ͽ��� �ش� ������ ����
					std::vector<InvArrangementItemInfo*>::iterator DelIter = InvArrItemList_.begin() + i;
					if (InvArrItemList_.end() != DelIter)
					{
						InvArrItemList_.erase(DelIter);
						break;
					}
				}
			}
			else
			{
				// �ε��� ����� ������������ ��� : �ش� Ÿ���ε����� Flag ���� �� ���콺 ����
				if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex() && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
				{
					// �������� �����۷����� ũ�⿡ ���� �ٸ�
					float4 ArrangeSize = InvArrItemList_[i]->GetArrangeItemSize();
					int TileIndex = InvArrItemList_[i]->GetStartTileIndex();
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOff();

					// �ش� �������� ã�Ҵٸ� �κ�â�� �����ϴ� �����۸�Ͽ��� ���ŵǰ�,
					// ���� ���θ��콺�� �������� ��������.
					std::string TextureName = InvArrItemList_[i]->GetTextureName();
					float4 RenderScale = InvArrItemList_[i]->GetRenderScale();

					// ���콺�� �ش� �������� ���
					GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

					// �÷��̾��� ������ ������Ͽ��� �ش� ������ ����
					MainPlayerInfomation::GetInst().PlayerItemDel(InvArrItemList_[i]->GetItemName(), InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

					// �ش� ������ Death ó��
					InvArrItemList_[i]->Death();

					// ��ġ�����۸�Ͽ��� �ش� ������ ����
					std::vector<InvArrangementItemInfo*>::iterator DelIter = InvArrItemList_.begin() + i;
					if (InvArrItemList_.end() != DelIter)
					{
						InvArrItemList_.erase(DelIter);
						break;
					}
				}
			}
		}
	}
}

void InventoryView::ItemSellProcess(int _TileIndex, InvTabType _InvTabType, NPCType _BuySellType)
{
	// �Ǹ�ó��
	std::string SellItemName;

	// �Ǹ��Ϸ��� �������� Ÿ���� �˾Ƴ���.
	if (InvTabType::NORMAL == _InvTabType)
	{
		// �κ�â �ϴܺ������� ������(_TileIndex == ��ġ�� Ÿ���� �����ε���)
		// ��, ������ ũ�Ⱑ 1x1�̸� �����ε����� �˻��Ͽ� �������̸��� ã�Ƴ���
		// �ƴ϶�� �ش� �������� �����ϴ� ��� �ε�������� �˻��Ͽ� �������̸��� ã�Ƴ���.
		int Cnt = static_cast<int>(InvArrItemList_.size());
		for (int i = 0; i < Cnt; ++i)
		{
			if (ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
			{
				// �ش� ������ ��ġ�ε�������� ����ִ°��
				if (true == InvArrItemList_[i]->GetItemIndexListEmpty())
				{
					// �ش� �������� �����ε����� ���� �浹�� Ÿ���ε����� �����ϸ� �ش� �������� ã��
					if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
					{
						SellItemName = InvArrItemList_[i]->GetItemName();
						break;
					}
				}
				else // �ش� ������ ��ġ�ε��� ����� �����ϴ� ���
				{
					// �ش� �������� �ε�����Ͽ� ���� �浹�� Ÿ���ε����� �����ϸ� �ش� �������� ã��
					if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex))
					{
						SellItemName = InvArrItemList_[i]->GetItemName();
						break;
					}
				}
			}
		}
	}
	else if (InvTabType::EQUIP == _InvTabType)
	{
		// �κ�â ����������� ������(_TileIndex == ��ġ�� ����ĭ�� �ε���)
		ItemLocType LocType = static_cast<ItemLocType>(_TileIndex);
		
		int Cnt = static_cast<int>(InvArrItemList_.size());
		for (int i = 0; i < Cnt; ++i)
		{
			if (LocType == InvArrItemList_[i]->GetLocType() && _TileIndex == InvArrItemList_[i]->GetStartTileIndex())
			{
				SellItemName = InvArrItemList_[i]->GetItemName();
				break;
			}
		}

		if (true == SellItemName.empty())
		{
			// ������ ã�� ����!!!!
			return;
		}
	}

	// �������� ã�����Ƿ� �ش� �������� �Ǹ��ϱ� ���� ���� Get
	ItemList SellItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindName(SellItemName, SellItemInfo))
	{
		// ������ ã�Ҵٸ� �Ǹ� ó�� ����

		switch (_BuySellType)
		{
			case NPCType::PotionShop:
			{
				// �Ǹ��Ϸ��� �������� ����/���̸� NPC�� ������常 ����
				if (!(16 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 18))
				{
					// NPC�� ������� ���� ��
					GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(SellItemInfo.Price);

					// �κ��丮���� �ش� ������ ����
					int Cnt = static_cast<int>(InvArrItemList_.size());
					for (int i = 0; i < Cnt; ++i)
					{
						if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName())
						{
							// 1. �ش� ���������� ��ġ�ϴ� ��ġ�� �˾Ƴ���.
							if (InvTabType::NORMAL == _InvTabType)
							{
								// 2. �ش� ��� �������� ���� ��ġ�� �κ�â �ϴ� �������̿��ٸ�
								//    �ش� �������� ũ�⸦ �˾Ƴ���.
								float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
								if (ItemSize.x == 1 && ItemSize.y == 1) // ������ũ�Ⱑ 1x1�϶�
								{
									if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
									{
										InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

										// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// �÷��̾��� ������� ����
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// �κ�â ������Ͽ��� �ش� �������� ����
										InvArrItemList_[i]->Death();
										std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
										InvArrItemList_.erase(FindIter);
										break;
									}
								}
								else // ������ũ�Ⱑ 1x1�� �ƴҶ�
								{
									if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex))
									{
										// �������� �����ϴ� �ε������ Get
										std::vector<int> ItemArrIndexs = InvArrItemList_[i]->GetItemArrIndexList();
										int IndexCnt = static_cast<int>(ItemArrIndexs.size());
										for (int k = 0; k < IndexCnt; ++k)
										{
											// �����ü Ÿ���ε��� Flag ����
											InvStoreInfo_[ItemArrIndexs[k]]->SetItemArrangeFlagOff();
										}

										// �÷��̾��� ������� ����
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// �κ�â ������Ͽ��� �ش������ ����
										InvArrItemList_[i]->Death();
										std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
										InvArrItemList_.erase(FindIter);
										break;
									}
								}
							}
							else if (InvTabType::EQUIP == _InvTabType)
							{
								// 2. �ش� ��� �������� ���� ��ġ�� �κ�â ��� �������̿��ٸ�
								//    LocType == _TileIndex �̹Ƿ� �ش� �����Ǹ� Flag ����
								if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
								{
									InvEquipInfo_[_TileIndex]->SetItemArrangeFlagOff();

									// �÷��̾��� ������� ����
									GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

									// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
									MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

									// �κ�â ������Ͽ��� �ش� �������� ����
									InvArrItemList_[i]->Death();
									std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
									InvArrItemList_.erase(FindIter);
								
									break;
								}
							}

							break;
						}
					}
				}
				else
				{
					// NPC�� �Ǹ�â ������Ͽ� �ش� �Ǹž����� ���翩�� üũ �� �����Ѵٸ� �ش������ ���������� ����, �ƴ϶�� �ش� ������ ��ġ
					if (true == GlobalValue::ChandleryNPC->GetChandleryShop()->SellItemCheck(SellItemInfo.ItemName_abbreviation_Inven))
					{
						// �ش� ������ �κ��丮��ġ��Ͽ��� ����, �÷��̾� ���������۸�� ���� �� �÷��̾ ������ ��差 ����
						int Cnt = static_cast<int>(InvArrItemList_.size());
						for (int i = 0; i < Cnt; ++i)
						{
							if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName() && 
								_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
							{
								// ��ȭ�� �������̹Ƿ� �׻� �κ�â�ϴ� �����ǿ� ����

								// �������� �ʺ�/���� Get
								float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
								if (ItemSize.x == 1 && ItemSize.y == 1) // ItemSize = 1x1
								{
									InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

									// �÷��̾��� ������� ����
									GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

									// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
									MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

									// �κ�â ������Ͽ��� �ش� �������� �����ϰ�,
									InvArrItemList_[i]->Death();
									std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
									InvArrItemList_.erase(FindIter);
									break;
								}

								break;
							}
						}
					}
				}
				break;
			}
			case NPCType::WeaponShop:
			{
				// �Ǹ��Ϸ��� �������� ��ȭ�̸� NPC�� ������常 ����
				if (16 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 18)
				{
					// ��ȭ�̸� NPC�� ��差�� ���ҽ�Ű��,
					GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(SellItemInfo.Price);

					// �ش� �������� ��ȭŸ���̱⶧���� �׻� �κ�â �ϴ� �����ǿ� ����
					int Cnt = static_cast<int>(InvArrItemList_.size());
					for (int i = 0; i < Cnt; ++i)
					{
						if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName() &&
							_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
						{
							// ��ȭ�� �������̹Ƿ� �׻� �κ�â�ϴ� �����ǿ� ����

							// �������� �ʺ�/���� Get
							float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
							if (ItemSize.x == 1 && ItemSize.y == 1) // ItemSize = 1x1
							{
								InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

								// �÷��̾��� ������� ����
								GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

								// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
								MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

								// �κ�â ������Ͽ��� �ش� �������� �����ϰ�,
								InvArrItemList_[i]->Death();
								std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
								InvArrItemList_.erase(FindIter);
								break;
							}

							break;
						}
					}
				}
				else
				{
					// NPC�� �Ǹ�â ������Ͽ� �ش� �Ǹž����� ���翩�� üũ �� �����Ѵٸ� �ش������ ���������� ����, �ƴ϶�� �ش� ������ ��ġ
					if (true == GlobalValue::WeaponNPC->GetWeaponShop()->SellItemCheck(SellItemInfo.ItemName_abbreviation_Inven))
					{
						int Cnt = static_cast<int>(InvArrItemList_.size());
						for (int i = 0; i < Cnt; ++i)
						{
							if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName())
							{
								// 1. �ش� ������� ������ ��ġ�ϰ��ִ� ���� �˾Ƴ���.
								if (InvTabType::NORMAL == _InvTabType)
								{
									// 2. �ش� ��� �������� ���� ��ġ�� �κ�â �ϴ� �������̿��ٸ�
									//    �ش� �������� ũ�⸦ �˾Ƴ���.
									float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
									if (ItemSize.x == 1 && ItemSize.y == 1) // ������ũ�Ⱑ 1x1�϶�
									{
										if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
										{
											InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

											// �÷��̾��� ������� ����
											GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

											// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
											MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

											// �κ�â ������Ͽ��� �ش� �������� ����
											InvArrItemList_[i]->Death();
											std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
											InvArrItemList_.erase(FindIter);
											break;
										}
									}
									else // ������ũ�Ⱑ 1x1�� �ƴҶ�
									{
										if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex))
										{
											// �������� �����ϴ� �ε������ Get
											std::vector<int> ItemArrIndexs = InvArrItemList_[i]->GetItemArrIndexList();
											int IndexCnt = static_cast<int>(ItemArrIndexs.size());
											for (int k = 0; k < IndexCnt; ++k)
											{
												// �����ü Ÿ���ε��� Flag ����
												InvStoreInfo_[ItemArrIndexs[k]]->SetItemArrangeFlagOff();
											}

											// �÷��̾��� ������� ����
											GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

											// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
											MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

											// �κ�â ������Ͽ��� �ش������ ����
											InvArrItemList_[i]->Death();
											std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
											InvArrItemList_.erase(FindIter);
											break;
										}
									}
								}
								else if (InvTabType::EQUIP == _InvTabType)
								{
									// 2. �ش� ��� �������� ���� ��ġ�� �κ�â ��� �������̿��ٸ�
									//    LocType == _TileIndex �̹Ƿ� �ش� �����Ǹ� Flag ����
									if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
									{
										InvEquipInfo_[_TileIndex]->SetItemArrangeFlagOff();

										// �÷��̾��� ������� ����
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// ���� �÷��̾� ������ ������Ͽ��� �ش� ������ ����
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// �κ�â ������Ͽ��� �ش� �������� ����
										InvArrItemList_[i]->Death();
										std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
										InvArrItemList_.erase(FindIter);
										break;
									}
								}
							}
						}
					}
				}
				break;
			}
		}
	}
	else
	{
		// ����ã�⸦ �����ߴٸ� �ش� ������ �Ǹ�ó�� �ߴ�
		return;
	}
}

void InventoryView::ItemRepairProcess(int _TileIndex, InvTabType _InvTabType)
{
	// ��������� �Ǹ�â���� ó������(����ó��)
	
	// �浹�� �������� �������� �����Ѵٸ� �ش� ������ ȸ�� ��


	// �÷��̾��� ������差�� �����ϰ�,


	// NPC�� ������尡 �����Ѵ�.


}

bool InventoryView::InventoryArrangeTileCheckOn(const float4& _ItemScaleIndex, const std::string& _ItemName)
{
	bool OneSizeItem = false;

	int StartIndex = -1;
	int StoreCnt = static_cast<int>(InvStoreInfo_.size());
	int CheckStart = -1;

// Goto������� ����� �����ȳ�!!!!! �ϴ� goto������ ��˻�ó���س��� ���� ����غ�
ArrangeTileCheck:

	++CheckStart;
	for (int i = CheckStart; i < StoreCnt; ++i)
	{
		if (false == InvStoreInfo_[i]->GetIsItemArrangeFlag())
		{
			StartIndex = i;
			break;
		}
	}

	if (-1 == StartIndex)
	{
		return false;
	}

	// ��ĭ ����� �˻�(1x1ũ���̸� ��ĭ�˻� ����)
	int ItemWidth = _ItemScaleIndex.ix();
	int ItemHeight = _ItemScaleIndex.iy();
	if (ItemWidth == 1 && ItemHeight == 1)
	{
		// StartIndex�� ����ϹǷ� üũ ���ʿ�
		OneSizeItem = true;
	}
	else
	{
		// StartIndex�� �����ϴ� �ε������ ��� �˻�
		for (int y = 0; y < ItemHeight; ++y)
		{
			for (int x = 0; x < ItemWidth; ++x)
			{
				int Index = StartIndex + x + (y * 10);
				if (0 <= Index && Index < 40)
				{
					if (true == InvStoreInfo_[Index]->GetIsItemArrangeFlag())
					{
						// goto������ص���???
						goto ArrangeTileCheck;
					}
				}
				else
				{
					// ��� Ÿ�Ϲ�ġ�� �˻��Ͽ� ���н�
					return false;
				}
			}
		}
	}

	// ���� ��� ���ǿ� �ش������ʴ´ٸ� �ش� ������ ��ġ�����ϹǷ� �κ��丮�� �ش� ������ ��ġ

	// 1. ������ ���� Get
	ItemList BuyItem = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(_ItemName, BuyItem))
	{
		// �ش� ������ ��ġ ���� ����
		BuyItem.StartPosition = StartIndex;
		BuyItem.ItemLocType = ItemLocType::Inven_Bottom;

		// ������ ã�����Ƿ� �ش� ������������ �κ��丮 ��ġ ������ ��Ͽ� �߰�(�׻� �ϴܺ��������� ��ġ����)
		int ListCnt = static_cast<int>(InvArrItemList_.size());
		ItemLocType LocType = ItemLocType::Inven_Bottom;
		float4 RenderPos = InvStoreInfo_[StartIndex]->GetTilePos();

		// ������ũ�Ⱑ 1x1�̸�
		if (true == OneSizeItem)
		{
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(ListCnt, StartIndex, LocType, BuyItem.ItemName_abbreviation, RenderPos, true))
			{
				// StartIndex�� �����ϴ� ������ ��ġ
				InvStoreInfo_[StartIndex]->SetItemArrangeFlagOn();

				// �κ�â�� Ȱ��ȭ�Ǿ��ִٸ� ������ On���·� ��ȯ
				NewItemInfo->On();

				// ��Ͽ� �ش� ������ �߰�
				InvArrItemList_.push_back(NewItemInfo);
			}
			else
			{
				NewItemInfo->Death();
			}
		}
		else
		{
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(ListCnt, StartIndex, LocType, BuyItem.ItemName_abbreviation, RenderPos, true))
			{
				// �ε��� ����� ��� �����ϴ� ������ ��ġ
				std::vector<int> TileArrIndexList;
				TileArrIndexList.clear();

				for (int k = 0; k < ItemHeight; ++k)
				{
					for (int l = 0; l < ItemWidth; ++l)
					{
						int CalcIndex = StartIndex + l + (k * 10);
						if (0 <= CalcIndex && CalcIndex < 40)
						{
							TileArrIndexList.push_back(CalcIndex);
						}
					}
				}

				// ��ġ��� ����
				std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

				// �����ϰ��ִ� ĭ�� �߾� ��ġ�� ����Ѵ�.
				// ù��° Ÿ���� ��ġ�� ��������° Ÿ���� ��ġ�� Get
				float4 ReRenderPos = float4::ZERO;
				int IndexCnt = static_cast<int>(TileArrIndexList.size());
				float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
				float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

				// �� Ÿ�� ��ġ�� ��
				if (BeginTilePos.x == EndTilePos.x) // �ش� �������� �ʺ� 1
				{
					ReRenderPos.x = BeginTilePos.x;
				}
				else
				{
					BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
					ReRenderPos.x = BeginTilePos.x;
				}

				if (BeginTilePos.y == EndTilePos.y) // �ش� �������� ���� 1
				{
					ReRenderPos.y = BeginTilePos.y;
				}
				else
				{
					BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
					ReRenderPos.y = BeginTilePos.y;
				}

				NewItemInfo->SetItemRenderPos(ReRenderPos);

				// ������ ���� Flag On
				for (int l = 0; l < IndexCnt; ++l)
				{
					InvStoreInfo_[TileArrIndexList[l]]->SetItemArrangeFlagOn();
				}
				NewItemInfo->SetTileIndexList(TileArrIndexList);

				// �κ�â�� Ȱ��ȭ�Ǿ��ִٸ� �����۷����� On���� ��ȯ
				NewItemInfo->On();

				// ��Ͽ� �ش� ������ �߰�
				InvArrItemList_.push_back(NewItemInfo);
			}
			else
			{
				NewItemInfo->Death();
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

void InventoryView::EquipItemCheck(ItemLocType _ItemLocType, const std::string& _ItemName, bool _OnAndOff)
{
	// ������ �����۸� ���� ó����
	if (true == _OnAndOff) // ����
	{
		// ������ �ش� �����۸� ���� �÷��̾��� ��Ʈ���������� ����ȴ�.
		// LIT_ -> HVY_
		switch (_ItemLocType)
		{
			case ItemLocType::Inven_Weapon:
			{
				// ������ �����۸��� crs�̸� HVY_ ������ȯ
				if ("crs" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Weapon);
				}
				// ������ �����۸��� wnd�̸� LIT_ ������ȯ
				else if ("wnd" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Weapon);
				}
				break;
			}
			case ItemLocType::Inven_Shield:
			{
				if ("bsh" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Shield);
				}
				break;
			}
			case ItemLocType::Inven_Helm:
			{
				if ("bhm" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Helm);
				}
				break;
			}
			case ItemLocType::Inven_Armor:
			{
				// ������ �����۸��� chn�̸� HVY_ ������ȯ
				if ("chn" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Armor);
				}
				break;
			}
			case ItemLocType::Inven_Gloves:
			{
				if ("tgl" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Gloves);
				}
				break;
			}
			case ItemLocType::Inven_Boots:
			{
				if ("hbt" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Boots);
				}
				break;
			}
		}
	}
	else // ��������
	{
		// ���������� �ش� �����۸� ���� �÷��̾��� ��Ʈ���������� ����ȴ�.
		// HVY_ -> LIT_
		switch (_ItemLocType)
		{
			case ItemLocType::Inven_Weapon:
			{
				// crs ������ LIT_Ÿ������ ���ư���.
				if ("crs" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Weapon);
				}
				break;
			}
			case ItemLocType::Inven_Shield:
			{
				if ("bsh" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Shield);
				}
				break;
			}
			case ItemLocType::Inven_Helm:
			{
				if ("bhm" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Helm);
				}
				break;
			}
			case ItemLocType::Inven_Armor:
			{
				// ���������� �����۸��� chn�̸� HVY_ ������ȯ
				if ("chn" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Armor);
				}
				break;
			}
			case ItemLocType::Inven_Gloves:
			{
				if ("tgl" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Gloves);
				}
				break;
			}
			case ItemLocType::Inven_Boots:
			{
				if ("hbt" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOff(ItemEquipPart::Inv_Boots);
				}
				break;
			}
		}
	}
}
