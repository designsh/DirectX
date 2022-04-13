#include "PreCompile.h"
#include "NPC_BuySellView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
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
	HaveGold_(100000),
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
}

void NPC_BuySellView::Update(float _DeltaTime)
{
#pragma region ��ư���°���
	if (BuyBtnState_ == Button_State::Click)	// ���Ź�ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			//BuyButtonRenderer_->SetChangeAnimation("Default");

			BuyBtnState_ = Button_State::Normal;
		}
	}

	if (SellBtnState_ == Button_State::Click)	// �ǸŹ�ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			//SellButtonRenderer_->SetChangeAnimation("Default");

			SellBtnState_ = Button_State::Normal;
		}
	}

	if (RepairBtnState_ == Button_State::Click)	// ������ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			//RepairButtonRenderer_->SetChangeAnimation("Default");

			RepairBtnState_ = Button_State::Normal;
		}
	}

	if (AllRepairBtnState_ == Button_State::Click)	// ���μ�����ư����
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư �ִϸ��̼� ����
			//AllRepairButtonRenderer_->SetChangeAnimation("Default");

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

	if (nullptr != AllRepairButtonCollider_)	// ���μ�����ư
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
			//BuyButtonRenderer_->SetChangeAnimation("Click");
			
			// ���콺Ŀ�� �ִϸ��̼� ����
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
			//SellButtonRenderer_->SetChangeAnimation("Click");

			// ���콺Ŀ�� �ִϸ��̼� ����
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

			SellBtnState_ = Button_State::Normal;
		}
	}
}

