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

// ������ ���� ����
enum class ItemEquipPart
{
	Inv_Helm,		// ����
	Inv_Armor,		// ����
	Inv_LRing,		// ���� ��
	Inv_RRing,		// ������ ��
	Inv_Amulet,		// �����
	Inv_Gloves,		// �尩
	Inv_Boots,		// ����
	Inv_Weapon,		// ����
	Inv_Shield,		// ����
	Inv_MAX
};

// ���� �÷��̾��� ������ ������������� üũ�� ����
// ����ü�� �������� �����Ѵ�.
class GameEngineImageRenderer;
struct PlayerRendererPart
{
	GameEngineImageRenderer*									Renderer_[static_cast<int>(ItemEquipState::TP_MAX)];			// ������(0 : TP_LIT(�⺻), 1 : TP_HVY(����������))
	RendererPartType											PartType_;														// ���� Ÿ��
	std::string													TextureName_;													// ���� �ؽ��ĸ�
	std::string													AnimationName_;													// ���� �ִϸ��̼Ǹ�
};

// �÷��̾� ���⺰ ��������
struct UnderChangeZOrder
{
	int															StartIndex_;				// �ִϸ��̼� ���� ���� �ε���
	int															EndIndex_;					// �ִϸ��̼� ���� ���� �ε���
	int															DirectZOrder_;				// �ִϸ��̼� ���� �⺻ ������ Z����
};

struct PlayerZOrderManagement
{
	// �ִϸ��̼� ������ Z������ ����Ǿ���ϴ��� �˻�
	bool														UnderChangeZOrderFlag_;		// �ִϸ��̼� ������ Z���� �������� Flag(true : �����ʿ�)
	int															UnderChangeZOrderCnt_;		// �ִϸ��̼� ������ Z������ ����Ǵ� ī��Ʈ
	std::vector<UnderChangeZOrder>								UnderChange1_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index
	std::vector<UnderChangeZOrder>								UnderChange2_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index
	std::vector<UnderChangeZOrder>								UnderChange3_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index
	std::vector<UnderChangeZOrder>								UnderChange4_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index
	std::vector<UnderChangeZOrder>								UnderChange5_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index

	std::vector<UnderChangeZOrder>								DefaultDirectZOrder_;		// �⺻ ������ ZOrder
};

// �з� : �÷��̾�
// �뵵 : 
// ���� : ������ ���� ������ �ٸ�
class BottomStateBar;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
#pragma region PlayerFlag
private: // �÷��̾���°��� Flag
	bool IsTown_;											// ����/�ʵ� ���� ����(true : ����)
	bool IsRun_;											// �ٱ�/�ȱ� ���� ����(true : �ٱ����(���¹̳� �Ҹ�))
	bool IsInventory_;										// �κ��丮 Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsStateView_;										// ����â Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� ������ �̵��������� ���� �Ұ�
	bool IsSkillView_;										// ��ųâ Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsRightSkillList_;									// ������ ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsLeftSkillList_;									// ���� ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsStorehouse_;										// â�� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ�Ǹ�, ���ÿ� �κ��丮 Ȱ��ȭ - ȭ�� ��ü�� �̵��������� ���� �Ұ�

private: // �÷��̾� �̵����� Flag
	bool IsMove_;											// ���� �÷��̾� ��ǥ���� �̵� ��
	
private: // �÷��̾� ������������� Flag
	std::map<RendererPartType, bool> IsItemEquipState_;		// �� ������ ������ ������� Flag
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� �Ӹ��κп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// �尩 ���뿩�� Flag(true : ����) - �κ��丮â�� �尩�κп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// �尩 ���뿩�� Flag(true : ����) - �κ��丮â�� �尩�κп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� ���ʺκп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� ���ʺκп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� ���ʺκп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� �����κп� ������ Ȱ��ȭ(HVY_���°��ȴ�.)
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� ����κп� ������ Ȱ��ȭ(HVY_���°��ȴ�.) - �����ʹ���
															// ���� ���뿩�� Flag(true : ����) - �κ��丮â�� ���кκп� ������ Ȱ��ȭ(HVY_���°��ȴ�.) - ���ʹ���
#pragma endregion

#pragma region PlayerFSMState
private: // FSM
	GameEngineFSM<MainPlayer> State_;
#pragma endregion

#pragma region PlayerRenderer
private: // �÷��̾� ������ �ִϸ��̼Ƿ�����
	std::vector<PlayerRendererPart> PartRenderer_;

private: // �÷��̾� ���º� ��������
	std::vector<PlayerZOrderManagement> DirectRenderOrder_[static_cast<int>(PlayerState::STAT_MAX)];
#pragma endregion

#pragma region PlayerFloatValue
private: // �÷��̾� ������ ũ��
	float4 RenderSize_;

private: // �̵� ��ǥ ����
	float4 MoveTargetPos_;
#pragma endregion

#pragma region PlayerDirectAndState
private: // �̵�����
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

private: // ����
	PlayerState PrevState_;
	PlayerState CurState_;
#pragma endregion

#pragma region PlayerUI
private: // �÷��̾� UI
	BottomStateBar* BottomStateBar_;

private:

#pragma endregion

#pragma region PlayerOverrideFunction
private:
	void Start() override;
	void Update(float _DeltaTime) override;
#pragma endregion

#pragma region MainPlayerBasicFunction
public:
	MainPlayer();
	~MainPlayer();

protected:		// delete constructer
	MainPlayer(const MainPlayer& _other) = delete;
	MainPlayer(MainPlayer&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer& operator=(const MainPlayer& _other) = delete;
	MainPlayer& operator=(const MainPlayer&& _other) = delete;
#pragma endregion

#pragma region InitPlayer
private: // �÷��̾� �ʱⰪ ������ ���� �ʱ�ȭ
	void MainPlayerinitialization();
	void MainPlayerStartSetting();
	
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

private: // FSM ���� �� �����̸� 
	void CreatePlayerStateFSM();					// FSM ���� ����

private:
	void CreateDirectRenderOrderType();				// �÷��̾� �̵����⺰ �������� Ÿ�� ����

private:
	void SettingRender();							// �ʱ� ������ ���ð���
#pragma endregion

#pragma region KeyCheck
private:
	void PlayerUIActiveKeyCheck();
#pragma endregion

#pragma region ChangeState
private: // ���� ó�� ����
	bool MoveDirectCheck(const float4& _MousePos);
	void MoveStart();

private: // FSM ó������
	void ChangeCheckProcess();						// ���� ������ üũ���� ó��
	void ChangeFSMState(std::string _StateName);	// ���� ����

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

private: // �ִϸ��̼� �������
	void ChangeAnimation(const std::string& _CurStateName);
	bool ItemEquipCheck(std::string& _AnimationName, RendererPartType _PartType);
	bool RnderPartType(std::string& _AnimationName, RendererPartType _PartType);
	bool RenderDirectCheck(std::string& _AnimationName);

private: // ZOrder �������
	void ChangeZOrderType(int _Index, ItemEquipState _ItemEquipType);
#pragma endregion

#pragma region ItemPutOnAndOffFunction
private: // ������ ���� / ������ ����
	ItemEquipState CheckItemEquip(RendererPartType _PlayerPart);
	void ItemPutOn(ItemEquipPart _ItemPart);
	void ItemPutOff(ItemEquipPart _ItemPart);
#pragma endregion

};

