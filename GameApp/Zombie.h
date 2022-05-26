#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "FixedTileMap_Common.h"
#include "RandomTileMap_Common.h"

// �������
enum class Zombie_TargetDir
{
	ZB_LB,
	ZB_LT,
	ZB_RT,
	ZB_RB,
	ZB_B,
	ZB_L,
	ZB_T,
	ZB_R
};

// ���°���
enum class Zombie_FSMState
{
	ZB_ROOMDETECT,				// ������ �� üũ ����
	ZB_IDLE,					// ������
	ZB_WALK,					// Ÿ�ٱ��� �̵�����
	ZB_ATTACK,					// ���ݹ����� �� ����
	ZB_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	ZB_DEATH,					// ��� ����(���� ü�� 0)
	ZB_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾ ���ݹ����� �����ϸ� ���������� ���Ѵ�.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Zombie : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int ZombieCnt;

private:	// member Var
	GameEngineImageRenderer* Zombie_;
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
	Zombie_FSMState PrevState_;
	Zombie_FSMState CurState_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Zombie_TargetDir PrevDir_;
	Zombie_TargetDir CurDir_;

private: // ���ݰ���
	bool Attack_;

private: // �������
	GameEngineSoundPlayer* StateSound_;

public:
	Zombie();
	~Zombie();

protected:		// delete constructer
	Zombie(const Zombie& _other) = delete;
	Zombie(Zombie&& _other) noexcept = delete;

private:		//delete operator
	Zombie& operator=(const Zombie& _other) = delete;
	Zombie& operator=(const Zombie&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline Zombie_FSMState GetCurState() const
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
	void InitZombie();
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
	void GetHitDamage(int _Damage);

public: // �� üũ ����Ʈ����
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetectCheck();
};

