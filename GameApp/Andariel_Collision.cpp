#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MonsterTopHPBar.h"

void Andariel::MouseCollision(GameEngineCollision* _Ohter)
{
	// ȭ���� ��� HP Bar ǥ��
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
	// �÷��̾�� �浹���̶�� �÷��̾�� ���ظ� ����
	if (_Other->GetActor() == GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->DelCurrentHP(MonsterInfo_.Damage);
	}
}

void Andariel::EnemyCollisionEnd(GameEngineCollision* _Other)
{

}
