#include "PreCompile.h"
#include "MainPlayerInfomation.h"

#include "AllSkillInfomation.h"

MainPlayerInfomation* MainPlayerInfomation::Inst = new MainPlayerInfomation();

MainPlayerInfomation::MainPlayerInfomation() :
	MainPlayerInfo_{},
	IsMainPlayerInfo_(false)
{
}

MainPlayerInfomation::~MainPlayerInfomation()
{
}

const MainPlayerInfo* MainPlayerInfomation::GetMainPlayerInfoRef()
{
	return &MainPlayerInfo_;
}

MainPlayerInfo MainPlayerInfomation::GetMainPlayerInfoValue() const
{
	return MainPlayerInfo_;
}

void MainPlayerInfomation::PlayerLevelUP()
{
	++MainPlayerInfo_.Level;
}

void MainPlayerInfomation::PlayerEXPUP()
{
	MainPlayerInfo_.Exp += 1;
}

void MainPlayerInfomation::PlayerStrengthStatUP()
{
	MainPlayerInfo_.Strength += 1;
}

void MainPlayerInfomation::PlayerDexterityStatUP()
{
	MainPlayerInfo_.Dexterity += 1;
}

void MainPlayerInfomation::PlayerVitalityStatUP()
{
	MainPlayerInfo_.Vitality += 1;
}

void MainPlayerInfomation::PlayerEnergyStatUP()
{
	MainPlayerInfo_.Energy += 1;
}

void MainPlayerInfomation::PlayerSkillLevelUp(int _SkillCode)
{
	int SkillCnt = static_cast<int>(MainPlayerInfo_.SkillInfo.size());
	for (int i = 0; i < SkillCnt; ++i)
	{
		if (MainPlayerInfo_.SkillInfo[i].SkillCode == _SkillCode)
		{
			MainPlayerInfo_.SkillInfo[i].CurSkillLevel += 1;
			break;
		}
	}
}

void MainPlayerInfomation::StrengthPointUP()
{
	MainPlayerInfo_.Strength += 1;
}

void MainPlayerInfomation::DexterityPointUP()
{
	MainPlayerInfo_.Dexterity += 1;
}

void MainPlayerInfomation::VitalityPointUP()
{
	MainPlayerInfo_.Vitality += 1;
}

void MainPlayerInfomation::EnergyPointUP()
{
	MainPlayerInfo_.Energy += 1;
}

void MainPlayerInfomation::PlayerItemAdd(ItemList _ItemInfo)
{
	// 동일한 아이템이 이미 있다면 정보만 교체
	for (auto& ItemList : MainPlayerInfo_.ItemInfo)
	{
		if (ItemList.ItemName_abbreviation == _ItemInfo.ItemName_abbreviation)
		{
			ItemList = _ItemInfo;
			return;
		}
	}

	// 신규 아이템이라면 보유목록에 추가
	MainPlayerInfo_.ItemInfo.push_back(_ItemInfo);
}

void MainPlayerInfomation::PlayerItemDel(const std::string& _ItemName)
{
	std::vector<ItemList>::iterator StartIter = MainPlayerInfo_.ItemInfo.begin();
	std::vector<ItemList>::iterator EndIter = MainPlayerInfo_.ItemInfo.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter).ItemName_abbreviation == _ItemName)
		{
			MainPlayerInfo_.ItemInfo.erase(StartIter);
			break;
		}
	}
}

void MainPlayerInfomation::PlayerSkillLevelUP(const std::string& _SkillName)
{
	std::vector<SkillList>::iterator StartIter = MainPlayerInfo_.SkillInfo.begin();
	std::vector<SkillList>::iterator EndIter = MainPlayerInfo_.SkillInfo.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter).SkillName == _SkillName)
		{
			(*StartIter).CurSkillLevel += 1;
		}
	}
}

