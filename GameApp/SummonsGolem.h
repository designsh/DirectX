#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// 골렘 타겟방향
enum class GolemTargetDir
{
	GL_LB,
	GL_LT,
	GL_RT,
	GL_RB,
	GL_B,
	GL_L,
	GL_T,
	GL_R,
};

// 소환된 골렘 타입
enum class GolemType
{
	NONE = -1,
	CLAY,
	BLOOD,
	IRON,
	FIRE,
};

// 골렘 상태
enum class GolemState
{
	SPAWN,
	IDLE,
	WALK,
	ATTACK,
	DEATH
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class SummonsGolem : public GameEngineActor
{
private:
	GameEngineImageRenderer* GolemRenderer_;
	GameEngineCollision* BodyCollider_;

private:
	GameEngineFSM State_;

private:
	SkillList GolemInfo_;

private:
	GolemType GolemType_;
	float4 SpawnPos_;

private:
	std::vector<TileIndex> MaxMoveRange_;			// 플레이어기준 이동가능범위(타일목록)
	float4 TargetPos_;								// 타겟 위치
	GolemTargetDir PrevDir_;						// 이전 방향
	GolemTargetDir CurDir_;							// 현재 방향

private:
	GolemState PrevState_;
	GolemState CurState_;

public:
	SummonsGolem();
	~SummonsGolem();

protected:		// delete constructer
	SummonsGolem(const SummonsGolem& _other) = delete;
	SummonsGolem(SummonsGolem&& _other) noexcept = delete;

private:		//delete operator
	SummonsGolem& operator=(const SummonsGolem& _other) = delete;
	SummonsGolem& operator=(const SummonsGolem&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitGolem();
	void TextureCutting();
	void CreateCollision();

private:
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // 이동제한범위셋팅
	void SetMoveRange();
	bool CheckMoveRange();

public:
	void SpawnGolem(GolemType _GolemType, const float4& _SpawnPos);

private:
	void CreateClayGolem();
	void CreateBloodGolem();
	void CreateIronGolem();
	void CreateFireGolem();

private:
	void SpawnAnimationEnd();
	void AttackAnimationEnd();
	void DeathAnimationEnd();

private:
	// 소환상태
	void StartSpawnState();
	void UpdateSpawnState();
	void EndSpawnState();

	// 대기상태
	void StartIdleState();
	void UpdateIdleState();
	void EndIdleState();

	// 이동상태
	void StartWalkState();
	void UpdateWalkState();
	void EndWalkState();

	// 공격상태
	void StartAttackState();
	void UpdateAttackState();
	void EndAttackState();

	// 사망상태
	void StartDeathState();
	void UpdateDeathState();
	void EndDeathState();

public:
	void CurGolemDeath();
};

