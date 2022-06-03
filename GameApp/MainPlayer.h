#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "Navigation_Common.h"
#include "MainPlayerInfomation.h"

// �����ڷ� ��ȯ�� �ִ��
#define SummonsWarrior 20
#define SummonsWizard 20

#pragma region Player_Direct
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
#pragma endregion

#pragma region Player_State
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
#pragma endregion

#pragma region Player_ItemEquipState
// ������ �������
enum class ItemEquipState
{
	TP_LIT,
	TP_HVY,
	TP_MAX
};
#pragma endregion

#pragma region Player_RenderPartType
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
#pragma endregion

#pragma region Player_ItemEquipPart
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
#pragma endregion

#pragma region Player_PartRenderer
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
#pragma endregion

#pragma region Player_RendererZOrder
// �÷��̾� ���⺰ ��������
struct UnderChangeZOrder
{
	int															ChangeStartIndex_;			// �ִϸ��̼� ������ ����� ������ Z���� ���� ���������� �ε���
	int															ChangeEndIndex_;			// �ִϸ��̼� ������ ����� ������ Z���� ���� ���������� �ε���
	std::vector<int>											ChangeZOrder_;				// �ִϸ��̼� ������ ���� ������ Z����
};

struct PlayerZOrderManagement
{
	// �⺻ ZOrder
	int															DefaultStartIndex_;		// �⺻ ������ ZOrder�� �ִϸ��̼� ���� �ε���
	int															DefaultEndIndex_;		// �⺻ ������ ZOrder�� �ִϸ��̼� ���� �ε���
	std::vector<int>											DefaultZOrder_;			// �⺻ ������ ZOrder

	// ���� Zorder
	bool														UnderChangeZOrderFlag_;	// �ִϸ��̼� ������ Z���� �������� Flag(true : �����ʿ�)
	int															UnderChangeZOrderCnt_;	// �ִϸ��̼� ������ Z������ ����Ǵ� ī��Ʈ

	int															UnderChangeCurIndex_;	// ����Ǵ� ������ ���� �������� ZOrder Index(����ɶ����� �����ϸ�, ������ ���� ZOrder�� ������ �ʱ�ȭ�ȴ�)
	std::vector<UnderChangeZOrder>								UnderChangeZOrder_;		// ����Ǵ� ������ ZOrder(UnderChangeZOrderCnt_ ��ŭ �Ҵ�ȴ�.)
																						// ���¸� üũ�Ͽ� �ش� �ִϸ��̼� �������� �Ǹ� �ش� ZOrder�� ����
};
#pragma endregion

// �з� : �÷��̾�
// �뵵 : 
// ���� : ������ ���� ������ �ٸ�
class GameEngineSoundPlayer;
class BottomStateBar;
class StatView;
class SkillView;
class InventoryView;
class GameEndMenuView;
class GameEngineImageRenderer;
class GameEngineLevel;
class SummonsGolem;
class SketelonWarrior;
class SketelonWizard;
class MainPlayer : public GameEngineActor
{
public:
	static int ArrangeRoomNo_;
	static int CurLeftSkill_;								// ���� ���ʹ��� ��ų���
	static int CurRightSkill_;								// ���� �����ʹ��� ��ų���

private: // �������
	GameEngineSoundPlayer* SpeechSound_;					// ���� ����
	GameEngineSoundPlayer* StateSound_;						// ���� ����
	GameEngineSoundPlayer* ItemSound_;						// �����۰��� ����

#pragma region PlayerFlag
private: // �÷��̾���°��� Flag
	bool IsTown_;											// ����/�ʵ� ���� ����(true : ����)
	bool IsRun_;											// �ٱ�/�ȱ� ���� ����(true : �ٱ����(���¹̳� �Ҹ�))
	bool IsInventoryView_;									// �κ��丮 Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsStateView_;										// ����â Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� ������ �̵��������� ���� �Ұ�
	bool IsSkillView_;										// ��ųâ Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� ȭ��ũ�������� �������� �̵��������� ���� �Ұ�
	bool IsRightSkillList_;									// ������ ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� �����ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsLeftSkillList_;									// ���� ��ų��ư ��� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� �ϴ� ���ʿ� Ȱ��ȭ - Ȱ��ȭ�� Ȱ��ȭ�� ��Ϲ�ư�� ���콺 �浹�� �̵��������� �����Ұ�
	bool IsStorehouse_;										// â�� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ�� ���ʿ� Ȱ��ȭ�Ǹ�, ���ÿ� �κ��丮 Ȱ��ȭ - ȭ�� ��ü�� �̵��������� ���� �Ұ�
	bool IsGameEndMenu_;									// ��������޴� Ȱ��ȭ ����(true : Ȱ��ȭ) - ȭ����ü�� Ȱ��ȭ�Ǹ�, �÷��̾�� ��� ���� �Ұ�

private: // �÷��̾� �̵����� Flag
	bool IsMove_;											// ���� �÷��̾� ��ǥ���� �̵� ��

private: // �÷��̾� ZOrder ����üũ Flag
	bool IsDefaultZOrderChangeChk_;							// ���� �÷��̾� ����, ���⿡ ���� �⺻ ZOrder ���� Flag
	bool IsFrameZOrderChangeChk_;							// ���� �÷��̾� ����, ���⿡ ���� ������ ZOrder ����/���� üũ Flag
	
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

#pragma region ��ȯ��ų�� ��ȯ�� ��ȯ������
private:
	float4 SkillCastPos_;									// ��ų ���� ���콺 Ŭ������
	SummonsGolem* SummonsGolem_;							// ��(Ÿ�Կ� ������� 1���� �񷽸��� ��ȯ����)
	std::list<SketelonWarrior*> SummonsSketelonWarrior_;	// ���̷���(������) - �ִ� 20���� ��ȯ
	std::list<SketelonWizard*> SummonsSketelonWizard_;		// ���̷���(��������) - �ִ� 20���� ��ȯ

private:
	GameEngineCollision* DeathMonster_;						// ���� ��ü �浹
	GameEngineCollision* TargetMonster_;					// ���� Ÿ�� �浹

#pragma endregion

#pragma region GamePlay Player Basic Info
private:
	int CurHP_;												// �÷��̾� ���� ü��(100 ����)
	int CurMP_;												// �÷��̾� ���� ����(100 ����)

