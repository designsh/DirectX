#include "PreCompile.h"
#include "NPC_BuySellView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "AllItemInfomation.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"
#include "InventoryView.h"

#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"

NPC_BuySellView::NPC_BuySellView() :
	ViewPanel_(nullptr),
	BuyButtonRenderer_(nullptr),
	BuyButtonCollider_(nullptr),
	SellButtonRenderer_(nullptr),
	SellButtonCollider_(nullptr),
	RepairButtonRenderer_(nullptr),
	RepairButtonCollider_(nullptr),
	AllRepairButtonRenderer_(nullptr),
	AllRepairButtonCollider_(nullptr),
	NPCClassType_(NPCClassType::Akara),
	BuySellViewType_(NPCType::PotionShop),
	HaveGoldRenderer_(nullptr),
	HaveGold_(100000),
	BuyActive_(false),
	SellActive_(false),
	RepairActive_(false),
	BuyBtnState_(Button_State::Normal),
	SellBtnState_(Button_State::Normal),
	RepairBtnState_(Button_State::Normal),
	AllRepairBtnState_(Button_State::Normal),
	CurTabIndex(0)
{
}

NPC_BuySellView::~NPC_BuySellView()
{
}

void NPC_BuySellView::Start()
{
	// Button Image Cutting
	GameEngineTexture* BuyBtnClick = GameEngineTextureManager::GetInst().Find("BuySellBtn_Buy_Click.png");
	BuyBtnClick->Cut(1, 1);
	GameEngineTexture* BuyBtnDefault = GameEngineTextureManager::GetInst().Find("BuySellBtn_Buy_Default.png");
	BuyBtnDefault->Cut(1, 1);

	GameEngineTexture* SellBtnClick = GameEngineTextureManager::GetInst().Find("BuySellBtn_Sell_Click.png");
	SellBtnClick->Cut(1, 1);
	GameEngineTexture* SellBtnDefault = GameEngineTextureManager::GetInst().Find("BuySellBtn_Sell_Default.png");
	SellBtnDefault->Cut(1, 1);

	GameEngineTexture* RepairBtnClick = GameEngineTextureManager::GetInst().Find("BuySellBtn_Repair_Click.png");
	RepairBtnClick->Cut(1, 1);
	GameEngineTexture* RepairBtnDefault = GameEngineTextureManager::GetInst().Find("BuySellBtn_Repair_Default.png");
	RepairBtnDefault->Cut(1, 1);

	GameEngineTexture* AllRepairBtnClick = GameEngineTextureManager::GetInst().Find("BuySellBtn_AllRepair_Click.png");
	AllRepairBtnClick->Cut(1, 1);
	GameEngineTexture* AllRepairBtnDefault = GameEngineTextureManager::GetInst().Find("BuySellBtn_AllRepair_Default.png");
	AllRepairBtnDefault->Cut(1, 1);

	GameEngineTexture* NoneBtnClick = GameEngineTextureManager::GetInst().Find("BuySellBtn_None_Click.png");
	NoneBtnClick->Cut(1, 1);
	GameEngineTexture* NoneBtnDefault = GameEngineTextureManager::GetInst().Find("BuySellBtn_None_Default.png");
	NoneBtnDefault->Cut(1, 1);

	// Tab Image Cutting
	GameEngineTexture* TabSel = GameEngineTextureManager::GetInst().Find("BuySellTab_Sel.png");
	TabSel->Cut(1, 1);
	GameEngineTexture* TabDesel = GameEngineTextureManager::GetInst().Find("BuySellTab_DeSel.png");
	TabDesel->Cut(1, 1);

	// 골드량 렌더러 생성
	HaveGoldRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
	HaveGoldRenderer_->SetImage("InvTestTileImage.png");
	HaveGoldRenderer_->GetTransform()->SetLocalScaling(float4(184.f, 17.f));
	HaveGoldRenderer_->GetTransform()->SetLocalPosition(float4(-212.f, -128.f));
	HaveGoldRenderer_->TextSetting("diablo", std::to_string(HaveGold_), 14.f, FW1_RIGHT | FW1_VCENTER, float4::WHITE, float4(90.f, 0.f), 100);
	HaveGoldRenderer_->SetAlpha(0.f);
}

void NPC_BuySellView::Update(float _DeltaTime)
{
#pragma region 플레이어이동체크판단용 충돌체
	if (nullptr != BuySellViewPanelCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(BuySellViewPanelCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
	}
#pragma endregion

#pragma region 버튼상태갱신
	if (BuyBtnState_ == Button_State::Click)	// 구매버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			BuyButtonRenderer_->SetChangeAnimation("Default");

			BuyBtnState_ = Button_State::Normal;
		}
	}

	if (SellBtnState_ == Button_State::Click)	// 판매버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			SellButtonRenderer_->SetChangeAnimation("Default");

			SellBtnState_ = Button_State::Normal;
		}
	}

	if (RepairBtnState_ == Button_State::Click)	// 수리버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			RepairButtonRenderer_->SetChangeAnimation("Default");

			RepairBtnState_ = Button_State::Normal;
		}
	}

	if (AllRepairBtnState_ == Button_State::Click)	// 전부수리/창닫기 버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// 해당 판매창종료(잡화상인이면 창닫기버튼이므로 창닫기 기능처리)
			if (NPCType::PotionShop == BuySellViewType_)
			{
				PrivateNPCBuySellViewInactive();

				// 모든 버튼 상태 리셋
				SpecialCursorFlagReset();
			}

			AllRepairBtnState_ = Button_State::Normal;
		}
	}
#pragma endregion

