#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// �����ڷ�(��������) Ÿ�ٹ���
enum class SketelonWizard_TargetDir
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

// �����ڷ�(��������) ����
enum class SketelonWizardState
{
	SPAWN,
	IDLE,
	WARP,
	WALK,
	ATTACK,
	GETHIT,
	DEATH
};

// ��ȯ�� ���̷���(��������) Ÿ��
enum class SkeletonWizardType
{
	NONE = -1,
	COLD,
	FIRE,
	LIGHTNING,
	POISON,
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class SketelonWizard : public GameEngineActor
{
public:
	static int WizardCnt;

private:
	GameEngineImageRenderer* WizardRenderer_;
	GameEngineCollision* BodyCollider_;

private: // ���� ���������� ����(������ nullptr �ʱ�ȭ)
	GameEngineActor* DetectMonster_;

private:
	SkillList SketelonWizardInfo_;
	GameEngineFSM State_;
	SketelonWizardState PrevState_;
	SketelonWizardState CurState_;
	float4 SpawnPos_;
	int WizardNavigationIndex_;

private:
	SkeletonWizardType WizardType_;
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
	SketelonWizard_TargetDir PrevDir_;				// ���� ����
	SketelonWizard_TargetDir CurDir_;				// ���� ����

private:
	GameEngineSoundPlayer* StateSound_;

public:
	SketelonWizard();
	~SketelonWizard();

protected:		// delete constructer
	SketelonWizard(const SketelonWizard& _other) = delete;
	SketelonWizard(SketelonWizard&& _other) noexcept = delete;

private:		//delete operator
	SketelonWizard& operator=(const SketelonWizard& _other) = delete;
	SketelonWizard& operator=(const SketelonWizard&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	inline void DecreaseNavationIndex()
	{
		WizardNavigationIndex_ -= 1;
	}

private:
	void CreateAnimation();
	void CreateWizardColdType();
	void CreateWizardFireType();
	void CreateWizardLightningType();
	void CreateWizardPoisonType();
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
	void SpawnSketelonWizard(SkeletonWizardType _WizardType, const float4& _SpawnPos);
};

