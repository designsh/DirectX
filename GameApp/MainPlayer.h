#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "Navigation_Common.h"
#include "MainPlayerInfomation.h"

// 스켈텔론 소환수 최대수
#define SummonsWarrior 20
#define SummonsWizard 20

#pragma region Player_Direct
// 플레이어는 총 8방향의 애니메이션을 소유한다.
// 그러므로 현재 플레이어의 위치와 마우스커서가 클릭한 위치의
// 각도를 계산하여 플레이어의 포커스방향을 결정한다.
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
// 애니메이션은 총 16방향의 애니메이션을 가지나,
// 게임내에서 8방향만 사용
enum class PlayerState
{
	STAT_A1,					// x : 19, y : 16 => 공격모션1
	STAT_A2,					// x : 19, y : 16 => 공격모션2
	STAT_BL,					// x :   6, y : 16 => 방어모션
	STAT_DD,					// x :   1, y : 16 => 시체모션
	STAT_DT,					// x : 27, y : 16 => 사망모션
	STAT_GH,					// x :   7, y : 16 => 피격모션
	STAT_KK,					// x : 12, y : 16 => 킥모션
	STAT_NU,					// x :   8, y : 16 => 필드_대기모션
	STAT_RN,					// x :   8, y : 16 => 뛰기모션
	STAT_S1,					// x : 16, y : 16 => 스킬공격모션
	STAT_SC,					// x : 16, y : 16 => 스킬캐스팅모션
	STAT_TN,					// x : 16, y : 16 => 마을_대기모션
	STAT_TW,					// x :   8, y : 16 => 마을_걷기모션
	STAT_WL,					// x :   8, y : 16 => 필드_걷기모션
	STAT_MAX,
};
#pragma endregion

#pragma region Player_ItemEquipState
// 아이템 착용상태
enum class ItemEquipState
{
	TP_LIT,
	TP_HVY,
	TP_MAX
};
#pragma endregion

#pragma region Player_RenderPartType
// 렌더러 부위별 타입
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
// 아이템 착용 부위
enum class ItemEquipPart
{
	Inv_Helm,		// 투구
	Inv_Armor,		// 갑옷
	Inv_LRing,		// 왼쪽 링
	Inv_RRing,		// 오른쪽 링
	Inv_Amulet,		// 목걸이
	Inv_Gloves,		// 장갑
	Inv_Boots,		// 부츠
	Inv_Weapon,		// 무기
	Inv_Shield,		// 방패
	Inv_MAX
};
#pragma endregion

#pragma region Player_PartRenderer
// 현재 플레이어의 부위별 아이템착용상태 체크를 위해
// 구조체로 렌더러를 관리한다.
class GameEngineImageRenderer;
struct PlayerRendererPart
{
	GameEngineImageRenderer*									Renderer_[static_cast<int>(ItemEquipState::TP_MAX)];			// 렌더러(0 : TP_LIT(기본), 1 : TP_HVY(아이템착용))
	RendererPartType											PartType_;														// 부위 타입
	std::string													TextureName_;													// 현재 텍스쳐명
	std::string													AnimationName_;													// 현재 애니메이션명
};
#pragma endregion

#pragma region Player_RendererZOrder
// 플레이어 방향별 렌더오더
struct UnderChangeZOrder
{
	int															ChangeStartIndex_;			// 애니메이션 실행중 변경된 렌더링 Z오더 적용 시작프레임 인덱스
	int															ChangeEndIndex_;			// 애니메이션 실행중 변경된 렌더링 Z오더 적용 종료프레임 인덱스
	std::vector<int>											ChangeZOrder_;				// 애니메이션 실행중 변경 렌더링 Z오더
};

struct PlayerZOrderManagement
{
	// 기본 ZOrder
	int															DefaultStartIndex_;		// 기본 렌더러 ZOrder의 애니메이션 시작 인덱스
	int															DefaultEndIndex_;		// 기본 렌더러 ZOrder의 애니메이션 종료 인덱스
	std::vector<int>											DefaultZOrder_;			// 기본 렌더러 ZOrder

	// 변경 Zorder
	bool														UnderChangeZOrderFlag_;	// 애니메이션 실행중 Z오더 변경유무 Flag(true : 변경필요)
	int															UnderChangeZOrderCnt_;	// 애니메이션 실행중 Z오더가 변경되는 카운트

