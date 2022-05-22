#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

// 1. 마우스와 충돌시 호출되는 함수
void Tainted::MouseCollision(GameEngineCollision* _Other)
{
	// 화면의 상단 HP Bar 표시
	if (CurState_ == Tainted_FSMState::ST_DEAD)
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_, float4(0.8f, 0.2f, 0.2f));
	}
	else
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_);
	}
}

// 2. 적과 총돌시 호출되는 함수
void Tainted::EnemyCollision(GameEngineCollision* _Other)
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		if (_Other->GetActor() == GlobalValue::CurPlayer)
		{
			// 공격 모션 전환
			if (false == TargetCol_)
			{
				State_.ChangeState("Tainted_ATTACK");
				TargetCol_ = true;
			}
		}
	}
}

void Tainted::EnemyCollisionEnd(GameEngineCollision* _Other)
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		if (_Other->GetActor() == GlobalValue::CurPlayer)
		{
			TargetCol_ = false;
		}
	}
}
