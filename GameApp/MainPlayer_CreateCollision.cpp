#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

void MainPlayer::CreateCollision()
{
	BodyCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Player));
	BodyCollider_->GetTransform()->SetLocalScaling(float4(60.f, 90.f));
	BodyCollider_->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	BodyCollider_->GetTransform()->SetWorldZOrder(-99.f);
}

void MainPlayer::PlayerBodyCollision(GameEngineCollision* _Other)
{
	// 몬스터의 공격모션에 몸체가 충돌하면 피격판정!!!!


	int a = 0;
}
