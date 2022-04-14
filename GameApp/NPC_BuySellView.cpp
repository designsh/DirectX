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

	// ��差 ������ ����
	HaveGoldRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
	HaveGoldRenderer_->SetImage("InvTestTileImage.png");
	HaveGoldRenderer_->GetTransform()->SetLocalScaling(float4(184.f, 17.f));
	HaveGoldRenderer_->GetTransform()->SetLocalPosition(float4(-212.f, -128.f));
	HaveGoldRenderer_->TextSetting("diablo", std::to_string(HaveGold_), 14.f, FW1_RIGHT | FW1_VCENTER, float4::WHITE, float4(90.f, 0.f), 100);
	HaveGoldRenderer_->SetAlpha(0.f);
}

void NPC_BuySellView::Update(float _DeltaTime)
{
#pragma region ��ư���°���
	if (BuyBtnState_ == Button_State::Click)	// ���Ź�ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			BuyButtonRenderer_->SetChangeAnimation("Default");

			BuyBtnState_ = Button_State::Normal;
		}
	}

	if (SellBtnState_ == Button_State::Click)	// �ǸŹ�ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			SellButtonRenderer_->SetChangeAnimation("Default");

			SellBtnState_ = Button_State::Normal;
		}
	}

	if (RepairBtnState_ == Button_State::Click)	// ������ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			RepairButtonRenderer_->SetChangeAnimation("Default");

			RepairBtnState_ = Button_State::Normal;
		}
	}

	if (AllRepairBtnState_ == Button_State::Click)	// ���μ���/â�ݱ� ��ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// �ش� �Ǹ�â����(��ȭ�����̸� â�ݱ��ư�̹Ƿ� â�ݱ� ���ó��)
			if (NPCType::PotionShop == BuySellViewType_)
			{
				PrivateNPCBuySellViewActive();
			}

			AllRepairBtnState_ = Button_State::Normal;
		}
	}
#pragma endregion

#pragma region ��ư�浹üũ
	if (nullptr != BuyButtonCollider_)	// ���Ź�ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(BuyButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		BuyButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::BuyButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != SellButtonCollider_)	// �ǸŹ�ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(SellButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		SellButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::SellButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != RepairButtonCollider_)	// ������ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(RepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		RepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::RepairButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != AllRepairButtonCollider_)	// ���μ���/â�ݱ��ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(AllRepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		AllRepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::AllRepairButtonClick, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region �Ǽ����浹üũ
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

