#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

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
	ST_SKILLATTACK,				// ��ų���ݹ����� �� ����, ��ų��Ÿ�� ��
	ST_GETHIT,					// �ǰ� ����(���� �����Ͽ� ��ȯ)
	ST_DEATH,					// ��� ����(���� ü�� 0)
	ST_DEAD,					// ��ü ����(���콺�� �浹���̸�, �÷��̰� ��ȯ��ų���� üũ)
};

// ������ȯ Ÿ�ϸ�� Ÿ��
enum class Tainted_TileCheckType
{
	MOVE,
	NORMALATTACK,
	SKILLATTACK,
};

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
private:
	AllMonsterInfo MonsterInfo_;

private: // ��������
	TileIndex SpawnTile_;
	int SpawnRoomNo_;

private:
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;
	GameEngineCollision* AttackCollider_;

private:
	GameEngineFSM State_;

private: // �̵�����
	float4 TargetPos_;
	float4 CurPos_;
	float MoveSpeed_;

private: // �������
	Tainted_Dir PrevDir_;
	Tainted_Dir CurDir_;

private: // ����������
	bool RoomDetect_;
	std::vector<TileIndex> RoomDetectList_;						// ���� ���� ������üũ Ÿ�ϸ��
	std::map<__int64, Tainted_TileCheckType> CheckTileList_;	// �̵�, �Ϲݰ���, ��ų���� ��ȯ üũŸ�ϸ��

private: // ���°���
	Tainted_FSMState PrevState_;
	Tainted_FSMState CurState_;

private: // ���ݰ���
	std::vector<TileIndex> AttackList_;	// ���ݰ��� ����
	std::vector<TileIndex> SkillList_;	// ��ų���� ���ɹ���
	float SkillDelayTime_;				// ��ų���� ��Ÿ��

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

private:
	void InitTainted();
	void TextureCutting();
	void CreateAnimation();
	void CreateFSMState();
	void CreateCollision();
	void CreateInfomation();

private:
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // üũŸ�ϸ�� ���� �� üũ�� ������ȯ
	void SetCheckTileList(TileIndex _CurTileIndex);
	void CheckChangeState(TileIndex _PlayerTileIndex);

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

	// ��ų���ݻ���
	void StartSpecialAttack();
	void UpdateSpecialAttack();
	void EndSpecialAttack();

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
	
public:
	void SetEnemyDetectionList(int _SpawnRoomNo);
};