void NPC_BuySellView::RepairButtonClick(GameEngineCollision* _Other)
{
	if (RepairBtnState_ != Button_State::Disabled)
	{
		if (NPCType::WeaponShop == BuySellViewType_)
		{
			// ������ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
				//RepairButtonRenderer_->SetChangeAnimation("Click");

				// ���콺Ŀ�� �ִϸ��̼� ����
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

				RepairBtnState_ = Button_State::Normal;
			}
		}
		else // ��������� �����ϰ� ������� ����
		{
			// ������ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
				//RepairButtonRenderer_->SetChangeAnimation("Click");

				RepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				//RepairButtonRenderer_->SetChangeAnimation("Default");

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
				//AllRepairButtonRenderer_->SetChangeAnimation("Click");

				if (false == AllRepairActive_)
				{
					AllRepairActive_ = true;
				}
				else
				{
					AllRepairActive_ = true;
				}

				AllRepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				//AllRepairButtonRenderer_->SetChangeAnimation("Default");

				AllRepairBtnState_ = Button_State::Normal;
			}
		}
		else // ��������� �����ϰ� ���μ������ ����
		{
			// ���μ�����ư Ŭ��
			if (true == GameEngineInput::GetInst().Down("MouseLButton"))
			{
				// ��ư�ִϸ��̼� ����
				//AllRepairButtonRenderer_->SetChangeAnimation("Click");

				AllRepairBtnState_ = Button_State::Click;
			}
			else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
			{
				//AllRepairButtonRenderer_->SetChangeAnimation("Default");

				AllRepairBtnState_ = Button_State::Normal;
			}
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
			//BuySellViewTabs_.clear();
			//BuySellViewTabs_.resize(1);
			//for (int i = 0; i < 1; ++i)
			//{
			//	BuySellViewTabs_[i].TabIndex_ = i;
			//	BuySellViewTabs_[i].TabType_ = ItemLocType::BuySell_Etc;
			//	BuySellViewTabs_[i].TabName_ = "��Ÿ";
			//	BuySellViewTabs_[i].TabActive_ = true;

			//	// �Ƿ����� �� �浹ü ����
			//	BuySellViewTabs_[i].TabRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
			//	BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_DeSel.png", "TabDeselect", 0, 0, 0.1f, false);
			//	BuySellViewTabs_[i].TabRenderer_->CreateAnimation("BuySellTab_Sel.png", "TabSelect", 0, 0, 0.1f, false);
			//	BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalPosition(float4());
			//	BuySellViewTabs_[i].TabRenderer_->GetTransform()->SetLocalScaling(float4(79.f, 30.f));
			//	if (true == BuySellViewTabs_[i].TabActive_)
			//	{
			//		BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabSelect");
			//	}
			//	else
			//	{
			//		BuySellViewTabs_[i].TabRenderer_->SetChangeAnimation("TabDeselect");
			//	}

			//	BuySellViewTabs_[i].TabCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//	BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalPosition(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalPosition());
			//	BuySellViewTabs_[i].TabCollision_->GetTransform()->SetLocalScaling(BuySellViewTabs_[i].TabRenderer_->GetTransform()->GetLocalScaling());

			//	// �ش� ���� ��ġŸ������(UI1)
			//	BuySellViewTabs_[i].ArrangeTiles_.clear();
			//	BuySellViewTabs_[i].ArrangeTiles_.resize(10 * 10);
			//	for (int y = 0; y < 10; ++y)
			//	{
			//		for (int x = 0; x < 10; ++x)
			//		{
			//			int Index = (y * 10) + x;
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].ItemArrangementFlag_ = false;
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].Index_ = Index;
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].IndexX_ = x;
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].IndexY_ = y;

			//			// ��ġ���� �� ũ������ ����
			//			float4 TilePos = float4();
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TilePos_ = TilePos;

			//			float4 TileScale = float4(28.f, 28.f, 1.f);
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileScale_ = TileScale;

			//			// ������ ����
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(1.f, 1.f, 1.f, 0.f));
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
			//			BuySellViewTabs_[i].ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
			//		}
			//	}

			//	// �ش� ���� �����ϰ��ִ� �����۸��(UI1_Render) - Ȱ�¹���, ��Ż��ũ��, �����۰�����ũ�� ����
			//	// HaveItemList_

			//}
			#pragma endregion

			#pragma region ��ư(����, �Ǹ�, null, null)
			//// ���Ź�ư ������ (UI1_Button)
			//BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			//BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			//BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//BuyButtonRenderer_->SetChangeAnimation("Default");

			//// ���Ź�ư �浹ü(UI1_Collider)
			//BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			//BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			//// �ǸŹ�ư ������ (UI1_Button)
			//SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			//SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			//SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//SellButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//SellButtonRenderer_->SetChangeAnimation("Default");

			//// �ǸŹ�ư �浹ü(UI1_Collider)
			//SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			//SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			//// ������ư ������(UI1_Button)
			//RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Default.png", "Default", 0, 0, 0.1f, false);
			//RepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Click.png", "Click", 0, 0, 0.1f, false);
			//RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//RepairButtonRenderer_->SetChangeAnimation("Default");

			//// ������ư �浹ü(UI1_Collider)
			//RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			//RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			//// ���μ�����ư ������(UI1_Button)
			//AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Default.png", "Default", 0, 0, 0.1f, false);
			//AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_None_Click.png", "Click", 0, 0, 0.1f, false);
			//AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//AllRepairButtonRenderer_->SetChangeAnimation("Default");

			//// ���μ�����ư �浹ü(UI1_Collider)
			//AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			//AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
		case NPCType::WeaponShop:
		{
			#pragma region ����������(����, ����)

			// ���̸� ����
			//std::string TabName[2] = { {"����"}, {"��"} };

			// ������ ����
			//BuySellViewTabs_.clear();
			//BuySellViewTabs_.resize(2);
			//for (int i = 0; i < 2; ++i)
			//{

			//}
			#pragma endregion

			#pragma region ��ư(����, �Ǹ�, ����, ���μ���)
			//// ���Ź�ư ������ (UI1_Button)
			//BuyButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Default.png", "Default", 0, 0, 0.1f, false);
			//BuyButtonRenderer_->CreateAnimation("BuySellBtn_Buy_Click.png", "Click", 0, 0, 0.1f, false);
			//BuyButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//BuyButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//BuyButtonRenderer_->SetChangeAnimation("Default");

			//// ���Ź�ư �浹ü(UI1_Collider)
			//BuyButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//BuyButtonCollider_->GetTransform()->SetLocalPosition(BuyButtonRenderer_->GetTransform()->GetLocalPosition());
			//BuyButtonCollider_->GetTransform()->SetLocalScaling(BuyButtonRenderer_->GetTransform()->GetLocalScaling());

			//// �ǸŹ�ư ������ (UI1_Button)
			//SellButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Default.png", "Default", 0, 0, 0.1f, false);
			//SellButtonRenderer_->CreateAnimation("BuySellBtn_Sell_Click.png", "Click", 0, 0, 0.1f, false);
			//SellButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//SellButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//SellButtonRenderer_->SetChangeAnimation("Default");

			//// �ǸŹ�ư �浹ü(UI1_Collider)
			//SellButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//SellButtonCollider_->GetTransform()->SetLocalPosition(SellButtonRenderer_->GetTransform()->GetLocalPosition());
			//SellButtonCollider_->GetTransform()->SetLocalScaling(SellButtonRenderer_->GetTransform()->GetLocalScaling());

			//// ������ư ������(UI1_Button)
			//RepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Default.png", "Default", 0, 0, 0.1f, false);
			//RepairButtonRenderer_->CreateAnimation("BuySellBtn_Repair_Click.png", "Click", 0, 0, 0.1f, false);
			//RepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//RepairButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//RepairButtonRenderer_->SetChangeAnimation("Default");

			//// ������ư �浹ü(UI1_Collider)
			//RepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//RepairButtonCollider_->GetTransform()->SetLocalPosition(RepairButtonRenderer_->GetTransform()->GetLocalPosition());
			//RepairButtonCollider_->GetTransform()->SetLocalScaling(RepairButtonRenderer_->GetTransform()->GetLocalScaling());

			//// ���μ�����ư ������(UI1_Button)
			//AllRepairButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
			//AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Default.png", "Default", 0, 0, 0.1f, false);
			//AllRepairButtonRenderer_->CreateAnimation("BuySellBtn_AllRepair_Click.png", "Click", 0, 0, 0.1f, false);
			//AllRepairButtonRenderer_->GetTransform()->SetLocalScaling(float4(32.f, 32.f));
			//AllRepairButtonRenderer_->GetTransform()->SetLocalPosition(float4());
			//AllRepairButtonRenderer_->SetChangeAnimation("Default");

			//// ���μ�����ư �浹ü(UI1_Collider)
			//AllRepairButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
			//AllRepairButtonCollider_->GetTransform()->SetLocalPosition(AllRepairButtonRenderer_->GetTransform()->GetLocalPosition());
			//AllRepairButtonCollider_->GetTransform()->SetLocalScaling(AllRepairButtonRenderer_->GetTransform()->GetLocalScaling());
			#pragma endregion
			break;
		}
	}

	// �Ǹ�â�� ��ġŸ�� �浹ü ����
	// ArrangeTiles_�� ��ġ/ũ������ Get �ʿ�
	
	//ArrangeTileCols_.clear();
	//ArrangeTileCols_.resize(10 * 10);
	//for (int y = 0; y < 10; ++y)
	//{
	//	for (int x = 0; x < 10; ++x)
	//	{
	//		float4 StartPos = float4();

	//		int Index = (y * 10) + x;
	//		ArrangeTileCols_[Index] = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	//		ArrangeTileCols_[Index]->GetTransform()->SetLocalPosition(float4());
	//		ArrangeTileCols_[Index]->GetTransform()->SetLocalScaling(float4(28.f, 28.f));
	//	}
	//}
}

