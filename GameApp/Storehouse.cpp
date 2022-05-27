#include "PreCompile.h"
#include "Storehouse.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"
#include "MouseObject.h"
#include "MainPlayer.h"

#include "StoreView.h"

Storehouse::Storehouse() :
	DistanceCheck_(false),
	StorehouseRenderer_(nullptr),
	StorehouseCollision_(nullptr),
	StoreView_(nullptr)
{
}

Storehouse::~Storehouse()
{
}

void Storehouse::Start()
{
	StorehouseRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	StorehouseRenderer_->SetRenderingPipeLine("TextureDepthOff");
	StorehouseRenderer_->SetImage("Storehouse.png");

	StorehouseCollision_ = CreateTransformComponent<GameEngineCollision>();
	StorehouseCollision_->GetTransform()->SetLocalScaling(StorehouseRenderer_->GetTransform()->GetLocalScaling());
	StorehouseCollision_->GetTransform()->SetLocalPosition(StorehouseRenderer_->GetTransform()->GetLocalPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
	StorehouseCollision_->GetTransform()->SetWorldZOrder(-99.f);
	
	// â��â ����
	StoreView_ = GetLevel()->CreateActor<StoreView>();
}

void Storehouse::Update(float _DeltaTime)
{
	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	StorehouseCollision_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	float4 CurPos = GetTransform()->GetWorldPosition();
	TileIndex CurTileIndex = GlobalValue::TownMap->GetPosToTileIndex(float4(CurPos.x, CurPos.y));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(StorehouseCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// �÷��̾���� �Ÿ�üũ
	if (true == DistanceCheck_)
	{
		// �÷��̾���� �Ÿ�üũ
		DistanceCheck();
		return;
	}

	StorehouseCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Storehouse::MouseLButtonClick, this, std::placeholders::_1));
}

void Storehouse::MouseLButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		if (false == DistanceCheck_)
		{
			DistanceCheck_ = true;
		}
	}
}

void Storehouse::DistanceCheck()
{
	// �ش� ������Ʈ�� �ֺ� Ÿ�ϵ��� �˻��Ͽ� �÷��̾ �����Ѵٸ�
	// â��â Ȱ��ȭ

	// �����ڸ��� ������ 8���� �̿�Ÿ�ϵ��� �˻�
	TileIndex SearchTile[9] = { {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

	TileIndex PlayerTile = GlobalValue::TownMap->GetPosToTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	TileIndex MyTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
	for (int i = 0; i < 9; ++i)
	{
		// ���� NPC�� Ÿ�Ͽ��� �̿����(8����) �˻��Ͽ� �÷��̾ ã�Ƴ���.
		TileIndex FindTile = MyTile + SearchTile[i];

		// �÷��̾ ã�Ƴ´ٸ� ��ȣ�ۿ� �������� â��â Ȱ��ȭ �� �Ÿ�üũ ����
		if (PlayerTile == FindTile)
		{
			// â��â Ȱ��ȭ
			StoreView_->StoreViewOn();

			// �Ÿ�üũ Flag ����
			DistanceCheck_ = false;
		}
	}
}
