#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// 스켈텔론(전사형) 타겟방향
enum class SketelonWarrior_TargetDir
{
	SW_LB,
	SW_LT,
	SW_RT,
	SW_RB,
	SW_B,
	SW_L,
	SW_T,
	SW_R,
};

// 스켈텔론(전사형) 상태
enum class SketelonWarriorState
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
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class SketelonWarrior : public GameEngineActor
{
public:
	static int WarriorCnt;

private:
	GameEngineImageRenderer* WarriorRenderer_;
	GameEngineCollision* BodyCollider_;

private: // 현재 감지성공한 몬스터(공격후 nullptr 초기화)
	GameEngineActor* DetectMonster_;

private:
	SkillList SketelonWarriorInfo_;
	GameEngineFSM State_;
	SketelonWarriorState PrevState_;
	SketelonWarriorState CurState_;
	float4 SpawnPos_;
	int WarriorNavigationIndex_;

private:
	float CheckTime_;
	int CurHP_;

private:
	std::vector<TileIndex> MaxMoveRange_;			// 플레이어기준 이동가능범위(타일목록)
	std::list<PathIndex> MovePath_;					// 이동경로
	TileIndex MoveTargetTile_;						// 이동목표 타일
	float4 TargetPos_;								// 타겟 위치
	float4 MoveTargetDir_;							// 실질적인 이동방향
	float MoveSpeed_;								// 이동속도

private:
	SketelonWarrior_TargetDir PrevDir_;				// 이전 방향
	SketelonWarrior_TargetDir CurDir_;				// 현재 방향

private:
	GameEngineSoundPlayer* StateSound_;

public:
	SketelonWarrior();
	~SketelonWarrior();

protected:		// delete constructer
	SketelonWarrior(const SketelonWarrior& _other) = delete;
	SketelonWarrior(SketelonWarrior&& _other) noexcept = delete;

private:		//delete operator
	SketelonWarrior& operator=(const SketelonWarrior& _other) = delete;
	SketelonWarrior& operator=(const SketelonWarrior&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	inline void DecreaseNavationIndex()
	{
		WarriorNavigationIndex_ -= 1;
	}

private:
	void CreateAnimation();
	void CreateAnimationEndCallbackFunction();
	void CreateFSMState();

private:
	void SpawnAnimationEnd();
	void AttackAnimationEnd();
	void GetHitAnimationEnd();
	void DeathAnimationEnd();

private:
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);
	bool MonsterDetect();
	bool CheckWarpStart();

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

private:
	void SetMoveRange();

public:
	void CurSkeletonDeath();

public:
	void SpawnSketelonWarrior(const float4& _SpawnPos);
};

