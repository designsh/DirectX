#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

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
	ST_ROOMDETECT,				// ������ �� üũ ����
	ST_IDLE,					// ������
	ST_WALK,					// Ÿ�ٱ��� �̵�����
	ST_NORMALATTACK,			// �Ϲݰ��ݹ����� �� ����
	ST_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	ST_DEATH,					// ��� ����(���� ü�� 0)
	ST_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// Ÿ��Ÿ��
enum class TargetType
{
	PLAYER,
	GOLEM,
	WARRIOR,
	WIZARD
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int TaintedCnt;

private:
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // ��������
	int SpawnRoomNo_;
	TileIndex SpawnTile_;
	int NavigationIndex_;

private:
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;

private: // �������
	Tainted_Dir PrevDir_;
	Tainted_Dir CurDir_;

private: // ���°���
	GameEngineFSM State_;
	Tainted_FSMState PrevState_;
	Tainted_FSMState CurState_;
	float IdleDelayTime_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;

private: // üũ����Ʈ����
	GameEngineActor* TargetActor_;
	TargetType TargetType_;
	bool TargetCol_;
	std::vector<TileIndex> RoomTileList_;
	std::vector<TileIndex> DetetTileList_;
	std::vector<TileIndex> AttackTileList_;

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

private: // ���콺�� �浹
	void MouseCollision(GameEngineCollision* _Other);

private: // ������ �浹
	void EnemyCollision(GameEngineCollision* _Other);
	void EnemyCollisionEnd(GameEngineCollision* _Other);

private: // �ش� ���� �ʱ�ȭ �� ����
	void InitTainted();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateFSMState();
	void CreateCollision();
	void CreateInfomation();

private: // ����üũ
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // �ִϸ��̼� ������� ȣ���Լ�
	void NormalAttackEnd();
	void GetHitEnd();
	void DeathEnd();

private:
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

public: // ���� ������ȯ����
	void GetHitDamage(int _Damage);
	void SpawnToDeath();

public: // �� Ÿ��üũ����
	// �� ���� üũ
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetect();

	// �뿡 ������ Ÿ�� �߿� �������� üũ
	void SetEnterTheDetectRangeList();
	bool EnterTheDetectRange();
};

