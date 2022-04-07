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

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"

InventoryView::InventoryView() :
	InventoryPanel_(nullptr),
	CloseButton_(nullptr),
	CloseButtonCollider_(nullptr),
	CloseButtonState_(Button_State::Normal),
	InvTabType_(InvTabType::NONE)
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

		// �ش� Ÿ���� �������� �������ְ�, ���콺�� �������� ��������ʴٸ�
		if (true == InvEquipInfo_[_Index]->GetIsItemBatch() && false == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOff(_Index, InvTabType_);
		}
		// �ش� Ÿ���� �������� �����������ʰ�, ���콺�� �������� ����ִٸ�
		else if (false == InvEquipInfo_[_Index]->GetIsItemBatch() && true == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOn(_Index, InvTabType_);
		}
		else
		{
			// �� ���ǿ� �������� �ʴٸ� ���� ���

		}
	}
}

void InventoryView::StoreTileBoxClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		InvTabType_ = InvTabType::NORMAL;

		// �ش� Ÿ���� �������� �������ְ�, ���콺�� �������� ��������ʴٸ�
		if (true == InvStoreInfo_[_Index]->GetIsItemBatch() && false == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOff(_Index, InvTabType_);
		}
		// �ش� Ÿ���� �������� �����������ʰ�, ���콺�� �������� ����ִٸ�
		else if (false == InvStoreInfo_[_Index]->GetIsItemBatch() && true == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOn(_Index, InvTabType_);
		}
		else
		{
			// �� ���ǿ� �������� �ʴٸ� ���� ���

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

	// Button Image Cutting
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

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

	Off();
}

void InventoryView::Update(float _DeltaTime)
{
#ifdef _DEBUG
	for (int i = 0; i < static_cast<int>(InvEquipCol_.size()); ++i)
	{
		GetLevel()->PushDebugRender(InvEquipCol_[i]->GetTransform(), CollisionType::Rect);
	}

	for (int i = 0; i < static_cast<int>(InvStoreCol_.size()); ++i)
	{
		GetLevel()->PushDebugRender(InvStoreCol_[i]->GetTransform(), CollisionType::Rect);
	}
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

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// �̺�â �����ư �浹üũ
	CloseButtonCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::CloseButtonClick, this, std::placeholders::_1));

#pragma endregion

#pragma region �κ�â ���/�ϴ� Ÿ�Ϲڽ� �浹üũ
	for (int i = 0; i < static_cast<int>(InvEquipCol_.size()); ++i)
	{
		InvEquipCol_[i]->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::EquipTileBoxClick, this, std::placeholders::_1, i));
	}

	for (int i = 0; i < static_cast<int>(InvStoreCol_.size()); ++i)
	{
		InvStoreCol_[i]->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::StoreTileBoxClick, this, std::placeholders::_1, i));
	}
