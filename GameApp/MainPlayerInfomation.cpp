#include "PreCompile.h"
#include "MainPlayerInfomation.h"

#include "AllSkillInfomation.h"

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
	// ĳ���ͻ���ȭ�鿡�� �����÷��̾� ������ ����

	// Ŭ����(����)�� ���� ������ ����
	MainPlayerInfo_ = InformationByClass(_JobType);

	MainPlayerInfo_.ID = _PlayerID;
	MainPlayerInfo_.Level = 1;
	MainPlayerInfo_.Exp = 0.0f;

	// �÷��̾� ���� ��ų����(����)
	MainPlayerInfo_.LeftStartSkill = 0;
	MainPlayerInfo_.RightStartSkill = 0;

	// ������ �� ����Ʈ
	MainPlayerInfo_.SkillPointsPerLevelUp = 3;
	MainPlayerInfo_.StatPointsPerLevelUp = 5;

	// ======================= �÷��̾� ��ų���� ======================= //
	std::vector<SkillList> ResultSkillList;
	ResultSkillList = SkillInfoLoad(_JobType);
	MainPlayerInfo_.SkillInfo = ResultSkillList;

	// ====================== �÷��̾� ���������� ====================== //
	// ������ �⺻ �����Ǵ� ������(�ϵ�, ��Ż��ũ��, �����۰�����ũ��)
	
	// �ϵ� : �κ��丮 - ����ĭ ����
	ItemList BasicWeaponItem = {};
	BasicWeaponItem.ItemName_Eng = "Wand";
	BasicWeaponItem.ItemName_Kor = L"�ϵ�";
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

	// ��Ż��ũ�� : �κ��丮 - �ϴ�ĭ(10x4)�� 29��° �ε��� ĭ
	ItemList BasicPortalScroll = {};
	BasicPortalScroll.ItemName_Eng = "PortalScroll";
	BasicPortalScroll.ItemName_Kor = L"��Ż ��ũ��";
	BasicPortalScroll.ItemCode = 7;
	BasicPortalScroll.ItemType = ItemType::Scroll;

	BasicPortalScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicPortalScroll.StartPosition = 29;
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
	
	// �����۰�����ũ�� : �κ��丮 - �ϴ�ĭ(10x4)�� 39��° �ε��� ĭ
	ItemList BasicIdentifyScroll = {};
	BasicIdentifyScroll.ItemName_Eng = "IdentifyScoll";
	BasicIdentifyScroll.ItemName_Kor = L"���� ��ũ��";
	BasicIdentifyScroll.ItemCode = 8;
	BasicIdentifyScroll.ItemType = ItemType::Scroll;

	BasicIdentifyScroll.ItemLocType = ItemLocType::Inven_Bottom;
	BasicIdentifyScroll.StartPosition = 39;
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


}

MainPlayerInfo MainPlayerInfomation::InformationByClass(JobType _JobType)
{
	MainPlayerInfo CurPlayerInfo = {};

	// �÷��̾� �⺻����(����)
	CurPlayerInfo.JobType = _JobType;
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			CurPlayerInfo.JobName = L"��ũ�θǼ�";

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
			CurPlayerInfo.JobName = L"�Ҽ�����";

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
			CurPlayerInfo.JobName = L"�Ƹ���";

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
			CurPlayerInfo.JobName = L"�ٹٸ���";

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
			CurPlayerInfo.JobName = L"�ȶ��";

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

	// �ش� Ŭ������ ��ų��� �ε�
	if (false == AllSkillInfomation::GetInst().ClassSkillFind(_JobType, SkillInfoList))
	{
		GameEngineDebug::MsgBoxError("�ش� Ŭ����(����)�� ��ų ������ �ε����� ���Ͽ����ϴ�.!!!!");
	}

	return SkillInfoList;
}

void MainPlayerInfomation::SaveMainPlayerInfo(const std::string& _PlayerID, bool _CreateFlag)
{
	GameEngineDirectory SaveFileDir;
	SaveFileDir.MoveParent("DirectX");
	SaveFileDir.MoveChild("Resources");
	SaveFileDir.MoveChild("SaveFile");

	// ��� ����



	// 1. ĳ���ͻ���ȭ�鿡�� ���� �������� ������ ����
	if (true == _CreateFlag)
	{
		// PlayerID.dat ���� ����






	}
	else // 2. �������� �� �ش� ���� ���ſ� ����
	{
		// PlayerID.dat ���� ã�Ƽ� ������





	}
}

void MainPlayerInfomation::LoadMainPlayerInfo(const std::string& _PlayerID)
{
	// ĳ���� ����ȭ�鿡�� �ش� ���� �ε�
	// �ð����� ó��

}
