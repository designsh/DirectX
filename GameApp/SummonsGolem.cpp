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
	// ���� ����
	GolemType_ = _GolemType;
	SpawnPos_ = _SpawnPos;

	// ���� �̵����� ����
	// => �÷��̾� �ֺ� 10x10 Ÿ���� ������ ������
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

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
}

void SummonsGolem::CurGolemDeath()
{
	// ���� ��� ���·� ��ȯ
	State_.ChangeState("DEATH_STATE");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// ��ȯ �ִϸ��̼� ����� ȣ��
	State_.ChangeState("IDLE_STATE");
}

void SummonsGolem::AttackAnimationEnd()
{
	// ���� �ִϸ��̼� ����� ȣ��
	State_.ChangeState("IDLE_STATE");
}

void SummonsGolem::DeathAnimationEnd()
{
	// ��� �ִϸ��̼� ����� ȣ��
	Death();
}
