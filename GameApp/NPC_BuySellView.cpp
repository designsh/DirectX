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

#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"

int NPC_BuySellView::CurTabIndex = 0;

int NPC_BuySellView::GetCurTabIndex()
{
	return CurTabIndex;
}

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
	AllRepairBtnState_(Button_State::Normal)
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
				PrivateNPCBuySellViewActive();
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

void NPC_BuySellView::PrivateNPCBuySellViewActive()
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
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(1.f, 1.f, 1.f, 0.f));
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

		// 변경된 현재 탭인덱스
		CurTabIndex = _Index;
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetChangeAnimation("TabSelect");
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetTextColor(float4(0.8f, 0.8f, 0.4f));

		// 현재 탭인덱스에 따른 활성화처리
		for (int i = 0; i < ArrangeTileCnt; ++i)
		{
			BuySellViewTabs_[CurTabIndex].ArrangeTiles_[i].TileRenderer_->On();
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
			// 아이템 커서 상태에 따른 처리
			if (MouseState::Buy == GlobalValue::CurMouse->GetMouseState())
			{
				// 판매창이 가지고있는 아이템에만 적용 가능
				// 판매창의 아이템을 클릭시 해당 아이템 구매 및 플레이어 인벤토리 빈칸에 배치, 아이템가격만큼 NPC보유골드 증가
				// 빈칸이 없다면 실패

				
			}
			else if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState())
			{
				// 플레이어가 가지고있는 아이템에만 적용 가능
				// 플레이어 인벤토리창의 아이템을 클릭시 해당 아이템 판매 및 NPC 판매창 빈칸에 배치, 아이템가격만큼 NPC보유골드 감소
				// 빈칸이 없다면 실패


			}
			else if (MouseState::Repair == GlobalValue::CurMouse->GetMouseState())
			{
				// 플레이어가 가지고있는 아이템에만 적용 가능
				// 플레이어 인벤토리창의 아이템을 클릭시 해당 아이템이 내구도가 존재할때 수리, 수리비용만큼 NPC보유골드 증가


			}
			else // 일반커서 상태 일때
			{
				// 아이템목록에서 해당 아이템 찾기
				switch (BuySellViewType_)
				{
					// 물약상점
					case NPCType::PotionShop:
					{
						std::string ItemName = FindChandleryItem(_Index);

						// 마우스에 전달


						// 해당 아이템의 갯수체크하여 남은수량이 0이면 아이템 목록에서 제거


						break;
					}
					// 무기상점
					case NPCType::WeaponShop:
					{
						std::string ItemName = FindWeaponItem(_Index);

						// 마우스에 전달


						// 해당 아이템의 갯수체크하여 남은수량이 0이면 아이템 목록에서 제거


						break;
					}
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
				///NewItem.ItemRenderer_->GetTransform()->SetLocalScaling(BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].TileScale_);
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





			}
			// 방어구탭
			else if (1 == _TabIndex)
			{





			}
			break;
		}
	}
}

std::string NPC_BuySellView::FindChandleryItem(int _ArrangeIndex)
{
	return std::string();
}

std::string NPC_BuySellView::FindWeaponItem(int _ArrangeIndex)
{
	return std::string();
}

void NPC_BuySellView::AddHaveGold(int _Gold)
{
	// 플레이어가 가지고있는 아이템을 NPC에게 판매시
	HaveGold_ += _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}

void NPC_BuySellView::SubHaveGold(int _Gold)
{
	// NPC가 가지고있는 아이템을 플레이어에게 판매시
	HaveGold_ -= _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}