	int PrevEXP_;											// �÷��̾� ���� ����ġ
	int CurEXP_;											// �÷��̾� ���� ����ġ

	int PrevLevel_;											// �÷��̾� ���� ����
	int CurLevel_;											// �÷��̾� ���� ����

	int HaveGold_;											// �÷��̾� ���� ������差
#pragma endregion

#pragma region PlayerFSMState
private: // FSM
	GameEngineFSM State_;
#pragma endregion

#pragma region PlayerRenderer
private: // �÷��̾� ������ �ִϸ��̼Ƿ�����
	std::vector<PlayerRendererPart> PartRenderer_;

private: // �÷��̾� ���º� ��������
	std::vector<PlayerZOrderManagement> DirectRenderOrder_[static_cast<int>(PlayerState::STAT_MAX)];
#pragma endregion

#pragma region PlayerCollider
	GameEngineCollision* BodyCollider_;						// �÷��̾��� ��ü �浹ü(��Ż�̵�, �ǰ�����, ...)
#pragma endregion

#pragma region PlayerFloat4Value
private: // �÷��̾� ������ ũ��
	float4 RenderSize_;

private: // �̵� ��ǥ ����
	float4 PrevMoveTargetPos_;
	float4 CurMoveTargetPos_;
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
	BottomStateBar* BottomStateBar_;						// �ϴܻ��¹�
	StatView* StatView_;									// ����â
	SkillView* SkillView_;									// ��ųƮ��â
	InventoryView* InventoryView_;							// �κ��丮â
	GameEndMenuView* GameEndMenuView_;						// ��������޴�â
#pragma endregion

#pragma region PlayerMove
private:
	float MoveSpeed_;										// �÷��̾� �̵��ӵ�
	std::list<PathIndex> MovePath_;							// �÷��̾� ���� �̵����
	float4 MoveTargetDir_;									// ���� �̵������ �̵�����(�÷��̾� �̵��� ���Ͽ�)
	TileIndex MoveTargetIndex_;								// ���� �̵������ �̵���ǥŸ�� �ε���

#pragma endregion

#pragma region PlayerOverrideFunction
private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
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

#pragma region GetFunction
public: // ���� Flag ����
	bool GetIsTown() const;
	bool GetIsRun() const;
	bool GetIsMove() const;
	bool GetIsDefaultZOrderChangeChk() const;
	bool GetIsFrameZOrderChangeChk() const;

public: // ���°���
	int GetCurrentHP() const;
	int GetCurrentMP() const;
	int GetPrevEXP() const;
	int GetCurrentEXP() const;
	int GetPrevLevel() const;
	int GetCurrentLevel() const;
	int GetCurHaveGold() const;

public: // UI Flag���� 
	bool GetIsInventory() const;
	bool GetIsStateView() const;
	bool GetIsSkillView() const;
	bool GetIsRightSkillList() const;
	bool GetIsLeftSkillList() const;
	bool GetIsStorehouse() const;
	bool GetIsGameEndMenu() const;

public: // UI ��ü����
	BottomStateBar* GetBottomStateBar() const;
	StatView* GetStatView() const;
	SkillView* GetSkillView() const;
	InventoryView* GetInventoryView() const;
	GameEndMenuView* GetGameEndMenuView() const;
#pragma endregion

#pragma region SetFunction
public: // ���� Flag ����
	void SetIsTown(bool _Flag);
	void SetIsRun(bool _Flag);
	void SetIsMove(bool _Flag);
	void SetIsDefaultZOrderChangeChk(bool _Flag);
	void SetIsFrameZOrderChangeChk(bool _Flag);

public: // ���°���
	// HP
	void SetCurrentHP(int _HP);
	void DelCurrentHP(int _HP);
	void AddCurrentHP(int _HP);
	void AllCurrentHPRecovery();

