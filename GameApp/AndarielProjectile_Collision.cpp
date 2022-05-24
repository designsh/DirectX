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
	// Ÿ�ٰ� �浹�� Ÿ�ٿ��� �������� ������
	if (GlobalValue::CurPlayer == _Other->GetActor())
	{
		GlobalValue::CurPlayer->DelCurrentHP(Damage_);
		Death();
	}
}
