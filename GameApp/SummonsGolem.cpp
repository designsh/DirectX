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

	// Z Order 갱신
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 10.f);
}

void SummonsGolem::SpawnGolem(GolemType _GolemType, const float4& _SpawnPos)
{
	// 정보 저장
	GolemType_ = _GolemType;
	SpawnPos_ = _SpawnPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// 최초 이동범위 셋팅
	// => 플레이어 주변 10x10 타일의 범위를 가진다
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		SetMoveRange();
	}

	// 현재 골렘 타입별 생성
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

#pragma region 애니메이션종료시점 호출함수 셋팅
	// 소환상태
	GolemRenderer_->SetEndCallBack("Spawn_LB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_LT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RT", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_RB", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_B", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_L", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_T", std::bind(&SummonsGolem::SpawnAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Spawn_R", std::bind(&SummonsGolem::SpawnAnimationEnd, this));

	// 공격상태
	GolemRenderer_->SetEndCallBack("Attack_LB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_LT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RT", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_RB", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_B", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_L", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_T", std::bind(&SummonsGolem::AttackAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Attack_R", std::bind(&SummonsGolem::AttackAnimationEnd, this));

	// 사망상태
	GolemRenderer_->SetEndCallBack("Death_LB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_LT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RT", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_RB", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_B", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_L", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_T", std::bind(&SummonsGolem::DeathAnimationEnd, this));
	GolemRenderer_->SetEndCallBack("Death_R", std::bind(&SummonsGolem::DeathAnimationEnd, this));
#pragma endregion

#pragma region FSM 생성
	State_.CreateState("Spawn", std::bind(&SummonsGolem::UpdateSpawnState, this), std::bind(&SummonsGolem::StartSpawnState, this), std::bind(&SummonsGolem::EndSpawnState, this));
	State_.CreateState("Idle", std::bind(&SummonsGolem::UpdateIdleState, this), std::bind(&SummonsGolem::StartIdleState, this), std::bind(&SummonsGolem::EndIdleState, this));
	State_.CreateState("Walk", std::bind(&SummonsGolem::UpdateWalkState, this), std::bind(&SummonsGolem::StartWalkState, this), std::bind(&SummonsGolem::EndWalkState, this));
	State_.CreateState("Warp", std::bind(&SummonsGolem::UpdateWarpState, this), std::bind(&SummonsGolem::StartWarpState, this), std::bind(&SummonsGolem::EndWarpState, this));
	State_.CreateState("Attack", std::bind(&SummonsGolem::UpdateAttackState, this), std::bind(&SummonsGolem::StartAttackState, this), std::bind(&SummonsGolem::EndAttackState, this));
	State_.CreateState("Death", std::bind(&SummonsGolem::UpdateDeathState, this), std::bind(&SummonsGolem::StartDeathState, this), std::bind(&SummonsGolem::EndDeathState, this));
	State_.ChangeState("Spawn");
#pragma endregion

	// 소환 애니메이션 실행
	ChangeAnimationCheck("Spawn");

	// 해당 골렘의 네비게이션 생성
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_Golem, 0);
}

void SummonsGolem::CurGolemDeath()
{
	// 골렘을 사망 상태로 전환
	State_.ChangeState("Death");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// 대기상태로 전환
	State_.ChangeState("Idle");
}

void SummonsGolem::AttackAnimationEnd()
{
	// 현재 충돌한 몬스터(적)에게 피해를 입히고
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

	// 대기상태로 전환
	State_.ChangeState("Idle");
}

void SummonsGolem::DeathAnimationEnd()
{
	// 사망모션 종료시 해당 액터를 실질적으로 사망처리(제거)
	Death();
}

void SummonsGolem::SetMoveRange()
{
	// 플레이어가 현재 위치한 타일 기준으로 현재 소환된 골렘의 이동범위를 설정한다.
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// 기존 이동제한범위 클리어 후
	MaxMoveRange_.clear();

	// 신규 이동제한범위 생성
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
	// 이동범위를 벗어난 골렘을 플레이어 위치로 워프시키며 대기상태로 전환한다.
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