bool MainPlayerInfomation::PlayerLeftSkillUseCheck(int _SkillCode)
{
	bool UseFlag = false;
	int SkillCnt = static_cast<int>(MainPlayerInfo_.SkillInfo.size());
	for (int i = 0; i < SkillCnt; ++i)
	{
		if (_SkillCode == MainPlayerInfo_.SkillInfo[i].SkillCode)
		{
			UseFlag = MainPlayerInfo_.SkillInfo[i].LeftSkillUse;
			break;
		}
	}

	return UseFlag;
}

void MainPlayerInfomation::CreateMainPlayerInfo(const std::string& _PlayerID, JobType _JobType)
{
	// 캐릭터생성화면에서 메인플레이어 정보를 생성
	IsMainPlayerInfo_ = true;

	// 클래스(직업)별 고유 정보를 생성
	MainPlayerInfo_ = InformationByClass(_JobType);

	MainPlayerInfo_.ID = _PlayerID;
	MainPlayerInfo_.Level = 1;
	MainPlayerInfo_.Exp = 0;

	// 플레이어 시작 스킬정보(공통)
	MainPlayerInfo_.LeftStartSkill = 0;
	MainPlayerInfo_.RightStartSkill = 0;

	// 레벨업 당 포인트
	MainPlayerInfo_.SkillPointsPerLevelUp = 3;
	MainPlayerInfo_.StatPointsPerLevelUp = 5;

	// ======================= 플레이어 스킬정보 ======================= //
	std::vector<SkillList> ResultSkillList;
	ResultSkillList = SkillInfoLoad(_JobType);
	MainPlayerInfo_.SkillInfo = ResultSkillList;
	MainPlayerInfo_.SkillInfoCnt = static_cast<int>(MainPlayerInfo_.SkillInfo.size());

	// ====================== 플레이어 아이템정보 ====================== //
	// 생성시 기본 생성되는 아이템(완드, 포탈스크롤, 아이템감정스크롤)
	
	// 완드 : 인벤토리 - 무기칸 장착
	ItemList BasicWeaponItem = {};
	BasicWeaponItem.ItemName_abbreviation = "wnd";
	BasicWeaponItem.ItemName_abbreviation_Inven = "invwnd";
	BasicWeaponItem.ItemCode = 1;
	BasicWeaponItem.ItemType = ItemType::Weapon;

	BasicWeaponItem.ItemLocType = ItemLocType::Inven_Weapon;
	BasicWeaponItem.StartPosition = 0;
	BasicWeaponItem.WidthSize = 1;
	BasicWeaponItem.HeightSize = 2;

	BasicWeaponItem.IsDurability = true;
	BasicWeaponItem.MaxDurability = 15;
	BasicWeaponItem.CurDurability = 15;

	BasicWeaponItem.Block = 0;
	BasicWeaponItem.Weight = 0;
	BasicWeaponItem.Price = 50;
	BasicWeaponItem.PullDamage = 100;
	BasicWeaponItem.PullArmor = 0;

	BasicWeaponItem.Recovery = 0;

	MainPlayerInfo_.ItemInfo.push_back(BasicWeaponItem);

	// 포탈스크롤 : 인벤토리 - 하단칸(10x4)의 9번째 인덱스 칸
	ItemList BasicPortalScroll = {};
	BasicPortalScroll.ItemName_abbreviation = "bsc";
	BasicPortalScroll.ItemName_abbreviation_Inven = "invbsc";
	BasicPortalScroll.ItemCode = 16;
	BasicPortalScroll.ItemType = ItemType::Scroll;

	BasicPortalScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicPortalScroll.StartPosition = 9;
	BasicPortalScroll.WidthSize = 1;
	BasicPortalScroll.HeightSize = 1;

	BasicPortalScroll.IsDurability = false;
	BasicPortalScroll.MaxDurability = 0;
	BasicPortalScroll.CurDurability = 0;

	BasicPortalScroll.Block = 0;
	BasicPortalScroll.Weight = 0;
	BasicPortalScroll.Price = 10;
	BasicPortalScroll.PullDamage = 0;
	BasicPortalScroll.PullArmor = 0;

	BasicPortalScroll.Recovery = 0;

	MainPlayerInfo_.ItemInfo.push_back(BasicPortalScroll);
	
	// 아이템감정스크롤 : 인벤토리 - 하단칸(10x4)의 19번째 인덱스 칸
	ItemList BasicIdentifyScroll = {};
	BasicIdentifyScroll.ItemName_abbreviation = "chm";
	BasicIdentifyScroll.ItemName_abbreviation_Inven = "invchm";
	BasicIdentifyScroll.ItemCode = 17;
	BasicIdentifyScroll.ItemType = ItemType::Scroll;

	BasicIdentifyScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicIdentifyScroll.StartPosition = 19;
	BasicIdentifyScroll.WidthSize = 1;
	BasicIdentifyScroll.HeightSize = 1;

	BasicIdentifyScroll.IsDurability = false;
	BasicIdentifyScroll.MaxDurability = 0;
	BasicIdentifyScroll.CurDurability = 0;

	BasicIdentifyScroll.Block = 0;
	BasicIdentifyScroll.Weight = 0;
	BasicIdentifyScroll.Price = 10;
	BasicIdentifyScroll.PullDamage = 0;
	BasicIdentifyScroll.PullArmor = 0;

	BasicIdentifyScroll.Recovery = 0;

	MainPlayerInfo_.ItemInfo.push_back(BasicIdentifyScroll);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// 테스트용 아이템
	//ItemList TestItem = {};
	//TestItem.ItemName_abbreviation = "chn";
	//TestItem.ItemName_abbreviation_Inven = "invchn";
	//TestItem.ItemCode = 7;
	//TestItem.ItemType = ItemType::Armor;

	//TestItem.ItemLocType = ItemLocType::Inven_Bottom;
	//TestItem.StartPosition = 0;
	//TestItem.WidthSize = 3;
	//TestItem.HeightSize = 3;

	//TestItem.IsDurability = false;
	//TestItem.MaxDurability = 0;
	//TestItem.CurDurability = 0;

	//TestItem.Block = 0;
	//TestItem.Weight = 0;
	//TestItem.Price = 10;
	//TestItem.PullDamage = 0;
	//TestItem.PullArmor = 0;

	//TestItem.Recovery = 0;

	//MainPlayerInfo_.ItemInfo.push_back(TestItem);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	MainPlayerInfo_.ItemInfoCnt = static_cast<int>(MainPlayerInfo_.ItemInfo.size());

	// 메인플레이어 정보 저장파일 최초 생성
	SaveMainPlayerInfo(_PlayerID);
}

