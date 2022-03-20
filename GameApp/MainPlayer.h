#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

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

// 아이템 착용상태
enum class ItemEquipState
{
	TP_LIT,
	TP_HVY,
	TP_MAX
};

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

// 현재 플레이어의 부위별 아이템착용상태 체크를 위해
// 구조체로 렌더러를 관리한다.
class GameEngineImageRenderer;
struct PlayerRendererPart
{
	ItemEquipState												ItemEquipState_;												// 아이템 장착상태
	GameEngineImageRenderer*									Renderer_[static_cast<int>(ItemEquipState::TP_MAX)];			// 렌더러(0 : TP_LIT(기본), 1 : TP_HVY(아이템착용))
	RendererPartType											PartType_;														// 부위 타입
	std::string													TextureName_;													// 현재 텍스쳐명
	std::string													AnimationName_;													// 현재 애니메이션명
};

// 플레이어 방향별 렌더오더
struct PlayerAnimationRenderOrder
{
	std::vector<RendererPartType>								DefaultDirectRenderOrder_;	// 애니메이션실행 기본 렌더링 오더

	// 애니메이션 실행중 렌더링 오더가 변경는지 검사
	bool														ChangeRenderOrderFlag_;		// 애니메이션실행 중간에 렌더링오더가 변경되어야하는지
	int															ChangeRenderCount_;			// 애니메이션실행 중간에 렌더링오더가 변경되는 수

	int															ChangeStartIndex_;			// 렌더링 오더가 변경되는 시점의 인덱스
	int															ChangeEndIndex_;			// 렌더링 오더가 기본렌더링 오더로 돌아가는 시점의 인덱스
	std::vector<RendererPartType>								ChangeDirectRenderOrder_;	// 애니메이션 중간 변경되는 렌더링 오더

};

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 다름
class BottomStateBar;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private: // 플레이어관련 Flag
	bool IsTown_;						// 마을/필드 존재 여부(true : 마을)
	bool IsRun_;						// 뛰기/걷기 상태 여부(true : 뛰기상태(스태미나 소모))
	bool IsInventory_;					// 인벤토리 활성화 여부(true : 활성화) - 화면 오른쪽에 활성화 - 활성화시 화면크기절반의 오른쪽은 이동방향으로 설정 불가
	bool IsStateView_;					// 스탯창 활성화 여부(true : 활성화) - 화면 왼쪽에 활성화 - 활성화시 화면크기절반의 왼쪽은 이동방향으로 설정 불가
	bool IsSkillView_;					// 스킬창 활성화 여부(true : 활성화) - 화면 오른쪽에 활성화 - 활성화시 화면크기절반의 오른쪽은 이동방향으로 설정 불가
	bool IsRightSkillList_;				// 오른쪽 스킬버튼 목록 활성화 여부(true : 활성화) - 화면 하단 오른쪽에 활성화 - 활성화시 활성화된 목록버튼과 마우스 충돌시 이동방향으로 설정불가
	bool IsLeftSkillList_;				// 왼쪽 스킬버튼 목록 활성화 여부(true : 활성화) - 화면 하단 왼쪽에 활성화 - 활성화시 활성화된 목록버튼과 마우스 충돌시 이동방향으로 설정불가
	bool IsStorehouse_;					// 창고 활성화 여부(true : 활성화) - 화면 왼쪽에 활성화되며, 동시에 인벤토리 활성화 - 화면 전체를 이동방향으로 설정 불가

private: // FSM
	GameEngineFSM<MainPlayer> State_;

private: // 이동방향
	TargetDirect PrevDirect_;
	TargetDirect CurDirect_;

private:
	PlayerState PrevState_;
	PlayerState CurState_;
	std::vector<std::string> StateName_;

private: // 플레이어 UI
	BottomStateBar* BottomStateBar_;

private: // 플레이어 부위별 애니메이션렌더러
	std::vector<PlayerRendererPart> PartRenderer_;
	float4 PlayerSize_;

private: // 플레이어 방향별 렌더오더
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

private: // 텍스쳐 컷팅관련
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

private: // 애니메이션 생성관련
	void SetFirstAnimation();						// 최초 애니메이션 지정
	void SetRenderSize();							// 최초 렌더링크기 지정
	void SetFirstZOrder();							// 최초 Z오더 설정
	void SetFirstItemEquipState();					// 최초 렌더링하는 애니메이션타입 지정
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

private: // FSM 생성관련
	void CreatePlayerStateFSM();

private:
	void CreateDirectRenderOrderType();				// 플레이어 이동방향별 렌더오더 타입 생성
	void ChangeZOrderType(TargetDirect _Direct);	// 플레이어의 이동방향에 따라 렌더오더 타입 변경

private: // 상태가 바뀌면 애니메이션과 텍스쳐정보가 변경되어야하므로 SetImage()와 ChangeAnimation()이 동시에 수행되는 기능제공
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

private: // FSM 처리관련
	void ChangeFSMState(std::string _StateName);

	// ========================== 마을 관련 ========================== //
	StateInfo StartTownNatural(StateInfo _state);
	StateInfo UpdateTownNatural(StateInfo _state);
	StateInfo StartTownWalk(StateInfo _state);
	StateInfo UpdateTownWalk(StateInfo _state);

	// ========================== 필드 관련 ========================== //
	StateInfo StartFieldNatural(StateInfo _state);
	StateInfo UpdateFieldNatural(StateInfo _state);
	StateInfo StartFieldWalk(StateInfo _state);
	StateInfo UpdateFieldWalk(StateInfo _state);

	// ========================== 공통 관련 ========================== //
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

	// ========================== 사망 관련 ========================== //
	StateInfo StartDead(StateInfo _state);
	StateInfo UpdateDead(StateInfo _state);
	StateInfo StartDeath(StateInfo _state);
	StateInfo UpdateDeath(StateInfo _state);
};

