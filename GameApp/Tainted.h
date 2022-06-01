#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "Monster_Common.h"
#include "FixedTileMap_Common.h"
#include "RandomTileMap_Common.h"

// �̵�����
enum class Tainted_Dir
{
	TT_LB,
	TT_LT,
	TT_RT,
	TT_RB,
	TT_B,
	TT_L,
	TT_T,
	TT_R
};

// ���°���
enum class Tainted_FSMState
{
	TT_ROOMDETECT,				// ������ �� üũ ����
	TT_IDLE,					// ������
	TT_WALK,					// Ÿ�ٱ��� �̵�����
	TT_ATTACK,					// ���ݹ����� �� ����
	TT_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	TT_DEATH,					// ��� ����(���� ü�� 0)
	TT_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : 
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int TaintedCnt;

private:
	GameEngineImageRenderer* Tainted_;
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
	Tainted_FSMState PrevState_;
	Tainted_FSMState CurState_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Tainted_Dir PrevDir_;
	Tainted_Dir CurDir_;

private: // ���ݰ���
	bool Attack_;

private: // �������
	GameEngineSoundPlayer* StateSound_;

private: // �ǰݰ���
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

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

public:
	inline Tainted_FSMState GetCurState() const
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
	void InitTainted();
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

