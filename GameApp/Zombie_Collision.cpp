#include "PreCompile.h"
#include "Zombie.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

void Zombie::MouseCollision(GameEngineCollision* _Ohter)
{
	// ȭ���� ��� HP Bar ǥ��
	if (CurState_ == Zombie_FSMState::ZB_DEAD)
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_, float4(0.8f, 0.2f, 0.2f));
	}
	else
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_);
	}
}

void Zombie::EnemyCollision(GameEngineCollision* _Other)
{
	// �÷��̾�� �浹���̶�� �÷��̾�� ���ظ� ����
	if (_Other->GetActor() == GlobalValue::CurPlayer && false == Attack_)
	{
		GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
		Attack_ = true;
	}
}
