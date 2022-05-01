#include "PreCompile.h"
#include "StoreView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"
#include "InventoryView.h"

#include "MouseObject.h"

#include "TakeInOutGoldPopup.h"

StoreView::StoreView() :
	StoreViewActive_(false),
	StoredGold_(0),
	StoredMaxGold_(2500000),
	StoreViewPanel_(nullptr),
	StoreViewPanelCol_(nullptr),
	StoreGoldTakeOutPopBtn_(nullptr),
	StoreGoldTakeOutPopColBtn_(nullptr),
	StoreGoldTakeOutPopBtnState_(Button_State::Normal),
	StoreGold_(nullptr),
	StoreMaxGold_(nullptr),
	TakeOutGoldPopup_(nullptr),
	CloseButton_(nullptr),
	CloseBtnCol_(nullptr),
	CloseBtnState_(Button_State::Normal)
{
}

StoreView::~StoreView()
{
}

void StoreView::Start()
{
	// ImageCutting
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);

	GameEngineTexture* GoldButtonDefault = GameEngineTextureManager::GetInst().Find("GoldIconBtn_Default.png");
	GoldButtonDefault->Cut(1, 1);
	GameEngineTexture* GoldButtonClick = GameEngineTextureManager::GetInst().Find("GoldIconBtn_Click.png");
	GoldButtonClick->Cut(1, 1);

	// Panel 생성
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StorehouseView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	StoreViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	StoreViewPanel_->SetImage("Player_StorehouseView_Panel.png");
	StoreViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// Player 이동제한용 판넬 충돌체 생성
	StoreViewPanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	StoreViewPanelCol_->SetName("Player_StoreView");
	StoreViewPanelCol_->GetTransform()->SetLocalScaling(StoreViewPanel_->GetTransform()->GetLocalScaling());
	StoreViewPanelCol_->GetTransform()->SetLocalPosition(StoreViewPanel_->GetTransform()->GetLocalPosition());

	// 창닫기 버튼관련
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-33.f, -162.f));
	CloseButton_->SetChangeAnimation("Default");

	CloseBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	CloseBtnCol_->GetTransform()->SetLocalScaling(CloseButton_->GetTransform()->GetLocalScaling());
	CloseBtnCol_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// 골드꺼내기팝업 관련
	StoreGoldTakeOutPopBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	StoreGoldTakeOutPopBtn_->CreateAnimation("GoldIconBtn_Default.png", "Default", 0, 0, 0.1f, false);
	StoreGoldTakeOutPopBtn_->CreateAnimation("GoldIconBtn_Click.png", "Click", 0, 0, 0.1f, false);
	StoreGoldTakeOutPopBtn_->GetTransform()->SetLocalScaling(float4(20.f, 18.f));
	StoreGoldTakeOutPopBtn_->GetTransform()->SetLocalPosition(float4(-236.f, 208.f));
	StoreGoldTakeOutPopBtn_->SetChangeAnimation("Default");

	StoreGoldTakeOutPopColBtn_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	StoreGoldTakeOutPopColBtn_->GetTransform()->SetLocalScaling(StoreGoldTakeOutPopBtn_->GetTransform()->GetLocalScaling());
	StoreGoldTakeOutPopColBtn_->GetTransform()->SetLocalPosition(StoreGoldTakeOutPopBtn_->GetTransform()->GetLocalPosition());

	// 골드량 관련
	StoreGold_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StoreGold_->SetImage("InvTestTileImage.png");
	StoreGold_->TextSetting("diablo", std::to_string(StoredGold_), 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	StoreGold_->GetTransform()->SetLocalScaling(float4(150.f, 15.f));
	StoreGold_->GetTransform()->SetLocalPosition(float4(-148.f, 208.f));
	StoreGold_->SetAlpha(0.f);

	StoreMaxGold_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StoreMaxGold_->SetImage("InvTestTileImage.png");
	StoreMaxGold_->TextSetting("diablo", "최대 저장량 : 2,500,000", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	StoreMaxGold_->GetTransform()->SetLocalScaling(float4(172.f, 17.f));
	StoreMaxGold_->GetTransform()->SetLocalPosition(float4(-160.f, 182.f));
	StoreMaxGold_->SetAlpha(0.f);

	// 골드꺼내기 팝업관련
	TakeOutGoldPopup_ = GetLevel()->CreateActor<TakeInOutGoldPopup>();
	TakeOutGoldPopup_->CreateTakePopup(TakeInOutPopupType::TakeOut, TakeInOutPopCreateType::STOREDVIEW, float4(280.f - WindowHarfSize.x, WindowHarfSize.y - 220.f), StoredGold_);

	// 아이템배치 정보관련
	StoreViewInfo_.ArrangeTiles_.clear();
	StoreViewInfo_.ArrangeTiles_.resize(6 * 8);
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			int Index = (y * 6) + x;
			StoreViewInfo_.ArrangeTiles_[Index].ItemArrangementFlag_ = false;
			StoreViewInfo_.ArrangeTiles_[Index].Index_ = Index;
			StoreViewInfo_.ArrangeTiles_[Index].IndexX_ = x;
			StoreViewInfo_.ArrangeTiles_[Index].IndexY_ = y;

			// 위치정보 및 크기정보 셋팅
			float4 TilePos = float4::ZERO;
			TilePos.x = -232.f + (x * 28.f) + (x * 1.f);
			TilePos.y = -60.f + (y * 28.f) + (y * 1.f);
			StoreViewInfo_.ArrangeTiles_[Index].TilePos_ = TilePos;

			float4 TileScale = float4(28.f, 28.f, 1.f);
			StoreViewInfo_.ArrangeTiles_[Index].TileScale_ = TileScale;

			// 렌더러 생성
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
		}
	}

	// 창고창의 배치타일 충돌체 생성
	StoreViewInfo_.StoreArrTileCols_.clear();
	StoreViewInfo_.StoreArrTileCols_.resize(6 * 8);
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 6; ++x)
		{
			int Index = (y * 6) + x;
			float4 ArrColPos = StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->GetTransform()->GetLocalPosition();
			StoreViewInfo_.StoreArrTileCols_[Index] = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
			StoreViewInfo_.StoreArrTileCols_[Index]->GetTransform()->SetLocalPosition(ArrColPos);
			StoreViewInfo_.StoreArrTileCols_[Index]->GetTransform()->SetLocalScaling(float4(28.f, 28.f));
		}
	}

	// 기본 Off상태로 생성
	Off();
}

