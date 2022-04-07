#include "PreCompile.h"
#include "InvArrangementItemInfo.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "MouseObject.h"

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

void InvArrangementItemInfo::SetTileIndexList(std::vector<int> _TileIndexList)
{
	// �ش� ������ ������ũ��(Width, Height ũ��)�� 1x1 ���� ũ�ٸ� �ش� ����� ����
	ArrangementTileIdxList_ = _TileIndexList;
}

bool InvArrangementItemInfo::CreateItemInfo(int _ListIndex, int _TileIndex, ItemLocType _TileLocType, const std::string& _ItemName, const float4& _RenderPos)
{
	// �ش� ���������� Get
	ItemList CurItemInfo = {};
	if(true == AllItemInfomation::GetInst().ItemInfoFindName(_ItemName, CurItemInfo))
	{
		// ��������
		TileLocType_ = _TileLocType;
		ListIndex_ = _ListIndex;
		TileIndex_ = _TileIndex;
		RenderPos_ = _RenderPos;
		ItemName_ = _ItemName;

		// ItemName_�� �����Ͽ� �ؽ��ĸ�, �����۸�(�κ���) ����
		InvItemName_ = "inv";
		InvItemName_ += ItemName_;

		ItemTexutreName_ = InvItemName_;
		ItemTexutreName_ += ".png";

		// �ش� �ؽ����� ������ ũ�� Get
		GameEngineTexture* CurItemTexture = GameEngineTextureManager::GetInst().Find(ItemTexutreName_);
		RenderScale_ = CurItemTexture->GetTextureSize();

		// �ʿ��� ���������� ����
		WidthSize_ = CurItemInfo.WidthSize;
		HeightSize_ = CurItemInfo.HeightSize;
		ItemCode_ = CurItemInfo.ItemCode;

		// ������ ���� �� ��ġ
		InvItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Render));
		InvItemRenderer_->SetImage(ItemTexutreName_);
		InvItemRenderer_->GetTransform()->SetLocalPosition(RenderPos_);
		InvItemRenderer_->GetTransform()->SetLocalScaling(RenderScale_);

		Off();

		return true;
	}

	return false;
}
