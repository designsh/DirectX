#include "PreCompile.h"
#include "Teeth.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

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

Teeth::Teeth() :
	Renderer_(nullptr),
	Collider_(nullptr),
	TeethInfo_{},
	AnimationCurDir_(),
	FireStart_(false),
	MoveDir_(float4::ZERO),
	MoveSpeed_(300.f),
	StateSound_(nullptr)
{
}

Teeth::~Teeth()
{
}

void Teeth::Start()
{
	// 스킬정보 저장
	MainPlayerInfomation::GetInst().GetSkillInfo(67, TeethInfo_);

	// 사운드 플레이어 생성
	StateSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void Teeth::Update(float _DeltaTime)
{
	if (true == FireStart_)
	{
		GetTransform()->SetWorldDeltaTimeMove(MoveDir_ * MoveSpeed_);

		// Z Order 정렬
		if (false == GlobalValue::CurPlayer->GetIsTown())
		{
			TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
			GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
		}

		// 충돌체크
		if (nullptr != Collider_)
		{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			// 충돌체 위치 갱신
			float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
			float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
			Collider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&Teeth::TargetCollision, this, std::placeholders::_1));
		}

		// 벽과 충돌 체크
		WallCollisionCheck();
	}
}

void Teeth::ProjectileAnimationEnd()
{
	// 이동 종료 후 
	FireStart_ = false;

	// 사망처리
	Death();
}

void Teeth::ExplodeAnimationEnd()
{
	Death();
}

void Teeth::WallCollisionCheck()
{
	// 맵의 벽과 충돌시에 해당 발사체는 소멸한다.
	if (true == GlobalValue::CatacombsMap->CurTileIndexWallCheck(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition())))
	{
		Death();
	}
}

void Teeth::CreateAnimation()
{
	// 렌더러생성
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(128.f, 128.f));
	Renderer_->SetAlpha(0.7f);
	Renderer_->SetRenderingPipeLine("TextureTransDepthOff");

	// 발사체 애니메이션 생성
	Renderer_->CreateAnimation("Teeth.png", "Move_LB", 0, 29, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_LT", 30, 59, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_RT", 60, 89, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_RB", 90, 119, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_B" , 120, 149, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_L" , 150, 179, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_T" , 180, 209, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_R" , 210, 239, 0.1f);

	// 발사체 애니메이션 종료시 호출되는 함수 등록
	Renderer_->SetEndCallBack("Move_LB", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_LT", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_RT", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_RB", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_B" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_L" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_T" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_R" , std::bind(&Teeth::ProjectileAnimationEnd, this));

	// 폭발체 애니메이션 생성
	Renderer_->CreateAnimation("Teeth_Explode.png", "Explode", 0, 12, 0.1f);

	// 폭발 애니메이션 종료시 호출되는 함수 등록
	Renderer_->SetEndCallBack("Explode", std::bind(&Teeth::ExplodeAnimationEnd, this));

	// 초기애니메이션 지정
	switch (AnimationCurDir_)
	{
		case Teeth_AniDir::TT_LB:
		{
			Renderer_->SetChangeAnimation("Move_LB");
			break;
		}
		case Teeth_AniDir::TT_LT:
		{
			Renderer_->SetChangeAnimation("Move_LT");
			break;
		}
		case Teeth_AniDir::TT_RT:
		{
			Renderer_->SetChangeAnimation("Move_RT");
			break;
		}
		case Teeth_AniDir::TT_RB:
		{
			Renderer_->SetChangeAnimation("Move_RB");
			break;
		}
		case Teeth_AniDir::TT_B:
		{
			Renderer_->SetChangeAnimation("Move_B");
			break;
		}
		case Teeth_AniDir::TT_L:
		{
			Renderer_->SetChangeAnimation("Move_L");
			break;
		}
		case Teeth_AniDir::TT_T:
		{
			Renderer_->SetChangeAnimation("Move_T");
			break;
		}
		case Teeth_AniDir::TT_R:
		{
			Renderer_->SetChangeAnimation("Move_R");
			break;
		}
	}
}

void Teeth::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}

void Teeth::TeethFire(int _DirType, float4 _MoveDir)
{
	// 기본정보 저장
	AnimationCurDir_ = static_cast<Teeth_AniDir>(_DirType);
	MoveDir_ = _MoveDir;

	// 이동방향 및 애니메이션 셋팅
	CreateAnimation();

	// 충돌체 생성
	CreateCollision();

	// 발사 시작
	FireStart_ = true;
}
