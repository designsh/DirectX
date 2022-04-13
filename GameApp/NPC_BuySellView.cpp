#include "PreCompile.h"
#include "NPC_BuySellView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
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
	BuyActive_(false),
	SellActive_(false),
	RepairActive_(false),
	BuyBtnState_(Button_State::Normal),
	SellBtnState_(Button_State::Normal),
	RepairBtnState_(Button_State::Normal)
{
}

NPC_BuySellView::~NPC_BuySellView()
{
}

void NPC_BuySellView::Start()
{
}

void NPC_BuySellView::Update(float _DeltaTime)
{
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

	if (nullptr != AllRepairButtonCollider_)	// 전부수리버튼
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(AllRepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		AllRepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::AllRepairButtonClick, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region 버튼상태갱신
	if (BuyBtnState_ == Button_State::Click)	// 구매버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			//BuyButtonRenderer_->SetChangeAnimation("Default");

			BuyBtnState_ = Button_State::Normal;
		}
	}

	if (SellBtnState_ == Button_State::Click)	// 판매버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			//SellButtonRenderer_->SetChangeAnimation("Default");

			SellBtnState_ = Button_State::Normal;
		}
	}

	if (RepairBtnState_ == Button_State::Click)	// 수리버튼상태
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 버튼 애니메이션 변경
			//RepairButtonRenderer_->SetChangeAnimation("Default");

			RepairBtnState_ = Button_State::Normal;
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
			//BuyButtonRenderer_->SetChangeAnimation("Click");
			
			// 마우스커서 애니메이션 변경
			if (false == BuyActive_)
			{
				BuyActive_ = true;
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
			//BuyButtonRenderer_->SetChangeAnimation("Default");
		}
	}
}

void NPC_BuySellView::SellButtonClick(GameEngineCollision* _Other)
{
	if (SellBtnState_ != Button_State::Disabled)
	{
		// 구매버튼 클릭
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// 버튼애니메이션 변경
			//SellButtonRenderer_->SetChangeAnimation("Click");

			// 마우스커서 애니메이션 변경
			if (false == SellActive_)
			{
				SellActive_ = true;
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
			//SellButtonRenderer_->SetChangeAnimation("Default");
		}
	}
}

void NPC_BuySellView::RepairButtonClick(GameEngineCollision* _Other)
{
	if (RepairBtnState_ != Button_State::Disabled)
	{
		// 구매버튼 클릭
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// 버튼애니메이션 변경
			//RepairButtonRenderer_->SetChangeAnimation("Click");

			// 마우스커서 애니메이션 변경
			if (false == RepairActive_)
			{
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
			//RepairButtonRenderer_->SetChangeAnimation("Default");
		}
	}
}

void NPC_BuySellView::AllRepairButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 현재 플레이어가 들고있는 모든 아이템 중 내구도가 존재하는 모든 아이템 수리

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
			// 탭 1칸(기타)


			// 버튼(구매/판매, null, null)


			break;
		}
		case NPCType::WeaponShop:
		{
			// 탭 2칸(무기, 갑옷)


			// 버튼(구매/판매, 수리, 전부수리)


			break;
		}
	}
}

void NPC_BuySellView::NPCBuySellViewActive()
{
	//On();

	// 판매창 활성화시 플레이어의 인벤토리창도 활성화되며,
	

	// 플레이어의 하단상태바의 미니메뉴를 비활성화 시킨다.




	// 해당 NPC의 상단메뉴 Off




}

void NPC_BuySellView::NPCBuySellViewInactive()
{
	//Off();

	// 판매창 비활성화시 플레이어의 인벤토리창도 비활성화되며,
	

	// 플레이어의 하단상태바의 미니메뉴를 활성화 시킨다.





	// 해당 NPC의 상단메뉴 On




}
