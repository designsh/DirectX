#include "PreCompile.h"
#include "InventoryView.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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
	// ������ ��� ����
	if (false == InvArrItemList_.empty())
	{
		for (int i = 0; i < static_cast<int>(InvArrItemList_.size()); ++i)
		{
			delete InvArrItemList_[i];
			InvArrItemList_[i] = nullptr;
		}
		InvArrItemList_.clear();
	}
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
	// ���� �����Ǵ� ������ �����÷��̾������� �̿��Ͽ� �����ϰ��ִ� ������ ����� �κ�â�� ��ġ
	MainPlayerInfo CurPlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	int ItemCnt = static_cast<int>(CurPlayerInfo.ItemInfo.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		// ���������� ������ �ʿ��� ���� Get
		ItemLocType LocType = CurPlayerInfo.ItemInfo[i].ItemLocType;
		int TileIndex = CurPlayerInfo.ItemInfo[i].StartPosition;
		int Width = CurPlayerInfo.ItemInfo[i].WidthSize;
		int Height = CurPlayerInfo.ItemInfo[i].HeightSize;
		std::string ItemName = CurPlayerInfo.ItemInfo[i].ItemName_abbreviation_Inven;

		// ���� Flag Check
		bool SuccessFlag = false;

		ItemInfo* NewItemInfo = new ItemInfo();
		if (ItemLocType::Inven_Bottom == LocType)
		{
			// �������� �����ϴ� Ÿ�ϰ���(�ε���)�� ����/���� 1ĭ�̸� ��Ͼ���
			if (1 == Width && 1 == Height)
			{
				if (true == NewItemInfo->CreateItemInfo(i, LocType, ItemName))
				{
					SuccessFlag = true;
					InvArrItemList_.push_back(NewItemInfo);
				}
			}
			else // �ƴ϶�� �����ϴ� Ÿ�� �ε������ ������ ��������
			{



			}
		}
		else // �������̹Ƿ� Ÿ�� �ε��� ����� ����
		{
			if (true == NewItemInfo->CreateItemInfo(i, LocType, ItemName))
			{
				SuccessFlag = true;
				InvArrItemList_.push_back(NewItemInfo);
			}
		}

		// ���� ���� ������
		if (true == SuccessFlag)
		{
			// �ش� Ÿ�Ͽ� ������ ��ġ Flag On



			// ���������� ���� �� ��Ͽ� �߰�

		}
	}
}

void InventoryView::ItemArrangementOn(int _TileIndex, InvTabType _InvTabType)
{
	if (InvTabType::EQUIP == _InvTabType) // ��� ������
	{
		// 1. ���콺�� ����ִ� �������� ���޹޴´�.


		// 2. �ش� �������� ������ �ε��Ͽ� �����ϴ� ĭ��(����, ����)�� �˾Ƴ���.


		// 3. �����ϴ� ĭ���� �°� ������ �����ϴٸ� �ش� �������� �����۸�Ͽ� �߰��ϰ�,
		//    �����ϴ� Ÿ���� Item Batch Flag On



	}
	else // �ϴ� ������
	{

	}
}

void InventoryView::ItemArrangementOff(int _TileIndex, InvTabType _InvTabType)
{
	if (InvTabType::EQUIP == _InvTabType) // ��� ������
	{
		// 1. �ش� �������� ������ ��Ͽ��� ã�Ƴ���.


		// 2. �ش� �������� ���콺�� �����Ͽ� ���콺�� �������� �鵵�� ����


		// 3. �ش� �������� ������ ��Ͽ��� �����ϰ�, �ش� �������� �����ϰ��ִ� Ÿ���� Item Batch Flag Off


	}
	else // �ϴ� ������
	{

	}
}

#pragma region ��������������
bool InventoryView::ItemInfo::CreateItemInfo(int _Index, ItemLocType _LocType, const std::string& _ItemName_)
{
	// ���� ����






	return true;
}


#pragma endregion
