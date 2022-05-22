#include "PreCompile.h"
#include "WizardProjectile.h"

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

WizardProjectile::WizardProjectile() :
	Renderer_(nullptr),
	Collider_(nullptr),
	ProjectileType_(SkeletonWizardType::NONE),
	StartPos_(float4::ZERO),
	TargetPos_(float4::ZERO),
	CurDir_(WizardProjectile_Dir::PJ_L),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	Damage_(0)
{
}

WizardProjectile::~WizardProjectile()
{
}

void WizardProjectile::Start()
{
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

	// 계속해서 이동
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// Z Order 갱신
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 50.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 22.f);
}

void WizardProjectile::TargetCollision(GameEngineCollision* _Other)
{
	// 타겟과 충돌시 타겟에게 데미지를 입히며
	std::string CollisionName = _Other->GetActor()->GetName();
	if (std::string::npos != CollisionName.find("Fallen"))
	{
		Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();

		Death();
	}
	else if (std::string::npos != CollisionName.find("SpikeFiend"))
	{
		SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();

		Death();
	}
	else if (std::string::npos != CollisionName.find("Tainted"))
	{
		Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
		CurAttackMonster->GetHitDamage(Damage_);
		Death();
	}
	else if (std::string::npos != CollisionName.find("Zombie"))
	{
		Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();

		Death();
	}
	else if (std::string::npos != CollisionName.find("Andariel"))
	{
		Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();

		Death();
	}

	// 어떠한 몬스터와도 충돌하지않았을시 자동소멸시간이(5초) 초과되면 자동소멸한다.
}

void WizardProjectile::TargetDirCheckAndAnimationSetting()
{
	// 타겟위치의 방향을 알아내고
	// 현재 위치와 타겟위치의 각도를 계산
	float4 Direct = TargetPos_ - GetTransform()->GetWorldPosition();
	Direct.Normalize3D();

	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // 오른쪽
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// 우상단
			CurDir_ = WizardProjectile_Dir::PJ_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = WizardProjectile_Dir::PJ_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = WizardProjectile_Dir::PJ_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = WizardProjectile_Dir::PJ_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = WizardProjectile_Dir::PJ_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = WizardProjectile_Dir::PJ_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = WizardProjectile_Dir::PJ_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = WizardProjectile_Dir::PJ_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = WizardProjectile_Dir::PJ_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = WizardProjectile_Dir::PJ_B;
		}
	}

	// 이동방향벡터 셋팅
	float4 DirPos = TargetPos_ - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
	MoveTargetDir_ = DirPos.NormalizeReturn3D();

	// 애니메이션을 변경
	ChangeAnimationCheck();
}

void WizardProjectile::ChangeAnimationCheck()
{
	std::string AnimationName = "Move";

	switch (CurDir_)
	{
		case WizardProjectile_Dir::PJ_LB:
		{
			AnimationName += "_LB";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_LT:
		{
			AnimationName += "_LT";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_RT:
		{
			AnimationName += "_RT";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_RB:
		{
			AnimationName += "_RB";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_B:
		{
			AnimationName += "_B";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_L:
		{
			AnimationName += "_L";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_T:
		{
			AnimationName += "_T";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case WizardProjectile_Dir::PJ_R:
		{
			AnimationName += "_R";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

void WizardProjectile::SkeletonWizardFire(SkeletonWizardType _ProjectileType, const float4& _FireStartPos, const float4& _TargetPos, int _Damage)
{
	// 스켈레톤(마법사형) 공격시 객체 생성 및 타겟방향으로 발사
	ProjectileType_ = _ProjectileType;
	StartPos_ = _FireStartPos;
	TargetPos_ = _TargetPos;
	Damage_ = _Damage;

	// 애니메이션 생성
	CreateAnimation();

	// 현재 생성위치에서 타겟이 위치한 방향을 알아내어 이동방향을 셋팅하며, 애니메이션을 셋팅
	TargetDirCheckAndAnimationSetting();

	// 충돌체 생성
	CreateCollision();
}