#pragma region 버튼충돌체크
	if (nullptr != BuyButtonCollider_)	// 구매버튼
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(BuyButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		BuyButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::BuyButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != SellButtonCollider_)	// 판매버튼
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(SellButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		SellButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::SellButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != RepairButtonCollider_)	// 수리버튼
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(RepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		RepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::RepairButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != AllRepairButtonCollider_)	// 전부수리/창닫기버튼
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(AllRepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		AllRepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::AllRepairButtonClick, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region 탭선택충돌체크
	if (false == BuySellViewTabs_.empty())
	{
		for (int i = 0; i < static_cast<int>(BuySellViewTabs_.size()); ++i)
		{
			if (nullptr != BuySellViewTabs_[i].TabCollision_)
			{
#ifdef _DEBUG
				GetLevel()->PushDebugRender(BuySellViewTabs_[i].TabCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

				BuySellViewTabs_[i].TabCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::SelectTabClick, this, std::placeholders::_1, i));
			}
		}
	}
#pragma endregion

#pragma region 배치타일충돌체크
	if (false == ArrangeTileCols_.empty())
	{
		for (int i = 0; i < static_cast<int>(ArrangeTileCols_.size()); ++i)
		{
			if (nullptr != ArrangeTileCols_[i])
			{
#ifdef _DEBUG
				GetLevel()->PushDebugRender(ArrangeTileCols_[i]->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

				ArrangeTileCols_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::ArrangeTileClick, this, std::placeholders::_1, i));
			}
		}
	}
#pragma endregion
}

void NPC_BuySellView::BuyButtonClick(GameEngineCollision* _Other)
{
	if (BuyBtnState_ != Button_State::Disabled)
	{
		// 구매버튼 클릭
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// 버튼애니메이션 변경
			BuyButtonRenderer_->SetChangeAnimation("Click");
			
			// 마우스커서 애니메이션 변경
			if (false == BuyActive_)
			{
				BuyActive_ = true;
				SellActive_ = false;
				RepairActive_ = false;
				GlobalValue::CurMouse->BuyCursorActive();
			}
			else
			{
				BuyActive_ = false;
				GlobalValue::CurMouse->BuyCursorInActive();
			}

			BuyBtnState_ = Button_State::Click;
		}
		else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			BuyButtonRenderer_->SetChangeAnimation("Default");

			BuyBtnState_ = Button_State::Normal;
		}
	}
}

void NPC_BuySellView::SellButtonClick(GameEngineCollision* _Other)
{
	if (SellBtnState_ != Button_State::Disabled)
	{
		// 판매버튼 클릭
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// 버튼애니메이션 변경
			SellButtonRenderer_->SetChangeAnimation("Click");

			// 마우스커서 애니메이션 변경
			if (false == SellActive_)
			{
				BuyActive_ = false;
				SellActive_ = true;
				RepairActive_ = false;
				GlobalValue::CurMouse->SellCursorActive();
			}
			else
			{
				SellActive_ = false;
				GlobalValue::CurMouse->SellCursorInactive();
			}

			SellBtnState_ = Button_State::Click;
		}
		else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			SellButtonRenderer_->SetChangeAnimation("Default");

			SellBtnState_ = Button_State::Normal;
		}
	}
}

void NPC_BuySellView::RepairButtonClick(GameEngineCollision* _Other)
{
	if (RepairBtnState_ != Button_State::Disabled)
	{
		// 무기상인일때만 수리기능 활성가능
		if (NPCType::WeaponShop == BuySellViewType_)
		{
			// 수리버튼 클릭
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// 버튼애니메이션 변경
				RepairButtonRenderer_->SetChangeAnimation("Click");

				if (false == RepairActive_)
				{
					BuyActive_ = false;
					SellActive_ = false;
					RepairActive_ = true;
					GlobalValue::CurMouse->RepairCursorActive();
				}
				else
				{
					RepairActive_ = false;
					GlobalValue::CurMouse->RepairCursorInactive();
				}

				RepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				RepairButtonRenderer_->SetChangeAnimation("Default");

				RepairBtnState_ = Button_State::Normal;
			}
		}
		else
		{
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// 버튼애니메이션 변경
				RepairButtonRenderer_->SetChangeAnimation("Click");

				RepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				RepairButtonRenderer_->SetChangeAnimation("Default");

				RepairBtnState_ = Button_State::Normal;
			}
		}
	}
}

void NPC_BuySellView::AllRepairButtonClick(GameEngineCollision* _Other)
{
	if (AllRepairBtnState_ != Button_State::Disabled)
	{
		if (NPCType::WeaponShop == BuySellViewType_)
		{
			// 전부수리버튼 클릭
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// 버튼애니메이션 변경
				AllRepairButtonRenderer_->SetChangeAnimation("Click");

				AllRepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				AllRepairButtonRenderer_->SetChangeAnimation("Default");

				AllRepairBtnState_ = Button_State::Normal;
			}
		}
		else // 무기상점이 아닐때 창닫기 버튼으로 사용
		{
			// 전부수리버튼 클릭
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// 버튼애니메이션 변경
				AllRepairButtonRenderer_->SetChangeAnimation("Click");

				AllRepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				AllRepairButtonRenderer_->SetChangeAnimation("Default");

				AllRepairBtnState_ = Button_State::Normal;
			}
		}
	}
}

