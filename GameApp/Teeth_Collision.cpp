#include "PreCompile.h"
#include "Teeth.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

void Teeth::TargetCollision(GameEngineCollision* _Other)
{
	std::string CollisionName = _Other->GetActor()->GetName();
	if (std::string::npos != CollisionName.find("Fallen"))
	{
		Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
		if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
			Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
		{
			// 발사 중단 후
			FireStart_ = false;

			// 적에게 데미지를 입히고 폭발 애니메이션실행
			Renderer_->SetChangeAnimation("Explode");
			CurAttackMonster->HitDamage(TeethInfo_.SkillDamage);
		}
	}
	else if (std::string::npos != CollisionName.find("SpikeFiend"))
	{
		SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
		if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
			SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
		{
			// 발사 중단 후
			FireStart_ = false;

			// 적에게 데미지를 입히고 폭발 애니메이션실행
			Renderer_->SetChangeAnimation("Explode");
			CurAttackMonster->HitDamage(TeethInfo_.SkillDamage);
		}
	}
	else if (std::string::npos != CollisionName.find("Tainted"))
	{
		Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
		if (Tainted_FSMState::TT_DEAD != CurAttackMonster->GetCurState() &&
			Tainted_FSMState::TT_DEATH != CurAttackMonster->GetCurState())
		{
			// 발사 중단 후
			FireStart_ = false;

			// 적에게 데미지를 입히고 폭발 애니메이션실행
			Renderer_->SetChangeAnimation("Explode");
			CurAttackMonster->HitDamage(TeethInfo_.SkillDamage);
		}
	}
	else if (std::string::npos != CollisionName.find("Zombie"))
	{
		Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();
		if (Zombie_FSMState::ZB_DEAD != CurAttackMonster->GetCurState() &&
			Zombie_FSMState::ZB_DEATH != CurAttackMonster->GetCurState())
		{
			// 발사 중단 후
			FireStart_ = false;

			// 적에게 데미지를 입히고 폭발 애니메이션실행
			Renderer_->SetChangeAnimation("Explode");
			CurAttackMonster->HitDamage(TeethInfo_.SkillDamage);
		}
	}
	else if (std::string::npos != CollisionName.find("Andariel"))
	{
		Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();
		if (Andariel_FSMState::AD_DEAD != CurAttackMonster->GetCurState() &&
			Andariel_FSMState::AD_DEATH != CurAttackMonster->GetCurState())
		{
			// 발사 중단 후
			FireStart_ = false;

			// 적에게 데미지를 입히고 폭발 애니메이션실행
			Renderer_->SetChangeAnimation("Explode");
			CurAttackMonster->HitDamage(TeethInfo_.SkillDamage);
		}
	}
}
