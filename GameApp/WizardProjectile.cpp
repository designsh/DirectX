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
	// �ؽ��� ����

	



}

void WizardProjectile::Update(float _DeltaTime)
{
	// �浹üũ
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
	// Ÿ�ٰ� �浹�� Ÿ�ٿ��� �������� ������ ���� �Ҹ�

}

void WizardProjectile::SkeletonWizardFire()
{
	// ���̷���(��������) ���ݽ� ��ü ���� �� Ÿ�ٹ������� �߻�

}
