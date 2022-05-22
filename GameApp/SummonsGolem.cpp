#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"
#include "CatacombsMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

SummonsGolem::SummonsGolem() :
	GolemRenderer_(nullptr),
	BodyCollider_(nullptr),
	State_(),
	GolemInfo_{},
	GolemType_(GolemType::NONE),
	SpawnPos_(float4::ZERO),
	MoveSpeed_(100.f),
	TargetPos_(float4::ZERO),
	PrevDir_(GolemTargetDir::GL_B),
	CurDir_(GolemTargetDir::GL_B),
	PrevState_(GolemState::SPAWN),
	CurState_(GolemState::SPAWN),
	CheckTime_(1.5f),
	DetectMonster_(nullptr)
{
}

SummonsGolem::~SummonsGolem()
{
}

void SummonsGolem::Start()
{
}

void SummonsGolem::Update(float _DeltaTime)
{
	State_.Update();

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 10.f);
}

void SummonsGolem::SpawnGolem(GolemType _GolemType, const float4& _SpawnPos)
{
	// ���� ����
	GolemType_ = _GolemType;
	SpawnPos_ = _SpawnPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// ���� �̵����� ����
	// => �÷��̾� �ֺ� 10x10 Ÿ���� ������ ������
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		SetMoveRange();
	}

	// ���� �� Ÿ�Ժ� ����
	switch (GolemType_)
	{
		case GolemType::CLAY:
		{
			CreateClayGolem();
			break;
		}
		case GolemType::BLOOD:
		{
			CreateBloodGolem();
			break;
		}
		case GolemType::IRON:
		{
			CreateIronGolem();
			break;
		}
		case GolemType::FIRE:
		{
			CreateFireGolem();
			break;
		}
	}

#pragma region �ִϸ��̼�������� ȣ���Լ� ����
	// ��ȯ����
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R", std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// ���ݻ���
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R", std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// �������
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R", std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM ����
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Warp", std::bind(&SummonsGolem::UpdateWarpState, this), std::bind(&SummonsGolem::StartWarpState, this), std::bind(&SummonsGolem::EndWarpState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion

	// ��ȯ �ִϸ��̼� ����
	ChangeAnimationCheck("Spawn");

	// �ش� ���� �׺���̼� ����
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_Golem, 0);
}

void SummonsGolem::CurGolemDeath()
{
	// ���� ��� ���·� ��ȯ
	State_.ChangeState("Death");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// �����·� ��ȯ
	State_.ChangeState("Idle");
}

void SummonsGolem::AttackAnimationEnd()
{
	// ���� �浹�� ����(��)���� ���ظ� ������
	if (nullptr != DetectMonster_)
	{
		std::string DetectActor = DetectMonster_->GetName();
		if (std::string::npos != DetectActor.find("Fallen"))
		{
			Fallen* CurAttackMonster = (Fallen*)DetectMonster_;

		}
		else if (std::string::npos != DetectActor.find("SpikeFiend"))
		{
			SpikeFiend* CurAttackMonster = (SpikeFiend*)DetectMonster_;

		}
		else if (std::string::npos != DetectActor.find("Tainted"))
		{
			Tainted* CurAttackMonster = (Tainted*)DetectMonster_;
			if (Tainted_FSMState::ST_DEAD != CurAttackMonster->GetCurState() &&
				Tainted_FSMState::ST_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->GetHitDamage(GolemInfo_.SkillDamage);
			}
		}
		else if (std::string::npos != DetectActor.find("Zombie"))
		{
			Zombie* CurAttackMonster = (Zombie*)DetectMonster_;

		}
		else if (std::string::npos != DetectActor.find("Andariel"))
		{
			Andariel* CurAttackMonster = (Andariel*)DetectMonster_;

		}

		DetectMonster_ = nullptr;
	}

	// �����·� ��ȯ
	State_.ChangeState("Idle");
}

void SummonsGolem::DeathAnimationEnd()
{
	// ������ ����� �ش� ���͸� ���������� ���ó��(����)
	Death();
}

void SummonsGolem::SetMoveRange()
{
	// �÷��̾ ���� ��ġ�� Ÿ�� �������� ���� ��ȯ�� ���� �̵������� �����Ѵ�.
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// ���� �̵����ѹ��� Ŭ���� ��
	MaxMoveRange_.clear();

	// �ű� �̵����ѹ��� ����
	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{
			MaxMoveRange_.push_back(PlayerTile + TileIndex(x, y));
		}
	}
}

bool SummonsGolem::CheckWarpStart()
{
	// �̵������� ��� ���� �÷��̾� ��ġ�� ������Ű�� �����·� ��ȯ�Ѵ�.
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

	for (auto& MoveabledTile : MaxMoveRange_)
	{
		if (CurTileIndex == MoveabledTile)
		{
			return false;
		}
	}

	return true;
}
