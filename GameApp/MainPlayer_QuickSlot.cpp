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
	// 퀵슬롯 정보 및 렌더러 생성

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

	// 퀵슬롯 키생성
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

#pragma region 퀵슬롯 키체크
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
		// 마우스의 상태가 Stay or Move 상태일때만 배치가능
		if (MouseState::Stay == GlobalValue::CurMouse->GetMouseState() ||
			MouseState::Move == GlobalValue::CurMouse->GetMouseState())
		{
			// 마우스가 아이템을 들고있으며, 해당 퀵슬롯 타일에 아이템이 존재하지않다면
			if (false == QuickSlotInfo_[_Index].ItemArrangementFlag_ && true == GlobalValue::CurMouse->IsItemHold())
			{
				ItemPlacement(_Index);
			}
			// 마우스가 아이템을 들고있지않으며, 해당 퀵슬롯 타일에 아이템이 존재한다면
			else if (true == QuickSlotInfo_[_Index].ItemArrangementFlag_ && false == GlobalValue::CurMouse->IsItemHold())
			{
				ItemDisposition(_Index);
			}
		}
		// 마우스의 상태가 Sell 상태이면 판매
		else if (MouseState::Sell == GlobalValue::CurMouse->GetMouseState())
		{
			// 해당 퀵슬롯의 아이템이 존재한다면
			if (false == QuickSlotInfo_[_Index].ItemArrangementFlag_)
			{
				if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate()) // 무기판매창 활성화일때
				{
					ItemSellProcess(_Index, NPCType::WeaponShop);
				}
				else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate()) // 잡화판매창 활성화일때
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

	// 아이템 전체목록에서 해당아이템 정보 Get
	ItemList CurItemInfo = {};
	if (true == AllItemInfomation::GetInst().ItemInfoFindInvName(ItemName, CurItemInfo))
	{
		// 해당 아이템의 크기가 1x1이고, 물약인경우에만 배치가능
		int WidthSize = CurItemInfo.WidthSize;
		int HeightSize = CurItemInfo.HeightSize;
		if (WidthSize == 1 && HeightSize == 1 && CurItemInfo.ItemCode == 18)
		{
			// 타일정보 갱신
			QuickSlotInfo_[_ColTileIndex].ItemArrangementFlag_ = true;
			QuickSlotInfo_[_ColTileIndex].TileRenderer_->SetAlpha(0.5f);

			// 아이템정보 생성
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

			// 플레이어정보의 보유아이템 목록에 해당 아이템을 추가
			MainPlayerInfomation::GetInst().PlayerItemAdd(QuickSlotInfo_[_ColTileIndex].ItemInfo_);

			// 배치 완료했으므로 마우스는 해당 아이템을 내려놓는다.
			GlobalValue::CurMouse->ItemPutDown();
		}
	}
}

void MainPlayer_QuickSlot::ItemDisposition(int _ColTileIndex)
{
	// 해당 아이템을 배치목록에서 제거하고, 해당 아이템을 마우스에 전달
	float4 ItemScale = QuickSlotInfo_[_ColTileIndex].ItemRenderer_->GetTransform()->GetLocalScaling();
	std::string ItemName = QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemName_abbreviation_Inven;
	ItemName += ".png";

	// 플레이어정보의 보유아이템 목록에 해당 아이템 제거
	MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_ColTileIndex].ItemInfo_.ItemLocType, QuickSlotInfo_[_ColTileIndex].ItemInfo_.StartPosition);

	// 
	QuickSlotInfo_[_ColTileIndex].ItemArrangementFlag_ = false;
	QuickSlotInfo_[_ColTileIndex].TileRenderer_->SetAlpha(0.f);

	QuickSlotInfo_[_ColTileIndex].ItemRenderer_->Death();
	QuickSlotInfo_[_ColTileIndex].ItemRenderer_ = nullptr;

	// 마우스는 해당 아이템을 들어올린다.
	GlobalValue::CurMouse->ItemHold(ItemName, ItemScale);
}

void MainPlayer_QuickSlot::QuickSlotItemUse(int _Index)
{
	// 해당 퀵슬롯에 아이템이 존재한다면 해당 아이템을 사용하며
	// 물약만을 배치하기때문에 플레이어의 HP와 MP를 전체 회복한다.
	if (true == QuickSlotInfo_[_Index].ItemArrangementFlag_)
	{
		// 해당 아이템을 목록에서 제거하고 Flag해제하며, 
		QuickSlotInfo_[_Index].ItemArrangementFlag_ = false;
		QuickSlotInfo_[_Index].TileRenderer_->SetAlpha(0.f);

		// 플레이어정보의 보유아이템 목록에 해당 아이템 제거
		MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_Index].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_Index].ItemInfo_.ItemLocType, QuickSlotInfo_[_Index].ItemInfo_.StartPosition);

		QuickSlotInfo_[_Index].ItemRenderer_->Death();
		QuickSlotInfo_[_Index].ItemRenderer_ = nullptr;

		// 플레이어의 HP와 MP를 전체회복
		GlobalValue::CurPlayer->AllCurrentHPRecovery();
		GlobalValue::CurPlayer->AllCurrentMPRecovery();
	}
}

void MainPlayer_QuickSlot::ItemSellProcess(int _TileIndex, NPCType _BuySellType)
{
	// 판매하려는 아이템이름 Get
	std::string SellItemName = QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation_Inven;

	// 잡화상인에게 판매하는 경우
	if (_BuySellType == NPCType::PotionShop)
	{
		// 해당 아이템의 정보를 해당 판매창에 전달

		// 해당 아이템 코드가 무기타입의 아이템이라면 NPC의 보유골드만 감소
		if (!(16 <= QuickSlotInfo_[_TileIndex].ItemInfo_.ItemCode && QuickSlotInfo_[_TileIndex].ItemInfo_.ItemCode <= 18))
		{
			// 
			GlobalValue::ChandleryNPC->GetChandleryShop()->SubHaveGold(QuickSlotInfo_[_TileIndex].ItemInfo_.Price);

			// 플레이어정보의 보유아이템 목록에 해당 아이템 제거
			MainPlayerInfomation::GetInst().PlayerItemDel(QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation, QuickSlotInfo_[_TileIndex].ItemInfo_.ItemLocType, QuickSlotInfo_[_TileIndex].ItemInfo_.StartPosition);

			// 퀵슬롯에서 해당 아이템 제거
			QuickSlotInfo_[_TileIndex].ItemArrangementFlag_ = false;
			QuickSlotInfo_[_TileIndex].TileRenderer_->SetAlpha(0.f);

			QuickSlotInfo_[_TileIndex].ItemRenderer_->Death();
			QuickSlotInfo_[_TileIndex].ItemRenderer_ = nullptr;

			// 플레이어의 보유골드 증가
			GlobalValue::CurPlayer->HaveGoldAdd(QuickSlotInfo_[_TileIndex].ItemInfo_.Price);
		}
		// 아니라면 해당아이템을 판매창에 전달
		else
		{
			// 현재 NPC의 보유목록에 해당 아이템이 존재하는지 판단
			if (true == GlobalValue::ChandleryNPC->GetChandleryShop()->SellItemCheck(QuickSlotInfo_[_TileIndex].ItemInfo_.ItemName_abbreviation_Inven))
			{
				// 존재한다면 해당 아이템의 수량만 증가

			}
			else
			{
				// 해당 아이템 배치가능 여부 판단

			}
		}
	}
	// 무기상인에게 판매하는 경우
	else if (_BuySellType == NPCType::WeaponShop)
	{
		// 해당 아이템의 정보를 해당 판매창에 전달



	}
}
