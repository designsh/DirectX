#include "PreCompile.h"
#include "TakeInOutGoldPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

TakeInOutGoldPopup::TakeInOutGoldPopup() :
	PopupType_(TakeInOutPopupType::NONE),
	CreateType_(TakeInOutPopCreateType::NONE),
	MaxHaveGole_(0),
	CurHaveGold_(0),
	Panel_(nullptr),
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

}

void TakeInOutGoldPopup::GoldDown()
{
	// 현재 화면에 표시되는 골드를 1 감소
	// 단, 0이하로 내려가면 계속해서 0으로 셋팅

}

void TakeInOutGoldPopup::Close()
{
	// 해당 창을 닫는다.

}

void TakeInOutGoldPopup::Approved()
{
	// 해당 창의 타입과 해당창을 생성한 액터의 타입에 따라 
	// 해당창을 생성한 액터에게 해당 골드량을 더하거나 빼준다.


}

void TakeInOutGoldPopup::CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos)
{
	// 정보저장
	PopupType_ = _PopupType;
	CreateType_ = _CreateType;

	// 판넬 생성
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
	Panel_->SetImage("TakeInOutGoldView_Panel.png");
	Panel_->GetTransform()->SetLocalPosition(_InitPos);

	// 숫자 텍스트 표시를 위한 UI렌더러 생성
	if (TakeInOutPopupType::TakeIn == PopupType_)
	{
		// 넣기용 팝업으로 생성됨
		//GoldText_ = createt

	}
	else
	{
		// 꺼내기용 팝업으로 생성됨


	}


	// 숫자증가 버튼생성

	// 숫자감소 버튼생성

	// 승인 버튼생성

	// 종료 버튼생성

}
