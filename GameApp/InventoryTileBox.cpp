#include "PreCompile.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

InventoryTileBox::InventoryTileBox() :
	ArrangementFlag_(false),
	BoxTileType_(ItemLocType::Inven_Bottom),
	Index_(-1),
	IndexX_(-1),
	IndexY_(-1),
	Pos_(float4::ZERO),
	Scale_(float4::ZERO),
	TileBoxRenderer_(nullptr),
	TileBoxCollider_(nullptr),
	TileBoxButtonState_(Button_State::Normal),
	TileBoxItemEquipRenderer_(nullptr),
	TextImage_{}
{
}

InventoryTileBox::~InventoryTileBox()
{
}

void InventoryTileBox::Start()
{
	TextImage_ = "InvTestTileImage.png";
}

void InventoryTileBox::Update(float _DeltaTime)
{
	if (TileBoxButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 아이템을 들고있는 상태에서 충돌했다면
			// 해당 아이템 해당 타일에 배치
			ItemEquipCheck(BoxTileType_);

			TileBoxButtonState_ = Button_State::Normal;
		}
	}

	if (nullptr != TileBoxCollider_)
	{
		TileBoxCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryTileBox::BoxTileClick, this, std::placeholders::_1));

		// 테스트용
		//GetLevel()->PushDebugRender(TileBoxCollider_->GetTransform(), CollisionType::Rect);
	}
}

void InventoryTileBox::BoxTileClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		TileBoxButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		
	}
}

void InventoryTileBox::ItemEquipCheck(ItemLocType _BoxTileType)
{
	// 현재 커서가 아이템을 들고있는지 체크하여 들고있다면 해당 아이템 타일에 배치


	// 아니라면 리턴
}

void InventoryTileBox::ItemBatch(const std::string _ItemName)
{
	// 정보 생성시 호출되며 해당 이미지렌더러의 텍스쳐를 변경하고,
	// 장착 Flag를 On


	
}

void InventoryTileBox::TileBoxActive()
{
	if (nullptr != TileBoxRenderer_)
	{
		TileBoxRenderer_->On();
	}

	if (nullptr != TileBoxCollider_)
	{
		TileBoxCollider_->On();
	}
}

void InventoryTileBox::TileBoxInactive()
{
	if (nullptr != TileBoxRenderer_)
	{
		TileBoxRenderer_->Off();
	}

	if (nullptr != TileBoxCollider_)
	{
		TileBoxCollider_->Off();
	}
}

void InventoryTileBox::CreateNormalTileBox(bool _ArrangementFlag, ItemLocType _BoxTileType, int _X, int _Y, int _Index)
{
	// 타일박스 정보 셋팅
	ArrangementFlag_ = _ArrangementFlag;
	BoxTileType_ = _BoxTileType;
	IndexX_ = _X;
	IndexY_ = _Y;
	Index_ = _Index;

	// Rendering Pos Calc & Scale Save
	Pos_ = float4::ZERO;
	Pos_.x = 33.f + (IndexX_ * 28.f) + (IndexX_ * 1.f);
	Pos_.y = -116.f + (IndexY_ * 28.f) + (IndexY_ * 1.f);;

	Scale_ = float4(28.f, 28.f, 1.f);

	// 타일박스 렌더러 생성
	TileBoxRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	TileBoxRenderer_->SetImage(TextImage_);
	TileBoxRenderer_->TextSetting("diablo", std::to_string(Index_), 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);
	TileBoxRenderer_->GetTransform()->SetLocalPosition(Pos_);
	TileBoxRenderer_->GetTransform()->SetLocalScaling(Scale_);
	TileBoxRenderer_->Off();

	// Create Item용 Renderer 생성(기본 Off) - 아이템장착시 이미지가 셋팅되며 On상태로 전환
	TileBoxItemEquipRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxItemEquipRenderer_->Off();

	// 타일박스 충돌체 생성
	TileBoxCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	TileBoxCollider_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxCollider_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxCollider_->Off();
}

void InventoryTileBox::CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, ItemLocType _BoxTileType, int _Index, float4 _Pos, float4 _Scale)
{
	// 타일박스 정보 셋팅
	ArrangementFlag_ = _ArrangementFlag;
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

	// Create Item용 Renderer 생성(기본 Off) - 아이템장착시 이미지가 셋팅되며 On상태로 전환
	TileBoxItemEquipRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxItemEquipRenderer_->Off();
	
	// Create TileBox Collider
	TileBoxCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	TileBoxCollider_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxCollider_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxCollider_->Off();
}
