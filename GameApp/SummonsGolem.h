#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// �� Ÿ�ٹ���
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

// ��ȯ�� �� Ÿ��
enum class GolemType
{
	NONE = -1,
	CLAY,
	BLOOD,
	IRON,
	FIRE,
};

// �� ����
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

// �з� : 
// �뵵 : 
// ���� : 
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
	std::vector<TileIndex> MaxMoveRange_;			// �÷��̾���� �̵����ɹ���(Ÿ�ϸ��)
	float MoveSpeed_;								// 
	TileIndex MoveTargetTile_;						// �̵���ǥ Ÿ��
	float4 TargetPos_;								// Ÿ�� ��ġ
	std::list<PathIndex> MovePath_;					// �̵����
	float4 MoveTargetDir_;							// �������� �̵�����
	GolemTargetDir PrevDir_;						// ���� ����
	GolemTargetDir CurDir_;							// ���� ����

private:
	GolemState PrevState_;
	GolemState CurState_;

private:
	float CheckTime_;								// �����¿��� ����������ȯ���� ���ð�

private:
	GameEngineActor* DetectMonster_;				// ���� ���������� ����

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

private: // ������ȯ üũ����
	void SetMoveRange();			// �÷��̾� ��ġ���� 10x10 Ÿ�Ϲ����� �̵�����
	bool CheckWarpStart();			// �̵����� ����üũ(TRUE : ��������ȯ -> �������·� ��ȯ��)
	bool MonsterDetect();				// TRUE : ���� �������� ����, FALSE : ����������������

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

public:
	void CurGolemDeath();
};

