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
	// ��ų���� ����
	MainPlayerInfomation::GetInst().GetSkillInfo(67, TeethInfo_);

	// ���� �÷��̾� ����
	StateSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void Teeth::Update(float _DeltaTime)
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
			float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
			float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
			Collider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&Teeth::TargetCollision, this, std::placeholders::_1));
		}

		// ���� �浹 üũ
		WallCollisionCheck();
	}
}

void Teeth::ProjectileAnimationEnd()
{
	// �̵� ���� �� 
	FireStart_ = false;

	// ���ó��
	Death();
}

void Teeth::ExplodeAnimationEnd()
{
	Death();
}

void Teeth::WallCollisionCheck()
{
	// ���� ���� �浹�ÿ� �ش� �߻�ü�� �Ҹ��Ѵ�.
	if (true == GlobalValue::CatacombsMap->CurTileIndexWallCheck(GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition())))
	{
		Death();
	}
}

void Teeth::CreateAnimation()
{
	// ����������
	Renderer_ = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer_->GetTransform()->SetLocalScaling(float4(128.f, 128.f));
	Renderer_->SetAlpha(0.7f);
	Renderer_->SetRenderingPipeLine("TextureTransDepthOff");

	// �߻�ü �ִϸ��̼� ����
	Renderer_->CreateAnimation("Teeth.png", "Move_LB", 0, 29, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_LT", 30, 59, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_RT", 60, 89, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_RB", 90, 119, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_B" , 120, 149, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_L" , 150, 179, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_T" , 180, 209, 0.1f);
	Renderer_->CreateAnimation("Teeth.png", "Move_R" , 210, 239, 0.1f);

	// �߻�ü �ִϸ��̼� ����� ȣ��Ǵ� �Լ� ���
	Renderer_->SetEndCallBack("Move_LB", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_LT", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_RT", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_RB", std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_B" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_L" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_T" , std::bind(&Teeth::ProjectileAnimationEnd, this));
	Renderer_->SetEndCallBack("Move_R" , std::bind(&Teeth::ProjectileAnimationEnd, this));

	// ����ü �ִϸ��̼� ����
	Renderer_->CreateAnimation("Teeth_Explode.png", "Explode", 0, 12, 0.1f);

	// ���� �ִϸ��̼� ����� ȣ��Ǵ� �Լ� ���
	Renderer_->SetEndCallBack("Explode", std::bind(&Teeth::ExplodeAnimationEnd, this));

	// �ʱ�ִϸ��̼� ����
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
	// �⺻���� ����
	AnimationCurDir_ = static_cast<Teeth_AniDir>(_DirType);
	MoveDir_ = _MoveDir;

	// �̵����� �� �ִϸ��̼� ����
	CreateAnimation();

	// �浹ü ����
	CreateCollision();

	// �߻� ����
	FireStart_ = true;
}
