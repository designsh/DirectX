#include "PreCompile.h"
#include "Storehouse.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

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
	StorehouseRenderer_->SetImage("Storehouse.png");
	StorehouseRenderer_->GetTransform()->SetLocalZOrder(11.f);

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
	// 기존의 거리보다 멀어졌다면 Flag 해제???


}