void NPC_BuySellView::PrivateNPCBuySellViewInactive()
{	
	// 판매창 비성화
	Off();

	// 현재탭에 속한 Renderer, Collider 비활성화
	int ArrangeTileCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].ArrangeTiles_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->Off();
	}

	int ArrangeColCnt = static_cast<int>(ArrangeTileCols_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		ArrangeTileCols_[i]->Off();
	}

	int HaveItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < HaveItemCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->Off();
	}

	// 현재마우스 커서상태를 리셋(기본상태로 전환)
	GlobalValue::CurMouse->CursorStateReset();

	// 판매창 활성화시 플레이어의 인벤토리창도 비활성화,
	GlobalValue::CurPlayer->InventoryViewEnabled(false);
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

	// 플레이어의 하단상태바의 미니메뉴를 활성화 시킨다.
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);

	// 해당 NPC의 상단메뉴 On
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			GlobalValue::ChandleryNPC->TopMenuBarActive();
			break;
		}
		case NPCClassType::Charsi:
		{
			GlobalValue::WeaponNPC->TopMenuBarActive();
			break;
		}
	}
}

void NPC_BuySellView::PublicNPCBuySellViewActive()
{
	// 판매창 활성화
	On();

	// 현재탭에 속한 Renderer, Collider 활성화
	int ArrangeTileCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].ArrangeTiles_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->On();
	}

	int ArrangeColCnt = static_cast<int>(ArrangeTileCols_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		ArrangeTileCols_[i]->On();
	}

	int HaveItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < HaveItemCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->On();
	}

	// 판매창 활성화시 플레이어의 인벤토리창도 활성화되며,
	GlobalValue::CurPlayer->InventoryViewEnabled(true);
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(true);

	// 플레이어의 하단상태바의 미니메뉴를 비활성화 시킨다.
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(false);

	// 해당 NPC의 상단메뉴 Off
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			GlobalValue::ChandleryNPC->TopMenuBarInactive();
			break;
		}
		case NPCClassType::Charsi:
		{
			GlobalValue::WeaponNPC->TopMenuBarInactive();
			break;
		}
	}
}

void NPC_BuySellView::PublicNPCBuySellViewInactive()
{
	// 판매창 비성화
	Off();

	// 현재탭에 속한 Renderer, Collider 비활성화
	int ArrangeTileCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].ArrangeTiles_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->Off();
	}

	int ArrangeColCnt = static_cast<int>(ArrangeTileCols_.size());
	for (int i = 0; i < ArrangeTileCnt; ++i)
	{
		ArrangeTileCols_[i]->Off();
	}

	int HaveItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < HaveItemCnt; ++i)
	{
		BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->Off();
	}

	// 현재마우스 커서상태를 리셋(기본상태로 전환)
	GlobalValue::CurMouse->CursorStateReset();

	// 특수기능 마우스커서 변경을 위한 버튼 Flag 모두 해제
	SpecialCursorFlagReset();

	// 해당 NPC의 상단메뉴 On
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			GlobalValue::ChandleryNPC->TopMenuBarActive();
			break;
		}
		case NPCClassType::Charsi:
		{
			GlobalValue::WeaponNPC->TopMenuBarActive();
			break;
		}
	}
}


