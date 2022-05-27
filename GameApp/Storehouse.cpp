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
	
	// 창고창 생성
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

	// 플레이어와의 거리체크
	if (true == DistanceCheck_)
	{
		// 플레이어와의 거리체크
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
	// 해당 오브젝트의 주변 타일들을 검사하여 플레이어가 존재한다면
	// 창고창 활성화

	// 본인자리를 포함한 8방향 이웃타일들을 검사
	TileIndex SearchTile[9] = { {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

	TileIndex PlayerTile = GlobalValue::TownMap->GetPosToTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	TileIndex MyTile = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
	for (int i = 0; i < 9; ++i)
	{
		// 현재 NPC의 타일에서 이웃노드(8방향) 검사하여 플레이어를 찾아낸다.
		TileIndex FindTile = MyTile + SearchTile[i];

		// 플레이어를 찾아냈다면 상호작용 성공으로 창고창 활성화 및 거리체크 해제
		if (PlayerTile == FindTile)
		{
			// 창고창 활성화
			StoreView_->StoreViewOn();

			// 거리체크 Flag 해제
			DistanceCheck_ = false;
		}
	}
}
