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
	//TakeOutGoldPopup_->CreateTakePopup(TakeInOutPopupType::TakeOut, TakeInOutPopCreateType::STOREDVIEW, float4());

	// 아이템배치 정보관련






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
		//GetLevel()->UIPushDebugRender(StoreGoldTakeOutPopColBtn_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		StoreGoldTakeOutPopColBtn_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StoreView::GoldButtonClick, this, std::placeholders::_1));
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

		// 창고창 비활성
		Off();

		// 플레이어의 인벤토리창 비활성화 처리
		GlobalValue::CurPlayer->InventoryViewEnabled(false);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

		// 플레이어의 하단상태바의 미니메뉴를 비활성화 시킨다.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);
	}
}

void StoreView::GoldPopupViewActive()
{
	// 골드꺼내기 팝업 활성화




}

void StoreView::StoreViewOff()
{
	// 플레이어의 인벤토리창에서 Close Button 클릭시 호출하므로
	// 창고창을 닫는 역할만 수행한다.
	if (true == StoreViewActive_)
	{
		// 활성화 Flag Off
		StoreViewActive_ = false;

		// 창고창 비활성화
		Off();
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
	int StoredGold = StoredMaxGold_ - _Gold;
	if (0 >= StoredGold)
	{
		// 현재 저장된 보유골드만큼만 반환
		return StoredMaxGold_;
	}

	// 현재 저장된 보유골드량을 알맞게 찾았다면 해당 골드만큼 차감
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// 현재 보유골드에 맞게 골드를 꺼냈다면 -1 반환
	return -1;
}
