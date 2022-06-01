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
enum class Fallen_TargetDir
{
	FL_LB,
	FL_LT,
	FL_RT,
	FL_RB,
	FL_B,
	FL_L,
	FL_T,
	FL_R
};

// ���°���
enum class Fallen_FSMState
{
	FL_ROOMDETECT,				// ������ �� üũ ����
	FL_IDLE,					// ������
	FL_WALK,					// Ÿ�ٱ��� �̵�����
	FL_ATTACK,					// ���ݹ����� �� ����
	FL_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	FL_DEATH,					// ��� ����(���� ü�� 0)
	FL_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾�� ������ ���Ѵ�.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Fallen : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int FallenCnt;

private:
	GameEngineImageRenderer* Fallen_;
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
	Fallen_FSMState PrevState_;
	Fallen_FSMState CurState_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Fallen_TargetDir PrevDir_;
	Fallen_TargetDir CurDir_;

private: // ���ݰ���
	bool Attack_;

private: // �������
	GameEngineSoundPlayer* StateSound_;

private: // �ǰݰ���
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

public:
	Fallen();
	~Fallen();

protected:		// delete constructer
	Fallen(const Fallen& _other) = delete;
	Fallen(Fallen&& _other) noexcept = delete;

private:		//delete operator
	Fallen& operator=(const Fallen& _other) = delete;
	Fallen& operator=(const Fallen&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline Fallen_FSMState GetCurState() const
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
	void InitFallen();
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

