#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

enum class ChandleryNPC_MoveDir
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

enum class ChandleryNPC_FSMState
{
	ST_IDLE,	// ������
	ST_WALK,	// �ȱ����
	ST_CONV,	// �÷��̾�� ��ȣ�ۿ��� ����
	ST_INTER,	// �÷��̾�� ��ȣ�ۿ��� ����
};


// �з� : 
// �뵵 : 
// ���� : 
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class NPC_TopMenuBar;
class NPC_MessageView;
class NPC_BuySellView;
class ChandleryNPC : public GameEngineActor
{
private:
	static bool FirstInteraction;
	static bool InteractionFlag;

public:
	static bool GetFirstInteaction();

private:	// member Var
	GameEngineImageRenderer* ChandleryNPCRenderer_;
	GameEngineCollision* ChandleryNPCCollision_;

private:
	ChandleryNPC_MoveDir PrevMoveDir_;
	ChandleryNPC_MoveDir CurMoveDir_;

private: // FSM
	GameEngineFSM State_;
	ChandleryNPC_FSMState PrevState_;
	ChandleryNPC_FSMState CurState_;

private: // �̵���� �� �ڵ��̵�����
	float MoveDelayTime_;				// NPC�� �����̵����� �����̽ð�
	float MoveSpeed_;					// NPC�� �̵��ӵ�
	float4 MoveStartPos_;				// �̵�����ġ
	float4 MoveCurPos_;					// �̵�����ġ

private:
	float4 MoveMinRange_;				// �ּ��̵�����(�̵������� Ÿ���ε��� ����)
	float4 MoveMaxRange_;				// �ִ��̵�����(�̵������� Ÿ���ε��� ����)

private: // UI����
	NPC_MessageView* MessageView_;
	NPC_TopMenuBar* TopMenuBar_;

private:
	GameEngineSoundPlayer* SpeechSound_;

public:
	ChandleryNPC();
	~ChandleryNPC();

protected:		// delete constructer
	ChandleryNPC(const ChandleryNPC& _other) = delete;
	ChandleryNPC(ChandleryNPC&& _other) noexcept = delete;

private:		//delete operator
	ChandleryNPC& operator=(const ChandleryNPC& _other) = delete;
	ChandleryNPC& operator=(const ChandleryNPC&& _other) = delete;

private:
	void InitChandleryNPC();
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

public:
	NPC_BuySellView* GetChandleryShop();

public:
	void SetMoveRange();
	void SetMessageBoxText(const std::string& _Text);
	void SetUIPosition();
	void SetTopMenu();

public:
	void TopMenuBarInactive();
	void TopMenuBarActive();

public:
	void InteractionEnd();
	void SelectConversationMenu();

public:
	bool SpeechEndCheck();
};