	int															UnderChangeCurIndex_;	// 변경되는 렌더러 현재 적용중인 ZOrder Index(변경될때마다 증가하며, 마지막 변경 ZOrder가 끝날때 초기화된다)
	std::vector<UnderChangeZOrder>								UnderChangeZOrder_;		// 변경되는 렌더러 ZOrder(UnderChangeZOrderCnt_ 만큼 할당된다.)
																						// 상태를 체크하여 해당 애니메이션 프레임이 되면 해당 ZOrder로 갱신
};
#pragma endregion

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 다름
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
	static int CurLeftSkill_;								// 현재 왼쪽무기 스킬목록
	static int CurRightSkill_;								// 현재 오른쪽무기 스킬목록

private: // 사운드관련
	GameEngineSoundPlayer* SpeechSound_;					// 음성 사운드
	GameEngineSoundPlayer* StateSound_;						// 상태 사운드
	GameEngineSoundPlayer* ItemSound_;						// 아이템관련 사운드

#pragma region PlayerFlag
private: // 플레이어상태관련 Flag
	bool IsTown_;											// 마을/필드 존재 여부(true : 마을)
	bool IsRun_;											// 뛰기/걷기 상태 여부(true : 뛰기상태(스태미나 소모))
	bool IsInventoryView_;									// 인벤토리 활성화 여부(true : 활성화) - 화면 오른쪽에 활성화 - 활성화시 화면크기절반의 오른쪽은 이동방향으로 설정 불가
	bool IsStateView_;										// 스탯창 활성화 여부(true : 활성화) - 화면 왼쪽에 활성화 - 활성화시 화면크기절반의 왼쪽은 이동방향으로 설정 불가
	bool IsSkillView_;										// 스킬창 활성화 여부(true : 활성화) - 화면 오른쪽에 활성화 - 활성화시 화면크기절반의 오른쪽은 이동방향으로 설정 불가
	bool IsRightSkillList_;									// 오른쪽 스킬버튼 목록 활성화 여부(true : 활성화) - 화면 하단 오른쪽에 활성화 - 활성화시 활성화된 목록버튼과 마우스 충돌시 이동방향으로 설정불가
	bool IsLeftSkillList_;									// 왼쪽 스킬버튼 목록 활성화 여부(true : 활성화) - 화면 하단 왼쪽에 활성화 - 활성화시 활성화된 목록버튼과 마우스 충돌시 이동방향으로 설정불가
	bool IsStorehouse_;										// 창고 활성화 여부(true : 활성화) - 화면 왼쪽에 활성화되며, 동시에 인벤토리 활성화 - 화면 전체를 이동방향으로 설정 불가
	bool IsGameEndMenu_;									// 게임종료메뉴 활성화 여부(true : 활성화) - 화면전체에 활성화되며, 플레이어는 모든 동작 불가

private: // 플레이어 이동관련 Flag
	bool IsMove_;											// 현재 플레이어 목표지점 이동 중

private: // 플레이어 ZOrder 변경체크 Flag
	bool IsDefaultZOrderChangeChk_;							// 현재 플레이어 상태, 방향에 따른 기본 ZOrder 종료 Flag
	bool IsFrameZOrderChangeChk_;							// 현재 플레이어 상태, 방향에 따른 프레임 ZOrder 시작/종료 체크 Flag
	
private: // 플레이어 아이템착용관련 Flag
	std::map<RendererPartType, bool> IsItemEquipState_;		// 각 부위별 아이템 착용상태 Flag
															// 투구 착용여부 Flag(true : 착용) - 인벤토리창의 머리부분에 장착시 활성화(HVY_상태가된다.)
															// 장갑 착용여부 Flag(true : 착용) - 인벤토리창의 장갑부분에 장착시 활성화(HVY_상태가된다.)
															// 장갑 착용여부 Flag(true : 착용) - 인벤토리창의 장갑부분에 장착시 활성화(HVY_상태가된다.)
															// 갑옷 착용여부 Flag(true : 착용) - 인벤토리창의 갑옷부분에 장착시 활성화(HVY_상태가된다.)
															// 갑옷 착용여부 Flag(true : 착용) - 인벤토리창의 갑옷부분에 장착시 활성화(HVY_상태가된다.)
															// 갑옷 착용여부 Flag(true : 착용) - 인벤토리창의 갑옷부분에 장착시 활성화(HVY_상태가된다.)
															// 부츠 착용여부 Flag(true : 착용) - 인벤토리창의 부츠부분에 장착시 활성화(HVY_상태가된다.)
															// 무기 착용여부 Flag(true : 착용) - 인벤토리창의 무기부분에 장착시 활성화(HVY_상태가된다.) - 오른쪽무기
															// 방패 착용여부 Flag(true : 착용) - 인벤토리창의 방패부분에 장착시 활성화(HVY_상태가된다.) - 왼쪽무기
