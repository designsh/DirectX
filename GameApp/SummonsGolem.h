#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

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
	WARP,
	WALK,
	ATTACK,
	GETHIT,
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
	float MoveSpeed_;								// 
	TileIndex MoveTargetTile_;						// 이동목표 타일
	float4 TargetPos_;								// 타겟 위치
	std::list<PathIndex> MovePath_;					// 이동경로
	float4 MoveTargetDir_;							// 실질적인 이동방향
	GolemTargetDir PrevDir_;						// 이전 방향
	GolemTargetDir CurDir_;							// 현재 방향

private:
	GolemState PrevState_;
	GolemState CurState_;

private:
	float CheckTime_;								// 대기상태에서 다음상태전환까지 대기시간

private:
	GameEngineActor* DetectMonster_;				// 현재 감지성공한 몬스터

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
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // 상태전환 체크관련
	void SetMoveRange();			// 플레이어 위치기준 10x10 타일범위의 이동범위
	bool CheckWarpStart();			// 이동제한 범위체크(TRUE : 대기상태전환 -> 워프상태로 전환됨)
	bool MonsterDetect();				// TRUE : 적이 범위내에 존재, FALSE : 적이존재하지않음

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

	// 워프상태
	void StartWarpState();
	void UpdateWarpState();
	void EndWarpState();

	// 공격상태
	void StartAttackState();
	void UpdateAttackState();
	void EndAttackState();

	// 피격상태
	void StartGetHitState();
	void UpdateGetHitState();
	void EndGetHitState();

	// 사망상태
	void StartDeathState();
	void UpdateDeathState();
	void EndDeathState();

public:
	void CurGolemDeath();
};

