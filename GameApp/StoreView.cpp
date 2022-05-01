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
	TakeOutGoldPopup_->CreateTakePopup(TakeInOutPopupType::TakeOut, TakeInOutPopCreateType::STOREDVIEW, float4(280.f - WindowHarfSize.x, WindowHarfSize.y - 220.f), StoredGold_);

	// �����۹�ġ ��������
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

			// ��ġ���� �� ũ������ ����
			float4 TilePos = float4::ZERO;
			TilePos.x = -232.f + (x * 28.f) + (x * 1.f);
			TilePos.y = -60.f + (y * 28.f) + (y * 1.f);
			StoreViewInfo_.ArrangeTiles_[Index].TilePos_ = TilePos;

			float4 TileScale = float4(28.f, 28.f, 1.f);
			StoreViewInfo_.ArrangeTiles_[Index].TileScale_ = TileScale;

			// ������ ����
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->SetImage("InvTestTileImage.png");
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->TextSetting("diablo", std::to_string(Index), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalPosition(TilePos);
			StoreViewInfo_.ArrangeTiles_[Index].TileRenderer_->GetTransform()->SetLocalScaling(TileScale);
		}
	}

	// â��â�� ��ġŸ�� �浹ü ����
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
			GetLevel()->UIPushDebugRender(StoreGoldTakeOutPopColBtn_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		StoreGoldTakeOutPopColBtn_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StoreView::GoldButtonClick, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region �����۹�ġŸ���浹üũ
	if (false == StoreViewInfo_.StoreArrTileCols_.empty())
	{
		for (int i = 0; i < static_cast<int>(StoreViewInfo_.StoreArrTileCols_.size()); ++i)
		{
			if (nullptr != StoreViewInfo_.StoreArrTileCols_[i])
			{
#ifdef _DEBUG
				if (false == TakeOutGoldPopup_->IsUpdate()) // ����˾�â�� Ȱ��ȭ�Ǹ� �浹ü ������ ǥ�þ���
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
	// â��â â�ݱ��ư Ŭ���� ȣ��
	if (true == StoreViewActive_)
	{
		// Flag ����
		StoreViewActive_ = false;

		// â���� ��岨���� �˾��� Ȱ��ȭ ���¶�� ��Ȱ��ȭ
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			TakeOutGoldPopup_->TakeInOutGoldPopupInactive();
		}

		// â��â ��Ȱ��
		Off();

		// ���� â��â�� �����ϰ��ִ� ��� �����۷����� ��Ȱ��ȭ
		int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
		for (int i = 0; i < HaveItemListCnt; ++i)
		{
			StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Off();
		}

		// �÷��̾��� �κ��丮â ��Ȱ��ȭ ó��
		GlobalValue::CurPlayer->InventoryViewEnabled(false);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(false);

		// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(true);
	}
}

void StoreView::GoldPopupViewActive()
{
	// ��岨���� �˾� Ȱ��ȭ(���� ����� ��差 �����Ͽ� �˾� ����)
	TakeOutGoldPopup_->TakeInOutGoldPopupActive(StoredGold_);
}

void StoreView::ArrangeTileClick(GameEngineCollision* _Other, int _Index)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ����˾�â�� Ȱ��ȭ�Ǹ� �����۹�ġ ���ϵ��� ó��
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			return;
		}

		// ���콺�� ���°� Stay or Move �����϶��� ����
		if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() ||
			MouseState::Move == GlobalValue::CurMouse->GetMouseState())
		{
			// ���콺�� �������� ����ְ�, �ش� �浹�� Ÿ�Ͽ� ��ġ�� �������� �������
			// => ���콺�� ����ִ� �������� �ش� Ÿ�Ͽ� ��ġ
			if (false == StoreViewInfo_.ArrangeTiles_[_Index].ItemArrangementFlag_ && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemPlacement(_Index);
			}
			// ���콺�� �������� ��������ʰ�, �ش� �浹�� Ÿ�Ͽ� ��ġ�� �������� �������
			// => �ش� Ÿ�Ͽ� ��ġ�� �������� ���콺�� ����
			else if (true == StoreViewInfo_.ArrangeTiles_[_Index].ItemArrangementFlag_ && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemDisposition(_Index);
			}
		}
	}
}