void NPC_BuySellView::CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType)
{
	// 정보저장
	BuySellViewType_ = _BuySellViewType;
	NPCClassType_ = _NPCClassType;

	// 윈도우크기 Get
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();

	// NPC타입에 따른 판매창 생성

	// 판매창 판넬
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("BuySell_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();
	ViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	ViewPanel_->SetImage("BuySell_Panel.png");
	ViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// 플레이어 이동불가처리를 위한 충돌체 생성
	BuySellViewPanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	BuySellViewPanelCol_->SetName("NPC_BuySellView");
	BuySellViewPanelCol_->GetTransform()->SetLocalScaling(ViewPanel_->GetTransform()->GetLocalScaling());
	BuySellViewPanelCol_->GetTransform()->SetLocalPosition(ViewPanel_->GetTransform()->GetLocalPosition());

	// 판매창타입별 버튼 및 탭생성
	switch (BuySellViewType_)
	{
		case NPCType::PotionShop:
		{
			#pragma region 탭정보생성(기타)

			// 탭이름 생성
			std::string TabName = "MISC";

			// 탭정보 생성
			BuySellViewTabs_.clear();
			BuySellViewTabs_.resize(1);
			for (int i = 0; i < 1; ++i)
			{
				BuySellViewTabs_[i].TabIndex_ = i;
				BuySellViewTabs_[i].TabType_ = ItemLocType::BuySell_Etc;
				BuySellViewTabs_[i].TabActive_ = true;

				// 탭렌더러 및 충돌체 생성
				BuySellViewTabs_[i].TabRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
				BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_DeSel.png", "TabDeselect", 0, 0, 0.1f, false);
				BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_Sel.png", "TabSelect", 0, 0, 0.1f, false);

				float4 TabPos = float4(-281.f + (i * 79.f), 224.f);
				BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalPosition(TabPos);
				BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalScaling(float4(79.f, 30.f));
				if (true == BuySellViewTabs_[i].TabActive_)
				{
					BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabSelect");
					BuySellViewTabs_[i].TabRenderer_->TextSetting("diablo", TabName, 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f));
				}
				else
				{
					BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabDeselect");
					BuySellViewTabs_[i].TabRenderer_->TextSetting("diablo", TabName, 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
				}

				BuySellViewTabs_[i].TabCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
				BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalPosition(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalPosition());
				BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalScaling(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalScaling());

				// 해당 탭의 배치타일정보(UI1_Tab)
				BuySellViewTabs_[i].ArrangeTiles_.clear();
				BuySellViewTabs_[i].ArrangeTiles_.resize(10 * 10);
				for (int y = 0; y < 10; ++y)
				{
					for (int x = 0; x < 10; ++x)
					{
						int Index = (y * 10) + x;
						BuySellViewTabs_[i].ArrangeTiles_[Index].ItemArrangementFlag_ = false;
						BuySellViewTabs_[i].ArrangeTiles_[Index].Index_ = Index;
						BuySellViewTabs_[i].ArrangeTiles_[Index].IndexX_ = x;
						BuySellViewTabs_[i].ArrangeTiles_[Index].IndexY_ = y;

						// 위치정보 및 크기정보 셋팅
						float4 TilePos = float4::ZERO;
						TilePos.x = -290.f + (x * 28.f) + (x * 1.f);
						TilePos.y = -98.f + (y * 28.f) + (y * 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TilePos_ = TilePos;

						float4 TileScale = float4(28.f, 28.f, 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileScale_ = TileScale;

						// 렌더러 생성
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->Off();
					}
				}

				// 해당 탭이 보유하고있는 아이템목록(UI1_Render) - 활력물약, 포탈스크롤, 아이템감정스크롤
				CreateItemList(i);
			}
			#pragma endregion

			#pragma region 버튼(구매, 판매, null, 창닫기)
			// 구매버튼 렌더러 (UI1_Button)
			BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4(-188.f, -162.f));
			BuyButtonRenderer_->SetChangeAnimation("Default");

			// 구매버튼 충돌체(UI1_Collider)
			BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			// 판매버튼 렌더러 (UI1_Button)
			SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			SellButtonRenderer_->GetTransform()->SetLocalPosition(float4(-136.f, -162.f));
			SellButtonRenderer_->SetChangeAnimation("Default");

			// 판매버튼 충돌체(UI1_Collider)
			SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			// 기본버튼 렌더러(UI1_Button)
			RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Default.png", "Default", 0, 0, 0.1f, false);
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Click.png", "Click", 0, 0, 0.1f, false);
			RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-84.f, -162.f));
			RepairButtonRenderer_->SetChangeAnimation("Default");

			// 기본버튼 충돌체(UI1_Collider)
			RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			// 창닫기버튼 렌더러(UI1_Button)
			AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			AllRepairButtonRenderer_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-32.f, -162.f));
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// 창닫기버튼 충돌체(UI1_Collider)
			AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
		case NPCType::WeaponShop:
		{
			#pragma region 탭정보생성(무기, 갑옷)

			// 탭이름 생성
			std::string TabName[2] = { {"WEAPONS"}, {"ARMORS"} };

			// 탭정보 생성
			BuySellViewTabs_.clear();
			BuySellViewTabs_.resize(2);
			for (int i = 0; i < 2; ++i)
			{
				BuySellViewTabs_[i].TabIndex_ = i;
				BuySellViewTabs_[i].TabType_ = static_cast<ItemLocType>(static_cast<int>(ItemLocType::BuySell_Weapon) + i);

				// 현재선택된 탭만 TRUE셋팅
				if (i == CurTabIndex)
				{
					BuySellViewTabs_[i].TabActive_ = true;
				}
				else
				{
					BuySellViewTabs_[i].TabActive_ = false;
				}
				
				// 탭렌더러 및 충돌체 생성
				BuySellViewTabs_[i].TabRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
				BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_DeSel.png", "TabDeselect", 0, 0, 0.1f, false);
				BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_Sel.png", "TabSelect", 0, 0, 0.1f, false);

				float4 TabPos = float4(-281.f + (i * 79.f), 224.f);
				BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalPosition(TabPos);
				BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalScaling(float4(79.f, 30.f));
				if (true == BuySellViewTabs_[i].TabActive_)
				{
					BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabSelect");
					BuySellViewTabs_[i].TabRenderer_->TextSetting("diablo", TabName[i], 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f));
				}
				else
				{
					BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabDeselect");
					BuySellViewTabs_[i].TabRenderer_->TextSetting("diablo", TabName[i], 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
				}

				BuySellViewTabs_[i].TabCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
				BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalPosition(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalPosition());
				BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalScaling(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalScaling());

				// 해당 탭의 배치타일정보(UI1_Tab)
				BuySellViewTabs_[i].ArrangeTiles_.clear();
				BuySellViewTabs_[i].ArrangeTiles_.resize(10 * 10);
				for (int y = 0; y < 10; ++y)
				{
					for (int x = 0; x < 10; ++x)
					{
						int Index = (y * 10) + x;
						BuySellViewTabs_[i].ArrangeTiles_[Index].ItemArrangementFlag_ = false;
						BuySellViewTabs_[i].ArrangeTiles_[Index].Index_ = Index;
						BuySellViewTabs_[i].ArrangeTiles_[Index].IndexX_ = x;
						BuySellViewTabs_[i].ArrangeTiles_[Index].IndexY_ = y;

						// 위치정보 및 크기정보 셋팅
						float4 TilePos = float4::ZERO;
						TilePos.x = -290.f + (x * 28.f) + (x * 1.f);
						TilePos.y = -98.f + (y * 28.f) + (y * 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TilePos_ = TilePos;

						float4 TileScale = float4(28.f, 28.f, 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileScale_ = TileScale;

						// 렌더러 생성
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->Off();
					}
				}

				// 해당 탭이 보유하고있는 아이템목록(UI1_Render) - 플레이어 장착무기,방어구 등등
				CreateItemList(i);
			}
			#pragma endregion

			#pragma region 버튼(구매, 판매, 전부수리, 창닫기)
			// 구매버튼 렌더러 (UI1_Button)
			BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4(-188.f, -162.f));
			BuyButtonRenderer_->SetChangeAnimation("Default");

			// 구매버튼 충돌체(UI1_Collider)
			BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			// 판매버튼 렌더러 (UI1_Button)
			SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			SellButtonRenderer_->GetTransform()->SetLocalPosition(float4(-136.f, -162.f));
			SellButtonRenderer_->SetChangeAnimation("Default");

			// 판매버튼 충돌체(UI1_Collider)
			SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			// 수리버튼 렌더러(UI1_Button)
			RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Default.png", "Default", 0, 0, 0.1f, false);
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Click.png", "Click", 0, 0, 0.1f, false);
			RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-84.f, -162.f));
			RepairButtonRenderer_->SetChangeAnimation("Default");

			// 수리버튼 충돌체(UI1_Collider)
			RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			// 전부수리버튼 렌더러(UI1_Button)
			AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Default.png", "Default", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Click.png", "Click", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-32.f, -162.f));
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// 전부수리버튼 충돌체(UI1_Collider)
			AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
	}

	// 판매창의 배치타일 충돌체 생성
	ArrangeTileCols_.clear();
	ArrangeTileCols_.resize(10 * 10);
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			int Index = (y * 10) + x;
			float4 ArrColPos = BuySellViewTabs_[CurTabIndex].ArrangeTiles_[Index].TileRenderer_->GetTransform()->GetLocalPosition();
			ArrangeTileCols_[Index] = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			ArrangeTileCols_[Index]->GetTransform()->SetLocalPosition(ArrColPos);
			ArrangeTileCols_[Index]->GetTransform()->SetLocalScaling(float4(28.f, 28.f));
			ArrangeTileCols_[Index]->Off();
		}
	}
}

