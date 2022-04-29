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

	// �����ư
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);

	// ���ι�ư
	GameEngineTexture* ApprovedButtonDefault = GameEngineTextureManager::GetInst().Find("ApprovedButton_Default.png");
	ApprovedButtonDefault->Cut(1, 1);
	GameEngineTexture* ApprovedButtonClick = GameEngineTextureManager::GetInst().Find("ApprovedButton_Click.png");
	ApprovedButtonClick->Cut(1, 1);

	// �������/���� ��ư
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
#pragma region ��ư����üũ
	if (GoldUpBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��差 ����(������/�ֱ�)
			GoldUp();

			GoldUpBtn_State_ = Button_State::Normal;
		}
	}

	if (GoldDownBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��差 ����(������/�ֱ�)
			GoldDown();

			GoldDownBtn_State_ = Button_State::Normal;
		}
	}

	if (CloseBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ش� â ��Ȱ��
			Close();

			CloseBtn_State_ = Button_State::Normal;
		}
	}

	if (ApprovedBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ����
			Approved();

			ApprovedBtn_State_ = Button_State::Normal;
		}
	}
#pragma endregion

#pragma region �� ��ư �浹ü������ �� �浹üũ
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
	// ���� ȭ�鿡 ǥ�õǴ� ��带 1�� ����
	// ��, ������差�� �ִ�ġ�� �Ѿ�� ����ؼ� ������差�� �ִ�ġ�� ����
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
	// ���� ȭ�鿡 ǥ�õǴ� ��带 1 ����
	// ��, 0���Ϸ� �������� ����ؼ� 0���� ����
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
	// �ش� â�� �ݴ´�.
	Off();
}

void TakeInOutGoldPopup::Approved()
{
	// �ش� â�� Ÿ�԰� �ش�â�� ������ ������ Ÿ�Կ� ���� 
	// �ش�â�� ������ ���Ϳ��� �ش� ��差�� ���ϰų� ���ش�.

	// â��â���� ������ �˾��̶��
	if (TakeInOutPopCreateType::STOREDVIEW == CreateType_)
	{
		// 1. â�� ������� ���� & �÷��̾� ������� ����
		if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::Storehouse)
		{
			// �������� ��尡 0���� Ŭ��
			if (0 < CurHaveGold_)
			{
				GlobalValue::Storehouse->GetStoreView()->StoredGoldSub(CurHaveGold_);

				GlobalValue::CurPlayer->HaveGoldAdd(CurHaveGold_);
			}
		}
	}
	// �÷��̾�� ������ �˾��̶��
	else if (TakeInOutPopCreateType::PLAYER == CreateType_)
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			// 1. ���� �÷��̾ ������ �����ϰ�, â��â�� �������¿����� ����˾�(â�� ������� ���� & �÷��̾� ������� ����)
			if (true == GlobalValue::CurPlayer->GetIsTown() && true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
			{
				if (0 < CurHaveGold_)
				{
					GlobalValue::Storehouse->GetStoreView()->StoredGoldAdd(CurHaveGold_);

					GlobalValue::CurPlayer->HaveGoldSub(CurHaveGold_);
				}
			}
			// 2. ���� �÷��̾ �ʵ忡 �����Ҷ�(�÷��̾� ������� ���� & �����差 Set)
			else
			{
				// ����� ��� ������.....


				GlobalValue::CurPlayer->HaveGoldSub(CurHaveGold_);
			}
		}
	}

	// �˾�â�� Off���� ��ȯ
	TakeInOutGoldPopupInactive();
}

