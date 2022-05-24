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
	if (GlobalValue::CurPlayer == _Other->GetActor())
	{
		GlobalValue::CurPlayer->DelCurrentHP(Damage_);
		Death();
	}
}