void NPC_BuySellView::SelectTabClick(GameEngineCollision* _Other, int _Index)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 현재 인덱스를 이용하여 처리
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetChangeAnimation("TabDeselect");
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetTextColor(float4::WHITE);

		// 현재 탭인덱스에 따른 비활성화 처리
		int ArrangeTileCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].ArrangeTiles_.size());
		for (int i = 0; i < ArrangeTileCnt; ++i)
		{
			BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->Off();
		}

		int TabItemListCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
		for (int i = 0; i < TabItemListCnt; ++i)
		{
			BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->Off();
		}

		// 변경된 현재 탭인덱스
		CurTabIndex = _Index;
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetChangeAnimation("TabSelect");
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetTextColor(float4(0.8f, 0.8f, 0.4f));

		// 현재 탭인덱스에 따른 활성화처리
		int CurArrangeTileCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].ArrangeTiles_.size());
		for (int i = 0; i < CurArrangeTileCnt; ++i)
		{
			BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->On();
		}

		int CurTabItemListCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
		for (int i = 0; i < CurTabItemListCnt; ++i)
		{
			BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->On();
		}
	}
}

void NPC_BuySellView::ArrangeTileClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 해당 배치타일에 아이템이 있다면
		if (true == BuySellViewTabs_[CurTabIndex].ArrangeTiles_[_Index].ItemArrangementFlag_)
		{
			std::string SelectItemName = "";

			// 아이템목록에서 해당 아이템 찾기
			switch (BuySellViewType_)
			{
				// 물약상점
				case NPCType::PotionShop:
				{
					SelectItemName = FindChandleryItem(_Index);

					break;
				}
				// 무기상점
				case NPCType::WeaponShop:
				{
					SelectItemName = FindWeaponItem(_Index);

					break;
				}
			}

			// 아이템을 찾지못했다면 리턴
			if (true == SelectItemName.empty())
			{
				return;
			}

			// 아이템을 찾았다면 현재 마우스의 커서상태에 따라 처리를 달리한다.
			if (MouseState::Buy == GlobalValue::CurMouse->GetMouseState())
			{
				// 판매창이 가지고있는 아이템에만 적용 가능
				// 판매창의 아이템을 클릭시 해당 아이템 구매 및 플레이어 인벤토리 빈칸에 배치, 아이템가격만큼 NPC보유골드 증가
				// 아이템가격만큼 플레이어의 보유골드 감소
				// 단, 플레이어의 인벤토리에 빈칸이 없다면 실패
				
				float4 ItemScale = GetItemScale(SelectItemName);
				if (float4::ZERO == ItemScale)
				{
					// 아이템 크기 Get 에러
					return;
				}

				// 1. 플레이어의 인벤토리를 검사(하단 보관탭) InventoryViewItemArrageCheckOn
				// 2. 인벤토리에 배치가능하다면 해당 아이템 인벤토리창에 배치 및 플레이어 보유아이템목록에 추가
				if (true == GlobalValue::CurPlayer->InventoryViewItemArrageCheckOn(ItemScale, SelectItemName))
				{
					// 3. 아이템 구매를 완료했으므로 해당 아이템 보유갯수를 체크하여
					//    갯수가 0일때 해당 아이템을 판매창 아이템목록에서 제거 후
					int ItemIndex = FindItemListIndex(SelectItemName);

					// 플레이어가 구매했으므로 남은 수량 -1
					--BuySellViewTabs_[CurTabIndex].HaveItemList_[ItemIndex].ItemRemainsQuantity_;

					// 아이템 판매가 정상적으로 완료되었으므로 해당 아이템 가격만큼 NPC 보유골드 증가 후
					AddHaveGold(BuySellViewTabs_[CurTabIndex].HaveItemList_[ItemIndex].ItemInfo_.Price);

					// 현재 남은수량이 0이면 더이상 판매할수 없으므로 목록에서 제거 및 관련 배치타일 Flag Off처리
					if (0 == BuySellViewTabs_[CurTabIndex].HaveItemList_[ItemIndex].ItemRemainsQuantity_)
					{
						if (true == ItemErase(SelectItemName))
						{
							return;
						}
						else
						{
							// 사운드실행
							// '~할 수없다'
							return;
						}
					}
				}
				else // 아이템을 더이상 구매할수없음(이유 : 인벤토리 창부족)
				{
					// 사운드실행
					// '~할 수없다'
					return;
				}
			}
		}
	}
}

