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

SummonsGolem::SummonsGolem() :
	GolemRenderer_(nullptr),
	BodyCollider_(nullptr),
	State_(),
	GolemInfo_{},
	GolemType_(GolemType::NONE),
	PrevDir_(GolemTargetDir::GL_B),
	CurDir_(GolemTargetDir::GL_B),
	PrevState_(GolemState::SPAWN),
	CurState_(GolemState::SPAWN)
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
}

void SummonsGolem::SpawnGolem(GolemType _GolemType, const float4& _SpawnPos)
{
	// 정보 저장
	GolemType_ = _GolemType;
	SpawnPos_ = _SpawnPos;

	// 최초 이동범위 셋팅
	// => 플레이어 주변 10x10 타일의 범위를 가진다
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

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
}

void SummonsGolem::CurGolemDeath()
{
	// 골렘을 사망 상태로 전환
	State_.ChangeState("DEATH_STATE");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// 소환 애니메이션 종료시 호출
	State_.ChangeState("IDLE_STATE");
}

void SummonsGolem::AttackAnimationEnd()
{
	// 공격 애니메이션 종료시 호출
	State_.ChangeState("IDLE_STATE");
}

void SummonsGolem::DeathAnimationEnd()
{
	// 사망 애니메이션 종료시 호출
	Death();
}
