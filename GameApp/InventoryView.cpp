#include "PreCompile.h"
#include "InventoryView.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"

InventoryView::InventoryView() :
	InventoryPanel_(nullptr),
	CloseButton_(nullptr),
	CloseButtonCollider_(nullptr),
	CloseButtonState_(Button_State::Normal)
{
}

InventoryView::~InventoryView()
{
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

void InventoryView::InitInventoryView()
{
	// 인벤토리창의 타일정보를 생성
	CreateInventoryTile();

	// 현재 플레이어 초기에 가지고있는 아이템을 인벤토리 목록에 배치
	MainPlayerInfo CurPlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	int ItemCnt = static_cast<int>(CurPlayerInfo.ItemInfo.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		std::string ItemName = CurPlayerInfo.ItemInfo[i].ItemName_abbreviation;
		ItemLocType ItemLocType = CurPlayerInfo.ItemInfo[i].ItemLocType;
		int StartIndex = CurPlayerInfo.ItemInfo[i].StartPosition;
		int WidthSize = CurPlayerInfo.ItemInfo[i].WidthSize;
		int HeightSize = CurPlayerInfo.ItemInfo[i].HeightSize;
		int ItemCode = CurPlayerInfo.ItemInfo[i].ItemCode;
		InitInventoryItemSetting(ItemName, ItemCode, ItemLocType, StartIndex, WidthSize, HeightSize);
	}
}

void InventoryView::CreateInventoryTile()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 인벤창 하단 배치타일박스목록 생성
	// x : 10, y : 4 => NORMAL
	NormalInventoryTile_.resize(10 * 4);	// 미리 할당
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			InventoryTileBox* NewTileBox =  GetLevel()->CreateActor<InventoryTileBox>();
			NewTileBox->CreateNormalTileBox(false, ItemLocType::Inven_Bottom, x, y, ((x * 1) + (y * 10)));
			NormalInventoryTile_[(x * 1) + (y * 10)] = NewTileBox;
		}
	}

	// 플레이어 아이템 장착용 박스 생성
	PlayerEquipInvTile_.resize(static_cast<size_t>(10));

	// HELM(투구)
	InventoryTileBox* NewHelmTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewHelmTileBox->CreatePlayerEquipTileBox("Helm.png", false, ItemLocType::Inven_Helm, 0, float4(164.f, 208.f), float4(57.f, 57.f));
	PlayerEquipInvTile_[0] = NewHelmTileBox;

	// ARMOR(갑옷)
	InventoryTileBox* NewArmorTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewArmorTileBox->CreatePlayerEquipTileBox("Armor.png", false, ItemLocType::Inven_Armor, 1, float4(164.f, 123.f), float4(57.f, 86.f));
	PlayerEquipInvTile_[1] = NewArmorTileBox;

	// LRING(왼쪽링)
	InventoryTileBox* NewLRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewLRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_LRing, 2, float4(108.f, 50.f), float4(27.f, 28.f));
	PlayerEquipInvTile_[2] = NewLRingTileBox;

	// RRING(오른쪽링)
	InventoryTileBox* NewRRingTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewRRingTileBox->CreatePlayerEquipTileBox("Ring.png", false, ItemLocType::Inven_RRing, 3, float4(222.f, 50.f), float4(27.f, 28.f));
	PlayerEquipInvTile_[3] = NewRRingTileBox;

	// AMULET(목걸이)
	InventoryTileBox* NewAmuletTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewAmuletTileBox->CreatePlayerEquipTileBox("Amulet.png", false, ItemLocType::Inven_Amulet, 4, float4(222.f, 194.f), float4(27.f, 28.f));
	PlayerEquipInvTile_[4] = NewAmuletTileBox;

	// GLOVES(장갑)
	InventoryTileBox* NewGlovesTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewGlovesTileBox->CreatePlayerEquipTileBox("Gloves.png", false, ItemLocType::Inven_Gloves, 5, float4(48.f, 36.f), float4(57.f, 58.f));
	PlayerEquipInvTile_[5] = NewGlovesTileBox;

	// BOOTS(부츠)
	InventoryTileBox* NewBootsTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBootsTileBox->CreatePlayerEquipTileBox("Boots.png", false, ItemLocType::Inven_Boots, 6, float4(280.f, 36.f), float4(57.f, 58.f));
	PlayerEquipInvTile_[6] = NewBootsTileBox;

	// BELT(벨트)
	InventoryTileBox* NewBeltTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewBeltTileBox->CreatePlayerEquipTileBox("Belt.png", false, ItemLocType::Inven_Belt, 7, float4(164.f, 50.f), float4(57.f, 25.f));
	PlayerEquipInvTile_[7] = NewBeltTileBox;

	// WEAPON(무기)
	InventoryTileBox* NewWeaponTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewWeaponTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Weapon, 8, float4(49.f, 136.f), float4(57.f, 113.f));
	PlayerEquipInvTile_[8] = NewWeaponTileBox;

	// SHIELD(방패)
	InventoryTileBox* NewShieldTileBox = GetLevel()->CreateActor<InventoryTileBox>();
	NewShieldTileBox->CreatePlayerEquipTileBox("Weapon.png", false, ItemLocType::Inven_Shield, 9, float4(280.f, 137.f), float4(57.f, 114.f));
	PlayerEquipInvTile_[9] = NewShieldTileBox;
}

void InventoryView::InitInventoryItemSetting(const std::string& _ItemName, int _ItemCode, ItemLocType _ItemLocType, int _StartIndex, int _WidthSize, int _HeightSize)
{
	switch (_ItemLocType)
	{
		case ItemLocType::Inven_Weapon:
		{
			PlayerEquipInvTile_[8]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Shield:
		{
			PlayerEquipInvTile_[9]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Helm:
		{
			PlayerEquipInvTile_[0]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Armor:
		{
			PlayerEquipInvTile_[1]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Gloves:
		{
			PlayerEquipInvTile_[5]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Belt:
		{
			PlayerEquipInvTile_[7]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Boots:
		{
			PlayerEquipInvTile_[6]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_LRing:
		{
			PlayerEquipInvTile_[2]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_RRing:
		{
			PlayerEquipInvTile_[3]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Amulet:
		{
			PlayerEquipInvTile_[4]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
		case ItemLocType::Inven_Bottom:
		{
			NormalInventoryTile_[_StartIndex]->GameStartItemBatch(_ItemName, _ItemCode, _WidthSize, _HeightSize);
			break;
		}
	}
}

void InventoryView::SetInventoryBoxTileActvie()
{
	// 인벤창 활성화시 호출
	int NormalTileCnt = static_cast<int>(NormalInventoryTile_.size());
	for (int i = 0; i < NormalTileCnt; ++i)
	{
		NormalInventoryTile_[i]->TileBoxActive();
	}

	int EquipTileCnt = static_cast<int>(PlayerEquipInvTile_.size());
	for (int i = 0; i < EquipTileCnt; ++i)
	{
		PlayerEquipInvTile_[i]->TileBoxActive();
	}
}

void InventoryView::SetInentroyBoxTileInactive()
{
	// 이벤창 비활성화시 호출
	int NormalTileCnt = static_cast<int>(NormalInventoryTile_.size());
	for (int i = 0; i < NormalTileCnt; ++i)
	{
		NormalInventoryTile_[i]->TileBoxInactive();
	}

	int EquipTileCnt = static_cast<int>(PlayerEquipInvTile_.size());
	for (int i = 0; i < EquipTileCnt; ++i)
	{
		PlayerEquipInvTile_[i]->TileBoxInactive();
	}
}
