#include "PreCompile.h"
#include "TakeInOutGoldPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "InventoryView.h"

#include "Storehouse.h"
#include "StoreView.h"

TakeInOutGoldPopup::TakeInOutGoldPopup() :
	PopupType_(TakeInOutPopupType::NONE),
	CreateType_(TakeInOutPopCreateType::NONE),
	MaxHaveGold_(0),
	CurHaveGold_(0),
	Panel_(nullptr),
	TakeInOutPopCol_(nullptr),
	GoldText_(nullptr),
	GoldUpBtn_(nullptr),
	GoldUpBtnCol_(nullptr),
	GoldUpBtn_State_(Button_State::Normal),
	GoldDownBtn_(nullptr),
	GoldDownBtnCol_(nullptr),
	GoldDownBtn_State_(Button_State::Normal),
	CloseBtn_(nullptr),
	CloseBtnCol_(nullptr),
	CloseBtn_State_(Button_State::Normal),
	ApprovedBtn_(nullptr),
	ApprovedCol_(nullptr),
	ApprovedBtn_State_(Button_State::Normal)
{


}

TakeInOutGoldPopup::~TakeInOutGoldPopup()
{
}

void TakeInOutGoldPopup::Start()
{
	// ImageCutting

	// 종료버튼
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);

	// 승인버튼
	GameEngineTexture* ApprovedButtonDefault = GameEngineTextureManager::GetInst().Find("ApprovedButton_Default.png");
	ApprovedButtonDefault->Cut(1, 1);
	GameEngineTexture* ApprovedButtonClick = GameEngineTextureManager::GetInst().Find("ApprovedButton_Click.png");
	ApprovedButtonClick->Cut(1, 1);

	// 골드증가/감소 버튼
	GameEngineTexture* GoldUpButtonDefault = GameEngineTextureManager::GetInst().Find("SpinnerUpBtn_Default.png");
	GoldUpButtonDefault->Cut(1, 1);
	GameEngineTexture* GoldUpButtonClick = GameEngineTextureManager::GetInst().Find("SpinnerUpBtn_Click.png");
	GoldUpButtonClick->Cut(1, 1);
	GameEngineTexture* GoldDownButtonDefault = GameEngineTextureManager::GetInst().Find("SpinnerDownBtn_Default.png");
	GoldDownButtonDefault->Cut(1, 1);
	GameEngineTexture* GoldDownButtonClick = GameEngineTextureManager::GetInst().Find("SpinnerDownBtn_Click.png");
	GoldDownButtonClick->Cut(1, 1);

	Off();
}

void TakeInOutGoldPopup::Update(float _DeltaTime)
{
#pragma region 버튼상태체크
	if (GoldUpBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 골드량 증가(꺼내기/넣기)
			GoldUp();

			GoldUpBtn_State_ = Button_State::Normal;
		}
	}

	if (GoldDownBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 골드량 감소(꺼내기/넣기)
			GoldDown();

			GoldDownBtn_State_ = Button_State::Normal;
		}
	}

	if (CloseBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 해당 창 비활성
			Close();

			CloseBtn_State_ = Button_State::Normal;
		}
	}

	if (ApprovedBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 승인
			Approved();

			ApprovedBtn_State_ = Button_State::Normal;
		}
	}
#pragma endregion