void NPC_BuySellView::CreateItemList(int _TabIndex)
{
	switch (BuySellViewType_)
	{
		// 잡화상점 - 활력물약, 포탈스크롤, 아이템감정스크롤
		case NPCType::PotionShop:
		{
			// 기타탭
			std::string ItemNameList[3] = { {"invvpl"}, {"invbsc"}, {"invchm"} };
			int ItemStartPos[3] = { {9}, {19}, {29} };

			// 0. 활력포션(invvpl)
			// 1. 포탈스크롤(invbsc)
			// 2. 아이템감정스크롤(invchm)

			for (int i = 0; i < 3; ++i)
			{
				HaveItem NewItem = {};
				NewItem.OneSize_ = true;
				NewItem.StartIndex = ItemStartPos[i];

				ItemList NewItemInfo = {};
				AllItemInfomation::GetInst().ItemInfoFindInvName(ItemNameList[i], NewItemInfo);
				NewItem.ItemInfo_ = NewItemInfo;
				NewItem.ItemRemainsQuantity_ = 999;
				NewItem.RenderPos_ = float4(BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].TilePos_);
				NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));

				std::string TextureName = ItemNameList[i];
				TextureName += ".png";
				NewItem.ItemRenderer_->SetImage(TextureName);
				NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);
				NewItem.ItemRenderer_->Off();

				// 아이템 배치 관련 갱신
				BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].TileRenderer_->SetAlpha(0.5f);
				BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].ItemArrangementFlag_ = true;

				// 관리목록에 추가
				BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
			}

			break;
		}
		// 무기상점 - 플레이어 장착무기,방어구 등등
		case NPCType::WeaponShop:
		{
			// 무기탭
			if (0 == _TabIndex)
			{
				// crs 크리스탈소드
				HaveItem NewItem = {};
				NewItem.OneSize_ = false;
				NewItem.StartIndex = 0;

				// 해당 아이템 크기에 따라 차지하는 배치타일 인덱스 목록 작성
				NewItem.ArrangeIndexs_.clear();
				for (int k = 0; k < 3; ++k)
				{
					for (int l = 0; l < 2; ++l)
					{
						int CalcIndex = NewItem.StartIndex + l + (k * 10);
						if (0 <= CalcIndex && CalcIndex < 100)
						{
							NewItem.ArrangeIndexs_.push_back(CalcIndex);
						}
					}
				}

				// 정렬
				std::sort(NewItem.ArrangeIndexs_.begin(), NewItem.ArrangeIndexs_.end());

				ItemList NewItemInfo = {};
				AllItemInfomation::GetInst().ItemInfoFindInvName("invcrs", NewItemInfo);
				NewItem.ItemInfo_ = NewItemInfo;
				NewItem.ItemRemainsQuantity_ = 1; // 장착아이템은 수량 1개
				NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));
				NewItem.ItemRenderer_->SetImage("invcrs.png");

				// 아이템렌더러 위치 계산
				//float4 RenderPos = float4(-297.f, -97.f);
				float4 RenderPos = float4::ZERO;
				int IndexCnt = static_cast<int>(NewItem.ArrangeIndexs_.size());
				float4 BeginTilePos = BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[0]].TilePos_;
				float4 EndTilePos = BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[IndexCnt - 1]].TilePos_;
				BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
				BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
				RenderPos.x = BeginTilePos.x;
				RenderPos.y = BeginTilePos.y;

				NewItem.RenderPos_ = RenderPos;
				NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(RenderPos);
				
				// 아이템 배치 관련 갱신
				for (int i = 0; i < static_cast<int>(NewItem.ArrangeIndexs_.size()); ++i)
				{
					BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].ItemArrangementFlag_ = true;
					BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].TileRenderer_->SetAlpha(0.5f);
				}
				NewItem.ItemRenderer_->Off();

				// 관리목록에 추가
				BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
			}
			// 방어구탭
			else if (1 == _TabIndex)
			{
				// bhm(투구 2x2), bsh(방패 2x3), chn(갑옷 2x3), hbt(부츠 2x2), tbl(벨트 3x1), tgl(장갑 2x2)
				std::string ItemName[6] = { {"invbhm"}, {"invbsh"}, {"invchn"}, {"invhbt"}, {"invtbl"}, {"invtgl"} };
				int ItemStartIndex[6] = { {0}, {3}, {7}, {30}, {42}, {50} };
				float4 ItemSize[6] = { {float4(2.f, 2.f)}, {float4(2.f, 3.f)}, {float4(2.f, 3.f)}, {float4(2.f, 2.f)}, {float4(3.f, 1.f)}, {float4(2.f, 2.f)} };

				for (int i = 0; i < 6; ++i)
				{
					HaveItem NewItem = {};
					NewItem.OneSize_ = false;
					NewItem.StartIndex = ItemStartIndex[i];

					// 해당 아이템 크기에 따라 차지하는 배치타일 인덱스 목록 작성
					NewItem.ArrangeIndexs_.clear();
					for (int k = 0; k < ItemSize[i].iy(); ++k)
					{
						for (int l = 0; l < ItemSize[i].ix(); ++l)
						{
							int CalcIndex = NewItem.StartIndex + l + (k * 10);
							if (0 <= CalcIndex && CalcIndex < 100)
							{
								NewItem.ArrangeIndexs_.push_back(CalcIndex);
							}
						}
					}

					// 정렬
					std::sort(NewItem.ArrangeIndexs_.begin(), NewItem.ArrangeIndexs_.end());

					ItemList NewItemInfo = {};
					AllItemInfomation::GetInst().ItemInfoFindInvName(ItemName[i], NewItemInfo);
					NewItem.ItemInfo_ = NewItemInfo;
					NewItem.ItemRemainsQuantity_ = 1; // 장착아이템은 수량 1개
					NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));

					std::string TextureName = ItemName[i];
					TextureName += ".png";
					NewItem.ItemRenderer_->SetImage(TextureName);

					// 아이템렌더러 위치 계산
					//float4 RenderPos = float4(-297.f, -97.f);
					float4 RenderPos = float4::ZERO;
					int IndexCnt = static_cast<int>(NewItem.ArrangeIndexs_.size());
					float4 BeginTilePos = BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[0]].TilePos_;
					float4 EndTilePos = BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[IndexCnt - 1]].TilePos_;
					BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
					BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
					RenderPos.x = BeginTilePos.x;
					RenderPos.y = BeginTilePos.y;

					NewItem.RenderPos_ = RenderPos;
					NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(RenderPos);

					// 아이템 배치 관련 갱신
					for (int i = 0; i < static_cast<int>(NewItem.ArrangeIndexs_.size()); ++i)
					{
						BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].ItemArrangementFlag_ = true;
						BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].TileRenderer_->SetAlpha(0.5f);
					}
					NewItem.ItemRenderer_->Off();

					// 관리목록에 추가
					BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
				}
			}
			break;
		}
	}
}

