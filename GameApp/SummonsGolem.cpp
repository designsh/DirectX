#include "PreCompile.h"
#include "SummonsGolem.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

SummonsGolem::SummonsGolem() :
	GolemRenderer_(nullptr),
	BodyCollider_(nullptr),
	GolemInfo_{},
	GolemType_(GolemType::NONE),
	PrevDir_(GolemTargetDir::GL_B),
	CurDir_(GolemTargetDir::GL_B)
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


	// ������(��ų����) ����
	CreateGolemInfo();

	// �ִϸ��̼� ����
	CreateAnimation();

	// �ִϸ��̼� ������� ȣ���Լ� ����
	CreateAnimationEndFunction();

}

void SummonsGolem::CurGolemDeath()
{
	// ���� ��� ���·� ��ȯ

}
