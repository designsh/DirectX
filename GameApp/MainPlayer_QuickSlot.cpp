#include "PreCompile.h"
#include "MainPlayer_QuickSlot.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "BottomStateBar.h"
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "MouseObject.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_BuySellView.h"

MainPlayer_QuickSlot::MainPlayer_QuickSlot() :
	QuickSlotInfo_()
{
}

MainPlayer_QuickSlot::~MainPlayer_QuickSlot()
{
}

void MainPlayer_QuickSlot::Start()
{
	// ������ ���� �� ������ ����

	QuickSlotInfo_.resize(4);
	int QuickSlotCnt = static_cast<int>(QuickSlotInfo_.size());
	for (int i = 0; i < QuickSlotCnt; ++i)
	{
		QuickSlotInfo_[i].ItemArrangementFlag_ = false;
		QuickSlotInfo_[i].TileRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
		QuickSlotInfo_[i].TileRenderer_->SetImage("InvTestTileImage.png");
		QuickSlotInfo_[i].TileRenderer_->GetTransform()->SetLocalScaling(float4(28.f, 28.f));
		QuickSlotInfo_[i].TileRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.f));

		float4 RenderPos = float4::ZERO;
		RenderPos.x = 36.f + (28.f * i) + (i * 3.f);
		RenderPos.y = -277.f;
		QuickSlotInfo_[i].TileRenderer_->GetTransform()->SetLocalPosition(RenderPos);

		QuickSlotInfo_[i].TileCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
		QuickSlotInfo_[i].TileCollision_->GetTransform()->SetLocalScaling(QuickSlotInfo_[i].TileRenderer_->GetTransform()->GetLocalScaling());
		QuickSlotInfo_[i].TileCollision_->GetTransform()->SetLocalPosition(QuickSlotInfo_[i].TileRenderer_->GetTransform()->GetLocalPosition());
	}

	// ������ Ű����
	if (false == GameEngineInput::GetInst().IsKey("QuickSlot_1_Use"))
	{
		GameEngineInput::GetInst().CreateKey("QuickSlot_1_Use", '1');
	}
	if (false == GameEngineInput::GetInst().IsKey("QuickSlot_2_Use"))
	{
		GameEngineInput::GetInst().CreateKey("QuickSlot_2_Use", '2');
	}
	if (false == GameEngineInput::GetInst().IsKey("QuickSlot_3_Use"))
	{
		GameEngineInput::GetInst().CreateKey("QuickSlot_3_Use", '3');
	}
	if (false == GameEngineInput::GetInst().IsKey("QuickSlot_4_Use"))
	{
		GameEngineInput::GetInst().CreateKey("QuickSlot_4_Use", '4');
	}
}

void MainPlayer_QuickSlot::Update(float _DeltaTime)
{
	if (false == QuickSlotInfo_.empty())
	{
		int QuickSlotCnt = static_cast<int>(QuickSlotInfo_.size());
		for (int i = 0; i < QuickSlotCnt; ++i)
		{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(QuickSlotInfo_[i].TileCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			if (nullptr != QuickSlotInfo_[i].TileCollision_)
			{
				QuickSlotInfo_[i].TileCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_QuickSlot::QuickSlotClick, this, std::placeholders::_1, i));
			}
		}
	}

#pragma region ������ Űüũ
	if (true == GameEngineInput::GetInst().Down("QuickSlot_1_Use"))
	{
		QuickSlotItemUse(0);
	}
	if (true == GameEngineInput::GetInst().Down("QuickSlot_2_Use"))
	{
		QuickSlotItemUse(1);
	}
	if (true == GameEngineInput::GetInst().Down("QuickSlot_3_Use"))
	{
		QuickSlotItemUse(2);
	}
	if (true == GameEngineInput::GetInst().Down("QuickSlot_4_Use"))
	{
		QuickSlotItemUse(3);
	}
#pragma endregion
}

