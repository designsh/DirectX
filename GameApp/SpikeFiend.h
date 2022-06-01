#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "Monster_Common.h"
#include "FixedTileMap_Common.h"
#include "RandomTileMap_Common.h"

// �������
enum class SpikeFiend_TargetDir
{
	SF_B,
	SF_LB,
	SF_L,
	SF_LT,
	SF_T,
	SF_RT,
	SF_R,
	SF_RB,
};

// ���°���
enum class SpikeFiend_FSMState
{
	SF_ROOMDETECT,				// ������ �� üũ ����
	SF_IDLE,					// ������
	SF_WALK,					// Ÿ�ٱ��� �̵�����
	SF_ATTACK,					// ���ݹ����� �� ����
	SF_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	SF_DEATH,					// ��� ����(���� ü�� 0)
	SF_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾ ���ݹ����� �����ϸ� ����ü�� �߻��Ͽ� �÷��̾�� ������ ���Ѵ�.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class SpikeFiend : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int SpikeFiendCnt;

private:
	GameEngineImageRenderer* SpikeFiend_;
	GameEngineCollision* BodyCollider_;

private: // ��������
	int SpawnRoomNo_;
	TileIndex SpawnTile_;
	float IdleDelayTime_;
	int NavigationIndex_;

private: // üũ����Ʈ����
	std::vector<TileIndex> RoomTileList_;

private: // ���� ����
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // ���°���
	GameEngineFSM State_;
	SpikeFiend_FSMState PrevState_;
	SpikeFiend_FSMState CurState_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	SpikeFiend_TargetDir PrevDir_;
	SpikeFiend_TargetDir CurDir_;

private: // ���ݰ���
	bool Attack_;

private: // �������
	GameEngineSoundPlayer* StateSound_;

private: // �ǰݰ���
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

public:
	SpikeFiend();
	~SpikeFiend();

protected:		// delete constructer
	SpikeFiend(const SpikeFiend& _other) = delete;
	SpikeFiend(SpikeFiend&& _other) noexcept = delete;

private:		//delete operator
	SpikeFiend& operator=(const SpikeFiend& _other) = delete;
	SpikeFiend& operator=(const SpikeFiend&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline SpikeFiend_FSMState GetCurState() const
	{
		return CurState_;
	}

private: // Collision Callback Function
	void MouseCollision(GameEngineCollision* _Ohter);
	void EnemyCollision(GameEngineCollision* _Other);

private:
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // �ش� ���� �ʱ�ȭ �� ����
	void InitSpikeFiend();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateFSMState();
	void CreateCollision();
	void CreateInfomation();

private: // FSM State
	// ���� ��Ž�� ����
	void StartRoomDetect();
	void UpdateRoomDetect();
	void EndRoomDetect();

	// ������
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// �̵�����(����������)
	void StartMove();
	void UpdateMove();
	void EndMove();

	// �⺻���ݻ���
	void StartNormalAttack();
	void UpdateNormalAttack();
	void EndNormalAttack();

	// �ǰݻ���
	void StartGetHit();
	void UpdateGetHit();
	void EndGetHit();

	// �������
	void StartDeath();
	void UpdateDeath();
	void EndDeath();

	// ��ü����
	void StartDead();
	void UpdateDead();
	void EndDead();

private: // Ư�� �ִϸ��̼� ����� ȣ��Ǵ� �Լ�
	void AttackEnd();
	void GetHitEnd();
	void DeathEnd();

public: // �ܺ����� ���� ������ȯ
	void SpawnToDeath();
	void HitDamage(int _Damage);
	void SpecialHitDamage(int _Damage, MonsterDamageType _DamageType);

public: // �� üũ ����Ʈ����
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetectCheck();
};