std::string NPC_BuySellView::FindChandleryItem(int _ArrangeIndex)
{
	// 잡화상점일때만 적용가능
	if (NPCType::PotionShop == BuySellViewType_)
	{
		int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
		for (int i = 0; i < ItemCnt; ++i)
		{
			if (_ArrangeIndex == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].StartIndex)
			{
				return BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
			}
		}
	}

	return std::string();
}

std::string NPC_BuySellView::FindWeaponItem(int _ArrangeIndex)
{
	// 무기상점일때만 적용가능
	if (NPCType::WeaponShop == BuySellViewType_)
	{
		int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
		for (int i = 0; i < ItemCnt; ++i)
		{
			int ArrangeIndexCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_.size());
			for (int j = 0; j < ArrangeIndexCnt; ++j)
			{
				// 배치한 인덱스목록을 모두 뒤져서 해당 클릭한 타일의 인덱스를 찾는다.
				if (_ArrangeIndex == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_[j])
				{
					return BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
				}
			}
		}
	}

	return std::string();
}

int NPC_BuySellView::FindItemListIndex(const std::string& _ItemName)
{
	int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		// 배치한 인덱스목록을 모두 뒤져서 해당 클릭한 타일의 인덱스를 찾는다.
		if (_ItemName == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven)
		{
			return i;
		}
	}

	return -1;
}

float4 NPC_BuySellView::GetItemScale(const std::string& _ItemName)
{
	int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		// 배치한 인덱스목록을 모두 뒤져서 해당 클릭한 타일의 인덱스를 찾는다.
		if (_ItemName == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven)
		{
			float4 ReturnValue = float4::ZERO;

			int Width = BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.WidthSize;
			int Height = BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.HeightSize;
			ReturnValue.x = static_cast<float>(Width);
			ReturnValue.y = static_cast<float>(Height);

			return ReturnValue;
		}
	}

	return float4::ZERO;
}

bool NPC_BuySellView::ItemErase(const std::string& _ItemName)
{
	int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
	for (int i = 0; i < ItemCnt; ++i)
	{
		if (_ItemName == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven)
		{
			// 해당아이템이 차지하는 배치타일의 모든 Flag Off 처리
			int IndexCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_.size());
			for (int j = 0; j < IndexCnt; ++j)
			{
				BuySellViewTabs_[CurTabIndex].ArrangeTiles_[BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_[j]].ItemArrangementFlag_ = false;
				BuySellViewTabs_[CurTabIndex].ArrangeTiles_[BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_[j]].TileRenderer_->SetAlpha(0.f);
			}

			// 남은 수량이 0개이므로 아이템 렌더러를 죽이고,
			BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemRenderer_->Death();

			// 해당 아이템은 목록에서 제거
			std::vector<HaveItem>::iterator FindIter = BuySellViewTabs_[CurTabIndex].HaveItemList_.begin() + i;
			BuySellViewTabs_[CurTabIndex].HaveItemList_.erase(FindIter);

			return true;
		}
	}

	return false;
}

void NPC_BuySellView::AddHaveGold(int _Gold)
{
	// NPC가 가지고있는 아이템을 플레이어에게 판매시
	HaveGold_ += _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}

void NPC_BuySellView::SubHaveGold(int _Gold)
{
	// 플레이어가 가지고있는 아이템을 NPC에게 판매시
	HaveGold_ -= _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}

