#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;
	GameEngineCollision* AttackCollider_;

private:
	GameEngineFSM State_;

private: 
	float SkillDelayTime_;			// ��ų���� ��Ÿ��

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

private:
	// ������(��Ž������)
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// ����������
	void StartEnemyDetect();
	void UpdateEnemyDetect();
	void EndEnemyDetect();

	// �̵�����
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
};