	// MP
	void SetCurrentMP(int _MP);
	void DelCurrentMP(int _MP);
	void AddCurrentMP(int _MP);
	void AllCurrentMPRecovery();

	// EXP
	void SetPrevEXP(int _EXP);
	void SetCurrentEXP(int _EXP);
	void AddCurrentEXP(int _EXP);

	// LEVEL
	void SetPrevLevel(int _LEVEL);
	void SetCurrentLevel(int _LEVEL);
	void SetLevelUP();

public:
	void HaveGoldAdd(int _Gold);				// ��带 ȹ���ϰų� â���� �����ö� ȣ��
	void HaveGoldSub(int _Gold);				// ��带 �������ų� â�� �����Ҷ� ȣ��

public: // UI Flag���� 
	void SetIsInventory(bool _Flag);
	void SetIsStateView(bool _Flag);
	void SetIsSkillView(bool _Flag);
	void SetIsRightSkillList(bool _Flag);
	void SetIsLeftSkillList(bool _Flag);
	void SetIsIsStorehouse(bool _Flag);

#pragma endregion

#pragma region InitPlayer
private: // �÷��̾� �ʱⰪ ������ ���� �ʱ�ȭ
	void MainPlayerinitialization();
	void MainPlayerStartSetting();

private: // �÷��̾� �浹ü ��������
	void CreateCollision();
	
private: // �ؽ��� ���ð���(�÷��̾� �ִϸ��̼�)
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

private: // �ؽ��� ���ð���(�÷��̾� ��ȯ��)
	void AllSummonsAnimationCut();					// �÷��̾��� ��ȯ�� ��ü �ִϸ��̼ǿ� �ʿ��� ��� �ؽ��� ����ó��
	void SummonsGolemAnimationCut();				// �񷽰��� �ؽ��� ����
	void SummonsSkelWarriorAnimationCut();			// ���̷���(������) �ؽ��� ����
	void SummonsSkelWizardAnimationCut();			// ���̷���(��������) �ؽ��� ����
	void SummonsSkelWizardProjectileAnimationCut();	// ���̷���(��������)�� �߻�ü �ؽ��� ����

private: // �ؽ��� ���ð���(�÷��̾� ��ų)
	void AllSkillAnimationCut();					// �÷��̾��� ��ų ��ü �ִϸ��̼ǿ� �ʿ��� ��� �ؽ��� ����ó��
	void TeethAnimationCut();						// Teeth Cutting
	void PoisonNovaAnimationCut();					// PoisonNove Cutting
	void BoneSpiritAnimationCut();					// BoneSpirit Cutting

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

private: // Ư�� �ִϸ��̼� ������� ȣ���Լ� ���
	void SetAnimationEnd();
	void SetAttack1AnimationEnd();
	void SetAttack2AnimationEnd();
	void SetBlockAnimationEnd();
	void SetDeathAnimationEnd();
	void SetGetHitAnimationEnd();
	void SetKickAnimationEnd();
	void SetSkillAttackAnimationEnd();
	void SetSkillCastingAnimationEnd();

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
	bool PlayerUIActiveConditionCheck();
	void PlayerMoveKeyCheck();
	void PlayerSkillCastKeyCheck();
#pragma endregion

#pragma region ChangeState
private: // ���� ó�� ����
	bool MoveDirectCheck(const float4& _MousePos);
	void MoveStart(const float4& _MousePos);

private: // �浹 ó������
	void PlayerBodyCollision(GameEngineCollision* _Other);

private: // ZOrder ����ó�� ����
	void StateAndDirectChangeZOrder();
	bool DefaultZOrderEndFrameCheck(GameEngineImageRenderer* _Renderer, int _CheckFrame);
	void AnimationFrameCheckZOrderChange();
	void ZorderCheckChange();
	
private: // FSM ó������
	void ChangeCheckProcess();						// ���� ������ üũ���� ó��

public:
	void ChangeFSMState(std::string _StateName);	// ���� ����

private:
	// ========================== ���� ���� ========================== //
	void StartTownNatural();
	void UpdateTownNatural();
	void EndTownNatural();
	void StartTownWalk();
	void UpdateTownWalk();
	void EndTownWalk();

