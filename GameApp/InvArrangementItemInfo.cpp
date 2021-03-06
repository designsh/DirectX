#include "PreCompile.h"
#include "InvArrangementItemInfo.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "MouseObject.h"

#include "MainPlayer.h"
#include "MainPlayerInfomation.h"

#include "AllItemInfomation.h"

InvArrangementItemInfo::InvArrangementItemInfo() :
	ListIndex_(-1),
	TileLocType_(),
	TileIndex_(-1),
	WidthSize_(1),
	HeightSize_(1),
	ItemName_(),
	InvItemName_(),
	ItemTexutreName_(),
	ItemCode_(-1),
	RenderPos_(float4::ZERO),
	RenderScale_(float4::ZERO),
	InvItemRenderer_(nullptr)
{
}

InvArrangementItemInfo::~InvArrangementItemInfo()
{
}

void InvArrangementItemInfo::Start()
{
}

void InvArrangementItemInfo::Update(float _DeltaTime)
{
}

void InvArrangementItemInfo::SetItemRenderPos(const float4& _RenderPos)
{
	if (nullptr != InvItemRenderer_)
	{
		RenderPos_ = _RenderPos;
		InvItemRenderer_->GetTransform()->SetLocalPosition(RenderPos_);
	}

}

void InvArrangementItemInfo::SetTileIndexList(std::vector<int> _TileIndexList)
{
	// 해당 아이템 렌더러크기(Width, Height 크기)가 1x1 보다 크다면 해당 목록을 셋팅
	ArrangementTileIdxList_ = _TileIndexList;
}

bool InvArrangementItemInfo::CreateItemInfo(int _ListIndex, int _TileIndex, ItemLocType _TileLocType, const std::string& _ItemName, const float4& _RenderPos, bool _CreateInfo)
{
	// 해당 아이템정보 Get
	ItemList CurItemInfo = {};
	if(true == AllItemInfomation::GetInst().ItemInfoFindName(_ItemName, CurItemInfo))
	{
		// 정보저장
		TileLocType_ = _TileLocType;
		ListIndex_ = _ListIndex;
		TileIndex_ = _TileIndex;
		RenderPos_ = _RenderPos;
		ItemName_ = _ItemName;

		// ItemName_을 편집하여 텍스쳐명, 아이템명(인벤용) 저장
		InvItemName_ = "inv";
		InvItemName_ += ItemName_;

		ItemTexutreName_ = InvItemName_;
		ItemTexutreName_ += ".png";

		// 해당 텍스쳐의 렌더링 크기 Get
		GameEngineTexture* CurItemTexture = GameEngineTextureManager::GetInst().Find(ItemTexutreName_);
		RenderScale_ = CurItemTexture->GetTextureSize();

		// 필요한 아이템정보 저장
		WidthSize_ = CurItemInfo.WidthSize;
		HeightSize_ = CurItemInfo.HeightSize;
		ItemCode_ = CurItemInfo.ItemCode;

		// 렌더러 생성 및 배치
		InvItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));
		InvItemRenderer_->SetImage(ItemTexutreName_);
		InvItemRenderer_->GetTransform()->SetLocalPosition(RenderPos_);
		InvItemRenderer_->GetTransform()->SetLocalScaling(RenderScale_);

		// 정보생성 성공시 플레이어 아이템 보유목록에 해당 아이템 정보 추가(초기 생성시 _CreateInfo = false)
		if (true == _CreateInfo)
		{
			// 현재 갱신 정보로 갱신 후 저장
			CurItemInfo.StartPosition = TileIndex_;
			CurItemInfo.ItemLocType = TileLocType_;
			MainPlayerInfomation::GetInst().PlayerItemAdd(CurItemInfo);
		}

		Off();

		return true;
	}

	return false;
}

bool InvArrangementItemInfo::ItemArrngeListFind(int _Index)
{
	// 목록 검색해서 동일한 인덱스가 존재한다면 true 리턴
	for (int i = 0; i < static_cast<int>(ArrangementTileIdxList_.size()); ++i)
	{
		if (ArrangementTileIdxList_[i] == _Index)
		{
			return true;
		}
	}

	return false;
}