#pragma endregion
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
				InvArrItemList_.push_back(NewItemInfo);

				// ������ �������� ũ�⿡ ���� �κ� �ϴ� �������� ĭ(Ÿ��)�� Flag On
				float4 ArrangeSize = NewItemInfo->GetArrangeTileSize();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1ĭ�� �����ϹǷ� �ش� Ÿ���ε����� Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOn();
				}
				else
				{
					// ĭ���� ���� Ÿ���ε������� �����ؼ� ����� Ÿ�ϰ�����ŭ ��� Flag Onó��

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
			if (true == NewItemInfo->CreateItemInfo(Cnt, static_cast<int>(LocType), LocType, ItemName, RenderPos))
			{
				// ������Ͽ� �ش� ������ �߰�
				InvArrItemList_.push_back(NewItemInfo);

				// 2) ���콺 Put Down(�����۳�������)
				GlobalValue::CurMouse->ItemPutDown();

				// 3) ��ġ�Ϸ��� ĭ(Ÿ��)�� Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();

				NewItemInfo->On();

				// 4) ����(wnd)�� �����ϰ� �� �Ǻ� �������������¿� ���� �÷��̾� �ִϸ��̼� ���� ��ȯ
				//    Ex) -. �����ǿ� ���� ������ �÷��̾��� �ִϸ��̼� SH ��Ʈ�� HVY_ ���°� �ȴ�.
				//        -. �����ǿ� �⺻������ wnd ���Ⱑ �����Ǿ�������, crs ����� ����Ǿ� �����Ǵ� ����
				//           �÷��̾��� �ִϸ��̼� RH ��Ʈ�� HVY_ ���°� �ȴ�.




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
			if (1 == WidthSize && 1 == HeightSize)
			{
				std::string ItemName = CurItemInfo.ItemName_abbreviation;
				ItemLocType LocType = CurItemInfo.ItemLocType;
				float4 RenderPos = InvStoreInfo_[_TileIndex]->GetTilePos();
				InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
				if (true == NewItemInfo->CreateItemInfo(Cnt, _TileIndex, LocType, ItemName, RenderPos))
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
				// �浹�� Ÿ���ε��� ���� ��,��,��,���� Ÿ���� �������¸� üũ
				// ���� �������� ��ġ�Ϸ��� Ÿ���� �����ϰų� ���������ʴٸ� ����

				//int TopCheckIndex = StartIndex - ;
				int BotCheckIndex = -1;
				// WidthSize;
				// HeightSize;

				// 1. �� �˻�
				int LeftCheckIndex = StartIndex - WidthSize;
				

				// 2. �� �˻�
				int RightCheckIndex = StartIndex + WidthSize;


				// 3. �� �˻�
				


				// 4. �� �˻�





				

			}
		}
	}
}

void InventoryView::ItemArrangementOff(int _TileIndex, InvTabType _InvTabType)
{
	// ���콺�� �����Ǿ� �����۷����� ���� �� ��ġ���� ��������

	// 1. �����۸�Ͽ��� �ش� �������� ã�Ƴ���.
	int FindItemIndex = -1;
	int ItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ItemListCnt; ++i)
	{
		if (InvTabType::EQUIP == _InvTabType)
		{
			// �������� ����ĭ�� ��ġ(ItemLocType)�ε����� ã�Ƴ�
			if (_TileIndex == InvArrItemList_[i]->GetLocTypeInt())
			{
				FindItemIndex = i;

				// �������� �ش� ĭ�� Flag ����
				int Index = InvArrItemList_[i]->GetLocTypeInt();
				InvEquipInfo_[Index]->SetItemArrangeFlagOff();

				// ���� �÷��̾��� �ִϸ��̼��� LIT_ ������ ������ ������Ȳ�� �ƴ϶��
				// �ش� ������Ʈ�� �÷��̾� �ִϸ��̼��� HVY_ -> LIT_ ���·� ��ȯ


				break;
			}
		}
		else
		{
			// �������� ����ĭ�� Ÿ���ε����� ã�Ƴ�
			if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex() && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
			{
				FindItemIndex = i;

				// �������� �����۷����� ũ�⿡ ���� �ٸ�
				float4 ArrangeSize = InvArrItemList_[i]->GetArrangeTileSize();
				int TileIndex = InvArrItemList_[i]->GetStartTileIndex();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1ĭ�� �����ϹǷ� �ش� Ÿ���ε����� Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOff();
				}
				else
				{
					// �ش� �������� ����ĭ�� �����ϰ��ִٰ� �����Ǵ°��̹Ƿ�,
					// �����ϰ��ִ� ��� ĭ�� ��ġ Flag Off ��ȯ


				}
				break;
			}
		}
	}

	// �ش� �������� ã�Ҵٸ� �κ�â�� �����ϴ� �����۸�Ͽ��� ���ŵǰ�,
	// ���� ���θ��콺�� �������� ��������.
	if (-1 != FindItemIndex)
	{
		std::string TextureName = InvArrItemList_[FindItemIndex]->GetTextureName();
		float4 RenderScale = InvArrItemList_[FindItemIndex]->GetRenderScale();
		GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

		// �ش� ������ Death ó��
		InvArrItemList_[FindItemIndex]->Death();

		// ��ġ�����۸�Ͽ��� �ش� ������ ����
		std::vector<InvArrangementItemInfo*>::iterator DelIter = InvArrItemList_.begin() + FindItemIndex;
		if (InvArrItemList_.end() != DelIter)
		{
			InvArrItemList_.erase(DelIter);
		}
	}
}
