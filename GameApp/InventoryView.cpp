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

		// 해당 타일이 아이템을 가지고있고, 마우스가 아이템을 들고있지않다면
		if (true == InvEquipInfo_[_Index]->GetIsItemBatch() && false == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOff(_Index, InvTabType_);
		}
		// 해당 타일이 아이템을 가지고있지않고, 마우스가 아이템을 들고있다면
		else if (false == InvEquipInfo_[_Index]->GetIsItemBatch() && true == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOn(_Index, InvTabType_);
		}
		else
		{
			// 두 조건에 만족하지 않다면 사운드 재생

		}
	}
}

void InventoryView::StoreTileBoxClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		InvTabType_ = InvTabType::NORMAL;

		// 해당 타일이 아이템을 가지고있고, 마우스가 아이템을 들고있지않다면
		if (true == InvStoreInfo_[_Index]->GetIsItemBatch() && false == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOff(_Index, InvTabType_);
		}
		// 해당 타일이 아이템을 가지고있지않고, 마우스가 아이템을 들고있다면
		else if (false == InvStoreInfo_[_Index]->GetIsItemBatch() && true == GlobalValue::CurMouse->IsItemHold())
		{
			ItemArrangementOn(_Index, InvTabType_);
		}
		else
		{
			// 두 조건에 만족하지 않다면 사운드 재생

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

#pragma region 종료버튼충돌 및 클릭체크
	// 인벤창 종료버튼 체크
	if (CloseButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 미니메뉴 원래자리 복귀
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// 스킬창 비활성화
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(1);
			}

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// 이벤창 종료버튼 충돌체크
	CloseButtonCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::CloseButtonClick, this, std::placeholders::_1));

#pragma endregion

#pragma region 인벤창 상단/하단 타일박스 충돌체크
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
	// 인벤창 활성화시 호출

	// 1. 하단탭
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

	// 2. 상단탭
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

	// 3. 배치된 아이템 목록
	int ArrItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ArrItemListCnt; ++i)
	{
		InvArrItemList_[i]->On();
	}
}

void InventoryView::SetInentroyBoxTileInactive()
{
	// 인벤창 비활성화시 호출

	// 1. 하단탭
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

	// 2. 상단탭
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

	// 3. 배치된 아이템 목록
	int ArrItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ArrItemListCnt; ++i)
	{
		InvArrItemList_[i]->Off();
	}
}

void InventoryView::InitInventoryView()
{
	// 인벤창 초기 셋팅

	// 1. 인벤창 하단&상단 타일박스 정보 생성 및 충돌체 생성
	CreateInvTile();

	// 2. 현재 생성되는 게임의 메인플레이어정보를 이용하여
	//    소유하고있는 아이템 목록을 인벤창에 배치
	PlayerItemListArrangement();
}

void InventoryView::CreateInvTile()
{
	// 인벤창 하단&상단 타일박스 정보 생성
	CreateInvTileInfo();

	// 인벤창 하단&상단 타일박스 충돌체 생성
	CreateInvTileCol();
}

void InventoryView::CreateInvTileInfo()
{
	// 인벤창 하단&상단 타일박스 정보 생성

	// 1. 하단 플레이어 보관탭
	// x : 10, y : 4 => 40칸
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

	// 2. 상단 플레이어 장착탭
	// 무기(0) ~ 목걸이(9)
	InvEquipInfo_.resize(static_cast<size_t>(10));

	// WEAPON(무기)
	InventoryTileBox* NewWeaponTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewWeaponTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Weapon, 0, float4(49.f, 136.f), float4(57.f, 113.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Weapon)] = NewWeaponTileBox;

	// SHIELD(방패)
	InventoryTileBox* NewShieldTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewShieldTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Shield, 1, float4(280.f, 137.f), float4(57.f, 114.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Shield)] = NewShieldTileBox;

	// HELM(투구)
	InventoryTileBox* NewHelmTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewHelmTileBox->CreatePlayerEquipTileBox("Helm.png", false, ItemLocType::Inven_Helm, 2, float4(164.f, 208.f), float4(57.f, 57.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Helm)] = NewHelmTileBox;

	// ARMOR(갑옷)
	InventoryTileBox* NewArmorTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewArmorTileBox->CreatePlayerEquipTileBox("Armor.png", false, ItemLocType::Inven_Armor, 3, float4(164.f, 123.f), float4(57.f, 86.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Armor)] = NewArmorTileBox;

	// GLOVES(장갑)
	InventoryTileBox* NewGlovesTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewGlovesTileBox->CreatePlayerEquipTileBox("Gloves.png", false, ItemLocType::Inven_Gloves, 4, float4(48.f, 36.f), float4(57.f, 58.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Gloves)] = NewGlovesTileBox;

	// BELT(벨트)
	InventoryTileBox* NewBeltTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBeltTileBox->CreatePlayerEquipTileBox("Belt.png", false, ItemLocType::Inven_Belt, 5, float4(164.f, 50.f), float4(57.f, 25.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Belt)] = NewBeltTileBox;

	// BOOTS(부츠)
	InventoryTileBox* NewBootsTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBootsTileBox->CreatePlayerEquipTileBox("Boots.png", false, ItemLocType::Inven_Boots, 6, float4(280.f, 36.f), float4(57.f, 58.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Boots)] = NewBootsTileBox;

	// LRING(왼쪽링)
	InventoryTileBox* NewLRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewLRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_LRing, 7, float4(108.f, 50.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_LRing)] = NewLRingTileBox;

	// RRING(오른쪽링)
	InventoryTileBox* NewRRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewRRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_RRing, 8, float4(222.f, 50.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_RRing)] = NewRRingTileBox;

	// AMULET(목걸이)
	InventoryTileBox* NewAmuletTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewAmuletTileBox->CreatePlayerEquipTileBox("Amulet.png", false, ItemLocType::Inven_Amulet, 9, float4(222.f, 194.f), float4(27.f, 28.f));
	InvEquipInfo_[static_cast<int>(ItemLocType::Inven_Amulet)] = NewAmuletTileBox;
}