#pragma region 각 버튼 충돌체렌더러 및 충돌체크
	if (nullptr != GoldUpBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(GoldUpBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		GoldUpBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::GoldUpButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != GoldDownBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(GoldDownBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		GoldDownBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::GoldDownButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != CloseBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(CloseBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		CloseBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::CloseButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != ApprovedCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ApprovedCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		ApprovedCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::ApprovedButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != TakeInOutPopCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(TakeInOutPopCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
	}
#pragma endregion
}

void TakeInOutGoldPopup::GoldUpButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		GoldUpBtn_->SetChangeAnimation("Click");

		GoldUpBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		GoldUpBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::GoldDownButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		GoldDownBtn_->SetChangeAnimation("Click");

		GoldDownBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		GoldDownBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::CloseButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseBtn_->SetChangeAnimation("Click");

		CloseBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::ApprovedButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		ApprovedBtn_->SetChangeAnimation("Click");

		ApprovedBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		ApprovedBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::GoldUp()
{
	// 현재 화면에 표시되는 골드를 1씩 증가
	// 단, 보유골드량의 최대치를 넘어가면 계속해서 보유골드량의 최대치를 셋팅
	int Gold = CurHaveGold_ + 1;
	if (MaxHaveGold_ <= Gold)
	{
		CurHaveGold_ = MaxHaveGold_;
		GoldText_->SetPrintText(std::to_string(CurHaveGold_));
		return;
	}

	CurHaveGold_ = Gold;
	GoldText_->SetPrintText(std::to_string(CurHaveGold_));
}

void TakeInOutGoldPopup::GoldDown()
{
	// 현재 화면에 표시되는 골드를 1 감소
	// 단, 0이하로 내려가면 계속해서 0으로 셋팅
	int Gold = CurHaveGold_ - 1;
	if (0 >= Gold)
	{
		CurHaveGold_ = 0;
		GoldText_->SetPrintText(std::to_string(CurHaveGold_));
		return;
	}

	CurHaveGold_ = Gold;
	GoldText_->SetPrintText(std::to_string(CurHaveGold_));
}

void TakeInOutGoldPopup::Close()
{
	// 해당 창을 닫는다.
	Off();
}

void TakeInOutGoldPopup::Approved()
{
	// 해당 창의 타입과 해당창을 생성한 액터의 타입에 따라 
	// 해당창을 생성한 액터에게 해당 골드량을 더하거나 빼준다.

	// 창고창에서 생성한 팝업이라면
	if (TakeInOutPopCreateType::STOREDVIEW == CreateType_)
	{
		// 1. 창고 보유골드 감소 & 플레이어 보유골드 증가
		if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::Storehouse)
		{
			// 꺼내려는 골드가 0보다 클때
			if (0 < CurHaveGold_)
			{
				GlobalValue::Storehouse->GetStoreView()->StoredGoldSub(CurHaveGold_);

				GlobalValue::CurPlayer->HaveGoldAdd(CurHaveGold_);
			}
		}
	}
	// 플레이어에서 생성한 팝업이라면
	else if (TakeInOutPopCreateType::PLAYER == CreateType_)
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			// 1. 현재 플레이어가 마을에 존재하고, 창고창이 열린상태에서의 골드팝업(창고 보유골드 증가 & 플레이어 보유골드 감소)
			if (true == GlobalValue::CurPlayer->GetIsTown() && true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
			{
				if (0 < CurHaveGold_)
				{
					GlobalValue::Storehouse->GetStoreView()->StoredGoldAdd(CurHaveGold_);

					GlobalValue::CurPlayer->HaveGoldSub(CurHaveGold_);
				}
			}
			// 2. 현재 플레이어가 필드에 존재할때(플레이어 보유골드 감소 & 드랍골드량 Set)
			else
			{
				// 드랍용 골드 생성전.....


				GlobalValue::CurPlayer->HaveGoldSub(CurHaveGold_);
			}
		}
	}

	// 팝업창은 Off상태 전환
	TakeInOutGoldPopupInactive();
}

void TakeInOutGoldPopup::CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos, int _MaxGold)
{
	// 정보저장
	PopupType_ = _PopupType;
	CreateType_ = _CreateType;
	MaxHaveGold_ = _MaxGold;

	// 모든 컴포넌트의 위치는 _InitPos을 기준으로 생성

	// 숫자 텍스트 표시를 위한 UI렌더러 생성
	if (TakeInOutPopupType::TakeIn == PopupType_)
	{
		// 저장용 팝업으로 생성됨

		// 판넬 생성(얼마를 저장하시겠습니까? 텍스트 생성)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "얼마를 저장하시겠습니까?", 14.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// 마우스와 충돌중일때 마우스 동작 제한 충돌체
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// 저장용 팝업으로 생성됨


	}
	else if(TakeInOutPopupType::TakeOut == PopupType_)
	{
		// 판넬 생성(얼마를 꺼내시겠습니까? 텍스트 생성)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "얼마를 꺼내시겠습니까?", 14.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// 마우스와 충돌중일때 마우스 동작 제한 충돌체
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// 꺼내기용 팝업으로 생성됨


	}
	else if (TakeInOutPopupType::Drop == PopupType_)
	{
		// 판넬 생성(얼마를 내려놓으시겠습니까? 텍스트 생성)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "얼마를 내려놓으시겠습니까?", 10.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// 마우스와 충돌중일때 마우스 동작 제한 충돌체
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// 내려놓기용 팝업으로 생성
	}

	// 현재 타입의 골드량 표시
	GoldText_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Text));
	GoldText_->SetImage("InvTestTileImage.png");
	GoldText_->GetTransform()->SetLocalScaling(float4(163.f, 20.f));
	GoldText_->GetTransform()->SetLocalPosition(float4(_InitPos.x + 9.f, _InitPos.y));
	GoldText_->TextSetting("diablo", std::to_string(CurHaveGold_), 14.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	GoldText_->SetAlpha(0.f);

	// 숫자증가 버튼생성
	GoldUpBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	GoldUpBtn_->CreateAnimation("SpinnerUpBtn_Default.png", "Default", 0, 0, 0.1f, false);
	GoldUpBtn_->CreateAnimation("SpinnerUpBtn_Click.png", "Click", 0, 0, 0.1f, false);
	GoldUpBtn_->GetTransform()->SetLocalScaling(float4(15.f, 12.f));
	GoldUpBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 88.f, _InitPos.y + 6.f));
	GoldUpBtn_->SetChangeAnimation("Default");

	GoldUpBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	GoldUpBtnCol_->GetTransform()->SetLocalScaling(GoldUpBtn_->GetTransform()->GetLocalScaling());
	GoldUpBtnCol_->GetTransform()->SetLocalPosition(GoldUpBtn_->GetTransform()->GetLocalPosition());

	// 숫자감소 버튼생성
	GoldDownBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	GoldDownBtn_->CreateAnimation("SpinnerDownBtn_Default.png", "Default", 0, 0, 0.1f, false);
	GoldDownBtn_->CreateAnimation("SpinnerDownBtn_Click.png", "Click", 0, 0, 0.1f, false);
	GoldDownBtn_->GetTransform()->SetLocalScaling(float4(15.f, 12.f));
	GoldDownBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 88.f, _InitPos.y - 8.f));
	GoldDownBtn_->SetChangeAnimation("Default");

	GoldDownBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	GoldDownBtnCol_->GetTransform()->SetLocalScaling(GoldDownBtn_->GetTransform()->GetLocalScaling());
	GoldDownBtnCol_->GetTransform()->SetLocalPosition(GoldDownBtn_->GetTransform()->GetLocalPosition());

	// 승인 버튼생성
	ApprovedBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	ApprovedBtn_->CreateAnimation("ApprovedButton_Default.png", "Default", 0, 0, 0.1f, false);
	ApprovedBtn_->CreateAnimation("ApprovedButton_Click.png", "Click", 0, 0, 0.1f, false);
	ApprovedBtn_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
	ApprovedBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 54.f, _InitPos.y - 53.f));
	ApprovedBtn_->SetChangeAnimation("Default");

	ApprovedCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	ApprovedCol_->GetTransform()->SetLocalPosition(ApprovedBtn_->GetTransform()->GetLocalPosition());
	ApprovedCol_->GetTransform()->SetLocalScaling(ApprovedBtn_->GetTransform()->GetLocalScaling());

	// 종료 버튼생성
	CloseBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	CloseBtn_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseBtn_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseBtn_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
	CloseBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x + 52.f, _InitPos.y - 53.f));
	CloseBtn_->SetChangeAnimation("Default");

	CloseBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	CloseBtnCol_->GetTransform()->SetLocalPosition(CloseBtn_->GetTransform()->GetLocalPosition());
	CloseBtnCol_->GetTransform()->SetLocalScaling(CloseBtn_->GetTransform()->GetLocalScaling());
}

void TakeInOutGoldPopup::TakeInOutGoldPopupActive(int _CurHaveGold)
{
	// 정보 리셋
	MaxHaveGold_ = _CurHaveGold;
	CurHaveGold_ = 0;
	GoldText_->SetPrintText(std::to_string(CurHaveGold_));

	// On상태 전환
	On();
}

void TakeInOutGoldPopup::TakeInOutGoldPopupInactive()
{
	// Off상태 전환
	Off();
}
