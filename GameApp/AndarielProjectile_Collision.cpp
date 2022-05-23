#include "PreCompile.h"
#include "AndarielProjectile.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

void AndarielProjectile::TargetCollision(GameEngineCollision* _Other)
{
	// 타겟과 충돌시 타겟에게 데미지를 입히며
	std::string CollisionName = _Other->GetActor()->GetName();
	if (std::string::npos != CollisionName.find("Fallen"))
	{
		Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
		if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
			Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
		{
			CurAttackMonster->GetHitDamage(Damage_);
		}
		Death();
	}
	else if (std::string::npos != CollisionName.find("SpikeFiend"))
	{
		SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
		if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
			SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
		{
			CurAttackMonster->GetHitDamage(Damage_);
		}
		Death();
	}
	else if (std::string::npos != CollisionName.find("Tainted"))
	{
		Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
		if (Tainted_FSMState::ST_DEAD != CurAttackMonster->GetCurState() &&
			Tainted_FSMState::ST_DEATH != CurAttackMonster->GetCurState())
		{
			CurAttackMonster->GetHitDamage(Damage_);
		}
		Death();
	}
	else if (std::string::npos != CollisionName.find("Zombie"))
	{
		Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();
		if (Zombie_FSMState::ZB_DEAD != CurAttackMonster->GetCurState() &&
			Zombie_FSMState::ZB_DEATH != CurAttackMonster->GetCurState())
		{
			CurAttackMonster->GetHitDamage(Damage_);
		}
		Death();
	}
	else if (std::string::npos != CollisionName.find("Andariel"))
	{
		Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();
		if (Andariel_FSMState::AD_DEAD != CurAttackMonster->GetCurState() &&
			Andariel_FSMState::AD_DEATH != CurAttackMonster->GetCurState())
		{
			CurAttackMonster->GetHitDamage(Damage_);
		}
		Death();
	}
}