void StoreView::Update(float _DeltaTime)
{
	// 창닫기 버튼 클릭상태일때 애니메이션 변경 및 모든 창닫기 처리
	if (CloseBtnState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 플레이어의 인벤토리창 Off 및 창고창 Off처리
				PrivateStoreViewActive();
			}

			CloseButton_->SetChangeAnimation("Default");
			CloseBtnState_ = Button_State::Normal;
		}
	}

	// 골드팝업 버튼 클릭상태일때 애니메이션 변경 및 골드꺼내기 팝업 열기 처리
	if (StoreGoldTakeOutPopBtnState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 골드 꺼내기 팝업창 활성화
			GoldPopupViewActive();

			StoreGoldTakeOutPopBtn_->SetChangeAnimation("Default");
			StoreGoldTakeOutPopBtnState_ = Button_State::Normal;
		}
	}

#pragma region 충돌체렌더러 & 충돌체크
	if (nullptr != StoreViewPanelCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(StoreViewPanelCol_->GetTransform(), CollisionType::Rect);
#endif
	}

	if (nullptr != CloseBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(CloseBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		CloseBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StoreView::CloseButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != StoreGoldTakeOutPopColBtn_)
	{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(StoreGoldTakeOutPopColBtn_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		StoreGoldTakeOutPopColBtn_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StoreView::GoldButtonClick, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region 아이템배치타일충돌체크
	if (false == StoreViewInfo_.StoreArrTileCols_.empty())
	{
		for (int i = 0; i < static_cast<int>(StoreViewInfo_.StoreArrTileCols_.size()); ++i)
		{
			if (nullptr != StoreViewInfo_.StoreArrTileCols_[i])
			{
#ifdef _DEBUG
				if (false == TakeOutGoldPopup_->IsUpdate()) // 골드팝업창이 활성화되면 충돌체 렌더러 표시안함
				{
					GetLevel()->UIPushDebugRender(StoreViewInfo_.StoreArrTileCols_[i]->GetTransform(), CollisionType::Rect);
				}
#endif // _DEBUG

				StoreViewInfo_.StoreArrTileCols_[i]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StoreView::ArrangeTileClick, this, std::placeholders::_1, i));
			}
		}
	}
#pragma endregion
}

