#include "PreCompile.h"
#include "MainPlayerInfomation.h"

MainPlayerInfomation* MainPlayerInfomation::Inst = new MainPlayerInfomation();

MainPlayerInfomation::MainPlayerInfomation() :
	MainPlayerInfo_{}
{
}

MainPlayerInfomation::~MainPlayerInfomation()
{
}

const MainPlayerInfo* MainPlayerInfomation::GetMainPlayerInfo()
{
	return &MainPlayerInfo_;
}

void MainPlayerInfomation::CreateMainPlayerInfo(const std::string& _PlayerID, JobType _JobType)
{
	// 캐릭터생성화면에서 메인플레이어 정보를 생성

	// 클래스(직업)별 고유 정보를 생성
	MainPlayerInfo_ = InformationByClass(_JobType);

	MainPlayerInfo_.ID = _PlayerID;
	MainPlayerInfo_.Level = 1;
	MainPlayerInfo_.Exp = 0.0f;

	// 플레이어 시작 스킬정보(공통)
	MainPlayerInfo_.LeftStartSkill = 0;
	MainPlayerInfo_.RightStartSkill = 0;

	// 레벨업 당 포인트
	MainPlayerInfo_.SkillPointsPerLevelUp = 3;
	MainPlayerInfo_.StatPointsPerLevelUp = 5;

	// ======================= 플레이어 스킬정보 ======================= //
	std::vector<SkillList> ResultSkillList;
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			ResultSkillList = NecromancerSkillInfo();
			break;
		}
		case JobType::amazon:
		{
			ResultSkillList = AmazonSkillInfo();
			break;
		}
		case JobType::Sorceress:
		{
			ResultSkillList = SorceressSkillInfo();
			break;
		}
		case JobType::barbarian:
		{
			ResultSkillList = BarbarianSkillInfo();
			break;
		}
		case JobType::paladin:
		{
			ResultSkillList = PaladinSkillInfo();
			break;
		}
	}

	MainPlayerInfo_.SkillInfo = ResultSkillList;

	// ====================== 플레이어 아이템정보 ====================== //
	// 생성시 기본 생성되는 아이템(완드, 포탈스크롤, 아이템감정스크롤)
	
	// 완드 : 인벤토리 - 무기칸 장착
	ItemList BasicWeaponItem = {};
	BasicWeaponItem.ItemName = L"완드";
	BasicWeaponItem.ItemCode = 1;
	BasicWeaponItem.ItemType = ItemType::Weapon;

	BasicWeaponItem.ItemLocType = ItemLocType::Inven_Weapon;
	BasicWeaponItem.StartPosition = 0;
	BasicWeaponItem.WidthSize = 1;
	BasicWeaponItem.HeightSize = 2;

	MainPlayerInfo_.ItemInfo.push_back(BasicWeaponItem);

	// 포탈스크롤 : 인벤토리 - 하단칸(10x4)의 29번째 인덱스 칸
	ItemList BasicPortalScroll = {};
	BasicPortalScroll.ItemName = L"포탈 스크롤";
	BasicPortalScroll.ItemCode = 7;
	BasicPortalScroll.ItemType = ItemType::Scroll;

	BasicPortalScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicPortalScroll.StartPosition = 29;
	BasicPortalScroll.WidthSize = 1;
	BasicPortalScroll.HeightSize = 1;

	MainPlayerInfo_.ItemInfo.push_back(BasicPortalScroll);
	
	// 아이템감정스크롤 : 인벤토리 - 하단칸(10x4)의 39번째 인덱스 칸
	ItemList BasicIdentifyScroll = {};
	BasicIdentifyScroll.ItemName = L"감정 스크롤";
	BasicIdentifyScroll.ItemCode = 8;
	BasicIdentifyScroll.ItemType = ItemType::Scroll;

	BasicIdentifyScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicIdentifyScroll.StartPosition = 39;
	BasicIdentifyScroll.WidthSize = 1;
	BasicIdentifyScroll.HeightSize = 1;

	MainPlayerInfo_.ItemInfo.push_back(BasicIdentifyScroll);
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
		case JobType::amazon:
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
		case JobType::barbarian:
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
		case JobType::paladin:
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

std::vector<SkillList> MainPlayerInfomation::NecromancerSkillInfo()
{
	std::vector<SkillList> SkillInfoList;

	// 스킬 정보 파일 로드


	
	return SkillInfoList;
}

std::vector<SkillList> MainPlayerInfomation::AmazonSkillInfo()
{
	std::vector<SkillList> SkillInfoList;

	return SkillInfoList;
}

std::vector<SkillList> MainPlayerInfomation::SorceressSkillInfo()
{
	std::vector<SkillList> SkillInfoList;

	return SkillInfoList;
}

std::vector<SkillList> MainPlayerInfomation::BarbarianSkillInfo()
{
	std::vector<SkillList> SkillInfoList;

	return SkillInfoList;
}

std::vector<SkillList> MainPlayerInfomation::PaladinSkillInfo()
{
	std::vector<SkillList> SkillInfoList;

	return SkillInfoList;
}

void MainPlayerInfomation::SaveMainPlayerInfo(const std::string& _PlayerID)
{
	// 캐릭터 생성화면에서 파일로 저장

}

void MainPlayerInfomation::LoadMainPlayerInfo(const std::string& _PlayerID)
{
	// 캐릭터 선택화면에서 해당 파일 로드
}