void MainPlayer_QuickSlot::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void MainPlayer_QuickSlot::QuickSlotClick(GameEngineCollision* _Other, int _Index)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���콺�� ���°� Stay or Move �����϶��� ��ġ����
		if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() ||
			MouseState::Move == GlobalValue::CurMouse->GetMouseState())
		{
			// ���콺�� �������� ���������, �ش� ������ Ÿ�Ͽ� �������� ���������ʴٸ�
			if (false == QuickSlotInfo_[_Index].ItemArrangementFlag_ && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemPlacement(_Index);
			}
			// ���콺�� �������� �������������, �ش� ������ Ÿ�Ͽ� �������� �����Ѵٸ�
			else if (true == QuickSlotInfo_[_Index].ItemArrangementFlag_ && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemDisposition(_Index);
			}
		}
		// ���콺�� ���°� Sell �����̸� �Ǹ�
		else if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState())
		{
			// �ش� �������� �������� �����Ѵٸ�
			if (false == QuickSlotInfo_[_Index].ItemArrangementFlag_)
			{
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // �����Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // ��ȭ�Ǹ�â Ȱ��ȭ�϶�
				{
					ItemSellProcess(_Index, NPCType::PotionShop);
				}
			}
		}
	}
}

void MainPlayer_QuickSlot::ItemPlacement(int _ColTileIndex)
{
	std::string ItemName = GlobalValue::CurMouse->GetHoldItemName();
	size_t DotFindIndex = ItemName.find('.');
	ItemName = ItemName.substr(0, DotFindIndex);

	// ������ ��ü��Ͽ��� �ش������ ���� Get
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(ItemName, CurItemInfo))
	{
		// �ش� �������� ũ�Ⱑ 1x1�̰�, �����ΰ�쿡�� ��ġ����
		int WidthSize = CurItemInfo.WidthSize;
		int HeightSize = CurItemInfo.HeightSize;
		if (WidthSize == 1 && HeightSize == 1 && CurItemInfo.ItemCode == 18)
		{
			// Ÿ������ ����
			QuickSlotInfo_[_ColTileIndex].ItemArrangementFlag_ = true;
			QuickSlotInfo_[_ColTileIndex].TileRenderer_->SetAlpha(0.5f);

			// ���������� ����
			QuickSlotInfo_[_ColTileIndex].ItemInfo_ = CurItemInfo;
			if (_ColTileIndex == 0)
			{
				QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType = ItemLocType::BotStat_Portion1;
			}
			else if (_ColTileIndex == 1)
			{
				QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType = ItemLocType::BotStat_Portion2;
			}
			else if (_ColTileIndex == 2)
			{
				QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType = ItemLocType::BotStat_Portion3;
			}
			else if (_ColTileIndex == 3)
			{
				QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType = ItemLocType::BotStat_Portion4;
			}
			QuickSlotInfo_[_ColTileIndex].ItemInfo_.StartPosition = 0;

			QuickSlotInfo_[_ColTileIndex].ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11_Render));
			QuickSlotInfo_[_ColTileIndex].ItemRenderer_->TextSetting("diablo", std::to_string(_ColTileIndex + 1), 12.f, FW1_LEFT | FW1_VCENTER, float4(0.8f, 0.8f, 0.2f), float4(-12.f, 6.f));
			QuickSlotInfo_[_ColTileIndex].ItemRenderer_->SetImage(GlobalValue::CurMouse->GetHoldItemName());
			QuickSlotInfo_[_ColTileIndex].ItemRenderer_->GetTransform()->SetLocalPosition(QuickSlotInfo_[_ColTileIndex].TileRenderer_->GetTransform()->GetLocalPosition());

			// �÷��̾������� ���������� ��Ͽ� �ش� �������� �߰�
			MainPlayerInfomation::GetInst().PlayerItemAdd(QuickSlotInfo_[_ColTileIndex].ItemInfo_);

			// ��ġ �Ϸ������Ƿ� ���콺�� �ش� �������� �������´�.
			GlobalValue::CurMouse->ItemPutDown();
		}
	}
}