void StoreView::CloseButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Click");

		CloseBtnState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Default");
	}
}

void StoreView::GoldButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		StoreGoldTakeOutPopBtn_->SetChangeAnimation("Click");

		StoreGoldTakeOutPopBtnState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		StoreGoldTakeOutPopBtn_->SetChangeAnimation("Default");
	}
}

void StoreView::PrivateStoreViewActive()
{
	// 창고창 창닫기버튼 클릭시 호출
	if (true == StoreViewActive_)
	{
		// Flag 해제
		StoreViewActive_ = false;

		// 창고에서 골드꺼내기 팝업이 활성화 상태라면 비활성화
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			TakeOutGoldPopup_->TakeInOutGoldPopupInactive();
		}

		// 창고창 비활성
		Off();

		// 현재 창고창이 보유하고있는 모든 아이템렌더러 비활성화
		int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
		for (int i = 0; i < HaveItemListCnt; ++i)
		{
			StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Off();
		}

		// 플레이어의 인벤토리창 비활성화 처리
		GlobalValue::CurPlayer->InventoryViewEnabled(false);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

		// 플레이어의 하단상태바의 미니메뉴를 비활성화 시킨다.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);
	}
}

void StoreView::GoldPopupViewActive()
{
	// 골드꺼내기 팝업 활성화(현재 저장된 골드량 전달하여 팝업 리셋)
	TakeOutGoldPopup_->TakeInOutGoldPopupActive(StoredGold_);
}

void StoreView::ArrangeTileClick(GameEngineCollision* _Other, int _Index)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 골드팝업창이 활성화되면 아이템배치 못하도록 처리
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			return;
		}

		// 마우스의 상태가 Stay or Move 상태일때만 가능
		if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() ||
			MouseState::Move == GlobalValue::CurMouse->GetMouseState())
		{
			// 마우스가 아이템을 들고있고, 해당 충돌한 타일에 배치된 아이템이 없을경우
			// => 마우스가 들고있는 아이템을 해당 타일에 배치
			if (false == StoreViewInfo_.ArrangeTiles_[_Index].ItemArrangementFlag_ && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemPlacement(_Index);
			}
			// 마우스가 아이템을 들고있지않고, 해당 충돌한 타일에 배치된 아이템이 있을경우
			// => 해당 타일에 배치된 아이템을 마우스에 전달
			else if (true == StoreViewInfo_.ArrangeTiles_[_Index].ItemArrangementFlag_ && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemDisposition(_Index);
			}
		}
	}
}

