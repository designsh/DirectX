#pragma once

// 직업타입
enum class JobType
{
	None = -1,
	Necromancer = 0,		// 네크로맨서
	Amazon,						// 아마존
	Sorceress,						// 소서리스
	Barbarian,						// 바바리안
	Paladin,							// 팔라딘
	MAX
};

// 아이템타입
enum class ItemType
{
	Weapon,						// 무기
	Shield,							// 방패 
	Helm,								// 투구
	Armor,							// 갑옷
	Gloves,							// 장갑
	Belt,								// 벨트
	Boots,							// 신발
	Ring,								// 반지
	Amulet,							// 목걸이
	Portion,							// 포션
	Scroll,								// 스크롤
	Etc,									// 기타
};

// 아이템 위치타입
enum class ItemLocType
{
	Inven_Weapon,			// 인벤토리 - 무기칸
	Inven_Shield,				// 인벤토리 - 방패칸
	Inven_Helm,					// 인벤토리 - 투구칸
	Inven_Armor,				// 인벤토리 - 갑옷칸
	Inven_Gloves,				// 인벤토리 - 장갑칸
	Inven_Belt,					// 인벤토리 - 벨트칸
	Inven_Boots,				// 인벤토리 - 신발칸
	Inven_LRing,				// 인벤토리 - 왼쪽 반지칸
	Inven_RRing,				// 인벤토리 - 오른쪽 반지칸
	Inven_Amulet,				// 인벤토리 - 목걸이칸
	Inven_Bottom,			// 인벤토리 - 하단칸
	BotStat_Portion1,		// 하단상태바 포션 첫번째칸
	BotStat_Portion2,		// 하단상태바 포션 두번째칸
	BotStat_Portion3,		// 하단상태바 포션 세번째칸
	BotStat_Portion4,		// 하단상태바 포션 네번째칸
	Storehouse_Bottom,	// 창고 - 하단칸
	BuySell_Weapon,		// 판매창 - 무기탭
	BuySell_Armor,			// 판매창 - 방어구탭
	BuySell_Etc,					// 판매창 - 기타탭
};

// 스킬타입
enum class SkillType
{
	None,								// 제한없음((Ex) FireBall))
	Range,							// 원거리만
	H2H,								// 근접공격만
	Both								// 근접 or 원거리
};

// 디버프 타입(저주스킬 or 소환수스킬)
enum class SkillDebuffType
{
	Poisoned,						// 중독 : 회복량 50% 감소
	Burning,						// 화상 : 초당 n데미지
	Bleeding,						// 출혈 : 초당 n데미지
	BlurredVision,				// 시야감소 : 일정시야반경 감소
	SpeedReduction,		// 속력감소 : 이동속도 감소
	Damage,						// 데미지감소
	BounceOffDamage,	// 데미지반환 : 적에게 입힌피해 반환
	Terror,							// 공포 : 공포에 떨며 도망
	Confusion,					// 혼란 : 공격대상이 플레이어에서 무작위로 변경(가장가까운위치에 존재한 물체)
	LowerResist,					// 저항력감소 : 모든 저항력을 감소
};

enum class SkillBuffType
{
	AmplifyDamage,			// 데미지 증폭
	LifeTap,							// 적에게 받은 데미지 생명력으로 전환하여 회복
};

// 패시브 타입(소환수스킬)
enum class SkillPassiveType
{
	Skeleton,						// 스켈텔론 마스터리 : 소환수 스켈텔론류의 라이프, 방어력, 데미지를 증가
	Golem,							// 골렘 마스터리 : 소환수 골렘류의 라이프, 이동속도, 공격등급을 증가
	SummonResist,			// 소환수저항 : 소환수의 모든 속성 저항력을 증가
};

struct ItemList
{
	// ============================== 플레이어 아이템정보 ============================== //
	// 아이템 기본정보
	std::string							ItemName_Eng;						// 아이템 영어명
	std::wstring						ItemName_Kor;						// 아이템 한글명
	int										ItemCode;									// 아이템코드
	ItemType							ItemType;									// 아이템타입

	// 아이템 장착정보
	ItemLocType						ItemLocType;							// 아이템위치(인벤토리, 하단상태바, 창고, 판매창)
	int										StartPosition;							// 각각의 창에서 시작하는 위치의 인덱스
	int										WidthSize;								// 아이템넓이 -> 이벤토리 or 창고 or 판매창에서 차지하는 너비칸수
	int										HeightSize;								// 아이템높이 -> 이벤토리 or 창고 or 판매창에서 차지하는 높이칸수

	// 아이템 상세정보
	bool									IsDurability;								// 내구도 사용여부 판단(TRUE : 내구도사용)
	int										MaxDurability;							// 최대 내구도
	int										CurDurability;							// 현재 내구도
	