#pragma endregion

#pragma region 소환스킬로 소환된 소환수관련
private:
	float4 SkillCastPos_;									// 스킬 시전 마우스 클릭지점
	SummonsGolem* SummonsGolem_;							// 골렘(타입에 관계없이 1개의 골렘만을 소환가능)
	std::list<SketelonWarrior*> SummonsSketelonWarrior_;	// 스켈레톤(전사형) - 최대 20마리 소환
	std::list<SketelonWizard*> SummonsSketelonWizard_;		// 스켈레톤(마법사형) - 최대 20마리 소환

private:
	GameEngineCollision* DeathMonster_;						// 몬스터 시체 충돌
	GameEngineCollision* TargetMonster_;					// 몬스터 타겟 충돌

#pragma endregion

#pragma region GamePlay Player Basic Info
private:
	int CurHP_;												// 플레이어 현재 체력(100 기준)
	int CurMP_;												// 플레이어 현재 마력(100 기준)

	int PrevEXP_;											// 플레이어 이전 경험치
	int CurEXP_;											// 플레이어 현재 경험치

	int PrevLevel_;											// 플레이어 이전 레벨
	int CurLevel_;											// 플레이어 현재 레벨

	int HaveGold_;											// 플레이어 현재 보유골드량
#pragma endregion

#pragma region PlayerFSMState
private: // FSM
	GameEngineFSM State_;
#pragma endregion

#pragma region PlayerRenderer
private: // 플레이어 부위별 애니메이션렌더러
	std::vector<PlayerRendererPart> PartRenderer_;

private: // 플레이어 상태별 렌더오더
	std::vector<PlayerZOrderManagement> DirectRenderOrder_[static_cast<int>(PlayerState::STAT_MAX)];
#pragma endregion

#pragma region PlayerCollider
	GameEngineCollision* BodyCollider_;						// 플레이어의 몸체 충돌체(포탈이동, 피격판정, ...)
#pragma endregion

#pragma region PlayerFloat4Value
private: // 플레이어 렌더링 크기
	float4 RenderSize_;

private: // 이동 목표 지점
	float4 PrevMoveTargetPos_;
	float4 CurMoveTargetPos_;
#pragma endregion

#pragma region PlayerDirectAndState
private: // 이동방향
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

private: // 상태
	PlayerState PrevState_;
	PlayerState CurState_;
#pragma endregion

#pragma region PlayerUI
private: // 플레이어 UI
	BottomStateBar* BottomStateBar_;						// 하단상태바
	StatView* StatView_;									// 상태창
	SkillView* SkillView_;									// 스킬트리창
	InventoryView* InventoryView_;							// 인벤토리창
	GameEndMenuView* GameEndMenuView_;						// 게임종료메뉴창
#pragma endregion

#pragma region PlayerMove
private:
	float MoveSpeed_;										// 플레이어 이동속도
	std::list<PathIndex> MovePath_;							// 플레이어 현재 이동경로
	float4 MoveTargetDir_;									// 현재 이동경로의 이동방향(플레이어 이동을 위하여)
	TileIndex MoveTargetIndex_;								// 현재 이동경로의 이동목표타일 인덱스

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
public: // 상태 Flag 관련
	bool GetIsTown() const;
	bool GetIsRun() const;
	bool GetIsMove() const;
	bool GetIsDefaultZOrderChangeChk() const;
	bool GetIsFrameZOrderChangeChk() const;

