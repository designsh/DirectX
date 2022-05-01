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

		// 현재 마우스의 커서상태 체크
		
		if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState()) // 마우스 판매커서상태
		{
			// 해당 타일이 아이템을 들고있을때 처리가능
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag())
			{
				// 판매커서 활성화 상태일때 장착탭에 아이템이 존재한다면 현재 상호작용중인 NPC의 판매창에 해당 아이템 판매
				// 1. 현재 활성화된 판매창이 어떤타입의 판매창인지 알아낸다.
				// 2. 해당 판매창과 거래를 시도(거래조건 체크)
				// 3. 거래완료시 처리
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // 무기판매창 활성화일때
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // 잡화판매창 활성화일때
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::PotionShop);
				}
			}
		}
		else if (MouseState::Repair == GlobalValue::CurMouse->GetMouseState()) // 마우스 수리커서상태
		{
			// 해당 타일이 아이템을 들고있고 현재 활성화되어있는 판매창이 무기상인의 판매창일때
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() &&
				(nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()))
			{
				ItemRepairProcess(_Index, InvTabType_);
			}
		}
		else if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() || MouseState::Move == GlobalValue::CurMouse->GetMouseState()) // 마우스 기본커서상태
		{
			// 해당 타일이 아이템을 가지고있고, 마우스가 아이템을 들고있지않다면
			if (true == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOff(_Index, InvTabType_);
			}
			// 해당 타일이 아이템을 가지고있지않고, 마우스가 아이템을 들고있다면
			else if (false == InvEquipInfo_[_Index]->GetIsItemArrangeFlag() && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOn(_Index, InvTabType_);
			}
			else
			{
				// 두 조건에 만족하지 않다면 사운드 재생

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

		// 현재 마우스의 커서상태 체크
		if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState()) // 마우스 판매커서상태
		{
			// 해당 타일이 아이템을 들고있을때 거래가능
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag())
			{
				// 판매커서 활성화 상태일때 보관탭에 아이템이 존재한다면 현재 상호작용중인 NPC의 판매창에 해당 아이템 판매
				// 1. 현재 활성화된 판매창이 어떤타입의 판매창인지 알아낸다.
				// 2. 해당 판매창과 거래를 시도(거래조건 체크)
				// 3. 거래완료시 처리
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // 무기판매창 활성화일때
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // 잡화판매창 활성화일때
				{
					ItemSellProcess(_Index, InvTabType_, NPCType::PotionShop);
				}
			}
		}
		else if (MouseState::Repair == GlobalValue::CurMouse->GetMouseState()) // 마우스 수리커서상태
		{
			// 해당 타일이 아이템을 들고있고 현재 활성화되어있는 판매창이 무기상인의 판매창일때
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && 
				(nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()))
			{
				ItemRepairProcess(_Index, InvTabType_);
			}
		}
		else if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() || MouseState::Move == GlobalValue::CurMouse->GetMouseState()) // 마우스 기본커서상태
		{
			// 해당 타일이 아이템을 가지고있고, 마우스가 아이템을 들고있지않다면
			if (true == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOff(_Index, InvTabType_);
			}
			// 해당 타일이 아이템을 가지고있지않고, 마우스가 아이템을 들고있다면
			else if (false == InvStoreInfo_[_Index]->GetIsItemArrangeFlag() && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemArrangementOn(_Index, InvTabType_);
			}
			else
			{
				// 두 조건에 만족하지 않다면 사운드 재생

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

	// 플레이어 이동불가처리를 위한 충돌체 생성
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

	// 플레이어 보유 골드 관련
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

			// 골드팝업이 열려있다면 골드팝업을 비활성화한다.
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

	// 이벤창 종료버튼 충돌체크
	CloseButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::CloseButtonClick, this, std::placeholders::_1));

#pragma endregion

#pragma region 인벤창 상단/하단 타일박스 충돌체크
	for (int i = 0; i < static_cast<int>(InvEquipCol_.size()); ++i)
	{
		InvEquipCol_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::EquipTileBoxClick, this, std::placeholders::_1, i));
	}

	for (int i = 0; i < static_cast<int>(InvStoreCol_.size()); ++i)
	{
		InvStoreCol_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryView::StoreTileBoxClick, this, std::placeholders::_1, i));
	}
#pragma endregion

