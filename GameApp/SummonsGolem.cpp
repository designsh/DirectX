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
	SpawnPos_(float4::ZERO),
	TargetPos_(float4::ZERO),
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
	// 골렘 관련 기본 초기화
	InitGolem();
}

void SummonsGolem::Update(float _DeltaTime)
{
	State_.Update();

	// Z Order 갱신
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 55.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 15.f);
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

	// 소환 애니메이션 실행
	ChangeAnimationCheck("Spawn");
}

void SummonsGolem::CurGolemDeath()
{
	// 골렘을 사망 상태로 전환
	State_.ChangeState("Death");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// 소환 애니메이션 종료시 호출

	// 대기상태로 전환
	State_.ChangeState("Idle");
}

void SummonsGolem::AttackAnimationEnd()
{
	// 현재 충돌한 몬스터(적)에게 피해를 입히고
	


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
	// 플레이어의 타일을 원점으로하여 10x10 타일의 이동 제한 범위를 가지며,
	// 이동범위에서 벗어난 위치에 있을대 모든 상태를 중단하고 플레이어주변타일로 워프시키기위한
	// 범위를 셋팅한다.
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// 기존 이동제한범위 클리어
	MaxMoveRange_.clear();
	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{

		}
	}
}

bool SummonsGolem::CheckMoveRange()
{
	// 골렘이 이동 or 공격 상태일때 호출되며,
	// 이동범위를 벗어난 골렘을 플레이어 위치로 워프시키며 대기상태로 전환한다.





}
