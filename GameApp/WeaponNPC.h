#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

enum class WeaponNPC_MoveDir
{
	DIR_B,
	DIR_LB,
	DIR_L,
	DIR_LT,
	DIR_T,
	DIR_RT,
	DIR_R,
	DIR_RB,
	MAX
};

enum class WeaponNPC_FSMState
{
	ST_IDLE,	// ������
	ST_WALK,	// �ȱ����
	ST_CONV,	// �÷��̾�� ��ȣ�ۿ��� ����
	ST_INTER,	// �÷��̾�� ��ȣ�ۿ��� ����
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class NPC_MessageView;
class WeaponNPC : public GameEngineActor
{
private:
	static bool FirstInteraction;
	static bool InteractionFlag;

public:
	static bool GetFirstInteaction();

private:	// member Var
	GameEngineImageRenderer* WeaponNPCRenderer_;
	GameEngineCollision* WeaponNPCCollision_;

private:
	WeaponNPC_MoveDir PrevMoveDir_;
	WeaponNPC_MoveDir CurMoveDir_;

private: // FSM
	GameEngineFSM State_;
	WeaponNPC_FSMState PrevState_;
	WeaponNPC_FSMState CurState_;

private: // �ڵ�ȭ��
	float MoveDelayTime_;		// �̵������̽ð�
	float InteractionDistance_;	// �ּ� ��ȣ�ۿ� Ȱ��ȭ�Ÿ�(�÷��̾���� �Ÿ�)
	float MoveSpeed_;			// �̵��ӵ�
	float4 MoveStartPos_;		// �̵�����ġ
	float4 MoveCurPos_;			// �̵�����ġ

private: // UI����
	NPC_MessageView* MessageView_;

public:
	WeaponNPC();
	~WeaponNPC();

protected:		// delete constructer
	WeaponNPC(const WeaponNPC& _other) = delete;
	WeaponNPC(WeaponNPC&& _other) noexcept = delete;

private:		//delete operator
	WeaponNPC& operator=(const WeaponNPC& _other) = delete;
	WeaponNPC& operator=(const WeaponNPC&& _other) = delete;

private:
	void InitWeaponNPC();
	void TextureCutting();
	void CreateAnimation();
	void CreateFSMState();
	void CreateCollision();

private: // ����/���⺰ üũ���Ͽ� �ִϸ��̼� ����
	void ChangeAnimationCheck(const std::string& _StateName);

private:
	// ������
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// �̵�����
	void StartWalk();
	void UpdateWalk();
	void EndWalk();

	// ��ȣ�ۿ��� ����
	void StartConversation();
	void UpdateConversation();
	void EndConversation();

	// ��ȣ�ۿ��� ����
	void StartInteraction();
	void UpdateInteraction();
	void EndInteraction();

private:
	void MouseLButtonClick(GameEngineCollision* _Other);
	
private:
	void InteractionDistanceCheck();

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