	int										Block;											// 피격차단확률
	int										Weight;										// 아이템무게(플레이어 이동속도 감소)
	int										Price;											// 아이템 비용(판매창에서 판매하는 비용)
	int										PullDamage;							// 아이템 장착시 증가공격력
	int										PullArmor;								// 아이템 장착시 증가방어력

	int										Recovery;									// 회복량(포션용) : 퍼센트
};

struct SkillList
{
	// =============================== 플레이어 스킬정보 =============================== //
	// 플레이어 스킬 기본정보
	std::string							SkillName;									// 스킬 영어명
	int										SkillCode;									// 스킬코드
	SkillType							SkillType;									// 스킬타입

	int										SkillPage;									// 플레이어 스킬창의 속한 페이지 No
	int										SkillRow;									// 플레이어 스킬창의 속한 페이지의 Row
	int										SkillColumn;								// 플레이어 스킬창의 속한 페이지의 Column

	int										reqSkillLevel;							// 해당 스킬 활성화 조건(스킬레벨)
	std::string							reqSkillName1;						// 해당 스킬 활성화 조건(선행스킬이름)
	int										reqSkillCode1;							// 해당 스킬 활성화 조건(선행스킬코드)
	std::string							reqSkillName2;						// 해당 스킬 활성화 조건(선행스킬이름)
	int										reqSkillCode2;							// 해당 스킬 활성화 조건(선행스킬코드)
	std::string							reqSkillName3;						// 해당 스킬 활성화 조건(선행스킬이름)
	int										reqSkillCode3;							// 해당 스킬 활성화 조건(선행스킬코드)

	int										MaxSkillLevel;							// 최대 스킬레벨
	int										CurSkillLevel;							// 현재 스킬레벨

	// 플레이어 스킬 상세정보(판단용 Flag)
	bool									SkillActive;								// 스킬사용가능여부(초기에 0번스킬인 일반공격만 TRUE 상태)
	bool									LineOfSight;								// 벽을 넘을수있는 스킬인지 판단(TURE : 벽통과가능)
	bool									Interrupt;									// 스킬 시전중 플레이어가 피격상태가 되면 해당 스킬시전이 취소되는지 판단(TRUE : 취소됨)
	bool									InTown;										// 마을내에서 사용가능한 스킬인지 판단(TRUE : 마을내 사용가능)
	bool									IsPassive;									// 해당 스킬이 패시브 스킬인지 판단(TRUE : 패시브스킬로 판단) - 플레이어 버프용
	bool									IsDebuff;									// 해당 스킬이 디버프 스킬인지 판단(TRUE : 디버프스킬) - 몬스터 디버프용
	bool									ManaUse;									// 해당 스킬 사용시 마나소모여부 판단(TRUE : 마나소모함)
	bool									LeftSkillUse;								// 왼쪽무기에 장착가능한 스킬인지 판단(TRUE : 사용가능)
	bool									IsSelDead;									// 해당 스킬이 몬스터 시체에 시전가능한 스킬인지 판단(TRUE : 시전가능) - 소환수 스킬전용

	// IsPassive = TURE 일때 사용
	SkillPassiveType				PassiveType;								// 패시브 타입
	int										PassiveLifePerLevel;				// 스킬레벨당 라이프 증가량
	int										PassiveBonusLifePerLevel;	// 스킬레벨당 보너스 라이프 증가량(시체로 선택된 몬스터의 본래체력의 퍼센트 : 100% 기준)
	int										PassiveVelocityPerLevel;		// 스킬레벨당 이동속도 증가량(100% 기준)
	int										PassiveDamagePerLevel;		// 스킬레벨당 데미지 증가량
	int										PassiveResistAllPerLevel;		// 스킬레벨당 모든속성 저항력 증가량(100% 기준)

	// IsDebuff = TRUE 일때 사용
	SkillDebuffType				DebuffType;								// 해당 스킬을 맞은 몬스터가 받는 디버프효과 타입
	SkillBuffType					BuffType;									// 해당 스킬시전시 플레이어가 받는 버프효과 타입
	int										DebuffDuration;						// 지속시간(1레벨값) - 100% 기준(값 / 100)
	int										DebuffDurationPerLevel;		// 스킬레벨당 디버프 지속시간 증가량 - 100% 기준(값 / 100)
	int										DebuffDamage;						// 디버프 타입의 데미지
	int										DebuffDamagePerLevel;		// 스킬레벨당 디버프 타입의 데미지 증가량

	// ManaUse = TURE일때 사용
	int										ManaUsage;							// 마나소모량

	// 
	int										SkillDamage;							// 스킬 데미지
	int										SkillDelay;									// 스킬 시전 딜레이시간
};

