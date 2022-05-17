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
	// 정보 저장
	GolemType_ = _GolemType;
	SpawnPos_ = _SpawnPos;

	// 최초 이동범위 셋팅
	// => 플레이어 주변 10x10 타일의 범위를 가진다


	// 골렘정보(스킬정보) 저장
	CreateGolemInfo();

	// 애니메이션 생성
	CreateAnimation();

	// 애니메이션 종료시점 호출함수 셋팅
	CreateAnimationEndFunction();

}

void SummonsGolem::CurGolemDeath()
{
	// 골렘을 사망 상태로 전환

}
