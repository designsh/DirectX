#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

void Andariel::MouseCollision(GameEngineCollision* _Ohter)
{
	// 화면의 상단 HP Bar 표시
	if (CurState_ == Andariel_FSMState::AD_DEAD)
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_, float4(0.8f, 0.2f, 0.2f));
	}
	else
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_);
	}
}

void Andariel::EnemyCollision(GameEngineCollision* _Other)
{
	// 플레이어와 충돌중이라면 플레이어에게 피해를 입힘
	if (_Other->GetActor() == GlobalValue::CurPlayer)
	{
		if (CurState_ == Andariel_FSMState::AD_ATTACK && false == Attack_)
		{
			GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
			Attack_ = true;
		}
	}
}