void InventoryView::CreateInvTileCol()
{
	// 인벤창 하단&상단 타일박스 충돌체 생성

	// 1. 하단 플레이어 보관탭
	// x : 10, y : 4 => 40칸
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

	// 2. 상단 플레이어 장착탭
	InvEquipCol_.resize(10);

	// WEAPON(무기)
	GameEngineCollision* NewWeaponTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewWeaponTileBox->GetTransform()->SetLocalPosition(float4(49.f, 136.f));
	NewWeaponTileBox->GetTransform()->SetLocalScaling(float4(57.f, 113.f));
	NewWeaponTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Weapon)] = NewWeaponTileBox;

	// SHIELD(방패)
	GameEngineCollision* NewShieldTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewShieldTileBox->GetTransform()->SetLocalPosition(float4(280.f, 137.f));
	NewShieldTileBox->GetTransform()->SetLocalScaling(float4(57.f, 114.f));
	NewShieldTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Shield)] = NewShieldTileBox;

	// HELM(투구)
	GameEngineCollision* NewHelmTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewHelmTileBox->GetTransform()->SetLocalPosition(float4(164.f, 208.f));
	NewHelmTileBox->GetTransform()->SetLocalScaling(float4(57.f, 57.f));
	NewHelmTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Helm)] = NewHelmTileBox;

	// ARMOR(갑옷)
	GameEngineCollision* NewArmorTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewArmorTileBox->GetTransform()->SetLocalPosition(float4(164.f, 123.f));
	NewArmorTileBox->GetTransform()->SetLocalScaling(float4(57.f, 86.f));
	NewArmorTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Armor)] = NewArmorTileBox;

	// GLOVES(장갑)
	GameEngineCollision* NewGlovesTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewGlovesTileBox->GetTransform()->SetLocalPosition(float4(48.f, 36.f));
	NewGlovesTileBox->GetTransform()->SetLocalScaling(float4(57.f, 58.f));
	NewGlovesTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Gloves)] = NewGlovesTileBox;

	// BELT(벨트)
	GameEngineCollision* NewBeltTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewBeltTileBox->GetTransform()->SetLocalPosition(float4(164.f, 50.f));
	NewBeltTileBox->GetTransform()->SetLocalScaling(float4(57.f, 25.f));
	NewBeltTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Belt)] = NewBeltTileBox;

	// BOOTS(부츠)
	GameEngineCollision* NewBootsTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewBootsTileBox->GetTransform()->SetLocalPosition(float4(280.f, 36.f));
	NewBootsTileBox->GetTransform()->SetLocalScaling(float4(57.f, 58.f));
	NewBootsTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Boots)] = NewBootsTileBox;

	// LRING(왼쪽링)
	GameEngineCollision* NewLRingTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewLRingTileBox->GetTransform()->SetLocalPosition(float4(108.f, 50.f));
	NewLRingTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewLRingTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_LRing)] = NewLRingTileBox;

	// RRING(오른쪽링)
	GameEngineCollision* NewRRingTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewRRingTileBox->GetTransform()->SetLocalPosition(float4(222.f, 50.f));
	NewRRingTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewRRingTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_RRing)] = NewRRingTileBox;

	// AMULET(목걸이)
	GameEngineCollision* NewAmuletTileBox = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	NewAmuletTileBox->GetTransform()->SetLocalPosition(float4(222.f, 194.f));
	NewAmuletTileBox->GetTransform()->SetLocalScaling(float4(27.f, 28.f));
	NewAmuletTileBox->Off();
	InvEquipCol_[static_cast<int>(ItemLocType::Inven_Amulet)] = NewAmuletTileBox;
}

