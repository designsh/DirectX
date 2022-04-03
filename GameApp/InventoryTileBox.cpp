#include "PreCompile.h"
#include "InventoryTileBox.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MainPlayerInfomation.h"

InventoryTileBox::InventoryTileBox() :
	ArrangementFlag_(false),
	BoxTileType_(InvenTileBoxType::NORMAL),
	Index_(-1),
	IndexX_(-1),
	IndexY_(-1),
	Pos_(float4::ZERO),
	Scale_(float4::ZERO),
	TileBoxRenderer_(nullptr),
	TileBoxCollider_(nullptr),
	TileBoxButtonState_(Button_State::Normal),
	TileBoxItemEquipRenderer_(nullptr)
{
}

InventoryTileBox::~InventoryTileBox()
{
}

void InventoryTileBox::Start()
{
	TextImage_.resize(2);
	TextImage_[0] = "InvTestTileImage1.png";
	TextImage_[1] = "InvTestTileImage2.png";
}

void InventoryTileBox::Update(float _DeltaTime)
{
	if (TileBoxButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �������� ����ִ� ���¿��� �浹�ߴٸ�
			// �ش� ������ �ش� Ÿ�Ͽ� ��ġ
			ItemEquipCheck(BoxTileType_);

			TileBoxButtonState_ = Button_State::Normal;
		}
	}

	if (nullptr != TileBoxCollider_)
	{
		TileBoxCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&InventoryTileBox::BoxTileClick, this, std::placeholders::_1));

		// �׽�Ʈ��
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

void InventoryTileBox::ItemEquipCheck(InvenTileBoxType _BoxTileType)
{
	// ���� Ŀ���� �������� ����ִ��� üũ�Ͽ� ����ִٸ� �ش� ������ Ÿ�Ͽ� ��ġ


	// �ƴ϶�� ����



	switch (_BoxTileType)
	{
		case InvenTileBoxType::NORMAL:	// �Ϲ�Ÿ��
		{

			break;
		}
		case InvenTileBoxType::HELM:	// ����
		{

			break;
		}
		case InvenTileBoxType::ARMOR:	// ����
		{

			break;
		}
		case InvenTileBoxType::LRING:	// ���� ��
		{

			break;
		}
		case InvenTileBoxType::RRING:	// ������ ��
		{

			break;
		}
		case InvenTileBoxType::AMULET:	// �����
		{

			break;
		}
		case InvenTileBoxType::GLOVES:	// �尩
		{

			break;
		}
		case InvenTileBoxType::BOOTS:	// ����
		{

			break;
		}
		case InvenTileBoxType::WEAPON:	// ����(��)
		{

			break;
		}
		case InvenTileBoxType::SHIELD:	// �ǵ�(��)
		{

			break;
		}
	}
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

void InventoryTileBox::CreateNormalTileBox(bool _ArrangementFlag, InvenTileBoxType _BoxTileType, int _X, int _Y, int _Index)
{
	// Ÿ�Ϲڽ� ���� ����
	ArrangementFlag_ = _ArrangementFlag;
	BoxTileType_ = _BoxTileType;
	IndexX_ = _X;
	IndexY_ = _Y;
	Index_ = _Index;

	// TEST Image Setting
	std::string TextureName = "";
	if (Index_ % 2 == 0)
	{
		TextureName = TextImage_[0];
	}
	else
	{
		TextureName = TextImage_[1];
	}

	// Rendering Pos Calc & Scale Save
	Pos_ = float4::ZERO;
	Pos_.x = 33.f + (IndexX_ * 28.f) + (IndexX_ * 1.f);
	Pos_.y = -116.f + (IndexY_ * 28.f) + (IndexY_ * 1.f);;

	Scale_ = float4(28.f, 28.f, 1.f);

	// Ÿ�Ϲڽ� ������ ����
	TileBoxRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	TileBoxRenderer_->SetImage(TextureName);
	TileBoxRenderer_->GetTransform()->SetLocalPosition(Pos_);
	TileBoxRenderer_->GetTransform()->SetLocalScaling(Scale_);
	TileBoxRenderer_->Off();

	// Create Item�� Renderer ����(�⺻ Off) - ������������ �̹����� ���õǸ� On���·� ��ȯ
	TileBoxItemEquipRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Tab));
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxItemEquipRenderer_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxItemEquipRenderer_->Off();

	// Ÿ�Ϲڽ� �浹ü ����
	TileBoxCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	TileBoxCollider_->GetTransform()->SetLocalScaling(TileBoxRenderer_->GetTransform()->GetLocalScaling());
	TileBoxCollider_->GetTransform()->SetLocalPosition(TileBoxRenderer_->GetTransform()->GetLocalPosition());
	TileBoxCollider_->Off();
}

void InventoryTileBox::CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, InvenTileBoxType _BoxTileType, int _Index, float4 _Pos, float4 _Scale)
{
	// Ÿ�Ϲڽ� ���� ����
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

	// Create Item�� Renderer ����(�⺻ Off) - ������������ �̹����� ���õǸ� On���·� ��ȯ
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
