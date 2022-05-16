#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;
	GameEngineCollision* AttackCollider_;

private:
	GameEngineFSM State_;

private: 
	float SkillDelayTime_;			// 스킬공격 쿨타임

public:
	Tainted();
	~Tainted();

protected:		// delete constructer
	Tainted(const Tainted& _other) = delete;
	Tainted(Tainted&& _other) noexcept = delete;

private:		//delete operator
	Tainted& operator=(const Tainted& _other) = delete;
	Tainted& operator=(const Tainted&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitTainted();
	void TextureCutting();
	void CreateAnimation();
	void CreateFSMState();
	void CreateCollision();

private:
	// 대기상태(적탐지상태)
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// 적감지상태
	void StartEnemyDetect();
	void UpdateEnemyDetect();
	void EndEnemyDetect();

	// 이동상태
	void StartMove();
	void UpdateMove();
	void EndMove();

	// 기본공격상태
	void StartNormalAttack();
	void UpdateNormalAttack();
	void EndNormalAttack();

	// 스킬공격상태
	void StartSpecialAttack();
	void UpdateSpecialAttack();
	void EndSpecialAttack();

	// 피격상태
	void StartGetHit();
	void UpdateGetHit();
	void EndGetHit();

	// 사망상태
	void StartDeath();
	void UpdateDeath();
	void EndDeath();

	// 시체상태
	void StartDead();
	void UpdateDead();
	void EndDead();
	
public:
};

