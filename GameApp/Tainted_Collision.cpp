#include "PreCompile.h"
#include "Tainted.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

// 1. ���콺�� �浹�� ȣ��Ǵ� �Լ�
void Tainted::MouseCollision(GameEngineCollision* _Other)
{
	// ȭ���� ��� HP Bar ǥ��
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
	// ȭ�� ��� HP�� ǥ�õǾ��־��ٸ� Off ���·� ��ȯ
	GlobalValue::TopHPBar->CurMonsterTopHPBarOff();
}