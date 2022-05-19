#include "PreCompile.h"
#include "WizardProjectile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

WizardProjectile::WizardProjectile() :
	Renderer_(nullptr),
	Collider_(nullptr)
{
}

WizardProjectile::~WizardProjectile()
{
}

void WizardProjectile::Start()
{
	// 텍스쳐 컷팅

	



}

void WizardProjectile::Update(float _DeltaTime)
{
	// 충돌체크
	if (nullptr != Collider_)
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&WizardProjectile::TargetCollision, this, std::placeholders::_1));
	}
}

void WizardProjectile::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
}

void WizardProjectile::TargetCollision(GameEngineCollision* _Other)
{
	// 타겟과 충돌시 타겟에게 데미지를 입히며 나는 소멸

}

void WizardProjectile::SkeletonWizardFire()
{
	// 스켈레톤(마법사형) 공격시 객체 생성 및 타겟방향으로 발사

}