#pragma region ��ġŸ���浹üũ
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
		// ���Ź�ư Ŭ��
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// ��ư�ִϸ��̼� ����
			BuyButtonRenderer_->SetChangeAnimation("Click");
			
			// ���콺Ŀ�� �ִϸ��̼� ����
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
		// �ǸŹ�ư Ŭ��
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// ��ư�ִϸ��̼� ����
			SellButtonRenderer_->SetChangeAnimation("Click");

			// ���콺Ŀ�� �ִϸ��̼� ����
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
		// ��������϶��� ������� Ȱ������
		if (NPCType::WeaponShop == BuySellViewType_)
		{
			// ������ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
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
				// ��ư�ִϸ��̼� ����
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
			// ���μ�����ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
				AllRepairButtonRenderer_->SetChangeAnimation("Click");

				AllRepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				AllRepairButtonRenderer_->SetChangeAnimation("Default");

				AllRepairBtnState_ = Button_State::Normal;
			}
		}
		else // ��������� �ƴҶ� â�ݱ� ��ư���� ���
		{
			// ���μ�����ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
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
	// �Ǹ�â ��ȭ
	Off();

	// �����ǿ� ���� Renderer, Collider ��Ȱ��ȭ
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

	// ���縶�콺 Ŀ�����¸� ����(�⺻���·� ��ȯ)
	GlobalValue::CurMouse->CursorStateReset();

	// �Ǹ�â Ȱ��ȭ�� �÷��̾��� �κ��丮â�� ��Ȱ��ȭ,
	GlobalValue::CurPlayer->InventoryViewEnabled(false);
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� Ȱ��ȭ ��Ų��.
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);

	// �ش� NPC�� ��ܸ޴� On
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
	// �Ǹ�â Ȱ��ȭ
	On();

	// �����ǿ� ���� Renderer, Collider Ȱ��ȭ
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

	// �Ǹ�â Ȱ��ȭ�� �÷��̾��� �κ��丮â�� Ȱ��ȭ�Ǹ�,
	GlobalValue::CurPlayer->InventoryViewEnabled(true);
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(true);

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.
	GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(false);

	// �ش� NPC�� ��ܸ޴� Off
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
	// �Ǹ�â ��ȭ
	Off();

	// �����ǿ� ���� Renderer, Collider ��Ȱ��ȭ
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

	// ���縶�콺 Ŀ�����¸� ����(�⺻���·� ��ȯ)
	GlobalValue::CurMouse->CursorStateReset();

	// �ش� NPC�� ��ܸ޴� On
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
	// ��������
	BuySellViewType_ = _BuySellViewType;
	NPCClassType_ = _NPCClassType;

	// ������ũ�� Get
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();

	// NPCŸ�Կ� ���� �Ǹ�â ����

	// �Ǹ�â �ǳ�
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("BuySell_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();
	ViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	ViewPanel_->SetImage("BuySell_Panel.png");
	ViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// �Ǹ�âŸ�Ժ� ��ư �� �ǻ���
	switch (BuySellViewType_)
	{
		case NPCType::PotionShop:
		{
			#pragma region ����������(��Ÿ)

			// ���̸� ����
			std::string TabName = "MISC";

			// ������ ����
			BuySellViewTabs_.clear();
			BuySellViewTabs_.resize(1);
			for (int i = 0; i < 1; ++i)
			{
				BuySellViewTabs_[i].TabIndex_ = i;
				BuySellViewTabs_[i].TabType_ = ItemLocType::BuySell_Etc;
				BuySellViewTabs_[i].TabActive_ = true;

				// �Ƿ����� �� �浹ü ����
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

				// �ش� ���� ��ġŸ������(UI1_Tab)
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

						// ��ġ���� �� ũ������ ����
						float4 TilePos = float4::ZERO;
						TilePos.x = -290.f + (x * 28.f) + (x * 1.f);
						TilePos.y = -98.f + (y * 28.f) + (y * 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TilePos_ = TilePos;

						float4 TileScale = float4(28.f, 28.f, 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileScale_ = TileScale;

						// ������ ����
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->Off();
					}
				}

				// �ش� ���� �����ϰ��ִ� �����۸��(UI1_Render) - Ȱ�¹���, ��Ż��ũ��, �����۰�����ũ��
				CreateItemList(i);
			}
			#pragma endregion

			#pragma region ��ư(����, �Ǹ�, null, â�ݱ�)
			// ���Ź�ư ������ (UI1_Button)
			BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4(-188.f, -162.f));
			BuyButtonRenderer_->SetChangeAnimation("Default");

			// ���Ź�ư �浹ü(UI1_Collider)
			BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			// �ǸŹ�ư ������ (UI1_Button)
			SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			SellButtonRenderer_->GetTransform()->SetLocalPosition(float4(-136.f, -162.f));
			SellButtonRenderer_->SetChangeAnimation("Default");

			// �ǸŹ�ư �浹ü(UI1_Collider)
			SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			// �⺻��ư ������(UI1_Button)
			RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Default.png", "Default", 0, 0, 0.1f, false);
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Click.png", "Click", 0, 0, 0.1f, false);
			RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-84.f, -162.f));
			RepairButtonRenderer_->SetChangeAnimation("Default");

			// �⺻��ư �浹ü(UI1_Collider)
			RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			// â�ݱ��ư ������(UI1_Button)
			AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			AllRepairButtonRenderer_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-32.f, -162.f));
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// â�ݱ��ư �浹ü(UI1_Collider)
			AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
		case NPCType::WeaponShop:
		{
			#pragma region ����������(����, ����)

			// ���̸� ����
			std::string TabName[2] = { {"WEAPONS"}, {"ARMORS"} };

			// ������ ����
			BuySellViewTabs_.clear();
			BuySellViewTabs_.resize(2);
			for (int i = 0; i < 2; ++i)
			{
				BuySellViewTabs_[i].TabIndex_ = i;
				BuySellViewTabs_[i].TabType_ = static_cast<ItemLocType>(static_cast<int>(ItemLocType::BuySell_Weapon) + i);

				// ���缱�õ� �Ǹ� TRUE����
				if (i == CurTabIndex)
				{
					BuySellViewTabs_[i].TabActive_ = true;
				}
				else
				{
					BuySellViewTabs_[i].TabActive_ = false;
				}
				
				// �Ƿ����� �� �浹ü ����
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

				// �ش� ���� ��ġŸ������(UI1_Tab)
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

						// ��ġ���� �� ũ������ ����
						float4 TilePos = float4::ZERO;
						TilePos.x = -290.f + (x * 28.f) + (x * 1.f);
						TilePos.y = -98.f + (y * 28.f) + (y * 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TilePos_ = TilePos;

						float4 TileScale = float4(28.f, 28.f, 1.f);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileScale_ = TileScale;

						// ������ ����
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
						BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->Off();
					}
				}

				// �ش� ���� �����ϰ��ִ� �����۸��(UI1_Render) - �÷��̾� ��������,�� ���
				CreateItemList(i);
			}
			#pragma endregion

			#pragma region ��ư(����, �Ǹ�, ���μ���, â�ݱ�)
			// ���Ź�ư ������ (UI1_Button)
			BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4(-188.f, -162.f));
			BuyButtonRenderer_->SetChangeAnimation("Default");

			// ���Ź�ư �浹ü(UI1_Collider)
			BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			// �ǸŹ�ư ������ (UI1_Button)
			SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			SellButtonRenderer_->GetTransform()->SetLocalPosition(float4(-136.f, -162.f));
			SellButtonRenderer_->SetChangeAnimation("Default");

			// �ǸŹ�ư �浹ü(UI1_Collider)
			SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			// ������ư ������(UI1_Button)
			RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Default.png", "Default", 0, 0, 0.1f, false);
			RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Click.png", "Click", 0, 0, 0.1f, false);
			RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-84.f, -162.f));
			RepairButtonRenderer_->SetChangeAnimation("Default");

			// ������ư �浹ü(UI1_Collider)
			RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			// ���μ�����ư ������(UI1_Button)
			AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Default.png", "Default", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Click.png", "Click", 0, 0, 0.1f, false);
			AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4(-32.f, -162.f));
			AllRepairButtonRenderer_->SetChangeAnimation("Default");

			// ���μ�����ư �浹ü(UI1_Collider)
			AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
	}

	// �Ǹ�â�� ��ġŸ�� �浹ü ����
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
		// ���� �ε����� �̿��Ͽ� ó��
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetChangeAnimation("TabDeselect");
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetTextColor(float4::WHITE);

		// ���� ���ε����� ���� ��Ȱ��ȭ ó��
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

		// ����� ���� ���ε���
		CurTabIndex = _Index;
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetChangeAnimation("TabSelect");
		BuySellViewTabs_[CurTabIndex].TabRenderer_->SetTextColor(float4(0.8f, 0.8f, 0.4f));

		// ���� ���ε����� ���� Ȱ��ȭó��
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
		// �ش� ��ġŸ�Ͽ� �������� �ִٸ�
		if (true == BuySellViewTabs_[CurTabIndex].ArrangeTiles_[_Index].ItemArrangementFlag_)
		{
			std::string SelectItemName = "";

			// �����۸�Ͽ��� �ش� ������ ã��
			switch (BuySellViewType_)
			{
				// �������
				case NPCType::PotionShop:
				{
					SelectItemName = FindChandleryItem(_Index);

					break;
				}
				// �������
				case NPCType::WeaponShop:
				{
					SelectItemName = FindWeaponItem(_Index);

					break;
				}
			}

			// �������� ã�����ߴٸ� ����
			if (true == SelectItemName.empty())
			{
				return;
			}

			// �������� ã�Ҵٸ� ���� ���콺�� Ŀ�����¿� ���� ó���� �޸��Ѵ�.
			if (MouseState::Buy == GlobalValue::CurMouse->GetMouseState())
			{
				// �Ǹ�â�� �������ִ� �����ۿ��� ���� ����
				// �Ǹ�â�� �������� Ŭ���� �ش� ������ ���� �� �÷��̾� �κ��丮 ��ĭ�� ��ġ, �����۰��ݸ�ŭ NPC������� ����
				// �����۰��ݸ�ŭ �÷��̾��� ������� ����
				// ��, �÷��̾��� �κ��丮�� ��ĭ�� ���ٸ� ����

				// 1. �÷��̾��� �κ��丮�� �˻�(�ϴ� ������)


				// 2. �κ��丮�� ��ġ�����ϴٸ� �ش� ������ �κ��丮â�� ��ġ �� �÷��̾� ���������۸�Ͽ� �߰�


				// 3. �ش� ������ ���ݸ�ŭ NPC ������� ����


				// 4. �ش� ������ ���ݸ�ŭ �÷��̾� ������� ����


				

				// �׿� 
				// 1. �Ǹ�Ŀ�� Ȱ��ȭ�� �÷��̾� �κ��丮���� ó��
				// 2. ����Ŀ�� Ȱ��ȭ�� �÷��̾� �κ��丮���� ó��
				int a = 0;
			}
		}
	}
}