MainPlayerInfo MainPlayerInfomation::InformationByClass(JobType _JobType)
{
	MainPlayerInfo CurPlayerInfo = {};

	// 플레이어 기본정보(공통)
	CurPlayerInfo.JobType = _JobType;
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			CurPlayerInfo.JobName = L"네크로맨서";

			CurPlayerInfo.Strength = 15;
			CurPlayerInfo.Dexterity = 25;
			CurPlayerInfo.Vitality = 25;
			CurPlayerInfo.Energy = 15;

			CurPlayerInfo.MinDamage = 2;
			CurPlayerInfo.MaxDamage = 4;
			CurPlayerInfo.AttackRating = 80;
			CurPlayerInfo.Defense = 6;
			CurPlayerInfo.Stamina = 79;
			CurPlayerInfo.Life = 45;
			CurPlayerInfo.Mana = 25;
			CurPlayerInfo.FireResistance = 0;
			CurPlayerInfo.ColdResistance = 0;
			CurPlayerInfo.LightningResistance = 0;
			CurPlayerInfo.PoisonResistance = 0;

			CurPlayerInfo.WalkVelocity = 300;
			CurPlayerInfo.RunVelocity = 500;
			CurPlayerInfo.RunStaminaDrain = 50;

			break;
		}
		case JobType::Sorceress:
		{
			CurPlayerInfo.JobName = L"소서리스";

			CurPlayerInfo.Strength = 10;
			CurPlayerInfo.Dexterity = 25;
			CurPlayerInfo.Vitality = 10;
			CurPlayerInfo.Energy = 35;

			CurPlayerInfo.MinDamage = 1;
			CurPlayerInfo.MaxDamage = 5;
			CurPlayerInfo.AttackRating = 75;
			CurPlayerInfo.Defense = 6;
			CurPlayerInfo.Stamina = 74;
			CurPlayerInfo.Life = 40;
			CurPlayerInfo.Mana = 35;
			CurPlayerInfo.FireResistance = 0;
			CurPlayerInfo.ColdResistance = 0;
			CurPlayerInfo.LightningResistance = 0;
			CurPlayerInfo.PoisonResistance = 0;

			CurPlayerInfo.WalkVelocity = 300;
			CurPlayerInfo.RunVelocity = 500;
			CurPlayerInfo.RunStaminaDrain = 50;

			break;
		}
		case JobType::Amazon:
		{
			CurPlayerInfo.JobName = L"아마존";

			CurPlayerInfo.Strength = 20;
			CurPlayerInfo.Dexterity = 25;
			CurPlayerInfo.Vitality = 20;
			CurPlayerInfo.Energy = 15;

			CurPlayerInfo.MinDamage = 1;
			CurPlayerInfo.MaxDamage = 6;
			CurPlayerInfo.AttackRating = 95;
			CurPlayerInfo.Defense = 10;
			CurPlayerInfo.Stamina = 84;
			CurPlayerInfo.Life = 50;
			CurPlayerInfo.Mana = 15;
			CurPlayerInfo.FireResistance = 0;
			CurPlayerInfo.ColdResistance = 0;
			CurPlayerInfo.LightningResistance = 0;
			CurPlayerInfo.PoisonResistance = 0;

			CurPlayerInfo.WalkVelocity = 300;
			CurPlayerInfo.RunVelocity = 500;
			CurPlayerInfo.RunStaminaDrain = 50;

			break;
		}
		case JobType::Barbarian:
		{
			CurPlayerInfo.JobName = L"바바리안";

			CurPlayerInfo.Strength = 30;
			CurPlayerInfo.Dexterity = 20;
			CurPlayerInfo.Vitality = 25;
			CurPlayerInfo.Energy = 10;

			CurPlayerInfo.MinDamage = 3;
			CurPlayerInfo.MaxDamage = 7;
			CurPlayerInfo.AttackRating = 85;
			CurPlayerInfo.Defense = 10;
			CurPlayerInfo.Stamina = 92;
			CurPlayerInfo.Life = 55;
			CurPlayerInfo.Mana = 10;
			CurPlayerInfo.FireResistance = 0;
			CurPlayerInfo.ColdResistance = 0;
			CurPlayerInfo.LightningResistance = 0;
			CurPlayerInfo.PoisonResistance = 0;

			CurPlayerInfo.WalkVelocity = 300;
			CurPlayerInfo.RunVelocity = 500;
			CurPlayerInfo.RunStaminaDrain = 50;

			break;
		}
		case JobType::Paladin:
		{
			CurPlayerInfo.JobName = L"팔라딘";

			CurPlayerInfo.Strength = 25;
			CurPlayerInfo.Dexterity = 20;
			CurPlayerInfo.Vitality = 25;
			CurPlayerInfo.Energy = 15;

			CurPlayerInfo.MinDamage = 2;
			CurPlayerInfo.MaxDamage = 8;
			CurPlayerInfo.AttackRating = 85;
			CurPlayerInfo.Defense = 10;
			CurPlayerInfo.Stamina = 89;
			CurPlayerInfo.Life = 55;
			CurPlayerInfo.Mana = 15;
			CurPlayerInfo.FireResistance = 0;
			CurPlayerInfo.ColdResistance = 0;
			CurPlayerInfo.LightningResistance = 0;
			CurPlayerInfo.PoisonResistance = 0;

			CurPlayerInfo.WalkVelocity = 300;
			CurPlayerInfo.RunVelocity = 500;
			CurPlayerInfo.RunStaminaDrain = 50;

			break;
		}
	}

	return CurPlayerInfo;
}

