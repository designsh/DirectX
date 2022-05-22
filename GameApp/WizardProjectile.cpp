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
	// �浹üũ
	if (nullptr != Collider_)
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&WizardProjectile::TargetCollision, this, std::placeholders::_1));
	}

	// ����ؼ� �̵�
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 50.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 22.f);
}

void WizardProjectile::TargetCollision(GameEngineCollision* _Other)
{
	// Ÿ�ٰ� �浹�� Ÿ�ٿ��� �������� ������
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

	// ��� ���Ϳ͵� �浹�����ʾ����� �ڵ��Ҹ�ð���(5��) �ʰ��Ǹ� �ڵ��Ҹ��Ѵ�.
}

void WizardProjectile::TargetDirCheckAndAnimationSetting()
{
	// Ÿ����ġ�� ������ �˾Ƴ���
	// ���� ��ġ�� Ÿ����ġ�� ������ ���
	float4 Direct = TargetPos_ - GetTransform()->GetWorldPosition();
	Direct.Normalize3D();

	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // ������
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// ����
			CurDir_ = WizardProjectile_Dir::PJ_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = WizardProjectile_Dir::PJ_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = WizardProjectile_Dir::PJ_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = WizardProjectile_Dir::PJ_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = WizardProjectile_Dir::PJ_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = WizardProjectile_Dir::PJ_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = WizardProjectile_Dir::PJ_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = WizardProjectile_Dir::PJ_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = WizardProjectile_Dir::PJ_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = WizardProjectile_Dir::PJ_B;
		}
	}

	// �̵����⺤�� ����
	float4 DirPos = TargetPos_ - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
	MoveTargetDir_ = DirPos.NormalizeReturn3D();

	// �ִϸ��̼��� ����
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
	// ���̷���(��������) ���ݽ� ��ü ���� �� Ÿ�ٹ������� �߻�
	ProjectileType_ = _ProjectileType;
	StartPos_ = _FireStartPos;
	TargetPos_ = _TargetPos;
	Damage_ = _Damage;

	// �ִϸ��̼� ����
	CreateAnimation();

	// ���� ������ġ���� Ÿ���� ��ġ�� ������ �˾Ƴ��� �̵������� �����ϸ�, �ִϸ��̼��� ����
	TargetDirCheckAndAnimationSetting();

	// �浹ü ����
	CreateCollision();
}