public: // 상태관련
	int GetCurrentHP() const;
	int GetCurrentMP() const;
	int GetPrevEXP() const;
	int GetCurrentEXP() const;
	int GetPrevLevel() const;
	int GetCurrentLevel() const;
	int GetCurHaveGold() const;

public: // UI Flag관련 
	bool GetIsInventory() const;
	bool GetIsStateView() const;
	bool GetIsSkillView() const;
	bool GetIsRightSkillList() const;
	bool GetIsLeftSkillList() const;
	bool GetIsStorehouse() const;
	bool GetIsGameEndMenu() const;

public: // UI 객체관련
	BottomStateBar* GetBottomStateBar() const;
	StatView* GetStatView() const;
	SkillView* GetSkillView() const;
	InventoryView* GetInventoryView() const;
	GameEndMenuView* GetGameEndMenuView() const;
#pragma endregion

#pragma region SetFunction
public: // 상태 Flag 관련
	void SetIsTown(bool _Flag);
	void SetIsRun(bool _Flag);
	void SetIsMove(bool _Flag);
	void SetIsDefaultZOrderChangeChk(bool _Flag);
	void SetIsFrameZOrderChangeChk(bool _Flag);

public: // 상태관련
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
	void HaveGoldAdd(int _Gold);				// 골드를 획득하거나 창고에서 꺼내올때 호출
	void HaveGoldSub(int _Gold);				// 골드를 내려놓거나 창고에 저장할때 호출

public: // UI Flag관련 
	void SetIsInventory(bool _Flag);
	void SetIsStateView(bool _Flag);
	void SetIsSkillView(bool _Flag);
	void SetIsRightSkillList(bool _Flag);
	void SetIsLeftSkillList(bool _Flag);
	void SetIsIsStorehouse(bool _Flag);

#pragma endregion

#pragma region InitPlayer
private: // 플레이어 초기값 설정을 위한 초기화
	void MainPlayerinitialization();
	void MainPlayerStartSetting();

private: // 플레이어 충돌체 생성관련
	void CreateCollision();
	
private: // 텍스쳐 컷팅관련(플레이어 애니메이션)
	void AllAnimationCut();							// 플레이어의 전체 애니메이션에 필요한 모든 텍스쳐 컷팅처리
	void AnimationA1Cut();							// 공격모션1
	void AnimationA2Cut();							// 공격모션2
	void AnimationBLCut();							// 방어모션
	void AnimationDDCut();							// 시체모션
	void AnimationDTCut();							// 사망모션
	void AnimationGHCut();							// 피격모션
	void AnimationKKCut();							// 킥모션
	void AnimationNUCut();							// 필드_대기모션
	void AnimationRNCut();							// 뛰기모션
	void AnimationS1Cut();							// 스킬공격모션
	void AnimationSCCut();							// 스킬캐스팅모션
	void AnimationTNCut();							// 마을_대기모션
	void AnimationTWCut();							// 마을_걷기모션
	void AnimationWLCut();							// 필드_걷기모션

private: // 텍스쳐 컷팅관련(플레이어 소환수)
	void AllSummonsAnimationCut();					// 플레이어의 소환수 전체 애니메이션에 필요한 모든 텍스쳐 컷팅처리
	void SummonsGolemAnimationCut();				// 골렘관련 텍스쳐 컷팅
	void SummonsSkelWarriorAnimationCut();			// 스켈레톤(전사형) 텍스쳐 컷팅
	void SummonsSkelWizardAnimationCut();			// 스켈레톤(마법사형) 텍스쳐 컷팅
	void SummonsSkelWizardProjectileAnimationCut();	// 스켈레톤(마법사형)의 발사체 텍스쳐 컷팅

private: // 텍스쳐 컷팅관련(플레이어 스킬)
	void AllSkillAnimationCut();					// 플레이어의 스킬 전체 애니메이션에 필요한 모든 텍스쳐 컷팅처리
	void TeethAnimationCut();						// Teeth Cutting
	void PoisonNovaAnimationCut();					// PoisonNove Cutting
	void BoneSpiritAnimationCut();					// BoneSpirit Cutting

