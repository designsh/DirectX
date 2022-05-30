#include "PreCompile.h"
#include "PoisonNova.h"

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

PoisonNova::PoisonNova() :
	Renderer_(nullptr),
	Collider_(nullptr),
	PoisonNovaInfo_{},
	AnimationCurDir_(),
	FireStart_(false),
	MoveDir_(float4::ZERO),
	MoveSpeed_(300.f)
{
}

PoisonNova::~PoisonNova()
{
}

void PoisonNova::Start()
{
	// ��ų���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(92, PoisonNovaInfo_);
}

void PoisonNova::Update(float _DeltaTime)
{
	if (true == FireStart_)
	{
		GetTransform()->SetWorldDeltaTimeMove(MoveDir_ * MoveSpeed_);

		// Z Order ����
		if (false == GlobalValue::CurPlayer->GetIsTown())
		{
			TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
			GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
		}

		// �浹üũ
		if (nullptr != Collider_)
		{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			// �浹ü ��ġ ����
			float4 MyPos = GetTransform()->GetLocalPosition();
			float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
			MyPos.z = 0.f;
			CamPos.z = 0.f;
			Collider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&PoisonNova::TargetCollision, this, std::placeholders::_1));
		}

		// ���� �浹 üũ
		WallCollisionCheck();
	}
}

void PoisonNova::WallCollisionCheck()
{
	// ���� ���� �浹�ÿ� �ش� �߻�ü�� �Ҹ��Ѵ�.
	if (true == GlobalValue::CatacombsMap->CurTileIndexWallCheck(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition())))
	{
		Death();
	}
}

void PoisonNova::CreateAnimation()
{
	// 
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	Renderer_->SetAlpha(0.7f);
	Renderer_->SetRenderingPipeLine("TextureTransDepthOff");

	// �ִϸ��̼� ����
	Renderer_->CreateAnimation("PoisonNova.png", "Move_LB",   0,  29, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_LT",  30,  59, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_RT",  60,  89, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_RB",  90, 119, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_B" , 120, 149, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_L" , 150, 179, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_T" , 180, 209, 0.1f);
	Renderer_->CreateAnimation("PoisonNova.png", "Move_R" , 210, 239, 0.1f);

	// �ʱ�ִϸ��̼� ����
	switch (AnimationCurDir_)
	{
		case PoisonNova_AniDir::PN_LB:
		{
			Renderer_->SetChangeAnimation("Move_LB");
			break;
		}
		case PoisonNova_AniDir::PN_LT:
		{
			Renderer_->SetChangeAnimation("Move_LT");
			break;
		}
		case PoisonNova_AniDir::PN_RT:
		{
			Renderer_->SetChangeAnimation("Move_RT");
			break;
		}
		case PoisonNova_AniDir::PN_RB:
		{
			Renderer_->SetChangeAnimation("Move_RB");
			break;
		}
		case PoisonNova_AniDir::PN_B:
		{
			Renderer_->SetChangeAnimation("Move_B");
			break;
		}
		case PoisonNova_AniDir::PN_L:
		{
			Renderer_->SetChangeAnimation("Move_L");
			break;
		}
		case PoisonNova_AniDir::PN_T:
		{
			Renderer_->SetChangeAnimation("Move_T");
			break;
		}
		case PoisonNova_AniDir::PN_R:
		{
			Renderer_->SetChangeAnimation("Move_R");
			break;
		}
	}
}

void PoisonNova::CreateCollision()
{
	Collider_ = CreateTransformComponent<GameEngineCollision>();
	Collider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f));
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	Collider_->GetTransform()->SetLocalPosition(Renderer_->GetTransform()->GetLocalPosition() - CamPos);
	Collider_->GetTransform()->SetWorldZOrder(-99.f);
}

void PoisonNova::PoisonNoveFire(int _DirType, float4 _MoveDir)
{
	// �⺻���� ����
	AnimationCurDir_ = static_cast<PoisonNova_AniDir>(_DirType);
	MoveDir_ = _MoveDir;

	// �̵����� �� �ִϸ��̼� ����
	CreateAnimation();

	// �浹ü ����
	CreateCollision();

	// �߻� ����
	FireStart_ = true;
}
