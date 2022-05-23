#include "PreCompile.h"
#include "Fallen.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

void Fallen::MouseCollision(GameEngineCollision* _Ohter)
{
	// 화면의 상단 HP Bar 표시
	if (CurState_ == Fallen_FSMState::FL_DEAD)
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_, float4(0.8f, 0.2f, 0.2f));
	}
	else
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_);
	}
}

void Fallen::EnemyCollision(GameEngineCollision* _Other)
{
	// 플레이어와 충돌중이라면 플레이어에게 피해를 입힘
	if (_Other->GetActor() == GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
	}
}

void Fallen::EnemyCollisionEnd(GameEngineCollision* _Other)
{

}