struct MainPlayerInfo
{
	// =============================== 플레이어 기본정보 =============================== //
	// 플레이어 기본정보(공통)
	std::string							ID;												// 캐릭터 생성시 입력한 ID
	JobType								JobType;									// 캐릭터 생성시 선택한 직업
	std::wstring						JobName;									// 선택한 직업의 한글명
	int										Level;											// 현재 레벨(생성시 1레벨 고정)
	int										Exp;											// 현재 경험치(생성시 0 고정)

	// 플레이어 시작 스킬정보(공통)
	int										LeftStartSkill;							// 캐릭터 생성시 SkillCode 0번 (일반공격) 고정 - LeftWeaponSkill(고정 - 사용안함)
	int										RightStartSkill;							// 캐릭터 생성시 SkillCode 0번 (일반공격) 고정 - RightWeaponSkill

	// 레벨업 당 포인트
	int										SkillPointsPerLevelUp;			// 레벨업당 스킬포인트(고정 - 3포인트)
	int										StatPointsPerLevelUp;			// 레벨업당 스탯포인트(고정 - 5포인트)

	// 플레이어 상세정보(JobType에 따라 다름)
	int										Strength;									// 힘
	int										Dexterity;									// 민첩
	int										Vitality;										// 생명력
	int										Energy;										// 에너지

	int										MinDamage;							// 공격데미지(최소)
	int										MaxDamage;							// 공격데미지(최대)
	int										AttackRating;							// 공격등급
	int										Defense;									// 방어
	int										Stamina;									// 스태미나
	int										Life;											// 라이프
	int										Mana;										// 마나
	int										FireResistance;							// 파이어 저항력
	int										ColdResistance;						// 콜드 저항력
	int										LightningResistance;				// 라이트닝 저항력
	int										PoisonResistance;					// 포이즌 저항력

	int										WalkVelocity;							// 걷기 속도
	int										RunVelocity;								// 뛰기 속도
	int										RunStaminaDrain;					// 뛰기상태(스태미나소모활성화)일때의 스태미나 소모량

	// 플레이어 스킬정보(JobType에 따라 다름)
	int										SkillInfoCnt;								// 스킬정보 갯수
	std::vector<SkillList>		SkillInfo;									// 스킬정보

	// 플레이어 아이템정보(초기 생성시 : 기본무기, 포탈스크롤, 아이템감정스크롤 고정)
	int										ItemInfoCnt;							// 보유 아이템정보 갯수
	std::vector<ItemList>		ItemInfo;									// 보유 아이템정보
};

class MainPlayerInfomation
{
private:
	static MainPlayerInfomation* Inst;

public:
	static MainPlayerInfomation& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	MainPlayerInfo MainPlayerInfo_;	// (플레이어 ID.txt 파일의 정보)
	
private:
	bool IsMainPlayerInfo_;	// 생성 조건 일치시 생성하면서 Flag On

private:
	MainPlayerInfomation();
	~MainPlayerInfomation();

protected:		// delete constructer
	MainPlayerInfomation(const MainPlayerInfomation& _other) = delete;
	MainPlayerInfomation(MainPlayerInfomation&& _other) noexcept = delete;

private:		//delete operator
	MainPlayerInfomation& operator=(const MainPlayerInfomation& _other) = delete;
	MainPlayerInfomation& operator=(const MainPlayerInfomation&& _other) = delete;

public:
	bool IsMainPlayerInfo() const
	{
		return IsMainPlayerInfo_;
	}

public:
	const MainPlayerInfo* GetMainPlayerInfoRef();
	MainPlayerInfo GetMainPlayerInfoValue() const;

public: // MainPlayerInfo Stat Infomation Update
	void PlayerLevelUP();
	void PlayerEXPUP();
	void PlayerStrengthStatUP();
	void PlayerDexterityStatUP();
	void PlayerVitalityStatUP();
	void PlayerEnergyStatUP();

public: // MainPlayer ItemInfo Update
	void PlayerItemAdd(ItemList _ItemInfo);
	void PlayerItemDel(const std::string& _ItemName);

public:
	void PlayerSkillLevelUP(const std::string& _SkillName);

public: // CreateMainPlayerInfo : 캐릭터생성화면에서 생성하여 해당 정보 파일로 저장한 후 생성
	void CreateMainPlayerInfo(const std::string& _PlayerID, JobType _JobType);					// 메인플레이어 정보 초기생성
	MainPlayerInfo InformationByClass(JobType _JobType);															// 클래스별 스탯정보 생성
	std::vector<SkillList> SkillInfoLoad(JobType _JobType);															// 해당 클래스의 스킬정보 로드

public: // MainPlayerInfo Save & Load
	void SaveMainPlayerInfo(const std::string& _PlayerID);
	void LoadMainPlayerInfo(const std::string& _PlayerID);
};