void TakeInOutGoldPopup::CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos, int _MaxGold)
{
	// ��������
	PopupType_ = _PopupType;
	CreateType_ = _CreateType;
	MaxHaveGold_ = _MaxGold;

	// ��� ������Ʈ�� ��ġ�� _InitPos�� �������� ����

	// ���� �ؽ�Ʈ ǥ�ø� ���� UI������ ����
	if (TakeInOutPopupType::TakeIn == PopupType_)
	{
		// ����� �˾����� ������

		// �ǳ� ����(�󸶸� �����Ͻðڽ��ϱ�? �ؽ�Ʈ ����)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "�󸶸� �����Ͻðڽ��ϱ�?", 14.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// ���콺�� �浹���϶� ���콺 ���� ���� �浹ü
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// ����� �˾����� ������


	}
	else if(TakeInOutPopupType::TakeOut == PopupType_)
	{
		// �ǳ� ����(�󸶸� �����ðڽ��ϱ�? �ؽ�Ʈ ����)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "�󸶸� �����ðڽ��ϱ�?", 14.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// ���콺�� �浹���϶� ���콺 ���� ���� �浹ü
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// ������� �˾����� ������


	}
	else if (TakeInOutPopupType::Drop == PopupType_)
	{
		// �ǳ� ����(�󸶸� ���������ðڽ��ϱ�? �ؽ�Ʈ ����)
		Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
		Panel_->SetImage("TakeInOutGoldView_Panel.png");
		Panel_->GetTransform()->SetLocalPosition(_InitPos);
		Panel_->TextSetting("diablo", "�󸶸� ���������ðڽ��ϱ�?", 10.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -60.f));

		// ���콺�� �浹���϶� ���콺 ���� ���� �浹ü
		TakeInOutPopCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
		TakeInOutPopCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
		TakeInOutPopCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

		// ��������� �˾����� ����
	}

	// ���� Ÿ���� ��差 ǥ��
	GoldText_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Text));
	GoldText_->SetImage("InvTestTileImage.png");
	GoldText_->GetTransform()->SetLocalScaling(float4(163.f, 20.f));
	GoldText_->GetTransform()->SetLocalPosition(float4(_InitPos.x + 9.f, _InitPos.y));
	GoldText_->TextSetting("diablo", std::to_string(CurHaveGold_), 14.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	GoldText_->SetAlpha(0.f);

	// �������� ��ư����
	GoldUpBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	GoldUpBtn_->CreateAnimation("SpinnerUpBtn_Default.png", "Default", 0, 0, 0.1f, false);
	GoldUpBtn_->CreateAnimation("SpinnerUpBtn_Click.png", "Click", 0, 0, 0.1f, false);
	GoldUpBtn_->GetTransform()->SetLocalScaling(float4(15.f, 12.f));
	GoldUpBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 88.f, _InitPos.y + 6.f));
	GoldUpBtn_->SetChangeAnimation("Default");

	GoldUpBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	GoldUpBtnCol_->GetTransform()->SetLocalScaling(GoldUpBtn_->GetTransform()->GetLocalScaling());
	GoldUpBtnCol_->GetTransform()->SetLocalPosition(GoldUpBtn_->GetTransform()->GetLocalPosition());

	// ���ڰ��� ��ư����
	GoldDownBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	GoldDownBtn_->CreateAnimation("SpinnerDownBtn_Default.png", "Default", 0, 0, 0.1f, false);
	GoldDownBtn_->CreateAnimation("SpinnerDownBtn_Click.png", "Click", 0, 0, 0.1f, false);
	GoldDownBtn_->GetTransform()->SetLocalScaling(float4(15.f, 12.f));
	GoldDownBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 88.f, _InitPos.y - 8.f));
	GoldDownBtn_->SetChangeAnimation("Default");

	GoldDownBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	GoldDownBtnCol_->GetTransform()->SetLocalScaling(GoldDownBtn_->GetTransform()->GetLocalScaling());
	GoldDownBtnCol_->GetTransform()->SetLocalPosition(GoldDownBtn_->GetTransform()->GetLocalPosition());

	// ���� ��ư����
	ApprovedBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	ApprovedBtn_->CreateAnimation("ApprovedButton_Default.png", "Default", 0, 0, 0.1f, false);
	ApprovedBtn_->CreateAnimation("ApprovedButton_Click.png", "Click", 0, 0, 0.1f, false);
	ApprovedBtn_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
	ApprovedBtn_->GetTransform()->SetLocalPosition(float4(_InitPos.x - 54.f, _InitPos.y - 53.f));
	ApprovedBtn_->SetChangeAnimation("Default");

	ApprovedCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	ApprovedCol_->GetTransform()->SetLocalPosition(ApprovedBtn_->GetTransform()->GetLocalPosition());
	ApprovedCol_->GetTransform()->SetLocalScaling(ApprovedBtn_->GetTransform()->GetLocalScaling());

	// ���� ��ư����
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
	// ���� ����
	MaxHaveGold_ = _CurHaveGold;
	CurHaveGold_ = 0;
	GoldText_->SetPrintText(std::to_string(CurHaveGold_));

	// On���� ��ȯ
	On();
}

void TakeInOutGoldPopup::TakeInOutGoldPopupInactive()
{
	// Off���� ��ȯ
	Off();
}