void StoreView::ItemPlacement(int _ColTileIndex)
{
	// 마우스가 들고있는 아이템의 크기정보를 이용하여 해당 타일을 포함한 타일에 아이템 배치하며,
	// 마우스가 해당 아이템을 내려놓도록 설정

	// 1. 마우스가 현재 들고있는 아이템명을 가져와 편집 후
	std::string CurItemName = GlobalValue::CurMouse->GetHoldItemName();
	size_t DotFindIndex = CurItemName.find('.');
	CurItemName = CurItemName.substr(0, DotFindIndex);

	// 2. 전체 아이템정보목록에서 해당 아이템의 정보를 Get
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(CurItemName, CurItemInfo))
	{
		// 해당 아이템 정보를 찾았다면 크기정보 Get
		int WidthSize = CurItemInfo.WidthSize;
		int HeightSize = CurItemInfo.HeightSize;
		if (WidthSize == 1 && HeightSize == 1)
		{
			// 1x1 크기를 가지는 아이템이므로 배치하려는 타일을 검사하여 해당 타일이 비어있다면 아이템배치
			// 비어있지않다면 리턴
			if (true == StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_)
			{
				// 해당 타일에 이미 아이템이 배치되었있으므로 리턴
				return;
			}
			// 해당 타일이 비어있어 아이템 배치가능
			else
			{
				// 해당 타일정보 갱신
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_ = true;
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TileRenderer_->SetAlpha(0.5f);

				// 해당 아이템을 보유아이템 목록에 추가
				StoredItem NewItem = {};
				NewItem.OneSize_ = true;
				NewItem.StartIndex = _ColTileIndex;
				NewItem.RenderPos_ = StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TilePos_;
				
				// 배치하기 위한아이템 정보 수정하여 정보저장
				CurItemInfo.ItemLocType = ItemLocType::Storehouse_Bottom;
				CurItemInfo.StartPosition = _ColTileIndex;
				NewItem.ItemInfo_ = CurItemInfo;

				// 아이템 렌더러 생성
				std::string ItemName = CurItemInfo.ItemName_abbreviation_Inven;
				ItemName += ".png";
				NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Render));

				// 아이템 렌더러 위치 및 크기정보 셋팅 후 저장
				NewItem.ItemRenderer_->SetImage(ItemName);
				NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);
				
				StoreViewInfo_.HaveItemList_.push_back(NewItem);
			}
		}
		else
		{
			// 1x1크기가 아닌 아이템이므로 배치하려는 타일의 주변타일을 모두 검사하여 배치가능한지 판단 후
			// 배치가능하다면 해당 아이템을 배치하고, 배치 불가능하다면 리턴
			if (false == ItemPlacementCheck(_ColTileIndex, CurItemInfo))
			{
				// 배치불가능 판정이므로 리턴
				return;
			}
		}

		// 모든 정보 생성과 아이템 배치완료가 되었다면 마우스가 해당 아이템을 내려놓는다.
		GlobalValue::CurMouse->ItemPutDown();
	}
}

