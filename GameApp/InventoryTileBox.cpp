#include "PreCompile.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "AllItemInfomation.h"

InventoryTileBox::InventoryTileBox() :
	ItemArrangementFlag_(false),
	BoxTileType_(ItemLocType::Inven_Bottom),
	Index_(-1),
	IndexX_(-1),
	IndexY_(-1),
	Pos_(float4::ZERO),
	Scale_(float4::ZERO),
	TileBoxRenderer_(nullptr)
{
}

InventoryTileBox::~InventoryTileBox()
{
}

void InventoryTileBox::Start()
{
}

void InventoryTileBox::Update(float _DeltaTime)
{
}

void InventoryTileBox::SetItemArrangeFlagOn()
{
	ItemArrangementFlag_ = true;

	if (nullptr != TileBoxRenderer_)
	{
		TileBoxRenderer_->SetResultColor(float4(0.f, 0.f, 1.f, 0.5f));
	}
}

void InventoryTileBox::SetItemArrangeFlagOff()
{
	ItemArrangementFlag_ = false;

	if (nullptr != TileBoxRenderer_)
	{
		if (ItemLocType::Inven_Bottom == BoxTileType_)
		{
			TileBoxRenderer_->SetResultColor(float4(1.f, 1.f, 1.f, 0.f));
		}
		else
		{
			TileBoxRenderer_->SetResultColor(float4(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void InventoryTileBox::TileBoxActive()
{
	if (nullptr != TileBoxRenderer_)
	{
		TileBoxRenderer_->On();
	}
}

void InventoryTileBox::TileBoxInactive()
{
	if (nullptr != TileBoxRenderer_)
	{
		TileBoxRenderer_->Off();
	}
}

void InventoryTileBox::CreateNormalTileBox(bool _ArrangementFlag, ItemLocType _BoxTileType, int _X, int _Y, int _Index)
{
	// 타일박스 정보 셋팅
	ItemArrangementFlag_ = _ArrangementFlag;
	BoxTileType_ = _BoxTileType;
	IndexX_ = _X;
	IndexY_ = _Y;
	Index_ = _Index;

	// Rendering Pos Calc & Scale Save
	Pos_ = float4::ZERO;
	Pos_.x = 33.f + (IndexX_ * 28.f) + (IndexX_ * 1.f);
	Pos_.y = -116.f + (IndexY_ * 28.f) + (IndexY_ * 1.f);

	Scale_ = float4(28.f, 28.f, 1.f);

	// 타일박스 렌더러 생성
	TileBoxRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	TileBoxRenderer_->SetImage("InvTestTileImage.png");
	TileBoxRenderer_->SetResultColor(float4(1.f, 1.f, 1.f, 0.f));
#ifdef _DEBUG
	TileBoxRenderer_->TextSetting("diablo", std::to_string(Index_), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
#endif // _DEBUG
	TileBoxRenderer_->GetTransform()->SetLocalPosition(Pos_);
	TileBoxRenderer_->GetTransform()->SetLocalScaling(Scale_);
	TileBoxRenderer_->Off();
}

void InventoryTileBox::CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, ItemLocType _BoxTileType, int _Index, float4 _Pos, float4 _Scale)
{
	// 타일박스 정보 셋팅
	ItemArrangementFlag_ = _ArrangementFlag;
	BoxTileType_ = _BoxTileType;
	IndexX_ = -1;
	IndexY_ = -1;
	Index_ = _Index;
	Pos_ = _Pos;
	Scale_ = _Scale;

	// Create TileBox Renderer
	TileBoxRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	TileBoxRenderer_->SetImage(_TextureName);
	TileBoxRenderer_->GetTransform()->SetLocalPosition(Pos_);
	TileBoxRenderer_->GetTransform()->SetLocalScaling(Scale_);
	TileBoxRenderer_->Off();
}
