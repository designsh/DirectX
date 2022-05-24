#include "PreCompile.h"
#include "BoneSpirit.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"
#include "CatacombsMap.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

int BoneSpirit::ProjetileCount = 0;;

BoneSpirit::BoneSpirit() :
	Renderer_(nullptr),
	Collider_(nullptr),
	State_(),
	BonsSpiritInfo_{},
	CurDir_(BoneSpirit_Dir::BS_L),
	StartPos_(float4::ZERO),
	MouseClickPos_(float4::ZERO),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(200.f),
	NavigationIndex_(-1),
	FireStart_(false),
	Targeting_(false),
	Damage_(0),
	TargetMonster_(nullptr)
{
	NavigationIndex_ = ProjetileCount;
	++ProjetileCount;
}

BoneSpirit::~BoneSpirit()
{
}

void BoneSpirit::Start()
{
}

void BoneSpirit::Update(float _DeltaTime)
{
	if (true == FireStart_)
	{
		// ���� ������Ʈ
		State_.Update();

		TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

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

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&BoneSpirit::TargetCollision, this, std::placeholders::_1));
		}
	}
}

void BoneSpirit::TargetCollision(GameEngineCollision* _Other)
{
	// Ÿ�����ϰ�� Ÿ�ٰ��� �浹�ÿ� Ÿ���� ������,
	if (true == Targeting_)
	{
		// Ÿ�ٸ��ͽ� �浹���� ó��
		if (TargetMonster_ == _Other->GetActor())
		{
			// Ÿ�ٰ� �浹�� Ÿ�ٿ��� �������� ������
			std::string CollisionName = _Other->GetActor()->GetName();
			if (std::string::npos != CollisionName.find("Fallen"))
			{
				Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
				if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
					Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
				{
					// ���� ��ȯ
					State_.ChangeState("Explode");

					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("SpikeFiend"))
			{
				SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
				if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
					SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
				{
					// ���� ��ȯ
					State_.ChangeState("Explode");

					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("Tainted"))
			{
				Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
				if (Tainted_FSMState::TT_DEAD != CurAttackMonster->GetCurState() && 
					Tainted_FSMState::TT_DEATH != CurAttackMonster->GetCurState())
				{
					// ���� ��ȯ
					State_.ChangeState("Explode");

					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("Zombie"))
			{
				Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();
				if (Zombie_FSMState::ZB_DEAD != CurAttackMonster->GetCurState() &&
					Zombie_FSMState::ZB_DEATH != CurAttackMonster->GetCurState())
				{
					// ���� ��ȯ
					State_.ChangeState("Explode");

					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("Andariel"))
			{
				Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();
				if (Andariel_FSMState::AD_DEAD != CurAttackMonster->GetCurState() &&
					Andariel_FSMState::AD_DEATH != CurAttackMonster->GetCurState())
				{
					// ���� ��ȯ
					State_.ChangeState("Explode");

					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
		}
	}
	// ��Ÿ�����ϰ�� ��� �����̵� �浹�� �ش� ���Ϳ��� Ÿ���� ������.
	else
	{
		// Ÿ�ٰ� �浹�� Ÿ�ٿ��� �������� ������
		std::string CollisionName = _Other->GetActor()->GetName();
		if (std::string::npos != CollisionName.find("Fallen"))
		{
			Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
			if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
				Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
			{
				// ���� ��ȯ
				State_.ChangeState("Explode");

				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("SpikeFiend"))
		{
			SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
			if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
				SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
			{
				// ���� ��ȯ
				State_.ChangeState("Explode");

				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("Tainted"))
		{
			Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
			if (Tainted_FSMState::TT_DEAD != CurAttackMonster->GetCurState() &&
				Tainted_FSMState::TT_DEATH != CurAttackMonster->GetCurState())
			{
				// ���� ��ȯ
				State_.ChangeState("Explode");

				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("Zombie"))
		{
			Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();
			if (Zombie_FSMState::ZB_DEAD != CurAttackMonster->GetCurState() &&
				Zombie_FSMState::ZB_DEATH != CurAttackMonster->GetCurState())
			{
				// ���� ��ȯ
				State_.ChangeState("Explode");

				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("Andariel"))
		{
			Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();
			if (Andariel_FSMState::AD_DEAD != CurAttackMonster->GetCurState() &&
				Andariel_FSMState::AD_DEATH != CurAttackMonster->GetCurState())
			{
				// ���� ��ȯ
				State_.ChangeState("Explode");

				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
	}
}

void BoneSpirit::BoneSpiritFire(const float4& _StartPos, const float4& _MouseClickPos, GameEngineActor* _TargetingMonster)
{
	// ���콺 Ŭ���������� �߻� �� ������⿡ ���Ϳ� �浹�� Ÿ���� ������ �Ҹ�
	TargetMonster_ = _TargetingMonster;
	
	// ��Ÿ����
	if (nullptr == TargetMonster_)
	{
		Targeting_ = false;
	}
	// Ÿ����
	else
	{
		Targeting_ = true;
	}

	StartPos_ = _StartPos;
	MouseClickPos_ = _MouseClickPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// ������ ���
	MainPlayerInfomation::GetInst().GetSkillInfo(93, BonsSpiritInfo_);
	Damage_ = BonsSpiritInfo_.SkillDamage;
	
	// �׺���̼� ����
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_ProjectileSkill, ProjetileCount);

	// �ִϸ��̼� ����
	CreateAnimation();

	// �浹ü ����
	CreateCollision();

	// FSM ����
	CreateFSMState();

	// ��ġ ����
	GetTransform()->SetWorldPosition(StartPos_);

	// ����
	State_.ChangeState("Move");

	// �߻� ����
	FireStart_ = true;
}
