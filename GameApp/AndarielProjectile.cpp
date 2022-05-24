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
	AnimationCurDir_(Animation_Dir::AD_B),
	FireStart_(false),
	MoveDir_(float4::ZERO),
	MoveSpeed_(300.f),
	Damage_(0)
{
}

AndarielProjectile::~AndarielProjectile()
{
}

void AndarielProjectile::Start()
{
	// 해당 발사체 초기화
	InitProjectile();
}

void AndarielProjectile::Update(float _DeltaTime)
{
	if (true == FireStart_)
	{
		// 충돌체크
		if (nullptr != Collider_)
		{
#ifdef _DEBUG
			GetLevel()->PushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&AndarielProjectile::TargetCollision, this, std::placeholders::_1));
		}

		// 계속해서 이동
		GetTransform()->SetWorldDeltaTimeMove(MoveDir_ * MoveSpeed_);

		// Z Order 갱신
		TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 5.f);
	}
}

void AndarielProjectile::SkillAttackProjectile(int _DirType, float4 _MoveDir, int _Damage)
{
	// 기본정보 저장
	MoveDir_ = _MoveDir;
	Damage_ = _Damage;
	AnimationCurDir_ = static_cast<Animation_Dir>(_DirType);

	// 이동방향에 따른 애니메이션 결정
	switch (AnimationCurDir_)
	{
	case Animation_Dir::AD_B:
		Renderer_->SetChangeAnimation("Move_B");
		break;
	case Animation_Dir::AD_LB:
		Renderer_->SetChangeAnimation("Move_LB");
		break;
	case Animation_Dir::AD_L:
		Renderer_->SetChangeAnimation("Move_L");
		break;
	case Animation_Dir::AD_LT:
		Renderer_->SetChangeAnimation("Move_LT");
		break;
	case Animation_Dir::AD_T:
		Renderer_->SetChangeAnimation("Move_T");
		break;
	case Animation_Dir::AD_RT:
		Renderer_->SetChangeAnimation("Move_RT");
		break;
	case Animation_Dir::AD_R:
		Renderer_->SetChangeAnimation("Move_R");
		break;
	case Animation_Dir::AD_RB:
		Renderer_->SetChangeAnimation("Move_RB");
		break;
	}

	// 발사 시작
	FireStart_ = true;
}