void NPC_BuySellView::NPCBuySellViewActive()
{
	//On();

	// �Ǹ�â Ȱ��ȭ�� �÷��̾��� �κ��丮â�� Ȱ��ȭ�Ǹ�,
	

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.


	// ����, ���� �Ǹ�â�� Ȱ��ȭ�� ���ε����� ���� �ش� �������� On


	// �ش� NPC�� ��ܸ޴� Off




}

void NPC_BuySellView::NPCBuySellViewInactive()
{
	//Off();

	// �Ǹ�â ��Ȱ��ȭ�� �÷��̾��� �κ��丮â�� ��Ȱ��ȭ�Ǹ�,
	

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� Ȱ��ȭ ��Ų��.





	// �ش� NPC�� ��ܸ޴� On




}

void NPC_BuySellView::SelectTabClick(GameEngineCollision* _Other, int _Index)
{
	// ���� ������ ���ε��� ����
	CurTabIndex = _Index;

	// ���� ���ε����� ���� Ȱ��ȭó��





}

void NPC_BuySellView::ArrangeTileClick(GameEngineCollision* _Other, int _Index)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// �ش� ��ġŸ�Ͽ� �������� �ִٸ�
		//if (true == BuySellViewTabs_[CurTabIndex].ArrangeTiles_[_Index].ItemArrangementFlag_)
		//{

		//}
		//else // �ش� ��ġŸ�Ͽ� �������� ���ٸ�
		//{

		//}
	}
}