void StoreView::ItemPlacement(int _ColTileIndex)
{
	// ���콺�� ����ִ� �������� ũ�������� �̿��Ͽ� �ش� Ÿ���� ������ Ÿ�Ͽ� ������ ��ġ�ϸ�,
	// ���콺�� �ش� �������� ���������� ����

	// 1. ���콺�� ���� ����ִ� �����۸��� ������ ���� ��
	std::string CurItemName = GlobalValue::CurMouse->GetHoldItemName();
	size_t DotFindIndex = CurItemName.find('.');
	CurItemName = CurItemName.substr(0, DotFindIndex);

	// 2. ��ü ������������Ͽ��� �ش� �������� ������ Get
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(CurItemName, CurItemInfo))
	{
		// �ش� ������ ������ ã�Ҵٸ� ũ������ Get
		int WidthSize = CurItemInfo.WidthSize;
		int HeightSize = CurItemInfo.HeightSize;
		if (WidthSize == 1 && HeightSize == 1)
		{
			// 1x1 ũ�⸦ ������ �������̹Ƿ� ��ġ�Ϸ��� Ÿ���� �˻��Ͽ� �ش� Ÿ���� ����ִٸ� �����۹�ġ
			// ��������ʴٸ� ����
			if (true == StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_)
			{
				// �ش� Ÿ�Ͽ� �̹� �������� ��ġ�Ǿ������Ƿ� ����
				return;
			}
			// �ش� Ÿ���� ����־� ������ ��ġ����
			else
			{
				// �ش� Ÿ������ ����
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_ = true;
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TileRenderer_->SetAlpha(0.5f);

				// �ش� �������� ���������� ��Ͽ� �߰�
				StoredItem NewItem = {};
				NewItem.OneSize_ = true;
				NewItem.StartIndex = _ColTileIndex;
				NewItem.RenderPos_ = StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TilePos_;
				
				// ��ġ�ϱ� ���Ѿ����� ���� �����Ͽ� ��������
				CurItemInfo.ItemLocType = ItemLocType::Storehouse_Bottom;
				CurItemInfo.StartPosition = _ColTileIndex;
				NewItem.ItemInfo_ = CurItemInfo;

				// ������ ������ ����
				std::string ItemName = CurItemInfo.ItemName_abbreviation_Inven;
				ItemName += ".png";
				NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Render));

				// ������ ������ ��ġ �� ũ������ ���� �� ����
				NewItem.ItemRenderer_->SetImage(ItemName);
				NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);
				
				StoreViewInfo_.HaveItemList_.push_back(NewItem);
			}
		}
		else
		{
			// 1x1ũ�Ⱑ �ƴ� �������̹Ƿ� ��ġ�Ϸ��� Ÿ���� �ֺ�Ÿ���� ��� �˻��Ͽ� ��ġ�������� �Ǵ� ��
			// ��ġ�����ϴٸ� �ش� �������� ��ġ�ϰ�, ��ġ �Ұ����ϴٸ� ����
			if (false == ItemPlacementCheck(_ColTileIndex, CurItemInfo))
			{
				// ��ġ�Ұ��� �����̹Ƿ� ����
				return;
			}
		}

		// ��� ���� ������ ������ ��ġ�Ϸᰡ �Ǿ��ٸ� ���콺�� �ش� �������� �������´�.
		GlobalValue::CurMouse->ItemPutDown();
	}
}

