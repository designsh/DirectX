#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// �÷��̾�� �� 8������ �ִϸ��̼��� �����Ѵ�.
// �׷��Ƿ� ���� �÷��̾��� ��ġ�� ���콺Ŀ���� Ŭ���� ��ġ��
// ������ ����Ͽ� �÷��̾��� ��Ŀ�������� �����Ѵ�.
enum class TargetDirect
{
	DIR_LB,
	DIR_LT,
	DIR_RT,
	DIR_RB,
	DIR_B,
	DIR_L,
	DIR_T,
	DIR_R,
	DIR_MAX,
};

// �ִϸ��̼��� �� 16������ �ִϸ��̼��� ������,
// ���ӳ����� 8���⸸ ���
enum class PlayerState
{
	STAT_A1,					// x : 19, y : 16 => ���ݸ��1
	STAT_A2,					// x : 19, y : 16 => ���ݸ��2
	STAT_BL,					// x :   6, y : 16 => �����
	STAT_DD,					// x :   1, y : 16 => ��ü���
	STAT_DT,					// x : 27, y : 16 => ������
	STAT_GH,					// x :   7, y : 16 => �ǰݸ��
	STAT_KK,					// x : 12, y : 16 => ű���
	STAT_NU,					// x :   8, y : 16 => �ʵ�_�����
	STAT_RN,					// x :   8, y : 16 => �ٱ���
	STAT_S1,					// x : 16, y : 16 => ��ų���ݸ��
	STAT_SC,					// x : 16, y : 16 => ��ųĳ���ø��
	STAT_TN,					// x : 16, y : 16 => ����_�����
	STAT_TW,					// x :   8, y : 16 => ����_�ȱ���
	STAT_WL,					// x :   8, y : 16 => �ʵ�_�ȱ���
	STAT_MAX,
};

// ������ �������
enum class ItemEquipState
{
	TP_LIT,
	TP_HVY,
	TP_MAX
};

// ������ ������ Ÿ��
enum class RendererPartType
{
	PART_HD,
	PART_LA,
	PART_LG,
	PART_RA,
	PART_RH,
	PART_S1,
	PART_S2,
	PART_SH,
	PART_TR,
	PART_MAX,
};

// ���� �÷��̾��� ������ ������������� üũ�� ����
// ����ü�� �������� �����Ѵ�.
class GameEngineImageRenderer;
struct PlayerRendererPart
{
	ItemEquipState												ItemEquipState_;												// ������ ��������
	GameEngineImageRenderer*									Renderer_[static_cast<int>(ItemEquipState::TP_MAX)];			// ������(0 : TP_LIT(�⺻), 1 : TP_HVY(����������))
	RendererPartType											PartType_;														// ���� Ÿ��
	std::string													TextureName_;													// ���� �ؽ��ĸ�
	std::string													AnimationName_;													// ���� �ִϸ��̼Ǹ�
};

// �÷��̾� ���⺰ ��������
struct PlayerAnimationRenderOrder
{
	std::vector<RendererPartType>								DefaultDirectRenderOrder_;	// �ִϸ��̼ǽ��� �⺻ ������ ����

	// �ִϸ��̼� ������ ������ ������ ������� �˻�
	bool														ChangeRenderOrderFlag_;		// �ִϸ��̼ǽ��� �߰��� ������������ ����Ǿ���ϴ���
	int															ChangeRenderCount_;			// �ִϸ��̼ǽ��� �߰��� ������������ ����Ǵ� ��

	int															ChangeStartIndex_;			// ������ ������ ����Ǵ� ������ �ε���
	int															ChangeEndIndex_;			// ������ ������ �⺻������ ������ ���ư��� ������ �ε���
	std::vector<RendererPartType>								ChangeDirectRenderOrder_;	// �ִϸ��̼� �߰� ����Ǵ� ������ ����

};

// �з� : �÷��̾�
// �뵵 : 
// ���� : ������ ���� ������ �ٸ�
class BottomStateBar;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private: // �÷��̾���� Flag
	bool IsTown_;						// ����/�ʵ� ���� ����(true : ����)
	bool IsRun_;						// �ٱ�/�ȱ� ���� ����(true : �ٱ����(���¹̳� �Ҹ�))
	bool IsInventory_;					// �κ��丮 Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsStateView_;					// ����â Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� ������ �̵��������� ���� �Ұ�
	bool IsSkillView_;					// ��ųâ Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsRightSkillList_;				// ������ ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsLeftSkillList_;				// ���� ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsStorehouse_;					// â�� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ�Ǹ�, ���ÿ� �κ��丮 Ȱ��ȭ - ȭ�� ��ü�� �̵��������� ���� �Ұ�

private: // FSM
	GameEngineFSM<MainPlayer> State_;

private: // �̵�����
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

private:
	PlayerState PrevState_;
	PlayerState CurState_;
	std::vector<std::string> StateName_;

private: // �÷��̾� UI
	BottomStateBar* BottomStateBar_;

private: // �÷��̾� ������ �ִϸ��̼Ƿ�����
	std::vector<PlayerRendererPart> PartRenderer_;
	float4 PlayerSize_;

private: // �÷��̾� ���⺰ ��������
	std::vector<PlayerAnimationRenderOrder> DirectRenderOrder_[static_cast<int>(TargetDirect::DIR_MAX)];

private: // test
	int StateTest = 0;
	int DirectText = 0;