void InventoryView::PlayerItemListArrangement()
{
	// 현재 시작되는 게임의 플레이어가 들고있는 아이템 배치
	MainPlayerInfo CurPlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	int ItemCnt = static_cast<int>(CurPlayerInfo.ItemInfo.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		// 아이템정보 생성을 위한 정보 Get
		int TileIndex = CurPlayerInfo.ItemInfo[i].StartPosition;
		ItemLocType LocType = CurPlayerInfo.ItemInfo[i].ItemLocType;
		std::string ItemName = CurPlayerInfo.ItemInfo[i].ItemName_abbreviation;

		// 하단 보관탭이면
		if (ItemLocType::Inven_Bottom == LocType)
		{
			// 해당 타일의 렌더링하기 위해 타일박스 위치 Get
			float4 RenderPos = InvStoreInfo_[TileIndex]->GetTilePos();

			// 타일인덱스는 말그대로 위치값을 변환한 타일인덱스로 셋팅
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(i, TileIndex, LocType, ItemName, RenderPos))
			{
				InvArrItemList_.push_back(NewItemInfo);

				// 아이템 렌더러의 크기에 따라 인벤 하단 보관탭의 칸(타일)의 Flag On
				float4 ArrangeSize = NewItemInfo->GetArrangeTileSize();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1칸만 차지하므로 해당 타일인덱스만 Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOn();
				}
				else
				{
					// 칸수에 따라 타일인덱스에서 시작해서 계산한 타일갯수만큼 모두 Flag On처리

				}
			}
			else // 생성 실패시 바로 죽임
			{
				NewItemInfo->Death();
			}
		}
		else // 상단 장착탭이면
		{
			// 해당 타일의 렌더링하기 위해 타일박스 위치 Get
			float4 RenderPos = InvEquipInfo_[static_cast<int>(LocType)]->GetTilePos();

			// 타일인덱스가 장착칸의 위치 정보로 셋팅
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(i, static_cast<int>(LocType), LocType, ItemName, RenderPos))
			{
				InvArrItemList_.push_back(NewItemInfo);

				// 인벤 상단 보관탭의 칸(타일)의 Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();
			}
			else // 생성 실패시 바로 죽임
			{
				NewItemInfo->Death();
			}
		}
	}
}

