#include "PreCompile.h"
#include "SpikeFiend.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

void SpikeFiend::MouseCollision(GameEngineCollision* _Ohter)
{
	// ȭ���� ��� HP Bar ǥ��
	if (CurState_ == SpikeFiend_FSMState::SF_DEAD)
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_, float4(0.8f, 0.2f, 0.2f));
	}
	else
	{
		GlobalValue::TopHPBar->SetCurMonster(MonsterInfo_.Name, MapHP_, CurHP_);
	}
}

void SpikeFiend::EnemyCollision(GameEngineCollision* _Other)
{
	// �÷��̾�� �浹���̶�� �÷��̾�� ���ظ� ����
	if (_Other->GetActor() == GlobalValue::CurPlayer && false == Attack_)
	{
		GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
		Attack_ = true;
	}
}