void MainPlayer_QuickSlot::ItemDisposition(int _ColTileIndex)
{
	// �ش� �������� ��ġ��Ͽ��� �����ϰ�, �ش� �������� ���콺�� ����
	float4 ItemScale = QuickSlotInfo_[_ColTileIndex].ItemRenderer_->GetTransform()->GetLocalScaling();
	std::string ItemName = QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemName_abbreviation_Inven;
	ItemName += ".png";

	// �÷��̾������� ���������� ��Ͽ� �ش� ������ ����
	MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType, QuickSlotInfo_[_ColTileIndex].ItemInfo_.StartPosition);

	// 
	QuickSlotInfo_[_ColTileIndex].ItemArrangementFlag_ = false;
	QuickSlotInfo_[_ColTileIndex].TileRenderer_->SetAlpha(0.f);

	QuickSlotInfo_[_ColTileIndex].ItemRenderer_->Death();
	QuickSlotInfo_[_ColTileIndex].ItemRenderer_ = nullptr;

	// ���콺�� �ش� �������� ���ø���.
	GlobalValue::CurMouse->ItemHold(ItemName, ItemScale);
}

void MainPlayer_QuickSlot::QuickSlotItemUse(int _Index)
{
	// �ش� �����Կ� �������� �����Ѵٸ� �ش� �������� ����ϸ�
	// ���ุ�� ��ġ�ϱ⶧���� �÷��̾��� HP�� MP�� ��ü ȸ���Ѵ�.
	if (true == QuickSlotInfo_[_Index].ItemArrangementFlag_)
	{
		// �ش� �������� ��Ͽ��� �����ϰ� Flag�����ϸ�, 
		QuickSlotInfo_[_Index].ItemArrangementFlag_ = false;
		QuickSlotInfo_[_Index].TileRenderer_->SetAlpha(0.f);

		// �÷��̾������� ���������� ��Ͽ� �ش� ������ ����
		MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_Index].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_Index].ItemInfo_.ItemLocType, QuickSlotInfo_[_Index].ItemInfo_.StartPosition);

		QuickSlotInfo_[_Index].ItemRenderer_->Death();
		QuickSlotInfo_[_Index].ItemRenderer_ = nullptr;

		// �÷��̾��� HP�� MP�� ��üȸ��
		GlobalValue::CurPlayer->AllCurrentHPRecovery();
		GlobalValue::CurPlayer->AllCurrentMPRecovery();
	}
}

void MainPlayer_QuickSlot::ItemSellProcess(int _TileIndex, NPCType _BuySellType)
{
	// �Ǹ��Ϸ��� �������̸� Get
	std::string SellItemName = QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation_Inven;

	// ��ȭ���ο��� �Ǹ��ϴ� ���
	if (_BuySellType == NPCType::PotionShop)
	{
		// �ش� �������� ������ �ش� �Ǹ�â�� ����

		// �ش� ������ �ڵ尡 ����Ÿ���� �������̶�� NPC�� ������常 ����
		if (!(16 <= QuickSlotInfo_[_TileIndex].ItemInfo_.ItemCode && QuickSlotInfo_[_TileIndex].ItemInfo_.ItemCode <= 18))
		{
			// 
			GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(QuickSlotInfo_[_TileIndex].ItemInfo_.Price);

			// �÷��̾������� ���������� ��Ͽ� �ش� ������ ����
			MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_TileIndex].ItemInfo_.ItemLocType, QuickSlotInfo_[_TileIndex].ItemInfo_.StartPosition);

			// �����Կ��� �ش� ������ ����
			QuickSlotInfo_[_TileIndex].ItemArrangementFlag_ = false;
			QuickSlotInfo_[_TileIndex].TileRenderer_->SetAlpha(0.f);

			QuickSlotInfo_[_TileIndex].ItemRenderer_->Death();
			QuickSlotInfo_[_TileIndex].ItemRenderer_ = nullptr;

			// �÷��̾��� ������� ����
			GlobalValue::CurPlayer->HaveGoldAdd(QuickSlotInfo_[_TileIndex].ItemInfo_.Price);
		}
		// �ƴ϶�� �ش�������� �Ǹ�â�� ����
		else
		{
			// ���� NPC�� ������Ͽ� �ش� �������� �����ϴ��� �Ǵ�
			if (true == GlobalValue::ChandleryNPC->GetChandleryShop()->SellItemCheck(QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation_Inven))
			{
				// �����Ѵٸ� �ش� �������� ������ ����

			}
			else
			{
				// �ش� ������ ��ġ���� ���� �Ǵ�

			}
		}
	}
	// ������ο��� �Ǹ��ϴ� ���
	else if (_BuySellType == NPCType::WeaponShop)
	{
		// �ش� �������� ������ �ش� �Ǹ�â�� ����



	}
}