void InventoryView::ItemArrangementOn(int _TileIndex, InvTabType _InvTabType)
{
	// 마우스와 연동되어 아이템렌더러 생성 및 위치에 장착

	// 1. 현재 마우스가 들고있는 아이템의 텍스쳐명을 가져온다.
	std::string InvItemName = GlobalValue::CurMouse->GetHoldItemName();
	size_t DotFindIndex = InvItemName.find('.');
	InvItemName = InvItemName.substr(0, DotFindIndex);

	// 2. 모든 아이템 정보에서 해당 아이템정보를 찾아낸다.
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(InvItemName, CurItemInfo))
	{
		// 3. 찾았다면 다음 아이템을 장착할 탭에 따라 처리진행
		if (InvTabType::EQUIP == _InvTabType)
		{
			// 배치하려는 아이템이 인벤 상단 장착탭 구간이라면
			int Cnt = static_cast<int>(InvArrItemList_.size());

			// 1) 배치하려는 아이템정보 생성 후 관리목록에 추가
			// 단, 아이템이 장착가능한 탭과 다르면 "~할 수 없다" 사운드 재생 후 리턴
			//   Ex) 무기 아이템인데 투구창에 장착하려고하면 장착이 되지않아야함
			ItemLocType LocType = static_cast<ItemLocType>(_TileIndex);
			if (LocType != CurItemInfo.ItemLocType)
			{
				// 사운드 재생 - "~할 수 없다"



				return;
			}

			std::string ItemName = CurItemInfo.ItemName_abbreviation;
			float4 RenderPos = InvEquipInfo_[static_cast<int>(LocType)]->GetTilePos();

			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(Cnt, static_cast<int>(LocType), LocType, ItemName, RenderPos))
			{
				// 관리목록에 해당 아이템 추가
				InvArrItemList_.push_back(NewItemInfo);

				// 2) 마우스 Put Down(아이템내려놓기)
				GlobalValue::CurMouse->ItemPutDown();

				// 3) 배치하려는 칸(타일)의 Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();

				NewItemInfo->On();

				// 4) 무기(wnd)를 제외하고 각 탭별 아이템장착상태에 따라 플레이어 애니메이션 상태 전환
				//    Ex) -. 방패탭에 방패 장착시 플레이어의 애니메이션 SH 파트는 HVY_ 상태가 된다.
				//        -. 무기탭에 기본적으로 wnd 무기가 장착되어있으나, crs 무기로 변경되어 장착되는 순간
				//           플레이어의 애니메이션 RH 파트는 HVY_ 상태가 된다.




			}
			else
			{
				// 정보 생성 실패시 바로 죽인다.
				NewItemInfo->Death();
			}
		}
		else
		{
			// 배치하려는 아이템이 인벤 하단 보관탭 구간이라면
			int Cnt = static_cast<int>(InvArrItemList_.size());

			// 해당 아이템이 차지하는 칸수(타일 인덱스(가로/세로))를 체크한다.
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
					// 정보 생성 성공시 

					// 관리목록에 해당 아이템정보 추가
					InvArrItemList_.push_back(NewItemInfo);

					// 마우스 Put Down(아이템내려놓기)
					GlobalValue::CurMouse->ItemPutDown();

					// 해당 아이템의 렌더러크기(차지하는타일칸수)에 따라 해당하는 모든 타일(칸)의 Flag On
					InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOn();

					NewItemInfo->On();
				}
				else
				{
					// 정보 생성 실패시 바로 죽인다.
					NewItemInfo->Death();
				}
			}
			else
			{
				// 아이템이 차지하는 칸수가 가로 1개, 세로 1개가 아니라면
				// 충돌한 타일인덱스 기준 좌,우,상,하의 타일의 장착상태를 체크
				// 만약 아이템이 위치하려는 타일이 부족하거나 존재하지않다면 리턴

				//int TopCheckIndex = StartIndex - ;
				int BotCheckIndex = -1;
				// WidthSize;
				// HeightSize;

				// 1. 좌 검사
				int LeftCheckIndex = StartIndex - WidthSize;
				

				// 2. 우 검사
				int RightCheckIndex = StartIndex + WidthSize;


				// 3. 상 검사
				


				// 4. 하 검사





				

			}
		}
	}
}

void InventoryView::ItemArrangementOff(int _TileIndex, InvTabType _InvTabType)
{
	// 마우스와 연동되어 아이템렌더러 제거 및 위치에서 장착해제

	// 1. 아이템목록에서 해당 아이템을 찾아낸다.
	int FindItemIndex = -1;
	int ItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ItemListCnt; ++i)
	{
		if (InvTabType::EQUIP == _InvTabType)
		{
			// 장착탭은 장착칸별 위치(ItemLocType)인덱스로 찾아냄
			if (_TileIndex == InvArrItemList_[i]->GetLocTypeInt())
			{
				FindItemIndex = i;

				// 장착탭은 해당 칸만 Flag 해제
				int Index = InvArrItemList_[i]->GetLocTypeInt();
				InvEquipInfo_[Index]->SetItemArrangeFlagOff();

				// 만약 플레이어의 애니메이션이 LIT_ 상태의 아이템 장착상황이 아니라면
				// 해당 장착파트의 플레이어 애니메이션이 HVY_ -> LIT_ 상태로 전환


				break;
			}
		}
		else
		{
			// 보관탭은 보관칸별 타일인덱스로 찾아냄
			if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex() && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
			{
				FindItemIndex = i;

				// 보관탭은 아이템렌더러 크기에 따라 다름
				float4 ArrangeSize = InvArrItemList_[i]->GetArrangeTileSize();
				int TileIndex = InvArrItemList_[i]->GetStartTileIndex();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1칸만 차지하므로 해당 타일인덱스만 Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOff();
				}
				else
				{
					// 해당 아이템이 여러칸을 차지하고있다가 해제되는것이므로,
					// 차지하고있던 모든 칸의 배치 Flag Off 전환


				}
				break;
			}
		}
	}

	// 해당 아이템을 찾았다면 인벤창이 관리하는 아이템목록에서 제거되고,
	// 현재 메인마우스가 아이템을 가져간다.
	if (-1 != FindItemIndex)
	{
		std::string TextureName = InvArrItemList_[FindItemIndex]->GetTextureName();
		float4 RenderScale = InvArrItemList_[FindItemIndex]->GetRenderScale();
		GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

		// 해당 아이템 Death 처리
		InvArrItemList_[FindItemIndex]->Death();

		// 배치아이템목록에서 해당 아이템 삭제
		std::vector<InvArrangementItemInfo*>::iterator DelIter = InvArrItemList_.begin() + FindItemIndex;
		if (InvArrItemList_.end() != DelIter)
		{
			InvArrItemList_.erase(DelIter);
		}
	}
}