bool StoreView::ItemPlacementCheck(int _ColTileIndex, ItemList& _CurItemInfo)
{
	// ��ġ����� ���� Ÿ���� �������� ������ũ�⸸ŭ ���Ͽ� ��ġ�������� üũ
	// ��ġ�����ϴٸ� �������� ��ġ�ϰ�, ��ġŸ�������� �����ϸ�, ������ ������Ͽ� �ش� �������� �߰��ϰ�,
	// true�� ��ȯ�Ѵ�.

	// �ش� ������ �⺻���� Get
	std::string CurItemName = _CurItemInfo.ItemName_abbreviation_Inven;

	int StartIndex = _ColTileIndex;
	int WidthSize = _CurItemInfo.WidthSize;
	int HeightSize = _CurItemInfo.HeightSize;

	// ��ġ���ɰ˻� ����!!!!

	// 1. ��ġ��� ����Ʈ�� �����س��´�.
	std::vector<int> TileArrIndexList;
	TileArrIndexList.clear();

	// 2. ������ ��ġ��ϸ���Ʈ�� �ش� ���ǿ� ���� Ÿ���ε����� �߰��Ҽ��ִ��� �˻��Ѵ�.
	
	// ��ġ�Ϸ��� Ÿ���� �������ΰ��
	if (StartIndex % 6 == 0)
	{
		// 1. ������Ÿ���̸鼭 �ֻ�� Ÿ���ΰ��
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
						// �����ε��� �������� �˻��Ͽ� �Ѱ��� TRUE����� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� ��ġ������ Ÿ���̶�� Ÿ�ϸ�ϻ���
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
		// 2. ������Ÿ���̸鼭 ���ϴ� Ÿ���ΰ��
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
		// 3. �ΰ�찡 �ƴѰ��
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
	// ��ġ�Ϸ��� Ÿ���� �������ΰ��
	else if (StartIndex % 6 == 5)
	{
		// 1. �ֿ���Ÿ���̸鼭 �ֻ�� Ÿ���ΰ��
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
		// 2. �ֿ���Ÿ���̸鼭 ���ϴ� Ÿ���ΰ��
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
		// 3. �ΰ�찡 �ƴѰ��
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
						ChkFlag = true;
						break;
					}
				}

				if (true == ChkFlag)
				{
					break;
				}
			}

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
	// ��ġ�Ϸ��� Ÿ���� �������� �ƴϰ�, �ֿ����� �ƴѰ��
	else
	{
		// 1. ��ġ�Ϸ��� Ÿ���� �»�� �˻�
		//    StartIndex�� ���� ���ϴ� Ÿ���ε����� �ȴ�.
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
						// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

		// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
		else // �»�� ��ġ ���н�
		{
			// 2. ��ġ�Ϸ��� Ÿ���� ��� �˻�
			//    StartIndex�� �߾��ϴ� Ÿ���ε����� �ȴ�.
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
							// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

			// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
			else // ��� ��ġ ���н�
			{
				// 3. ���� �˻�
				//    StartIndex�� ���� ���ϴ� Ÿ���ε����� �ȴ�.
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
								// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

				// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
				else // ���� ���н�
				{
					// 4. ��� �˻�
					//    StartIndex�� �����´� Ÿ���ε����� �ȴ�.
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
									// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

					// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
					else // ��� ���н�
					{
						// 5. ���ϴ� �˻�
						//    StartIndex�� ���� �»�� Ÿ���ε����� �ȴ�.
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
										// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

						// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
						else // ���ϴ� ���н�
						{
							// 6. �ϴ� �˻�
							//    StartIndex�� ���� ���ͻ�� Ÿ���ε����� �ȴ�.
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
											// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

							// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
							else // �ϴܽ��н�
							{
								// 7. ���ϴ� �˻�
								//    StartIndex�� ���� ���� Ÿ���ε����� �ȴ�.
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
												// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

								// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
								else // ���ϴܽ��н�
								{
									// 8. �´� �˻�
									//    StartIndex�� ���� ���Ϳ�� Ÿ���ε����� �ȴ�.
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
													// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

									// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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
									else // �´ܽ��н�
									{
										// 9. ����
										//    StartIndex�� ���� Ÿ���ε����� �ȴ�.
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
														// Ÿ�ϰ˻��ؼ� �Ѱ��� true�̸� ��ġ�Ұ��� �Ǵ�
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

										// ��� �ε��� �˻��ؼ� ��ġ�����ϴٸ� �ε������ �ۼ�
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

	// 3. �� ���ǿ� ���Ͽ� Ÿ���ε�����Ͽ� Ÿ�ϸ���� �����Ǿ� �ִٸ� ��ġ�������� �Ǵ��ϰ�
	//    �ش� �������� ��ġ�ϱ����� ó���� �����Ѵ�.
	if (false == TileArrIndexList.empty())
	{
		// ��ġ �ε��� ��� ����
		std::sort(TileArrIndexList.begin(), TileArrIndexList.end());

		// ������ ���� ����
		StoredItem NewItem = {};
		NewItem.OneSize_ = false;
		NewItem.StartIndex = _ColTileIndex;
		NewItem.ArrangeIndexs_ = TileArrIndexList;
		
		// ������ ������ ��ġ ���
		// ������ ���������Ƿ� �ε�������� ù��°�� ��������° Ÿ���� ��ġ�� �̿��Ͽ� ���
		int ArrTileIndexCnt = static_cast<int>(TileArrIndexList.size());
		float4 BeginTilePos = StoreViewInfo_.ArrangeTiles_[TileArrIndexList[0]].TilePos_;
		float4 EndTilePos = StoreViewInfo_.ArrangeTiles_[TileArrIndexList[ArrTileIndexCnt - 1]].TilePos_;
		if (BeginTilePos.x == EndTilePos.x) // �ش� �������� �ʺ� 1
		{
			NewItem.RenderPos_.x = BeginTilePos.x;
		}
		else
		{
			BeginTilePos.x += ((EndTilePos.x - BeginTilePos.x) * 0.5f);
			NewItem.RenderPos_.x = BeginTilePos.x;
		}

		if (BeginTilePos.y == EndTilePos.y) // �ش� �������� ���� 1
		{
			NewItem.RenderPos_.y = BeginTilePos.y;
		}
		else
		{
			BeginTilePos.y -= ((BeginTilePos.y - EndTilePos.y) * 0.5f);
			NewItem.RenderPos_.y = BeginTilePos.y;
		}

		// ������ ���� �� �������� ����
		NewItem.ItemInfo_ = _CurItemInfo;
		NewItem.ItemInfo_.ItemLocType = ItemLocType::Storehouse_Bottom;
		NewItem.ItemInfo_.StartPosition = _ColTileIndex;

		// ������ ������ ����
		std::string TextureName = NewItem.ItemInfo_.ItemName_abbreviation_Inven;
		TextureName += ".png";
		NewItem.ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Render));
		NewItem.ItemRenderer_->SetImage(TextureName);
		NewItem.ItemRenderer_->GetTransform()->SetLocalPosition(NewItem.RenderPos_);

		StoreViewInfo_.HaveItemList_.push_back(NewItem);

		// ��ġ�� Ÿ�� ��� Flag Onó��
		for (int i = 0; i < ArrTileIndexCnt; ++i)
		{
			StoreViewInfo_.ArrangeTiles_[TileArrIndexList[i]].ItemArrangementFlag_ = true;
			StoreViewInfo_.ArrangeTiles_[TileArrIndexList[i]].TileRenderer_->SetAlpha(0.5f);
		}

		// 4. ��ġ�Ϸ��ߴٸ� true�� ��ȯ�Ͽ� ��ġ�Ϸ� ó���Ѵ�.
		return true;
	}

	return false;
}

void StoreView::ItemDisposition(int _ColTileIndex)
{
	// â��â �ش� Ÿ�Ͽ� ��ġ�� �������� ũ�������� �̿��Ͽ� �ش� Ÿ�Ͽ��� ��ġ������ ��Ű��,
	// �ش� �������� ���콺�� �����Ͽ� ���콺�� �ش�������� �������� ����

	// ���� ������ ����� �˻�
	int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
	for (int i = 0; i < HaveItemListCnt; ++i)
	{
		if (true == StoreViewInfo_.HaveItemList_[i].OneSize_)
		{
			// 1x1 ũ���� �������̹Ƿ� �ش� �浹�� Ÿ���� �ε����� �����ϴ� ���������� �Ǵ�
			if (StoreViewInfo_.HaveItemList_[i].StartIndex == _ColTileIndex)
			{
				// �����ϴ� �������̶�� �ش� �������� ���콺�� �����ϰ� �ش� �������� ��Ͽ��� �����ϸ�,
				// Ÿ�� Flag�� ������Ų��.
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].ItemArrangementFlag_ = false;
				StoreViewInfo_.ArrangeTiles_[_ColTileIndex].TileRenderer_->SetAlpha(0.f);

				std::string PutItemName = StoreViewInfo_.HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
				PutItemName += ".png";
				float4 ItemScale = StoreViewInfo_.HaveItemList_[i].ItemRenderer_->GetTransform()->GetLocalScaling();
				StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Death();

				// ���콺�� �ش� �������� �鵵�� ����
				GlobalValue::CurMouse->ItemHold(PutItemName, ItemScale);

				// �ش� �������� �����۸�Ͽ��� ����
				std::vector<StoredItem>::iterator DelIter = StoreViewInfo_.HaveItemList_.begin() + i;
				StoreViewInfo_.HaveItemList_.erase(DelIter);
				return;
			}
		}
		else
		{
			// 1x1 ũ���� �������� �ƴϹǷ� �ش� �������� �����ϴ� �ε�����Ͽ� �ش� �浹�� Ÿ���� �ε����� �����ϴ��� �Ǵ�
			int ArrTileCnt = static_cast<int>(StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_.size());
			for (int j = 0; j < ArrTileCnt; ++j)
			{
				if (StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[j] == _ColTileIndex)
				{
					// �ش� �������� ���������۸�Ͽ��� �����ϸ�, �ش� �������� �����ϰ��ִ� Ÿ���� �ε��� ������ �����ϰ�,
					// �ش� �������� ���콺�� �����Ѵ�.
					std::string ItemName = StoreViewInfo_.HaveItemList_[i].ItemInfo_.ItemName_abbreviation_Inven;
					ItemName += ".png";
					float4 ItemScale = StoreViewInfo_.HaveItemList_[i].ItemRenderer_->GetTransform()->GetLocalScaling();

					// �ش� �������� �����ϰ� �ִ� Ÿ������ ����
					int CurItemArrTileCnt = static_cast<int>(StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_.size());
					for (int k = 0; k < CurItemArrTileCnt; ++k)
					{
						StoreViewInfo_.ArrangeTiles_[StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[k]].ItemArrangementFlag_ = false;
						StoreViewInfo_.ArrangeTiles_[StoreViewInfo_.HaveItemList_[i].ArrangeIndexs_[k]].TileRenderer_->SetAlpha(0.f);
					}

					// �ش� ������ �������� ���� ���δ���
					StoreViewInfo_.HaveItemList_[i].ItemRenderer_->Death();

					// �ش� �������� ��Ͽ��� ����
					std::vector<StoredItem>::iterator DelIter = StoreViewInfo_.HaveItemList_.begin() + i;
					StoreViewInfo_.HaveItemList_.erase(DelIter);

					// �ش� �������� ���콺�� ���.
					GlobalValue::CurMouse->ItemHold(ItemName, ItemScale);
					
					return;
				}
			}
		}
	}
}

void StoreView::StoreViewOff()
{
	// �÷��̾��� �κ��丮â���� Close Button Ŭ���� ȣ���ϹǷ�
	// â��â�� �ݴ� ���Ҹ� �����Ѵ�.
	if (true == StoreViewActive_)
	{
		// Ȱ��ȭ Flag Off
		StoreViewActive_ = false;

		// â���� ��岨���� �˾��� Ȱ��ȭ ���¶�� ��Ȱ��ȭ
		if (true == TakeOutGoldPopup_->IsUpdate())
		{
			TakeOutGoldPopup_->TakeInOutGoldPopupInactive();
		}

		// â��â ��Ȱ��ȭ
		Off();

		// â��â�� ���� �����ϰ��ִ� ��� �������� ��Ȱ��ȭ
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
		// Ȱ��ȭ Flag On
		StoreViewActive_ = true;

		// 1. �÷��̾��� �κ��丮â�� Ȱ��ȭ��Ų��.
		GlobalValue::CurPlayer->InventoryViewEnabled(true);
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->GetMenuButton(1)->SetMiniMenuActive(true);

		// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.
		GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->SetMiniMenuActiveFlag(false);

		// 2. â��â Ȱ��ȭ ��Ų��.
		On();

		// 3. â��â�� ���� �����ϰ��ִ� ��� �������� Ȱ��ȭ
		int HaveItemListCnt = static_cast<int>(StoreViewInfo_.HaveItemList_.size());
		for (int i = 0; i < HaveItemListCnt; ++i)
		{
			StoreViewInfo_.HaveItemList_[i].ItemRenderer_->On();
		}
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
	int StoredGold = StoredGold_ - _Gold;
	if (0 >= StoredGold)
	{
		// ������差�� 0�� �ȴ�
		StoredGold_ = 0;
		StoreGold_->SetPrintText(std::to_string(StoredGold_));

		return 0;
	}

	// ���� ����� ������差�� �˸°� ã�Ҵٸ� �ش� ��常ŭ ����
	StoredGold_ = StoredGold;
	StoreGold_->SetPrintText(std::to_string(StoredGold_));

	// ���� ������忡 �°� ��带 ���´ٸ� -1 ��ȯ
	return -1;
}
