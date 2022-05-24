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
		// 계속해서 이동
		GetTransform()->SetWorldDeltaTimeMove(MoveDir_ * MoveSpeed_);

		TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

		// 이동중 벽과 충돌시 소멸
		if (true == GlobalValue::CatacombsMap->CurTileIndexWallCheck(CurTileIndex))
		{
			Death();
		}

		if (nullptr != Collider_)
		{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			// 충돌체 위치 갱신
			float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
			float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
			Collider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

			// 충돌체크
			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&AndarielProjectile::TargetCollision, this, std::placeholders::_1));
		}
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
