#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineCollision.h>

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

// 2. ���� �ѵ��� ȣ��Ǵ� �Լ�
void Tainted::EnemyCollision(GameEngineCollision* _Other)
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		if (_Other->GetActor() == GlobalValue::CurPlayer)
		{
			// ���� ��� ��ȯ
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