#pragma region 골드팝업활성화버튼 충돌체크
	if (GoldButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 골드팝업 활성화 처리
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
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
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

	// 인벤토리가 들고있는 모든 액터를 넘김

	// 장착탭(무기, 방어구, ...) 정보목록
	if (false == InvEquipInfo_.empty())
	{
		int InvEquipInfoCnt = static_cast<int>(InvEquipInfo_.size());
		for (int i = 0; i < InvEquipInfoCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvEquipInfo_[i]);
		}
	}

	// 보관탭 정보목록
	if (false == InvStoreInfo_.empty())
	{
		int InvStoreInfoCnt = static_cast<int>(InvStoreInfo_.size());
		for (int i = 0; i < InvStoreInfoCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvStoreInfo_[i]);
		}
	}

	// 인벤창에 배치되어있는 아이템정보 목록
	if (false == InvArrItemList_.empty())
	{
		int InvArrItemCnt = static_cast<int>(InvArrItemList_.size());
		for (int i = 0; i < InvArrItemCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, InvArrItemList_[i]);
		}
	}

	// 골드팝업
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
	// 창고오브젝트와의 상호작용을 통한 창고창이 활성화 상태라면 저장용 GoldTakeInPopup_ 활성화
	if (nullptr != GlobalValue::Storehouse)
	{
		// 창고창이 활성화되어있을때
		if (true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
		{
			// 골드 드랍용 팝업이 열려있다면 비활성화
			if (true == GoldDropPopup_->IsUpdate())
			{
				GoldDropPopup_->TakeInOutGoldPopupInactive();
			}

			// 창고창의 골드 꺼내기용 팝업이 열려있다면 비활성화
			if (true == GlobalValue::Storehouse->GetStoreView()->GetTakeOutGoldPopup()->IsUpdate())
			{
				GlobalValue::Storehouse->GetStoreView()->GetTakeOutGoldPopup()->TakeInOutGoldPopupInactive();
			}

			// 골드 저장용 팝업창 활성화
			GoldTakeInPopup_->TakeInOutGoldPopupActive(GlobalValue::CurPlayer->GetCurHaveGold());
		}
		// 창고창이 비활성되어있을때
		else
		{
			// 골드 저장용 팝업이 열려있다면 비활성 후
			if (true == GoldTakeInPopup_->IsUpdate())
			{
				GoldTakeInPopup_->TakeInOutGoldPopupInactive();
			}

			// 골드 드랍용 팝업 활성화
			GoldDropPopup_->TakeInOutGoldPopupActive(GlobalValue::CurPlayer->GetCurHaveGold());
		}
	}
	// 창고창이 존재하지않다면
	else
	{
		// 골드 저장용 팝업이 열려있다면 비활성화 후
		if (true == GoldTakeInPopup_->IsUpdate())
		{
			GoldTakeInPopup_->TakeInOutGoldPopupInactive();
		}

		// 골드 드랍용 팝업을 활성화
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
	// 현재 인벤창 무기탭에 장착된 아이템이 없으면 false
	// 그반대의 경우라면 true
	return InvEquipInfo_[static_cast<int>(_LocType)]->GetIsItemArrangeFlag();
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

	// 3. 현재 플레이어 골드량 갱신
	if (nullptr != CurHaveGoldText_)
	{
		CurHaveGoldText_->SetPrintText(std::to_string(GlobalValue::CurPlayer->GetCurHaveGold()));
	}
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
				// 아이템 렌더러의 크기에 따라 인벤 하단 보관탭의 칸(타일)의 Flag On
				float4 ArrangeSize = NewItemInfo->GetArrangeItemSize();
				if (1 == ArrangeSize.x && 1 == ArrangeSize.y)
				{
					// 1칸만 차지하므로 해당 타일인덱스만 Flag On
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOn();

					// 목록에 해당 아이템 추가
					InvArrItemList_.push_back(NewItemInfo);
				}
				else
				{
					// 칸수에 따라 타일인덱스에서 시작해서 계산한 타일갯수만큼 모두 Flag On처리

					// 시작타일기준 아이템배치
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

					// 배치목록 정렬
					std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

					// 아이템 배치 위치 재계산 및 재조정
					float4 ReRenderPos = float4(33.f, -116.f);	// 초기값 셋팅(0번인덱스인경우)

					// 차지하고있는 칸의 중앙 위치를 계산한다.
					// 첫번째 타일의 위치와 마지막번째 타일의 위치를 Get
					int IndexCnt = static_cast<int>(TileArrIndexList.size());
					float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
					float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

					// 두 타일 위치를 비교
					if (BeginTilePos.x == EndTilePos.x) // 해당 아이템의 너비 1
					{
						ReRenderPos.x = BeginTilePos.x;
					}
					else
					{
						BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
						ReRenderPos.x = BeginTilePos.x;
					}

					if (BeginTilePos.y == EndTilePos.y) // 해당 아이템의 높이 1
					{
						ReRenderPos.y = BeginTilePos.y;
					}
					else
					{
						BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
						ReRenderPos.y = BeginTilePos.y;
					}

					NewItemInfo->SetItemRenderPos(ReRenderPos);

					// 아이템 장착 Flag On
					for (int l = 0; l < IndexCnt; ++l)
					{
						InvStoreInfo_[TileArrIndexList[l]]->SetItemArrangeFlagOn();
					}
					NewItemInfo->SetTileIndexList(TileArrIndexList);
					
					// 목록에 해당 아이템 추가
					InvArrItemList_.push_back(NewItemInfo);
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
			if (true == NewItemInfo->CreateItemInfo(Cnt, static_cast<int>(LocType), LocType, ItemName, RenderPos, true))
			{
				// 관리목록 추가
				InvArrItemList_.push_back(NewItemInfo);

				// 2) 마우스 Put Down(아이템내려놓기)
				GlobalValue::CurMouse->ItemPutDown();

				// 3) 배치하려는 칸(타일)의 Flag On
				InvEquipInfo_[static_cast<int>(LocType)]->SetItemArrangeFlagOn();
				NewItemInfo->On();

				// 4) 아이템 장착상태에 따른 플레이어 파트별 렌더러 갱신
				EquipItemCheck(LocType, ItemName, true);
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

			// 아이템 배치타입 변경(하단 보관탭타입으로 변경)
			CurItemInfo.ItemLocType = ItemLocType::Inven_Bottom;

			if (1 == WidthSize && 1 == HeightSize)
			{
				// 아이템렌더러 크기가 1x1이면 해당 타일인덱스만 활성화되면서 아이템 배치
				std::string ItemName = CurItemInfo.ItemName_abbreviation;

				ItemLocType LocType = CurItemInfo.ItemLocType;
				float4 RenderPos = InvStoreInfo_[_TileIndex]->GetTilePos();
				InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
				if (true == NewItemInfo->CreateItemInfo(Cnt, _TileIndex, LocType, ItemName, RenderPos, true))
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
				// 충돌한 타일인덱스 기준 배치가능한 타일이 존재하는지 탐색하여
				// 배치가능한 타일이 존재한다면 해당 타일목록을 생성한다.
				// 단, 배치가능한 타일이 존재하지않다면 해당 아이템을 배치시킬수 없다.

				// 유효카운트를 이용하여 아이템배치 인덱스목록 생성
				// 단, 생성 실패시 아이템 배치불가
				std::vector<int> TileArrIndexList;
				TileArrIndexList.clear();

				// 해당 아이템의 너비/높이 인덱스를 가져온다.
				int StartIndex = _TileIndex;
				int WidthSize = CurItemInfo.WidthSize;
				int HeightSize = CurItemInfo.HeightSize;
				int InvTileCnt = static_cast<int>(InvStoreInfo_.size());

				// 시작타일이 좌측 타일인경우
				if (StartIndex % 10 == 0)
				{
					// 가장 좌측이면서 상단 타일인경우
					if (30 <= StartIndex && StartIndex <= 39)
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l - (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
					// 가장 좌측이면서 하단 타일인경우
					else if (0 <= StartIndex && StartIndex <= 9)
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
					// 가장 좌측일때 우단 타일검사
					else
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = -1; k < HeightSize - 1; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
				// 시작타일이 우측 타일인경우
				else if (StartIndex % 10 == 9)
				{
					// 가장 우측이면서 상단 타일인경우
					if (30 <= StartIndex && StartIndex <= 39)
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l - (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
					// 가장 우측이면서 하단 타일인경우
					else if (0 <= StartIndex && StartIndex <= 9)
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
					// 가장 우측일때 좌단 타일검사
					else
					{
						// 계산된 인덱스 모두 검사
						bool ChkFlag = false;
						for (int k = -1; k < HeightSize - 1; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex - l + (k * 10);
								if (true == InvStoreInfo_[CalcIndex]->GetIsItemArrangeFlag())
								{
									// 타일검사해서 한개라도 true이면 배치불가능 판단
									ChkFlag = true;
									break;
								}
							}

							if (true == ChkFlag)
							{
								break;
							}
						}

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
				// 두 경우가 아닌경우
				else
				{
					// 좌상단 검사
					// StartIndex가 가장 우하단 타일인덱스가 된다.
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
									// 타일검사해서 한개라도 true이면 배치불가능 판단
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

					// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
					else // 좌상단 실패시
					{
						// 상단 검사
						// StartIndex가 중앙하단 타일인덱스가 된다.
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
										// 타일검사해서 한개라도 true이면 배치불가능 판단
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

						// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
						else // 상단배치 실패시
						{
							// 우상단 검사
							// StartIndex가 가장 좌하단 타일인덱스가 된다.
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
											// 타일검사해서 한개라도 true이면 배치불가능 판단
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

							// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
							else // 우상단 실패시
							{
								// 우단 검사
								// StartIndex가 센터좌단 타일인덱스가 된다.
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
												// 타일검사해서 한개라도 true이면 배치불가능 판단
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

								// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
								else // 우단 실패시
								{
									// 우하단 검사
									// StartIndex가 가장 좌상단 타일인덱스가 된다.
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
													// 타일검사해서 한개라도 true이면 배치불가능 판단
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

									// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
									else // 우하단 실패시
									{
										// 하단 검사
										// StartIndex가 가장 센터상단 타일인덱스가 된다.
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
														// 타일검사해서 한개라도 true이면 배치불가능 판단
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

										// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
										else // 하단실패시
										{
											// 좌하단 검사
											// StartIndex가 가장 우상단 타일인덱스가 된다.
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
															// 타일검사해서 한개라도 true이면 배치불가능 판단
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

											// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
											else // 좌하단실패시
											{
												// 좌단 검사
												// StartIndex가 가장 센터우단 타일인덱스가 된다.
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
																// 타일검사해서 한개라도 true이면 배치불가능 판단
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

												// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
												else // 좌단실패시
												{
													// 센터
													// StartIndex가 센터 타일인덱스가 된다.
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
																	// 타일검사해서 한개라도 true이면 배치불가능 판단
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

													// 모든 인덱스 검사해서 배치가능하다면 인덱스목록 작성
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
				
				// 배치가능한 타일이 존재하여 인덱스 목록이 생성되었다면
				if (false == TileArrIndexList.empty())
				{
					// 아이템정보 액터 생성
					InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();

					// 배치 인덱스 목록 정렬
					std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

					// 아이템 배치 인덱스목록 아이템정보에 저장
					NewItemInfo->SetTileIndexList(TileArrIndexList);

					// 실질적인 아이템 정보 생성
					std::string ItemName = CurItemInfo.ItemName_abbreviation;
					ItemLocType LocType = ItemLocType::Inven_Bottom;

					// 장착가능한 타일정보를 이용하여 아이템 생성

					float4 RenderPos = InvStoreInfo_[_TileIndex]->GetTilePos();
					if (true == NewItemInfo->CreateItemInfo(Cnt, _TileIndex, LocType, ItemName, RenderPos, true))
					{
						// 정보 생성 성공시
						
						// 1. 인덱스목록을 반복하며, 아이템배치 Flag On
						int IndexCnt = static_cast<int>(TileArrIndexList.size());
						for (int i = 0; i < IndexCnt; ++i)
						{
							InvStoreInfo_[TileArrIndexList[i]]->SetItemArrangeFlagOn();
						}

						// 2. 아이템 배치 위치 재계산 및 재조정
						float4 ReRenderPos = float4(33.f, -116.f);	// 초기값 셋팅(0번인덱스인경우)

						// 차지하고있는 칸의 중앙 위치를 계산한다.
						// 첫번째 타일의 위치와 마지막번째 타일의 위치를 Get
						float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
						float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

						// 두 타일 위치를 비교
						if (BeginTilePos.x == EndTilePos.x) // 해당 아이템의 너비 1
						{
							ReRenderPos.x = BeginTilePos.x;
						}
						else
						{
							BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
							ReRenderPos.x = BeginTilePos.x;
						}

						if (BeginTilePos.y == EndTilePos.y) // 해당 아이템의 높이 1
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

						// 모든 정보 생성 성공시 관리목록에 해당 아이템정보 추가
						InvArrItemList_.push_back(NewItemInfo);

						// 마우스 Put Down(아이템내려놓기)
						GlobalValue::CurMouse->ItemPutDown();
					}
					else
					{
						// 정보생성 실패시 아이템정보액터 바로 제거
						NewItemInfo->Death();
						return;
					}
				}
				else
				{
					// 생성된 목록이 없다면 바로 클리어
					TileArrIndexList.clear();
				}
			}
		}
	}
}

void InventoryView::ItemArrangementOff(int _TileIndex, InvTabType _InvTabType)
{
	// 마우스와 연동되어 아이템렌더러 제거 및 위치에서 장착해제

	// 1. 아이템목록에서 해당 아이템을 찾아낸다.
	int ItemListCnt = static_cast<int>(InvArrItemList_.size());
	for (int i = 0; i < ItemListCnt; ++i)
	{
		if (InvTabType::EQUIP == _InvTabType)
		{
			// 장착탭은 장착칸별 위치(ItemLocType)인덱스로 찾아냄
			if (_TileIndex == InvArrItemList_[i]->GetLocTypeInt())
			{
				// 장착탭은 해당 칸만 Flag 해제
				int Index = InvArrItemList_[i]->GetLocTypeInt();
				InvEquipInfo_[Index]->SetItemArrangeFlagOff();

				// 만약 플레이어의 애니메이션이 LIT_ 상태의 아이템 장착상황이 아니라면
				// 해당 장착파트의 플레이어 애니메이션이 HVY_ -> LIT_ 상태로 전환
				std::string ItemName = InvArrItemList_[i]->GetItemName();
				ItemLocType LocType = InvArrItemList_[i]->GetLocType();
				EquipItemCheck(LocType, ItemName, false);

				// 마우스 전달
				std::string TextureName = InvArrItemList_[i]->GetTextureName();
				float4 RenderScale = InvArrItemList_[i]->GetRenderScale();
				GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

				// 플레이어의 아이템 보유목록에서 해당 아이템 제거
				MainPlayerInfomation::GetInst().PlayerItemDel(ItemName, LocType, _TileIndex);

				// 해당 아이템 Death 처리
				InvArrItemList_[i]->Death();

				// 배치아이템목록에서 해당 아이템 삭제
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
			// 인벤창 하단 보관탭일때
			// 타일인덱스
			if (false == InvArrItemList_[i]->GetItemIndexListEmpty())
			{
				// 인덱스 목록이 존재할 경우 : 해당 아이템의 인덱스 목록을 검사 true이고, 해당 아이템 위치가 인벤 하단 보관탭에 있었을때
				if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex) && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
				{
					// 존재한다면 해당 아이템이 관여하는 모든 타일(칸)의 Flag Off 처리
					std::vector<int> IndexList = InvArrItemList_[i]->GetItemArrIndexList();
					int ListCnt = static_cast<int>(IndexList.size());
					for (int i = 0; i < ListCnt; ++i)
					{
						InvStoreInfo_[IndexList[i]]->SetItemArrangeFlagOff();
					}

					// 해당 아이템을 찾았다면 인벤창이 관리하는 아이템목록에서 제거되고,
					// 현재 메인마우스가 아이템을 가져간다.
					std::string TextureName = InvArrItemList_[i]->GetTextureName();
					float4 RenderScale = InvArrItemList_[i]->GetRenderScale();

					// 마우스가 해당 아이템을 들기
					GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

					// 플레이어의 아이템 보유목록에서 해당 아이템 제거
					MainPlayerInfomation::GetInst().PlayerItemDel(InvArrItemList_[i]->GetItemName(), InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

					// 해당 아이템 Death 처리
					InvArrItemList_[i]->Death();

					// 배치아이템목록에서 해당 아이템 삭제
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
				// 인덱스 목록이 존재하지않을 경우 : 해당 타일인덱스만 Flag 해제 후 마우스 전달
				if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex() && ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
				{
					// 보관탭은 아이템렌더러 크기에 따라 다름
					float4 ArrangeSize = InvArrItemList_[i]->GetArrangeItemSize();
					int TileIndex = InvArrItemList_[i]->GetStartTileIndex();
					InvStoreInfo_[TileIndex]->SetItemArrangeFlagOff();

					// 해당 아이템을 찾았다면 인벤창이 관리하는 아이템목록에서 제거되고,
					// 현재 메인마우스가 아이템을 가져간다.
					std::string TextureName = InvArrItemList_[i]->GetTextureName();
					float4 RenderScale = InvArrItemList_[i]->GetRenderScale();

					// 마우스가 해당 아이템을 들기
					GlobalValue::CurMouse->ItemHold(TextureName, RenderScale);

					// 플레이어의 아이템 보유목록에서 해당 아이템 제거
					MainPlayerInfomation::GetInst().PlayerItemDel(InvArrItemList_[i]->GetItemName(), InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

					// 해당 아이템 Death 처리
					InvArrItemList_[i]->Death();

					// 배치아이템목록에서 해당 아이템 삭제
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
	// 판매처리
	std::string SellItemName;

	// 판매하려는 아이템의 타입을 알아낸다.
	if (InvTabType::NORMAL == _InvTabType)
	{
		// 인벤창 하단보관탭의 아이템(_TileIndex == 배치된 타일의 시작인덱스)
		// 단, 아이템 크기가 1x1이면 시작인덱스만 검사하여 아이템이름을 찾아내고
		// 아니라면 해당 아이템이 포함하는 모든 인덱스목록을 검사하여 아이템이름을 찾아낸다.
		int Cnt = static_cast<int>(InvArrItemList_.size());
		for (int i = 0; i < Cnt; ++i)
		{
			if (ItemLocType::Inven_Bottom == InvArrItemList_[i]->GetLocType())
			{
				// 해당 아이템 배치인덱스목록이 비어있는경우
				if (true == InvArrItemList_[i]->GetItemIndexListEmpty())
				{
					// 해당 아이템의 시작인덱스와 현재 충돌한 타일인덱스가 동일하면 해당 아이템을 찾음
					if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
					{
						SellItemName = InvArrItemList_[i]->GetItemName();
						break;
					}
				}
				else // 해당 아이템 배치인덱스 목록이 존재하는 경우
				{
					// 해당 아이템의 인덱스목록에 현재 충돌한 타일인덱스가 존재하면 해당 아이템을 찾음
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
		// 인벤창 상단장착탭의 아이템(_TileIndex == 배치된 장착칸의 인덱스)
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
			// 아이템 찾기 실패!!!!
			return;
		}
	}

	// 아이템을 찾았으므로 해당 아이템을 판매하기 위해 정보 Get
	ItemList SellItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindName(SellItemName, SellItemInfo))
	{
		// 정보를 찾았다면 판매 처리 시작

		switch (_BuySellType)
		{
			case NPCType::PotionShop:
			{
				// 판매하려는 아이템이 무기/방어구이면 NPC의 보유골드만 감소
				if (!(16 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 18))
				{
					// NPC의 보유골드 감소 후
					GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(SellItemInfo.Price);

					// 인벤토리에서 해당 아이템 제거
					int Cnt = static_cast<int>(InvArrItemList_.size());
					for (int i = 0; i < Cnt; ++i)
					{
						if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName())
						{
							// 1. 해당 장비아이템이 위치하던 위치를 알아낸다.
							if (InvTabType::NORMAL == _InvTabType)
							{
								// 2. 해당 장비 아이템의 이전 위치가 인벤창 하단 보관탭이였다면
								//    해당 아이템의 크기를 알아낸다.
								float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
								if (ItemSize.x == 1 && ItemSize.y == 1) // 아이템크기가 1x1일때
								{
									if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
									{
										InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

										// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// 플레이어의 보유골드 증가
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// 인벤창 보유목록에서 해당 아이템을 제거
										InvArrItemList_[i]->Death();
										std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
										InvArrItemList_.erase(FindIter);
										break;
									}
								}
								else // 아이템크기가 1x1이 아닐때
								{
									if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex))
									{
										// 아이템이 차지하던 인덱스목록 Get
										std::vector<int> ItemArrIndexs = InvArrItemList_[i]->GetItemArrIndexList();
										int IndexCnt = static_cast<int>(ItemArrIndexs.size());
										for (int k = 0; k < IndexCnt; ++k)
										{
											// 목록전체 타일인덱스 Flag 해제
											InvStoreInfo_[ItemArrIndexs[k]]->SetItemArrangeFlagOff();
										}

										// 플레이어의 보유골드 증가
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// 인벤창 보유목록에서 해당아이템 제거
										InvArrItemList_[i]->Death();
										std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
										InvArrItemList_.erase(FindIter);
										break;
									}
								}
							}
							else if (InvTabType::EQUIP == _InvTabType)
							{
								// 2. 해당 장비 아이템의 이전 위치가 인벤창 상단 장착탭이였다면
								//    LocType == _TileIndex 이므로 해당 장착탭만 Flag 해제
								if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
								{
									InvEquipInfo_[_TileIndex]->SetItemArrangeFlagOff();

									// 플레이어의 보유골드 증가
									GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

									// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
									MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

									// 인벤창 보유목록에서 해당 아이템을 제거
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
					// NPC의 판매창 보유목록에 해당 판매아이템 존재여부 체크 후 존재한다면 해당아이템 남은수량이 증가, 아니라면 해당 아이템 배치
					if (true == GlobalValue::ChandleryNPC->GetChandleryShop()->SellItemCheck(SellItemInfo.ItemName_abbreviation_Inven))
					{
						// 해당 아이템 인벤토리배치목록에서 제거, 플레이어 보유아이템목록 제거 후 플레이어가 보유한 골드량 증가
						int Cnt = static_cast<int>(InvArrItemList_.size());
						for (int i = 0; i < Cnt; ++i)
						{
							if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName() && 
								_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
							{
								// 잡화인 아이템이므로 항상 인벤창하단 보관탭에 존재

								// 아이템의 너비/높이 Get
								float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
								if (ItemSize.x == 1 && ItemSize.y == 1) // ItemSize = 1x1
								{
									InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

									// 플레이어의 보유골드 증가
									GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

									// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
									MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

									// 인벤창 보유목록에서 해당 아이템을 제거하고,
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
				// 판매하려는 아이템이 잡화이면 NPC의 보유골드만 증가
				if (16 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 18)
				{
					// 잡화이면 NPC의 골드량을 감소시키고,
					GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(SellItemInfo.Price);

					// 해당 아이템은 잡화타입이기때문에 항상 인벤창 하단 보관탭에 존재
					int Cnt = static_cast<int>(InvArrItemList_.size());
					for (int i = 0; i < Cnt; ++i)
					{
						if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName() &&
							_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
						{
							// 잡화인 아이템이므로 항상 인벤창하단 보관탭에 존재

							// 아이템의 너비/높이 Get
							float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
							if (ItemSize.x == 1 && ItemSize.y == 1) // ItemSize = 1x1
							{
								InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

								// 플레이어의 보유골드 증가
								GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

								// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
								MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

								// 인벤창 보유목록에서 해당 아이템을 제거하고,
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
					// NPC의 판매창 보유목록에 해당 판매아이템 존재여부 체크 후 존재한다면 해당아이템 남은수량이 증가, 아니라면 해당 아이템 배치
					if (true == GlobalValue::WeaponNPC->GetWeaponShop()->SellItemCheck(SellItemInfo.ItemName_abbreviation_Inven))
					{
						int Cnt = static_cast<int>(InvArrItemList_.size());
						for (int i = 0; i < Cnt; ++i)
						{
							if (SellItemInfo.ItemName_abbreviation == InvArrItemList_[i]->GetItemName())
							{
								// 1. 해당 장비템이 기존에 위치하고있던 곳을 알아낸다.
								if (InvTabType::NORMAL == _InvTabType)
								{
									// 2. 해당 장비 아이템의 이전 위치가 인벤창 하단 보관탭이였다면
									//    해당 아이템의 크기를 알아낸다.
									float4 ItemSize = InvArrItemList_[i]->GetArrangeItemSize();
									if (ItemSize.x == 1 && ItemSize.y == 1) // 아이템크기가 1x1일때
									{
										if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
										{
											InvStoreInfo_[_TileIndex]->SetItemArrangeFlagOff();

											// 플레이어의 보유골드 증가
											GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

											// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
											MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

											// 인벤창 보유목록에서 해당 아이템을 제거
											InvArrItemList_[i]->Death();
											std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
											InvArrItemList_.erase(FindIter);
											break;
										}
									}
									else // 아이템크기가 1x1이 아닐때
									{
										if (true == InvArrItemList_[i]->ItemArrngeListFind(_TileIndex))
										{
											// 아이템이 차지하던 인덱스목록 Get
											std::vector<int> ItemArrIndexs = InvArrItemList_[i]->GetItemArrIndexList();
											int IndexCnt = static_cast<int>(ItemArrIndexs.size());
											for (int k = 0; k < IndexCnt; ++k)
											{
												// 목록전체 타일인덱스 Flag 해제
												InvStoreInfo_[ItemArrIndexs[k]]->SetItemArrangeFlagOff();
											}

											// 플레이어의 보유골드 증가
											GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

											// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
											MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

											// 인벤창 보유목록에서 해당아이템 제거
											InvArrItemList_[i]->Death();
											std::vector<InvArrangementItemInfo*>::iterator FindIter = InvArrItemList_.begin() + i;
											InvArrItemList_.erase(FindIter);
											break;
										}
									}
								}
								else if (InvTabType::EQUIP == _InvTabType)
								{
									// 2. 해당 장비 아이템의 이전 위치가 인벤창 상단 장착탭이였다면
									//    LocType == _TileIndex 이므로 해당 장착탭만 Flag 해제
									if (_TileIndex == InvArrItemList_[i]->GetStartTileIndex())
									{
										InvEquipInfo_[_TileIndex]->SetItemArrangeFlagOff();

										// 플레이어의 보유골드 증가
										GlobalValue::CurPlayer->HaveGoldAdd(SellItemInfo.Price);

										// 현재 플레이어 아이템 보유목록에서 해당 아이템 삭제
										MainPlayerInfomation::GetInst().PlayerItemDel(SellItemInfo.ItemName_abbreviation, InvArrItemList_[i]->GetLocType(), InvArrItemList_[i]->GetStartTileIndex());

										// 인벤창 보유목록에서 해당 아이템을 제거
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
		// 정보찾기를 실패했다면 해당 아이템 판매처리 중단
		return;
	}
}

void InventoryView::ItemRepairProcess(int _TileIndex, InvTabType _InvTabType)
{
	// 무기상인의 판매창과만 처리가능(수리처리)
	
	// 충돌한 아이템의 내구도가 존재한다면 해당 내구도 회복 후


	// 플레이어의 보유골드량이 감소하고,


	// NPC의 보유골드가 증가한다.


}

bool InventoryView::InventoryArrangeTileCheckOn(const float4& _ItemScaleIndex, const std::string& _ItemName)
{
	bool OneSizeItem = false;

	int StartIndex = -1;
	int StoreCnt = static_cast<int>(InvStoreInfo_.size());
	int CheckStart = -1;

// Goto문말고는 방법이 생각안남!!!!! 일단 goto문으로 재검사처리해놓고 추후 고민해봄
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

	// 빈칸 존재시 검사(1x1크기이면 빈칸검사 제외)
	int ItemWidth = _ItemScaleIndex.ix();
	int ItemHeight = _ItemScaleIndex.iy();
	if (ItemWidth == 1 && ItemHeight == 1)
	{
		// StartIndex만 사용하므로 체크 불필요
		OneSizeItem = true;
	}
	else
	{
		// StartIndex를 포함하는 인덱스목록 모두 검사
		for (int y = 0; y < ItemHeight; ++y)
		{
			for (int x = 0; x < ItemWidth; ++x)
			{
				int Index = StartIndex + x + (y * 10);
				if (0 <= Index && Index < 40)
				{
					if (true == InvStoreInfo_[Index]->GetIsItemArrangeFlag())
					{
						// goto문사용해도됨???
						goto ArrangeTileCheck;
					}
				}
				else
				{
					// 모든 타일배치을 검사하여 실패시
					return false;
				}
			}
		}
	}

	// 위의 모든 조건에 해당하지않는다면 해당 아이템 배치가능하므로 인벤토리에 해당 아이템 배치

	// 1. 아이템 정보 Get
	ItemList BuyItem = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(_ItemName, BuyItem))
	{
		// 해당 아이템 배치 정보 수정
		BuyItem.StartPosition = StartIndex;
		BuyItem.ItemLocType = ItemLocType::Inven_Bottom;

		// 정보를 찾았으므로 해당 아이템정보를 인벤토리 배치 아이템 목록에 추가(항상 하단보관탭으로 위치설정)
		int ListCnt = static_cast<int>(InvArrItemList_.size());
		ItemLocType LocType = ItemLocType::Inven_Bottom;
		float4 RenderPos = InvStoreInfo_[StartIndex]->GetTilePos();

		// 아이템크기가 1x1이면
		if (true == OneSizeItem)
		{
			InvArrangementItemInfo* NewItemInfo = GetLevel()->CreateActor<InvArrangementItemInfo>();
			if (true == NewItemInfo->CreateItemInfo(ListCnt, StartIndex, LocType, BuyItem.ItemName_abbreviation, RenderPos, true))
			{
				// StartIndex만 차지하는 아이템 배치
				InvStoreInfo_[StartIndex]->SetItemArrangeFlagOn();

				// 인벤창이 활성화되어있다면 렌더러 On상태로 전환
				NewItemInfo->On();

				// 목록에 해당 아이템 추가
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
				// 인덱스 목록을 모두 차지하는 아이템 배치
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

				// 배치목록 정렬
				std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

				// 차지하고있는 칸의 중앙 위치를 계산한다.
				// 첫번째 타일의 위치와 마지막번째 타일의 위치를 Get
				float4 ReRenderPos = float4::ZERO;
				int IndexCnt = static_cast<int>(TileArrIndexList.size());
				float4 BeginTilePos = InvStoreInfo_[TileArrIndexList[0]]->GetTilePos();
				float4 EndTilePos = InvStoreInfo_[TileArrIndexList[IndexCnt - 1]]->GetTilePos();

				// 두 타일 위치를 비교
				if (BeginTilePos.x == EndTilePos.x) // 해당 아이템의 너비 1
				{
					ReRenderPos.x = BeginTilePos.x;
				}
				else
				{
					BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
					ReRenderPos.x = BeginTilePos.x;
				}

				if (BeginTilePos.y == EndTilePos.y) // 해당 아이템의 높이 1
				{
					ReRenderPos.y = BeginTilePos.y;
				}
				else
				{
					BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
					ReRenderPos.y = BeginTilePos.y;
				}

				NewItemInfo->SetItemRenderPos(ReRenderPos);

				// 아이템 장착 Flag On
				for (int l = 0; l < IndexCnt; ++l)
				{
					InvStoreInfo_[TileArrIndexList[l]]->SetItemArrangeFlagOn();
				}
				NewItemInfo->SetTileIndexList(TileArrIndexList);

				// 인벤창이 활성화되어있다면 아이템렌더러 On상태 전환
				NewItemInfo->On();

				// 목록에 해당 아이템 추가
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
	// 장착한 아이템명에 따라 처리됨
	if (true == _OnAndOff) // 장착
	{
		// 장착시 해당 아이템명에 따라 플레이어의 파트별렌더러가 변경된다.
		// LIT_ -> HVY_
		switch (_ItemLocType)
		{
			case ItemLocType::Inven_Weapon:
			{
				// 장착한 아이템명이 crs이면 HVY_ 상태전환
				if ("crs" == _ItemName)
				{
					GlobalValue::CurPlayer->ItemPutOn(ItemEquipPart::Inv_Weapon);
				}
				// 장착한 아이템명이 wnd이면 LIT_ 상태전환
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
				// 장착한 아이템명이 chn이면 HVY_ 상태전환
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
	else // 장착해제
	{
		// 장착해제시 해당 아이템명에 따라 플레이어의 파트별렌더러가 변경된다.
		// HVY_ -> LIT_
		switch (_ItemLocType)
		{
			case ItemLocType::Inven_Weapon:
			{
				// crs 해제시 LIT_타입으로 돌아간다.
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
				// 장착해제한 아이템명이 chn이면 HVY_ 상태전환
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