void NPC_BuySellView::CreateItemList(int _TabIndex)
{
	switch (BuySellViewType_)
	{
		// ��ȭ���� - Ȱ�¹���, ��Ż��ũ��, �����۰�����ũ��
		case NPCType::PotionShop:
		{
			// ��Ÿ��
			std::string ItemNameList[3] = { {"invvpl"}, {"invbsc"}, {"invchm"} };
			int ItemStartPos[3] = { {9}, {19}, {29} };

			// 0. Ȱ������(invvpl)
			// 1. ��Ż��ũ��(invbsc)
			// 2. �����۰�����ũ��(invchm)

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

				// ������ ��ġ ���� ����
				BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].TileRenderer_->SetAlpha(0.5f);
				BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.StartIndex].ItemArrangementFlag_ = true;

				// ������Ͽ� �߰�
				BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
			}

			break;
		}
		// ������� - �÷��̾� ��������,�� ���
		case NPCType::WeaponShop:
		{
			// ������
			if (0 == _TabIndex)
			{
				// crs ũ����Ż�ҵ�
				HaveItem NewItem = {};
				NewItem.OneSize_ = false;
				NewItem.StartIndex = 0;

				// �ش� ������ ũ�⿡ ���� �����ϴ� ��ġŸ�� �ε��� ��� �ۼ�
				NewItem.ArrangeIndexs_.clear();
				for (int k = 0; k < 3; ++k)
				{
					for (int l = 0; l < 3; ++l)
					{
						int CalcIndex = NewItem.StartIndex + l + (k * 10);
						if (0 <= CalcIndex && CalcIndex < 100)
						{
							NewItem.ArrangeIndexs_.push_back(CalcIndex);
						}
					}
				}

				// ����
				std::sort(NewItem.ArrangeIndexs_.begin(), NewItem.ArrangeIndexs_.end());

				ItemList NewItemInfo = {};
				AllItemInfomation::GetInst().ItemInfoFindInvName("invcrs", NewItemInfo);
				NewItem.ItemInfo_ = NewItemInfo;
				NewItem.ItemRemainsQuantity_ = 1; // ������������ ���� 1��
				NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));
				NewItem.ItemRenderer_->SetImage("invcrs.png");

				// �����۷����� ��ġ ���
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
				
				// ������ ��ġ ���� ����
				for (int i = 0; i < static_cast<int>(NewItem.ArrangeIndexs_.size()); ++i)
				{
					BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].ItemArrangementFlag_ = true;
					BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].TileRenderer_->SetAlpha(0.5f);
				}
				NewItem.ItemRenderer_->Off();

				// ������Ͽ� �߰�
				BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
			}
			// ����
			else if (1 == _TabIndex)
			{
				// bhm(���� 2x2), bsh(���� 3x3), chn(���� 3x3), hbt(���� 2x2), tbl(��Ʈ 1x3), tgl(�尩 2x2)
				std::string ItemName[6] = { {"invbhm"}, {"invbsh"}, {"invchn"}, {"invhbt"}, {"invtbl"}, {"invtgl"} };
				int ItemStartIndex[6] = { {0}, {3}, {7}, {30}, {42}, {50} };
				float4 ItemSize[6] = { {float4(2.f, 2.f)}, {float4(3.f, 3.f)}, {float4(3.f, 3.f)}, {float4(2.f, 2.f)}, {float4(3.f, 1.f)}, {float4(2.f, 2.f)} };

				for (int i = 0; i < 6; ++i)
				{
					HaveItem NewItem = {};
					NewItem.OneSize_ = false;
					NewItem.StartIndex = ItemStartIndex[i];

					// �ش� ������ ũ�⿡ ���� �����ϴ� ��ġŸ�� �ε��� ��� �ۼ�
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

					// ����
					std::sort(NewItem.ArrangeIndexs_.begin(), NewItem.ArrangeIndexs_.end());

					ItemList NewItemInfo = {};
					AllItemInfomation::GetInst().ItemInfoFindInvName(ItemName[i], NewItemInfo);
					NewItem.ItemInfo_ = NewItemInfo;
					NewItem.ItemRemainsQuantity_ = 1; // ������������ ���� 1��
					NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));

					std::string TextureName = ItemName[i];
					TextureName += ".png";
					NewItem.ItemRenderer_->SetImage(TextureName);

					// �����۷����� ��ġ ���
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

					// ������ ��ġ ���� ����
					for (int i = 0; i < static_cast<int>(NewItem.ArrangeIndexs_.size()); ++i)
					{
						BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].ItemArrangementFlag_ = true;
						BuySellViewTabs_[_TabIndex].ArrangeTiles_[NewItem.ArrangeIndexs_[i]].TileRenderer_->SetAlpha(0.5f);
					}
					NewItem.ItemRenderer_->Off();

					// ������Ͽ� �߰�
					BuySellViewTabs_[_TabIndex].HaveItemList_.push_back(NewItem);
				}
			}
			break;
		}
	}
}