bool StoreView::ItemPlacementCheck(int _ColTileIndex, ItemList& _CurItemInfo)
{
	// 배치명령이 들어온 타일을 기준으로 아이템크기만큼 비교하여 배치가능한지 체크
	// 배치가능하다면 아이템을 배치하고, 배치타일정보를 갱신하며, 아이템 보유목록에 해당 아이템을 추가하고,
	// true를 반환한다.

	// 해당 아이템 기본정보 Get
	std::string CurItemName = _CurItemInfo.ItemName_abbreviation_Inven;

	int StartIndex = _ColTileIndex;
	int WidthSize = _CurItemInfo.WidthSize;
	int HeightSize = _CurItemInfo.HeightSize;

	// 배치가능검사 시작!!!!

	// 1. 배치목록 리스트를 생성해놓는다.
	std::vector<int> TileArrIndexList;
	TileArrIndexList.clear();

	// 2. 생성한 배치목록리스트에 해당 조건에 따라 타일인덱스를 추가할수있는지 검사한다.
	
	// 배치하려는 타일이 좌측끝인경우
	if (StartIndex % 6 == 0)
	{
		// 1. 최좌측타일이면서 최상단 타일인경우
		if (42 <= StartIndex && StartIndex <= 47)
		{
			bool ChkFlag = false;
			for (int k = 0; k < HeightSize; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex + l - (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
					{
						// 시작인덱스 기준으로 검사하여 한개라도 TRUE검출시 배치불가능 판단
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// 모두 배치가능한 타일이라면 타일목록생성
			if (false == ChkFlag)
			{
				for (int k = 0; k < HeightSize; ++k)
				{
					for (int l = 0; l < WidthSize; ++l)
					{
						int CalcIndex = StartIndex + l - (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
		// 2. 최좌측타일이면서 최하단 타일인경우
		else if (0 <= StartIndex && StartIndex <= 5)
		{
			bool ChkFlag = false;
			for (int k = 0; k < HeightSize; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex + l + (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
						int CalcIndex = StartIndex + l + (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
		// 3. 두경우가 아닌경우
		else
		{
			bool ChkFlag = false;
			for (int k = -1; k < HeightSize - 1; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex + l + (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
						int CalcIndex = StartIndex + l + (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
	}
	// 배치하려는 타일이 우측끝인경우
	else if (StartIndex % 6 == 5)
	{
		// 1. 최우측타일이면서 최상단 타일인경우
		if (42 <= StartIndex && StartIndex <= 47)
		{
			bool ChkFlag = false;
			for (int k = 0; k < HeightSize; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex - l - (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
						int CalcIndex = StartIndex - l - (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
		// 2. 최우측타일이면서 최하단 타일인경우
		else if (0 <= StartIndex && StartIndex <= 5)
		{
			bool ChkFlag = false;
			for (int k = 0; k < HeightSize; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex - l + (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
						int CalcIndex = StartIndex - l + (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
		// 3. 두경우가 아닌경우
		else
		{
			bool ChkFlag = false;
			for (int k = -1; k < HeightSize - 1; ++k)
			{
				for (int l = 0; l < WidthSize; ++l)
				{
					int CalcIndex = StartIndex - l + (k * 6);
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
						int CalcIndex = StartIndex - l + (k * 6);
						TileArrIndexList.push_back(CalcIndex);
					}
				}
			}
		}
	}
	// 배치하려는 타일이 최좌측도 아니고, 최우측도 아닌경우
	else
	{
		// 1. 배치하려는 타일의 좌상단 검사
		//    StartIndex가 가장 우하단 타일인덱스가 된다.
		bool LeftTop = false;
		for (int k = 0; k < HeightSize; ++k)
		{
			for (int l = 0; l < WidthSize; ++l)
			{
				int CalcIndex = StartIndex - l + (k * 6);
				if (0 <= CalcIndex && CalcIndex < 48)
				{
					if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
					int CalcIndex = StartIndex - l + (k * 6);
					TileArrIndexList.push_back(CalcIndex);
				}
			}
		}
		else // 좌상단 배치 실패시
		{
			// 2. 배치하려는 타일의 상단 검사
			//    StartIndex가 중앙하단 타일인덱스가 된다.
			bool Top = false;
			for (int k = 0; k < HeightSize; ++k)
			{
				for (int l = -1; l < WidthSize - 1; ++l)
				{
					int CalcIndex = StartIndex + l + (k * 6);
					if (0 <= CalcIndex && CalcIndex < 48)
					{
						if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
			else // 상단 배치 실패시
			{
				// 3. 우상단 검사
				//    StartIndex가 가장 좌하단 타일인덱스가 된다.
				bool RightTop = false;
				for (int k = 0; k < HeightSize; ++k)
				{
					for (int l = 0; l < WidthSize; ++l)
					{
						int CalcIndex = StartIndex + l + (k * 6);
						if (0 <= CalcIndex && CalcIndex < 48)
						{
							if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
							int CalcIndex = StartIndex + l + (k * 6);
							TileArrIndexList.push_back(CalcIndex);
						}
					}
				}
				else // 우상단 실패시
				{
					// 4. 우단 검사
					//    StartIndex가 센터좌단 타일인덱스가 된다.
					bool Right = false;
					for (int k = -1; k < HeightSize - 1; ++k)
					{
						for (int l = 0; l < WidthSize; ++l)
						{
							int CalcIndex = StartIndex + l + (k * 6);
							if (0 <= CalcIndex && CalcIndex < 48)
							{
								if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
								int CalcIndex = StartIndex + l + (k * 6);
								TileArrIndexList.push_back(CalcIndex);
							}
						}
					}
					else // 우단 실패시
					{
						// 5. 우하단 검사
						//    StartIndex가 가장 좌상단 타일인덱스가 된다.
						bool RightBot = false;
						for (int k = 0; k < HeightSize; ++k)
						{
							for (int l = 0; l < WidthSize; ++l)
							{
								int CalcIndex = StartIndex + l - (k * 6);
								if (0 <= CalcIndex && CalcIndex < 48)
								{
									if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
									int CalcIndex = StartIndex + l - (k * 6);
									TileArrIndexList.push_back(CalcIndex);
								}
							}
						}
						else // 우하단 실패시
						{
							// 6. 하단 검사
							//    StartIndex가 가장 센터상단 타일인덱스가 된다.
							bool Bot = false;
							for (int k = 0; k < HeightSize; ++k)
							{
								for (int l = -1; l < WidthSize - 1; ++l)
								{
									int CalcIndex = StartIndex + l - (k * 6);
									if (0 <= CalcIndex && CalcIndex < 48)
									{
										if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
										int CalcIndex = StartIndex + l - (k * 6);
										TileArrIndexList.push_back(CalcIndex);
									}
								}
							}
							else // 하단실패시
							{
								// 7. 좌하단 검사
								//    StartIndex가 가장 우상단 타일인덱스가 된다.
								bool LeftBot = false;
								for (int k = 0; k < HeightSize; ++k)
								{
									for (int l = 0; l < WidthSize; ++l)
									{
										int CalcIndex = StartIndex - l - (k * 6);
										if (0 <= CalcIndex && CalcIndex < 48)
										{
											if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
											int CalcIndex = StartIndex - l - (k * 6);
											TileArrIndexList.push_back(CalcIndex);
										}
									}
								}
								else // 좌하단실패시
								{
									// 8. 좌단 검사
									//    StartIndex가 가장 센터우단 타일인덱스가 된다.
									bool Left = false;
									for (int k = 0; k < HeightSize; ++k)
									{
										for (int l = 0; l < WidthSize; ++l)
										{
											int CalcIndex = StartIndex - l - (k * 6);
											if (0 <= CalcIndex && CalcIndex < 48)
											{
												if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
												int CalcIndex = StartIndex - l - (k * 6);
												TileArrIndexList.push_back(CalcIndex);
											}
										}
									}
									else // 좌단실패시
									{
										// 9. 센터
										//    StartIndex가 센터 타일인덱스가 된다.
										bool Center = false;
										for (int k = -1; k < HeightSize - 1; ++k)
										{
											for (int l = -1; l < WidthSize - 1; ++l)
											{
												int CalcIndex = StartIndex + l + (k * 6);
												if (0 <= CalcIndex && CalcIndex < 48)
												{
													if (true == StoreViewInfo_.ArrangeTiles_[CalcIndex].ItemArrangementFlag_)
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
													int CalcIndex = StartIndex + l + (k * 6);
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

	// 3. 위 조건에 의하여 타일인덱스목록에 타일목록이 생성되어 있다면 배치가능으로 판단하고
	//    해당 아이템을 배치하기위한 처리를 수행한다.
	if (false == TileArrIndexList.empty())
	{
		// 배치 인덱스 목록 정렬
		std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

		// 아이템 정보 생성
		StoredItem NewItem = {};
		NewItem.OneSize_ = false;
		NewItem.StartIndex = _ColTileIndex;
		NewItem.ArrangeIndexs_ = TileArrIndexList;
		
		// 아이템 렌더링 위치 계산
		// 위에서 정렬했으므로 인덱스목록의 첫번째와 마지막번째 타일의 위치를 이용하여 계산
		int ArrTileIndexCnt = static_cast<int>(TileArrIndexList.size());
		float4 BeginTilePos = StoreViewInfo_.ArrangeTiles_[TileArrIndexList[0]].TilePos_;
		float4 EndTilePos = StoreViewInfo_.ArrangeTiles_[TileArrIndexList[ArrTileIndexCnt - 1]].TilePos_;
		if (BeginTilePos.x == EndTilePos.x) // 해당 아이템의 너비 1
		{
			NewItem.RenderPos_.x = BeginTilePos.x;
		}
		else
		{
			BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
			NewItem.RenderPos_.x = BeginTilePos.x;
		}

		if (BeginTilePos.y == EndTilePos.y) // 해당 아이템의 높이 1
		{
			NewItem.RenderPos_.y = BeginTilePos.y;
		}
		else
		{
			BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
			NewItem.RenderPos_.y = BeginTilePos.y;
		}

		// 아이템 정보 중 수정사항 수정
		NewItem.ItemInfo_ = _CurItemInfo;
		NewItem.ItemInfo_.ItemLocType = ItemLocType::Storehouse_Bottom;
		NewItem.ItemInfo_.StartPosition = _ColTileIndex;

		// 아이템 렌더러 생성
		std::string TextureName = NewItem.ItemInfo_.ItemName_abbreviation_Inven;
		TextureName += ".png";
		NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Render));
		NewItem.ItemRenderer_->SetImage(TextureName);
		NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);

		StoreViewInfo_.HaveItemList_.push_back(NewItem);

		// 배치된 타일 목록 Flag On처리
		for (int i = 0; i < ArrTileIndexCnt; ++i)
		{
			StoreViewInfo_.ArrangeTiles_[TileArrIndexList[i]].ItemArrangementFlag_ = true;
			StoreViewInfo_.ArrangeTiles_[TileArrIndexList[i]].TileRenderer_->SetAlpha(0.5f);
		}

		// 4. 배치완료했다면 true를 반환하여 배치완료 처리한다.
		return true;
	}

	return false;
}

void StoreView::ItemDisposition(int _ColTileIndex)
{
	// 창고창 해당 타일에 배치된 아이템의 크기정보를 이용하여 해당 타일에서 배치해제를 시키고,
	// 해당 아이템을 마우스에 전달하여 마우스가 해당아이템을 가지도록 설정

	// 보유 아이템 목록을 검사
	int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
	for (int i = 0; i < HaveItemListCnt; ++i)
	{
		if (true == StoreViewInfo_.HaveItemList_[i].OneSize_)
		{
			// 1x1 크기의 아이템이므로 해당 충돌된 타일의 인덱스에 존재하는 아이템인지 판단
			if (StoreViewInfo_.HaveItemList_[i].StartIndex == _ColTileIndex)
			{
				// 존재하는 아이템이라면 해당 아이템을 마우스에 전달하고 해당 아이템을 목록에서 삭제하며,
				// 타일 Flag를 해제시킨다.
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_ = false;
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TileRenderer_->SetAlpha(0.f);

				std::string PutItemName = StoreViewInfo_.HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
				PutItemName += ".png";
				float4 ItemScale = StoreViewInfo_.HaveItemList_[i].ItemRenderer_->GetTransform()->GetLocalScaling();
				StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Death();

				// 마우스가 해당 아이템을 들도록 설정
				GlobalValue::CurMouse->ItemHold(PutItemName, ItemScale);

				// 해당 아이템을 아이템목록에서 제거
				std::vector<StoredItem>::iterator DelIter = StoreViewInfo_.HaveItemList_.begin() + i;
				StoreViewInfo_.HaveItemList_.erase(DelIter);
				return;
			}
		}
		else
		{
			// 1x1 크기의 아이템이 아니므로 해당 아이템이 차지하는 인덱스목록에 해당 충돌된 타일의 인덱스가 존재하는지 판단
			int ArrTileCnt = static_cast<int>(StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_.size());
			for (int j = 0; j < ArrTileCnt; ++j)
			{
				if (StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[j] == _ColTileIndex)
				{
					// 해당 아이템을 보유아이템목록에서 제거하며, 해당 아이템이 차지하고있던 타일의 인덱스 정보를 갱신하고,
					// 해당 아이템을 마우스에 전달한다.
					std::string ItemName = StoreViewInfo_.HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
					ItemName += ".png";
					float4 ItemScale = StoreViewInfo_.HaveItemList_[i].ItemRenderer_->GetTransform()->GetLocalScaling();

					// 해당 아이템이 차지하고 있던 타일정보 갱신
					int CurItemArrTileCnt = static_cast<int>(StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_.size());
					for (int k = 0; k < CurItemArrTileCnt; ++k)
					{
						StoreViewInfo_.ArrangeTiles_[StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[k]].ItemArrangementFlag_ = false;
						StoreViewInfo_.ArrangeTiles_[StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[k]].TileRenderer_->SetAlpha(0.f);
					}

					// 해당 아이템 렌더러를 먼저 죽인다음
					StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Death();

					// 해당 아이템을 목록에서 제거
					std::vector<StoredItem>::iterator DelIter = StoreViewInfo_.HaveItemList_.begin() + i;
					StoreViewInfo_.HaveItemList_.erase(DelIter);

					// 해당 아이템을 마우스가 든다.
					GlobalValue::CurMouse->ItemHold(ItemName, ItemScale);
					
					return;
				}
			}
		}
	}
}

void StoreView::StoreViewOff()
{
	// 플레이어의 인벤토리창에서 Close Button 클릭시 호출하므로
	// 창고창을 닫는 역할만 수행한다.
	if (true == StoreViewActive_)
	{
		// 활성화 Flag Off
		StoreViewActive_ = false;

		// 창고에서 골드꺼내기 팝업이 활성화 상태라면 비활성화
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			TakeOutGoldPopup_->TakeInOutGoldPopupInactive();
		}

		// 창고창 비활성화
		Off();

		// 창고창이 현재 보유하고있는 모든 아이템을 비활성화
		int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
		for (int i = 0; i < HaveItemListCnt; ++i)
		{
			StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Off();
		}
	}
}

void StoreView::StoreViewOn()
{
	if (false == StoreViewActive_)
	{
		// 활성화 Flag On
		StoreViewActive_ = true;

		// 1. 플레이어의 인벤토리창이 활성화시킨다.
		GlobalValue::CurPlayer->InventoryViewEnabled(true);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(true);

		// 플레이어의 하단상태바의 미니메뉴를 비활성화 시킨다.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(false);

		// 2. 창고창 활성화 시킨다.
		On();

		// 3. 창고창이 현재 보유하고있는 모든 아이템을 활성화
		int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
		for (int i = 0; i < HaveItemListCnt; ++i)
		{
			StoreViewInfo_.HaveItemList_[i].ItemRenderer_->On();
		}
	}
}

int StoreView::StoredGoldAdd(int _Gold)
{
	// 현재 저장된 골드량에서 저장한골드 더하기
	// 단, 최대 저장량을 넘어가면 최대량까지만 저장하고,
	// 나머지는 다시 돌려준다.
	int StoredGold = StoredGold_ + _Gold;
	if (StoredMaxGold_ < StoredGold)
	{
		// 보유골드량은 최대량이 된다.
		StoredGold_ = StoredMaxGold_;
		StoreGold_->SetPrintText(std::to_string(StoredGold_));

		// 최대치에서 현재보유골드량+추가저장골드량을 빼서 나머지값을 반환한다.
		return StoredMaxGold_ - StoredGold;
	}
	
	// 최대량이 넘어가지않는다면 골드량 저장
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// 모든 골드 저장완료시 -1 반환
	return -1;
}

int StoreView::StoredGoldSub(int _Gold)
{
	// 현재 저장된 골드량에서 해당 골드만큼 빼기
	// 단, 꺼내려는 골드량이 현재 저장된 보유골드보다 클경우
	// 현재 저장된 보유골드만 반환한다.
	int StoredGold = StoredGold_ - _Gold;
	if (0 >= StoredGold)
	{
		// 보유골드량은 0이 된다
		StoredGold_ = 0;
		StoreGold_->SetPrintText(std::to_string(StoredGold_));

		return 0;
	}

	// 현재 저장된 보유골드량을 알맞게 찾았다면 해당 골드만큼 차감
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// 현재 보유골드에 맞게 골드를 꺼냈다면 -1 반환
	return -1;
}