public:
	MainPlayer();
	~MainPlayer();

protected:		// delete constructer
	MainPlayer(const MainPlayer& _other) = delete;
	MainPlayer(MainPlayer&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer& operator=(const MainPlayer& _other) = delete;
	MainPlayer& operator=(const MainPlayer&& _other) = delete;

private: // �ؽ��� ���ð���
	void AllAnimationCut();							// �÷��̾��� ��ü �ִϸ��̼ǿ� �ʿ��� ��� �ؽ��� ����ó��
	void AnimationA1Cut();							// ���ݸ��1
	void AnimationA2Cut();							// ���ݸ��2
	void AnimationBLCut();							// �����
	void AnimationDDCut();							// ��ü���
	void AnimationDTCut();							// ������
	void AnimationGHCut();							// �ǰݸ��
	void AnimationKKCut();							// ű���
	void AnimationNUCut();							// �ʵ�_�����
	void AnimationRNCut();							// �ٱ���
	void AnimationS1Cut();							// ��ų���ݸ��
	void AnimationSCCut();							// ��ųĳ���ø��
	void AnimationTNCut();							// ����_�����
	void AnimationTWCut();							// ����_�ȱ���
	void AnimationWLCut();							// �ʵ�_�ȱ���

private: // �ִϸ��̼� ��������
	void SetFirstAnimation();						// ���� �ִϸ��̼� ����
	void SetRenderSize();							// ���� ������ũ�� ����
	void SetFirstZOrder();							// ���� Z���� ����
	void SetFirstItemEquipState();					// ���� �������ϴ� �ִϸ��̼�Ÿ�� ����
	void CreateAnimation();							// �÷��̾��� ��ü �ִϸ��̼� ��� ����
	void CreateA1Animation();						// ���ݸ��1
	void CreateA2Animation();						// ���ݸ��2
	void CreateBLAnimation();						// �����
	void CreateDDAnimation();						// ��ü���
	void CreateDTAnimation();						// ������
	void CreateGHAnimation();						// �ǰݸ��
	void CreateKKAnimation();						// ű���
	void CreateNUAnimation();						// �ʵ�_�����
	void CreateRNAnimation();						// �ٱ���
	void CreateS1Animation();						// ��ų���ݸ��
	void CreateSCAnimation();						// ��ųĳ���ø��
	void CreateTNAnimation();						// ����_�����
	void CreateTWAnimation();						// ����_�ȱ���
	void CreateWLAnimation();						// �ʵ�_�ȱ���

private: // FSM ��������
	void CreatePlayerStateFSM();

private:
	void CreateDirectRenderOrderType();				// �÷��̾� �̵����⺰ �������� Ÿ�� ����
	void ChangeZOrderType(TargetDirect _Direct);	// �÷��̾��� �̵����⿡ ���� �������� Ÿ�� ����

private: // ���°� �ٲ�� �ִϸ��̼ǰ� �ؽ��������� ����Ǿ���ϹǷ� SetImage()�� ChangeAnimation()�� ���ÿ� ����Ǵ� �������
	void CreateStateName();
	std::string ChangeStateCheck(RendererPartType _PartType);
	void ReSettingTextureName();
	std::string ChangeDirectCheck(RendererPartType _PartType);
	void ChangePlayerAnimation(PlayerState _ChangeState, TargetDirect _MoveDir);

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void PlayerUIActiveKeyCheck();

private:
	bool MoveDirectCheck();
	void MoveStart();

private: // FSM ó������
	void ChangeFSMState(std::string _StateName);

	// ========================== ���� ���� ========================== //
	StateInfo StartTownNatural(StateInfo _state);
	StateInfo UpdateTownNatural(StateInfo _state);
	StateInfo StartTownWalk(StateInfo _state);
	StateInfo UpdateTownWalk(StateInfo _state);

	// ========================== �ʵ� ���� ========================== //
	StateInfo StartFieldNatural(StateInfo _state);
	StateInfo UpdateFieldNatural(StateInfo _state);
	StateInfo StartFieldWalk(StateInfo _state);
	StateInfo UpdateFieldWalk(StateInfo _state);

	// ========================== ���� ���� ========================== //
	StateInfo StartAttack1(StateInfo _state);
	StateInfo UpdateAttack1(StateInfo _state);
	StateInfo StartAttack2(StateInfo _state);
	StateInfo UpdateAttack2(StateInfo _state);
	StateInfo StartBlock(StateInfo _state);
	StateInfo UpdateBlock(StateInfo _state);
	StateInfo StartGetHit(StateInfo _state);
	StateInfo UpdateGetHit(StateInfo _state);
	StateInfo StartKick(StateInfo _state);
	StateInfo UpdateKick(StateInfo _state);
	StateInfo StartRun(StateInfo _state);
	StateInfo UpdateRun(StateInfo _state);
	StateInfo StartSkillAttack(StateInfo _state);
	StateInfo UpdateSkillAttack(StateInfo _state);
	StateInfo StartSkillCasting(StateInfo _state);
	StateInfo UpdateSkillCasting(StateInfo _state);

	// ========================== ��� ���� ========================== //
	StateInfo StartDead(StateInfo _state);
	StateInfo UpdateDead(StateInfo _state);
	StateInfo StartDeath(StateInfo _state);
	StateInfo UpdateDeath(StateInfo _state);
};

