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
	// �� ���� �⺻ �ʱ�ȭ
	InitGolem();
}

void SummonsGolem::Update(float _DeltaTime)
{
	State_.Update();

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 55.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 15.f);
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
	State_.ChangeState("Death");
}

void SummonsGolem::SpawnAnimationEnd()
{
	// ��ȯ �ִϸ��̼� ����� ȣ��
	//State_.ChangeState("Idle");
}

void SummonsGolem::AttackAnimationEnd()
{
	// ���� �ִϸ��̼� ����� ȣ��
	State_.ChangeState("Idle");
}

void SummonsGolem::DeathAnimationEnd()
{
	// ��� �ִϸ��̼� ����� ȣ��
	Death();
}