private: // 애니메이션 생성관련
	void CreateAnimation();							// 플레이어의 전체 애니메이션 모두 생성
	void CreateA1Animation();						// 공격모션1
	void CreateA2Animation();						// 공격모션2
	void CreateBLAnimation();						// 방어모션
	void CreateDDAnimation();						// 시체모션
	void CreateDTAnimation();						// 사망모션
	void CreateGHAnimation();						// 피격모션
	void CreateKKAnimation();						// 킥모션
	void CreateNUAnimation();						// 필드_대기모션
	void CreateRNAnimation();						// 뛰기모션
	void CreateS1Animation();						// 스킬공격모션
	void CreateSCAnimation();						// 스킬캐스팅모션
	void CreateTNAnimation();						// 마을_대기모션
	void CreateTWAnimation();						// 마을_걷기모션
	void CreateWLAnimation();						// 필드_걷기모션

private: // 특정 애니메이션 종료시점 호출함수 등록
	void SetAnimationEnd();
	void SetAttack1AnimationEnd();
	void SetAttack2AnimationEnd();
	void SetBlockAnimationEnd();
	void SetDeathAnimationEnd();
	void SetGetHitAnimationEnd();
	void SetKickAnimationEnd();
	void SetSkillAttackAnimationEnd();
	void SetSkillCastingAnimationEnd();

private: // FSM 생성 및 상태이름 
	void CreatePlayerStateFSM();					// FSM 상태 생성

private:
	void CreateDirectRenderOrderType();				// 플레이어 이동방향별 렌더오더 타입 생성

private:
	void SettingRender();							// 초기 렌더링 셋팅관련
#pragma endregion

#pragma region KeyCheck
private:
	void PlayerUIActiveKeyCheck();
	bool PlayerUIActiveConditionCheck();
	void PlayerMoveKeyCheck();
	void PlayerSkillCastKeyCheck();
#pragma endregion

#pragma region ChangeState
private: // 방향 처리 관련
	bool MoveDirectCheck(const float4& _MousePos);
	void MoveStart(const float4& _MousePos);

private: // 충돌 처리관련
	void PlayerBodyCollision(GameEngineCollision* _Other);

private: // ZOrder 변경처리 관련
	void StateAndDirectChangeZOrder();
	bool DefaultZOrderEndFrameCheck(GameEngineImageRenderer* _Renderer, int _CheckFrame);
	void AnimationFrameCheckZOrderChange();
	void ZorderCheckChange();
	
private: // FSM 처리관련
	void ChangeCheckProcess();						// 상태 변경전 체크사항 처리

public:
	void ChangeFSMState(std::string _StateName);	// 상태 변경

private:
	// ========================== 마을 관련 ========================== //
	void StartTownNatural();
	void UpdateTownNatural();
	void EndTownNatural();
	void StartTownWalk();
	void UpdateTownWalk();
	void EndTownWalk();

	// ========================== 필드 관련 ========================== //
	void StartFieldNatural();
	void UpdateFieldNatural();
	void EndFieldNatural();
	void StartFieldWalk();
	void UpdateFieldWalk();
	void EndFieldWalk();

	// ========================== 공통 관련 ========================== //
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

	// ========================== 사망 관련 ========================== //
	void StartDead();
	void UpdateDead();
	void EndDead();
	void StartDeath();
	void UpdateDeath();
	void EndDeath();

private: // 애니메이션 변경관련
	void ChangeAnimation(const std::string& _CurStateName);
	bool ItemEquipCheck(std::string& _AnimationName, RendererPartType _PartType);
	bool RnderPartType(std::string& _AnimationName, RendererPartType _PartType);
	bool RenderDirectCheck(std::string& _AnimationName);
#pragma endregion

#pragma region ItemPutOnAndOffFunction
public: // 아이템 착용 / 아이템 해제
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

#pragma region 애니메이션종료시점호출함수
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

#pragma region 소환스킬
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

#pragma region 포이즌&본스킬
private:
	void TeethFire();
	void PoisonNoveFire();
	void BoneSpiritFire();

#pragma endregion

#pragma region 저주스킬
private:


#pragma endregion

#pragma region 사운드 및 음성 관련
public: // 음성
	void PlayerSpeechIcant();

public: // 아이템 장착/해제
	void ItemEquipOnSound(const std::string& _ItemName);
	void ItemEquipOffSound();

public:
	void PortionDrink();

#pragma endregion
};