bool NPC_BuySellView::SellItemCheck(const std::string& _SellItemName)
{
	// 보유아이템 목록에서 해당 아이템 탐색하여 해당 아이템이 존재한다면 보유수량 증가,
	// 존재하지않는다면 해당 아이템 목록에 배치
	int TabCnt = static_cast<int>(BuySellViewTabs_.size());
	for (int i = 0; i < TabCnt; ++i)
	{
		int HaveItemListCnt = static_cast<int>(BuySellViewTabs_[i].HaveItemList_.size());
		for (int j = 0; j < HaveItemListCnt; ++j)
		{
			// 동일한 아이템이 존재하면 해당 아이템 남은수량 증가 후 판매창 보유골드량 감소
			if (_SellItemName == BuySellViewTabs_[i].HaveItemList_[j].ItemInfo_.ItemName_abbreviation_Inven)
			{
				++BuySellViewTabs_[i].HaveItemList_[j].ItemRemainsQuantity_;
				SubHaveGold(BuySellViewTabs_[i].HaveItemList_[j].ItemInfo_.Price);
				return true;
			}
		}
	}

	// 보유목록에 존재하지않는다면 해당 아이템 배치처리 후 판매창 보유골드량 감소

	// 1. 해당 아이템의 타입에 따라 Tab인덱스를 결정
	int ArrangeTabIndex = -1;
	ItemList SellItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(_SellItemName, SellItemInfo))
	{
		// 1~5 무기
		if (1 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 5)
		{
			ArrangeTabIndex = 0;
		}
		// 6~15방어구
		else if (6 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 15)
		{
			ArrangeTabIndex = 1;
		}
		// 16~18 잡화탭
		else if (16 <= SellItemInfo.ItemCode && SellItemInfo.ItemCode <= 18)
		{
			ArrangeTabIndex = 0;
		}
	}

	if (-1 == ArrangeTabIndex)
	{
		// 가지고있는 아이템 정보를 넘어서는 코드의 아이템임!!!
		return false;
	}

	// 탭인덱스를 알아내었으므로 해당 탭의 현재 플레이어가 판매한 아이템 보유목록추가 및 배치
	
	// 비어있는 칸 탐색
	int StartIndex = -1;
	int TileCnt = static_cast<int>(BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_.size());
	for (int i = 0; i < TileCnt; ++i)
	{
		if (false == BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[i].ItemArrangementFlag_)
		{
			StartIndex = i;
			break;
		}
	}

	// 판매창의 현재 탭에 비어있는 칸이 미존재
	if (-1 == StartIndex)
	{
		return false;
	}

	// 존재한다면 해당 아이템 크기만큼의 타일을 모두 체크
	int ItemWidth = SellItemInfo.WidthSize;
	int ItemHeight = SellItemInfo.HeightSize;
	for (int y = 0; y < ItemHeight; ++y)
	{
		for (int x = 0; x < ItemWidth; ++x)
		{
			int Index = StartIndex + x + (y * 10);
			if (true == BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[Index].ItemArrangementFlag_)
			{
				// 한칸이라도 배치불가능하다면 판매처리 실패
				return false;
			}
		}
	}

	// 플레이어가 판매한 아이템이 판매가능하고, 해당 탭에 배치가가능하다면 아이템을 생성하여 배치
	HaveItem NewItem = {};
	if (ItemHeight == 1 && ItemWidth == 1)
	{
		NewItem.OneSize_ = true;
	}
	else
	{
		NewItem.OneSize_ = false;
	}

	// 해당 아이템 기본정보 수정
	NewItem.ItemInfo_ = SellItemInfo;
	NewItem.ItemRemainsQuantity_ = 1;

	if (true == NewItem.OneSize_)
	{
		NewItem.StartIndex = StartIndex;

		BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[NewItem.StartIndex].TileRenderer_->SetAlpha(0.5f);
		BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[NewItem.StartIndex].ItemArrangementFlag_ = true;

		// 렌더위치 = 시작인덱스 타일의 위치
		NewItem.RenderPos_ = BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[NewItem.StartIndex].TilePos_;
	}
	else
	{
		std::vector<int> TileArrIndexList;
		TileArrIndexList.clear();
		for (int y = 0; y < ItemHeight; ++y)
		{
			for (int x = 0; x < ItemWidth; ++x)
			{
				int CalcIndex = StartIndex + x + (y * 10);
				if (0 <= CalcIndex && CalcIndex < 40)
				{
					TileArrIndexList.push_back(CalcIndex);
				}
			}
		}

		// 배치인덱스목록 정렬
		std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

		// 배치 인덱스목록 저장
		NewItem.ArrangeIndexs_ = TileArrIndexList;

		int ArrTileIndexListCnt = static_cast<int>(TileArrIndexList.size());
		for (int k = 0; k < ArrTileIndexListCnt; ++k)
		{
			BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[TileArrIndexList[k]].TileRenderer_->SetAlpha(0.5f);
			BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[TileArrIndexList[k]].ItemArrangementFlag_ = true;
		}

		// 렌더위치 계산 = 인덱스목록의 최소인덱스 위치 <-> 인덱스목록의 최대인덱스 위치 사이값
		float4 ReRenderPos = float4::ZERO;
		int IndexCnt = static_cast<int>(NewItem.ArrangeIndexs_.size());
		float4 BeginTilePos = BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[0]].TilePos_;
		float4 EndTilePos = BuySellViewTabs_[ArrangeTabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[IndexCnt - 1]].TilePos_;

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

		NewItem.RenderPos_ = ReRenderPos;
	}

	// 아이템 렌더러생성
	NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));

	std::string TextureName = _SellItemName;
	TextureName += ".png";
	NewItem.ItemRenderer_->SetImage(TextureName);
	NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);

	// 현재 활성화 탭인덱스에 해당 하는 아이템이라면 On, 아니라면 Off
	if (CurTabIndex == ArrangeTabIndex)
	{
		NewItem.ItemRenderer_->On();
	}
	else
	{
		NewItem.ItemRenderer_->Off();
	}

	// 판매창타입과 탭인덱스 타입으로 해당 아이템 위치정보를 결정
	switch (BuySellViewType_)
	{
		case NPCType::PotionShop:
		{
			if (0 == ArrangeTabIndex)
			{
				NewItem.ItemInfo_.ItemLocType = ItemLocType::BuySell_Etc;
			}
			break;
		}
		case NPCType::WeaponShop:
		{
			if (0 == ArrangeTabIndex)
			{
				NewItem.ItemInfo_.ItemLocType = ItemLocType::BuySell_Weapon;
			}
			else if (1 == ArrangeTabIndex)
			{
				NewItem.ItemInfo_.ItemLocType = ItemLocType::BuySell_Armor;
			}
			break;
		}
	}
	
	BuySellViewTabs_[ArrangeTabIndex].HaveItemList_.push_back(NewItem);

	return true;
}

void NPC_BuySellView::SpecialCursorFlagReset()
{
	BuyActive_ = false;
	SellActive_ = false;
	RepairActive_ = false;
}
