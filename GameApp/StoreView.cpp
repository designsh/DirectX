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

	// Panel ����
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StorehouseView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	StoreViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	StoreViewPanel_->SetImage("Player_StorehouseView_Panel.png");
	StoreViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// Player �̵����ѿ� �ǳ� �浹ü ����
	StoreViewPanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	StoreViewPanelCol_->SetName("Player_StoreView");
	StoreViewPanelCol_->GetTransform()->SetLocalScaling(StoreViewPanel_->GetTransform()->GetLocalScaling());
	StoreViewPanelCol_->GetTransform()->SetLocalPosition(StoreViewPanel_->GetTransform()->GetLocalPosition());

	// â�ݱ� ��ư����
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-33.f, -162.f));
	CloseButton_->SetChangeAnimation("Default");

	CloseBtnCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	CloseBtnCol_->GetTransform()->SetLocalScaling(CloseButton_->GetTransform()->GetLocalScaling());
	CloseBtnCol_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// ��岨�����˾� ����
	StoreGoldTakeOutPopBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	StoreGoldTakeOutPopBtn_->CreateAnimation("GoldIconBtn_Default.png", "Default", 0, 0, 0.1f, false);
	StoreGoldTakeOutPopBtn_->CreateAnimation("GoldIconBtn_Click.png", "Click", 0, 0, 0.1f, false);
	StoreGoldTakeOutPopBtn_->GetTransform()->SetLocalScaling(float4(20.f, 18.f));
	StoreGoldTakeOutPopBtn_->GetTransform()->SetLocalPosition(float4(-236.f, 208.f));
	StoreGoldTakeOutPopBtn_->SetChangeAnimation("Default");

	StoreGoldTakeOutPopColBtn_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	StoreGoldTakeOutPopColBtn_->GetTransform()->SetLocalScaling(StoreGoldTakeOutPopBtn_->GetTransform()->GetLocalScaling());
	StoreGoldTakeOutPopColBtn_->GetTransform()->SetLocalPosition(StoreGoldTakeOutPopBtn_->GetTransform()->GetLocalPosition());

	// ��差 ����
	StoreGold_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StoreGold_->SetImage("InvTestTileImage.png");
	StoreGold_->TextSetting("diablo", std::to_string(StoredGold_), 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	StoreGold_->GetTransform()->SetLocalScaling(float4(150.f, 15.f));
	StoreGold_->GetTransform()->SetLocalPosition(float4(-148.f, 208.f));
	StoreGold_->SetAlpha(0.f);

	StoreMaxGold_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StoreMaxGold_->SetImage("InvTestTileImage.png");
	StoreMaxGold_->TextSetting("diablo", "�ִ� ���差 : 2,500,000", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);
	StoreMaxGold_->GetTransform()->SetLocalScaling(float4(172.f, 17.f));
	StoreMaxGold_->GetTransform()->SetLocalPosition(float4(-160.f, 182.f));
	StoreMaxGold_->SetAlpha(0.f);

	// ��岨���� �˾�����
	TakeOutGoldPopup_ = GetLevel()->CreateActor<TakeInOutGoldPopup>();
	//TakeOutGoldPopup_->CreateTakePopup(TakeInOutPopupType::TakeOut, TakeInOutPopCreateType::STOREDVIEW, float4());

	// �����۹�ġ ��������






	// �⺻ Off���·� ����
	Off();
}

void StoreView::Update(float _DeltaTime)
{
	// â�ݱ� ��ư Ŭ�������϶� �ִϸ��̼� ���� �� ��� â�ݱ� ó��
	if (CloseBtnState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// �÷��̾��� �κ��丮â Off �� â��â Offó��
				PrivateStoreViewActive();
			}

			CloseButton_->SetChangeAnimation("Default");
			CloseBtnState_ = Button_State::Normal;
		}
	}

	// ����˾� ��ư Ŭ�������϶� �ִϸ��̼� ���� �� ��岨���� �˾� ���� ó��
	if (StoreGoldTakeOutPopBtnState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��� ������ �˾�â Ȱ��ȭ
			GoldPopupViewActive();

			StoreGoldTakeOutPopBtn_->SetChangeAnimation("Default");
			StoreGoldTakeOutPopBtnState_ = Button_State::Normal;
		}
	}

#pragma region �浹ü������ & �浹üũ
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
	// â��â â�ݱ��ư Ŭ���� ȣ��
	if (true == StoreViewActive_)
	{
		// Flag ����
		StoreViewActive_ = false;

		// â��â ��Ȱ��
		Off();

		// �÷��̾��� �κ��丮â ��Ȱ��ȭ ó��
		GlobalValue::CurPlayer->InventoryViewEnabled(false);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

		// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);
	}
}

void StoreView::GoldPopupViewActive()
{
	// ��岨���� �˾� Ȱ��ȭ




}

void StoreView::StoreViewOff()
{
	// �÷��̾��� �κ��丮â���� Close Button Ŭ���� ȣ���ϹǷ�
	// â��â�� �ݴ� ���Ҹ� �����Ѵ�.
	if (true == StoreViewActive_)
	{
		// Ȱ��ȭ Flag Off
		StoreViewActive_ = false;

		// â��â ��Ȱ��ȭ
		Off();
	}
}

void StoreView::StoreViewOn()
{
	if (false == StoreViewActive_)
	{
		// Ȱ��ȭ Flag On
		StoreViewActive_ = true;

		// 1. �÷��̾��� �κ��丮â�� Ȱ��ȭ��Ų��.
		GlobalValue::CurPlayer->InventoryViewEnabled(true);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(true);

		// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(false);

		// 2. â��â Ȱ��ȭ ��Ų��.
		On();
	}
}

int StoreView::StoredGoldAdd(int _Gold)
{
	// ���� ����� ��差���� �����Ѱ�� ���ϱ�
	// ��, �ִ� ���差�� �Ѿ�� �ִ뷮������ �����ϰ�,
	// �������� �ٽ� �����ش�.
	int StoredGold = StoredGold_ + _Gold;
	if (StoredMaxGold_ < StoredGold)
	{
		// ������差�� �ִ뷮�� �ȴ�.
		StoredGold_ = StoredMaxGold_;
		StoreGold_->SetPrintText(std::to_string(StoredGold_));

		// �ִ�ġ���� ���纸����差+�߰������差�� ���� ���������� ��ȯ�Ѵ�.
		return StoredMaxGold_ - StoredGold;
	}
	
	// �ִ뷮�� �Ѿ���ʴ´ٸ� ��差 ����
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// ��� ��� ����Ϸ�� -1 ��ȯ
	return -1;
}

int StoreView::StoredGoldSub(int _Gold)
{
	// ���� ����� ��差���� �ش� ��常ŭ ����
	// ��, �������� ��差�� ���� ����� ������庸�� Ŭ���
	// ���� ����� ������常 ��ȯ�Ѵ�.
	int StoredGold = StoredMaxGold_ - _Gold;
	if (0 >= StoredGold)
	{
		// ���� ����� ������常ŭ�� ��ȯ
		return StoredMaxGold_;
	}

	// ���� ����� ������差�� �˸°� ã�Ҵٸ� �ش� ��常ŭ ����
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// ���� ������忡 �°� ��带 ���´ٸ� -1 ��ȯ
	return -1;
}
