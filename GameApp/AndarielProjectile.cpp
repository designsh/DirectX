#include "PreCompile.h"
#include "AndarielProjectile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

AndarielProjectile::AndarielProjectile() :
	Renderer_(nullptr),
	Collider_(nullptr),
	CurDir_(AndarielProjectile_Dir::PJ_L),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	Damage_(0)
{
}

AndarielProjectile::~AndarielProjectile()
{
}

void AndarielProjectile::Start()
{
	// �ش� �߻�ü �ʱ�ȭ
	InitProjectile();
}

void AndarielProjectile::Update(float _DeltaTime)
{
	// �浹üũ
	if (nullptr != Collider_)
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&AndarielProjectile::TargetCollision, this, std::placeholders::_1));
	}

	// ����ؼ� �̵�
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 5.f);
}

void AndarielProjectile::SkillAttackProjectile(AndarielProjectile_Dir _AnimationDir, float4 _MoveDir, int _Damage)
{
	// �⺻���� ����
	CurDir_ = _AnimationDir;
	MoveTargetDir_ = _MoveDir;
	Damage_ = _Damage;

	// 




}
