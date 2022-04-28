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

StoreView::StoreView() :
	StoreViewActive_(false),
	StoreViewPanel_(nullptr),
	StoreViewPanelCol_(nullptr),
	StoreGold_(nullptr),
	StoreMaxGold_(nullptr),
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
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

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
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-33.f, -162.f));
	CloseButton_->SetChangeAnimation("Default");

	CloseBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	CloseBtnCol_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.0f));
	CloseBtnCol_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

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