std::string NPC_BuySellView::FindChandleryItem(int _ArrangeIndex)
{
	// ��ȭ�����϶��� ���밡��
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
	// ��������϶��� ���밡��
	if (NPCType::WeaponShop == BuySellViewType_)
	{
		int ItemCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_.size());
		for (int i = 0; i < ItemCnt; ++i)
		{
			int ArrangeIndexCnt = static_cast<int>(BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_.size());
			for (int j = 0; j < ArrangeIndexCnt; ++j)
			{
				// ��ġ�� �ε�������� ��� ������ �ش� Ŭ���� Ÿ���� �ε����� ã�´�.
				if (_ArrangeIndex == BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ArrangeIndexs_[j])
				{
					return BuySellViewTabs_[CurTabIndex].HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
				}
			}
		}
	}

	return std::string();
}

void NPC_BuySellView::AddHaveGold(int _Gold)
{
	// �÷��̾ �������ִ� �������� NPC���� �ǸŽ�
	HaveGold_ += _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}

void NPC_BuySellView::SubHaveGold(int _Gold)
{
	// NPC�� �������ִ� �������� �÷��̾�� �ǸŽ�
	HaveGold_ -= _Gold;
	HaveGoldRenderer_->SetPrintText(std::to_string(HaveGold_));
}
