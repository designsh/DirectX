#include "PreCompile.h"
#include "Tainted.h"

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

void Tainted::MouseCollisionEnd(GameEngineCollision* _Other)
{
	// 화면 상단 HP가 표시되어있었다면 Off 상태로 전환
	GlobalValue::TopHPBar->CurMonsterTopHPBarOff();
}