	// ========================== �ʵ� ���� ========================== //
	void StartFieldNatural();
	void UpdateFieldNatural();
	void EndFieldNatural();
	void StartFieldWalk();
	void UpdateFieldWalk();
	void EndFieldWalk();

	// ========================== ���� ���� ========================== //
	void StartAttack1();
	void UpdateAttack1();
	void EndAttack1();
	void StartAttack2();
	void UpdateAttack2();
	void EndAttack2();
	void StartBlock();
	void UpdateBlock();
	void EndBlock();
	void StartGetHit();
	void UpdateGetHit();
	void EndGetHit();
	void StartKick();
	void UpdateKick();
	void EndKick();
	void StartRun();
	void UpdateRun();
	void EndRun();
	void StartSkillAttack();
	void UpdateSkillAttack();
	void EndSkillAttack();
	void StartSkillCasting();
	void UpdateSkillCasting();
	void EndSkillCasting();

	// ========================== ��� ���� ========================== //
	void StartDead();
	void UpdateDead();
	void EndDead();
	void StartDeath();
	void UpdateDeath();
	void EndDeath();

private: // �ִϸ��̼� �������
	void ChangeAnimation(const std::string& _CurStateName);
	bool ItemEquipCheck(std::string& _AnimationName, RendererPartType _PartType);
	bool RnderPartType(std::string& _AnimationName, RendererPartType _PartType);
	bool RenderDirectCheck(std::string& _AnimationName);
#pragma endregion

#pragma region ItemPutOnAndOffFunction
public: // ������ ���� / ������ ����
	ItemEquipState CheckItemEquip(RendererPartType _PlayerPart);
	void ItemPutOn(ItemEquipPart _ItemPart);
	void ItemPutOff(ItemEquipPart _ItemPart);
	void WeaponOff();
#pragma endregion

#pragma region UI Process Function
public:
	void CreatePlayerUIInfomation();

public:
	void StateViewEnabled(bool _Enabled);
	void SkillViewEnabled(bool _Enabled);
	void InventoryViewEnabled(bool _Enabled);
	void GameEndMenuViewEnabled(bool _Enabled);

public:
	bool InventoryViewItemArrageCheckOn(const float4& _ItemScale, const std::string& _ItemName);
#pragma endregion

#pragma region �ִϸ��̼��������ȣ���Լ�
private:
	void Attack1AnimationEnd();
	void Attack2AnimationEnd();
	void BlockAnimationEnd();
	void DeathAnimationEnd();
	void GetHitAnimationEnd();
	void KickAnimationEnd();
	void SkillAttackAnimationEnd();
	void SkillCastingAnimationEnd();

#pragma endregion

#pragma region Object Active Check Function
private:
	void TownMapObjectCheck(const float4& _MousePos);
	void RandomMapObjectCheck(const float4& _MousePos);

#pragma endregion

#pragma region ��ȯ��ų
private:
	void GolemSummons();
	void SkeletonWarriorSummons();
	void SkeletonWizardSummons();

public:
	void SkeletonWarriorDeath(SketelonWarrior* _DeathWarrior);
	void SkeletonWizardDeath(SketelonWizard* _DeathWizard);

public:
	SummonsGolem* SummonsGolemTileCheck(TileIndex _CheckTile);
	SketelonWarrior* SummonsSkeletonWarriorTileCheck(TileIndex _CheckTile);
	SketelonWizard* SummonsSkeletonWizardTileCheck(TileIndex _CheckTile);

#pragma endregion

#pragma region ������&����ų
private:
	void TeethFire();
	void PoisonNoveFire();
	void BoneSpiritFire();

#pragma endregion

#pragma region ���ֽ�ų
private:


#pragma endregion

#pragma region ���� �� ���� ����
public: // ����
	void PlayerSpeechIcant();

public: // ������ ����/����
	void ItemEquipOnSound(const std::string& _ItemName);
	void ItemEquipOffSound();

public:
	void PortionDrink();

#pragma endregion
};