std::vector<SkillList> MainPlayerInfomation::SkillInfoLoad(JobType _JobType)
{
	std::vector<SkillList> SkillInfoList;

	// 해당 클래스의 스킬목록 로드
	if (false == AllSkillInfomation::GetInst().ClassSkillFind(_JobType, SkillInfoList))
	{
		GameEngineDebug::MsgBoxError("해당 클래스(직업)의 스킬 정보를 로드하지 못하였습니다.!!!!");
	}

	return SkillInfoList;
}

void MainPlayerInfomation::LevelChangeUpdatePlayerInfo(MainPlayerInfo _MainPlayerInfo)
{
	MainPlayerInfo_ = _MainPlayerInfo;
}

void MainPlayerInfomation::SaveMainPlayerInfo(const std::string& _PlayerID)
{
	GameEngineDirectory SaveFileDir;
	SaveFileDir.MoveParent("DirectX");
	SaveFileDir.MoveChild("Resources");
	SaveFileDir.MoveChild("SaveFile");

	// 경로 편집
	std::string FullPath = SaveFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += _PlayerID;
	FullPath += ".dat";

	// PlayerID.dat 파일 생성
	GameEngineFile pFile = GameEngineFile(FullPath, "wb");

	// MainPlayerInfo_ << 이 정보 모두 저장한 파일 .dat
	// 1. 캐릭터생성화면에서 최초 정보파일 생성용 저장
	// 2. 게임종료 시 해당 파일 갱신용 저장

	// =============================== 플레이어 기본정보 =============================== //
	// 플레이어 기본정보(공통)

	// 캐릭터 생성시 입력한 ID
	pFile.Write(MainPlayerInfo_.ID);

	// 캐릭터 생성시 선택한 직업
	pFile.Write(static_cast<int>(MainPlayerInfo_.JobType));
	
	// 선택한 직업의 한글명
	pFile.Write(MainPlayerInfo_.JobName);

	// 현재 레벨(생성시 1레벨 고정)
	pFile.Write(MainPlayerInfo_.Level);

	// 현재 경험치(생성시 0 고정)
	pFile.Write(MainPlayerInfo_.Exp);

	// 플레이어 시작 스킬정보(공통)

	// 캐릭터 생성시 SkillCode 0번 (일반공격) 고정 - LeftWeaponSkill(고정 - 사용안할꺼임)
	pFile.Write(MainPlayerInfo_.LeftStartSkill);

	// 캐릭터 생성시 SkillCode 0번 (일반공격) 고정 - RightWeaponSkill
	pFile.Write(MainPlayerInfo_.RightStartSkill);

	// 레벨업 당 포인트

	// 레벨업당 스킬포인트(고정 - 3포인트)
	pFile.Write(MainPlayerInfo_.SkillPointsPerLevelUp);

	// 레벨업당 스탯포인트(고정 - 5포인트)
	pFile.Write(MainPlayerInfo_.StatPointsPerLevelUp);

	// 플레이어 상세정보(JobType에 따라 다름)

	// 힘
	pFile.Write(MainPlayerInfo_.Strength);

	// 민첩
	pFile.Write(MainPlayerInfo_.Dexterity);

	// 생명력
	pFile.Write(MainPlayerInfo_.Vitality);

	// 에너지
	pFile.Write(MainPlayerInfo_.Energy);

	// 공격데미지(최소)
	pFile.Write(MainPlayerInfo_.MinDamage);

	// 공격데미지(최대)
	pFile.Write(MainPlayerInfo_.MaxDamage);

	// 공격등급
	pFile.Write(MainPlayerInfo_.AttackRating);

	// 방어
	pFile.Write(MainPlayerInfo_.Defense);

	// 스태미나
	pFile.Write(MainPlayerInfo_.Stamina);

	// 라이프
	pFile.Write(MainPlayerInfo_.Life);

	// 마나
	pFile.Write(MainPlayerInfo_.Mana);

	// 파이어 저항력
	pFile.Write(MainPlayerInfo_.FireResistance);

	// 콜드 저항력
	pFile.Write(MainPlayerInfo_.ColdResistance);

	// 라이트닝 저항력
	pFile.Write(MainPlayerInfo_.LightningResistance);

	// 포이즌 저항력
	pFile.Write(MainPlayerInfo_.PoisonResistance);

	// 걷기 속도
	pFile.Write(MainPlayerInfo_.WalkVelocity);

	// 뛰기 속도
	pFile.Write(MainPlayerInfo_.RunVelocity);

	// 뛰기상태(스태미나소모활성화)일때의 스태미나 소모량
	pFile.Write(MainPlayerInfo_.RunStaminaDrain);

	// =============================== 플레이어 스킬정보 =============================== //
	// 스킬정보 갯수
	pFile.Write(MainPlayerInfo_.SkillInfoCnt);

	for (int i = 0; i < MainPlayerInfo_.SkillInfoCnt; ++i)
	{
		// 플레이어 스킬 기본정보
		
		// 스킬 영어명
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillName);

		// 스킬코드
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillCode);

		// 스킬타입
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].SkillType));

		// 플레이어 스킬창의 속한 페이지 No
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillPage);

		// 플레이어 스킬창의 속한 페이지의 Row
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillRow);

		// 플레이어 스킬창의 속한 페이지의 Column
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillColumn);

		// 해당 스킬 활성화 조건(스킬레벨)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillLevel);

		// 해당 스킬 활성화 조건(선행스킬이름1)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName1);

		// 해당 스킬 활성화 조건(선행스킬코드1)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode1);

		// 해당 스킬 활성화 조건(선행스킬이름2)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName2);

		// 해당 스킬 활성화 조건(선행스킬코드2)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode2);

		// 해당 스킬 활성화 조건(선행스킬이름3)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName3);

		// 해당 스킬 활성화 조건(선행스킬코드3)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode3);

		// 최대 스킬레벨
		pFile.Write(MainPlayerInfo_.SkillInfo[i].MaxSkillLevel);

		// 현재 스킬레벨
		pFile.Write(MainPlayerInfo_.SkillInfo[i].CurSkillLevel);

		// 플레이어 스킬 상세정보(판단용 Flag)

		// 스킬사용가능여부(초기에 0번스킬인 일반공격만 TRUE 상태)
		if (true == MainPlayerInfo_.SkillInfo[i].SkillActive)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 벽을 넘을수있는 스킬인지 판단(TURE : 벽통과가능)
		if (true == MainPlayerInfo_.SkillInfo[i].LineOfSight)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 스킬 시전중 플레이어가 피격상태가 되면 해당 스킬시전이 취소되는지 판단(TRUE : 취소됨)
		if (true == MainPlayerInfo_.SkillInfo[i].Interrupt)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 마을내에서 사용가능한 스킬인지 판단(TRUE : 마을내 사용가능)
		if (true == MainPlayerInfo_.SkillInfo[i].InTown)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 해당 스킬이 패시브 스킬인지 판단(TRUE : 패시브스킬로 판단) - 플레이어 버프용
		if (true == MainPlayerInfo_.SkillInfo[i].IsPassive)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 해당 스킬이 디버프 스킬인지 판단(TRUE : 디버프스킬) - 몬스터 디버프용
		if (true == MainPlayerInfo_.SkillInfo[i].IsDebuff)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 해당 스킬 사용시 마나소모여부 판단(TRUE : 마나소모함)
		if (true == MainPlayerInfo_.SkillInfo[i].ManaUse)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 왼쪽무기에 장착가능한 스킬인지 판단(TRUE : 사용가능)
		if (true == MainPlayerInfo_.SkillInfo[i].LeftSkillUse)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 해당 스킬이 몬스터 시체에 시전가능한 스킬인지 판단(TRUE : 시전가능) - 소환수 스킬전용
		if (true == MainPlayerInfo_.SkillInfo[i].IsSelDead)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// IsPassive = TURE 일때 사용

		// 패시브 타입
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].PassiveType));

		// 스킬레벨당 라이프 증가량
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveLifePerLevel);

		// 스킬레벨당 보너스 라이프 증가량(시체로 선택된 몬스터의 본래체력의 퍼센트 : 100% 기준)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveBonusLifePerLevel);

		// 스킬레벨당 이동속도 증가량(100% 기준)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveVelocityPerLevel);

		// 스킬레벨당 데미지 증가량
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveDamagePerLevel);

		// 스킬레벨당 모든속성 저항력 증가량(100% 기준)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveResistAllPerLevel);

		// IsDebuff = TRUE 일때 사용

		// 해당 스킬을 맞은 몬스터가 받는 디버프효과 타입
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].DebuffType));

		// 해당 스킬시전시 플레이어가 받는 버프효과 타입
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].BuffType));

		// 지속시간(1레벨값) - 100% 기준(값 / 100)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDuration);

		// 스킬레벨당 디버프 지속시간 증가량 - 100% 기준(값 / 100)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDurationPerLevel);

		// 스킬레벨당 디버프 타입의 데미지 증가량
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDamagePerLevel);

		// ManaUse = TURE일때 사용

		// 마나소모량
		pFile.Write(MainPlayerInfo_.SkillInfo[i].ManaUsage);

		// 

		// 스킬 데미지
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillDamage);

		// 스킬 시전 딜레이시간
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillDelay);
	}

	// ============================== 플레이어 아이템정보 ============================== //
	// 보유 아이켐정보 갯수
	pFile.Write(MainPlayerInfo_.ItemInfoCnt);

	for (int i = 0; i < MainPlayerInfo_.ItemInfoCnt; ++i)
	{
		// 아이템 기본정보

		// 아이템명(약어)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemName_abbreviation);

		// 아이템명(약어) - 인벤용
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemName_abbreviation_Inven);

		// 아이템코드
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemCode);

		// 아이템타입
		pFile.Write(static_cast<int>(MainPlayerInfo_.ItemInfo[i].ItemType));

		// 아이템 장착정보

		// 아이템위치(인벤토리, 하단상태바, 창고, 판매창)
		pFile.Write(static_cast<int>(MainPlayerInfo_.ItemInfo[i].ItemLocType));

		// 각각의 창에서 시작하는 위치의 인덱스
		pFile.Write(MainPlayerInfo_.ItemInfo[i].StartPosition);

		// 아이템넓이 -> 이벤토리 or 창고 or 판매창에서 차지하는 너비칸수
		pFile.Write(MainPlayerInfo_.ItemInfo[i].WidthSize);

		// 아이템높이 -> 이벤토리 or 창고 or 판매창에서 차지하는 높이칸수
		pFile.Write(MainPlayerInfo_.ItemInfo[i].HeightSize);

		// 아이템 상세정보
		if (true == MainPlayerInfo_.ItemInfo[i].IsDurability)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// 최대 내구도
		pFile.Write(MainPlayerInfo_.ItemInfo[i].MaxDurability);

		// 현재 내구도
		pFile.Write(MainPlayerInfo_.ItemInfo[i].CurDurability);

		// 피격차단확률
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Block);

		// 아이템무게(플레이어 이동속도 감소)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Weight);

		// 아이템 비용(판매창에서 판매하는 비용)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Price);

		// 아이템 장착시 증가공격력
		pFile.Write(MainPlayerInfo_.ItemInfo[i].PullDamage);

		// 아이템 장착시 증가방어력
		pFile.Write(MainPlayerInfo_.ItemInfo[i].PullArmor);

		// 회복량(포션용) : 퍼센트
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Recovery);
	}

	pFile.Close();
}

void MainPlayerInfomation::LoadMainPlayerInfo(const std::string& _PlayerID)
{
	// 캐릭터 선택화면에서 해야할일!!!!!
	// 시간 나면 구현할것!!!!!

}
