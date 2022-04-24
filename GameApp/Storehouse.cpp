#include "PreCompile.h"
#include "Storehouse.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MouseObject.h"
#include "MainPlayer.h"

Storehouse::Storehouse() :
	DistanceCheck_(false),
	StorehouseRenderer_(nullptr),
	StorehouseCollision_(nullptr)
{
}

Storehouse::~Storehouse()
{
}

void Storehouse::Start()
{
	StorehouseRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	StorehouseRenderer_->SetImage("Storehouse.png");

	StorehouseCollision_ = CreateTransformComponent<GameEngineCollision>();
	StorehouseCollision_->GetTransform()->SetLocalScaling(StorehouseRenderer_->GetTransform()->GetLocalScaling());
	StorehouseCollision_->GetTransform()->SetWorldZOrder(-99.f);
}

void Storehouse::Update(float _DeltaTime)
{
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
