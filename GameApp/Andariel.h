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
enum class Andariel_TargetDir
{
	AD_B,
	AD_LB,
	AD_L,
	AD_LT,
	AD_T,
	AD_RT,
	AD_R,
	AD_RB
};

// ���°���
enum class Andariel_FSMState
{
	AD_ROOMDETECT,				// 
	AD_IDLE,					// 
	AD_WALK,					// 
	AD_ATTACK,					// 
	AD_SKILLATTACK,				// 
	AD_GETHIT,					// 
	AD_DEATH,					// 
	AD_DEAD,					// 
};

// �з� : ��������
// �뵵 : īŸ�޷����� ��������
// ���� : �ʵ�(��ü��)���� �÷��̾ ���� ������ ���� ��ġ�� ���� �� ��ġ�� �����ϴ� �濡 �����ϸ�,
//            �Ϲݰ���(��������)�� ��ų����(���Ÿ�) ������ ������.
//            �� 1������ �ʵ忡 �����ϸ�, ����� ��� ����Ʈ(ī�޶� ����ŷ, �Ҳɿ�����Ʈ ��ȯ ��)�� �����ϸ�,
//            �������Ʈ ����� Boss Portal(Auto)�� �����Ͽ� �÷��̾ ���� ������ ������ �� �ְ� �����Ѵ�.
//            �������Ʈ�� ���ÿ� �뷮�� ������ or ��带 ����Ѵ�.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Andariel : public GameEngineActor
{
public: // �������� = �׺���̼� �ε���
	static int AndarielCnt;

private:	// member Var
	GameEngineImageRenderer* Andariel_;
	GameEngineImageRenderer* AndarielEffect_;
	GameEngineCollision* BodyCollider_;

private: // ��������
	int SpawnRoomNo_;
	TileIndex SpawnTile_;
	float IdleDelayTime_;
	int NavigationIndex_;

private: // ��ų���ݰ���
	float SkillDelayTime_;
	bool SkillAttack_;
	int ProjectileCnt_;
	float4 ProjectileStartDir_;

private: // �Ϲݰ��ݰ���
	bool Attack_;

private: // üũ����Ʈ����
	std::vector<TileIndex> RoomTileList_;

private: // ���� ����
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // ���°���
	GameEngineFSM State_;
	Andariel_FSMState PrevState_;
	Andariel_FSMState CurState_;

private: // �̵�����
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Andariel_TargetDir PrevDir_;
	Andariel_TargetDir CurDir_;

private: // ȿ���� ����
	GameEngineSoundPlayer* StateSound_;

private: // �ǰݰ���
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

public:
	Andariel();
	~Andariel();

protected:		// delete constructer
	Andariel(const Andariel& _other) = delete;
	Andariel(Andariel&& _other) noexcept = delete;

private:		//delete operator
	Andariel& operator=(const Andariel& _other) = delete;
	Andariel& operator=(const Andariel&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline Andariel_FSMState GetCurState() const
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
	void InitAndariel();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateSpecificFrameFunction();
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

	// ��ų���ݻ���
	void StartSkillAttack();
	void UpdateSkillAttack();
	void EndSkillAttack();

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
	void SkillAttackEnd();
	void DeathEnd();

private: // Ư�� �ִϸ��̼� Ư�� �����ӿ� ȣ��Ǵ� �Լ�
	void ProjectileFire();
	void DeathEffectStart();

public: // �ܺ����� ���� ������ȯ
	void SpawnToDeath();
	void HitDamage(int _Damage);
	void SpecialHitDamage(int _Damage, MonsterDamageType _DamageType);

public: // �� üũ ����Ʈ����
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetectCheck();

public: // ������ ���ó�� �� ��Ż����
	void PortalSpawnAfterDeath();
};

