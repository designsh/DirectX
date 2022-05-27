#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// �����ڷ�(������) Ÿ�ٹ���
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

// �����ڷ�(������) ����
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

// �з� : 
// �뵵 : 
// ���� : 
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

private: // ���� ���������� ����(������ nullptr �ʱ�ȭ)
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
	std::vector<TileIndex> MaxMoveRange_;			// �÷��̾���� �̵����ɹ���(Ÿ�ϸ��)
	std::list<PathIndex> MovePath_;					// �̵����
	TileIndex MoveTargetTile_;						// �̵���ǥ Ÿ��
	float4 TargetPos_;								// Ÿ�� ��ġ
	float4 MoveTargetDir_;							// �������� �̵�����
	float MoveSpeed_;								// �̵��ӵ�

private:
	SketelonWarrior_TargetDir PrevDir_;				// ���� ����
	SketelonWarrior_TargetDir CurDir_;				// ���� ����

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
	// ��ȯ����
	void StartSpawnState();
	void UpdateSpawnState();
	void EndSpawnState();

	// ������
	void StartIdleState();
	void UpdateIdleState();
	void EndIdleState();

	// �̵�����
	void StartWalkState();
	void UpdateWalkState();
	void EndWalkState();

	// ��������
	void StartWarpState();
	void UpdateWarpState();
	void EndWarpState();

	// ���ݻ���
	void StartAttackState();
	void UpdateAttackState();
	void EndAttackState();

	// �ǰݻ���
	void StartGetHitState();
	void UpdateGetHitState();
	void EndGetHitState();

	// �������
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

