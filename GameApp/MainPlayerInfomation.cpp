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
	// ������ �������� �̹� �ִٸ� ������ ��ü
	for (auto& ItemList : MainPlayerInfo_.ItemInfo)
	{
		if (ItemList.ItemName_abbreviation == _ItemInfo.ItemName_abbreviation)
		{
			ItemList = _ItemInfo;
			return;
		}
	}

	// �ű� �������̶�� ������Ͽ� �߰�
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
	// ĳ���ͻ���ȭ�鿡�� �����÷��̾� ������ ����
	IsMainPlayerInfo_ = true;

	// Ŭ����(����)�� ���� ������ ����
	MainPlayerInfo_ = InformationByClass(_JobType);

	MainPlayerInfo_.ID = _PlayerID;
	MainPlayerInfo_.Level = 1;
	MainPlayerInfo_.Exp = 0;

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
	MainPlayerInfo_.SkillInfoCnt = static_cast<int>(MainPlayerInfo_.SkillInfo.size());

	// ====================== �÷��̾� ���������� ====================== //
	// ������ �⺻ �����Ǵ� ������(�ϵ�, ��Ż��ũ��, �����۰�����ũ��)
	
	// �ϵ� : �κ��丮 - ����ĭ ����
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

	// ��Ż��ũ�� : �κ��丮 - �ϴ�ĭ(10x4)�� 9��° �ε��� ĭ
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
	
	// �����۰�����ũ�� : �κ��丮 - �ϴ�ĭ(10x4)�� 19��° �ε��� ĭ
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
	//// �׽�Ʈ�� ������
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

	// �����÷��̾� ���� �������� ���� ����
	SaveMainPlayerInfo(_PlayerID);
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

	// ��� ����
	std::string FullPath = SaveFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += _PlayerID;
	FullPath += ".dat";

	// PlayerID.dat ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "wb");

	// MainPlayerInfo_ << �� ���� ��� ������ ���� .dat
	// 1. ĳ���ͻ���ȭ�鿡�� ���� �������� ������ ����
	// 2. �������� �� �ش� ���� ���ſ� ����

	// =============================== �÷��̾� �⺻���� =============================== //
	// �÷��̾� �⺻����(����)

	// ĳ���� ������ �Է��� ID
	pFile.Write(MainPlayerInfo_.ID);

	// ĳ���� ������ ������ ����
	pFile.Write(static_cast<int>(MainPlayerInfo_.JobType));
	
	// ������ ������ �ѱ۸�
	pFile.Write(MainPlayerInfo_.JobName);

	// ���� ����(������ 1���� ����)
	pFile.Write(MainPlayerInfo_.Level);

	// ���� ����ġ(������ 0 ����)
	pFile.Write(MainPlayerInfo_.Exp);

	// �÷��̾� ���� ��ų����(����)

	// ĳ���� ������ SkillCode 0�� (�Ϲݰ���) ���� - LeftWeaponSkill(���� - �����Ҳ���)
	pFile.Write(MainPlayerInfo_.LeftStartSkill);

	// ĳ���� ������ SkillCode 0�� (�Ϲݰ���) ���� - RightWeaponSkill
	pFile.Write(MainPlayerInfo_.RightStartSkill);

	// ������ �� ����Ʈ

	// �������� ��ų����Ʈ(���� - 3����Ʈ)
	pFile.Write(MainPlayerInfo_.SkillPointsPerLevelUp);

	// �������� ��������Ʈ(���� - 5����Ʈ)
	pFile.Write(MainPlayerInfo_.StatPointsPerLevelUp);

	// �÷��̾� ������(JobType�� ���� �ٸ�)

	// ��
	pFile.Write(MainPlayerInfo_.Strength);

	// ��ø
	pFile.Write(MainPlayerInfo_.Dexterity);

	// �����
	pFile.Write(MainPlayerInfo_.Vitality);

	// ������
	pFile.Write(MainPlayerInfo_.Energy);

	// ���ݵ�����(�ּ�)
	pFile.Write(MainPlayerInfo_.MinDamage);

	// ���ݵ�����(�ִ�)
	pFile.Write(MainPlayerInfo_.MaxDamage);

	// ���ݵ��
	pFile.Write(MainPlayerInfo_.AttackRating);

	// ���
	pFile.Write(MainPlayerInfo_.Defense);

	// ���¹̳�
	pFile.Write(MainPlayerInfo_.Stamina);

	// ������
	pFile.Write(MainPlayerInfo_.Life);

	// ����
	pFile.Write(MainPlayerInfo_.Mana);

	// ���̾� ���׷�
	pFile.Write(MainPlayerInfo_.FireResistance);

	// �ݵ� ���׷�
	pFile.Write(MainPlayerInfo_.ColdResistance);

	// ����Ʈ�� ���׷�
	pFile.Write(MainPlayerInfo_.LightningResistance);

	// ������ ���׷�
	pFile.Write(MainPlayerInfo_.PoisonResistance);

	// �ȱ� �ӵ�
	pFile.Write(MainPlayerInfo_.WalkVelocity);

	// �ٱ� �ӵ�
	pFile.Write(MainPlayerInfo_.RunVelocity);

	// �ٱ����(���¹̳��Ҹ�Ȱ��ȭ)�϶��� ���¹̳� �Ҹ�
	pFile.Write(MainPlayerInfo_.RunStaminaDrain);

	// =============================== �÷��̾� ��ų���� =============================== //
	// ��ų���� ����
	pFile.Write(MainPlayerInfo_.SkillInfoCnt);

	for (int i = 0; i < MainPlayerInfo_.SkillInfoCnt; ++i)
	{
		// �÷��̾� ��ų �⺻����
		
		// ��ų �����
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillName);

		// ��ų�ڵ�
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillCode);

		// ��ųŸ��
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].SkillType));

		// �÷��̾� ��ųâ�� ���� ������ No
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillPage);

		// �÷��̾� ��ųâ�� ���� �������� Row
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillRow);

		// �÷��̾� ��ųâ�� ���� �������� Column
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillColumn);

		// �ش� ��ų Ȱ��ȭ ����(��ų����)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillLevel);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�1)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName1);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�1)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode1);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�2)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName2);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�2)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode2);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�3)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillName3);

		// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�3)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].reqSkillCode3);

		// �ִ� ��ų����
		pFile.Write(MainPlayerInfo_.SkillInfo[i].MaxSkillLevel);

		// ���� ��ų����
		pFile.Write(MainPlayerInfo_.SkillInfo[i].CurSkillLevel);

		// �÷��̾� ��ų ������(�Ǵܿ� Flag)

		// ��ų��밡�ɿ���(�ʱ⿡ 0����ų�� �Ϲݰ��ݸ� TRUE ����)
		if (true == MainPlayerInfo_.SkillInfo[i].SkillActive)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// ���� �������ִ� ��ų���� �Ǵ�(TURE : ���������)
		if (true == MainPlayerInfo_.SkillInfo[i].LineOfSight)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// ��ų ������ �÷��̾ �ǰݻ��°� �Ǹ� �ش� ��ų������ ��ҵǴ��� �Ǵ�(TRUE : ��ҵ�)
		if (true == MainPlayerInfo_.SkillInfo[i].Interrupt)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// ���������� ��밡���� ��ų���� �Ǵ�(TRUE : ������ ��밡��)
		if (true == MainPlayerInfo_.SkillInfo[i].InTown)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// �ش� ��ų�� �нú� ��ų���� �Ǵ�(TRUE : �нú꽺ų�� �Ǵ�) - �÷��̾� ������
		if (true == MainPlayerInfo_.SkillInfo[i].IsPassive)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// �ش� ��ų�� ����� ��ų���� �Ǵ�(TRUE : �������ų) - ���� �������
		if (true == MainPlayerInfo_.SkillInfo[i].IsDebuff)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// �ش� ��ų ���� �����Ҹ𿩺� �Ǵ�(TRUE : �����Ҹ���)
		if (true == MainPlayerInfo_.SkillInfo[i].ManaUse)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// ���ʹ��⿡ ���������� ��ų���� �Ǵ�(TRUE : ��밡��)
		if (true == MainPlayerInfo_.SkillInfo[i].LeftSkillUse)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// �ش� ��ų�� ���� ��ü�� ���������� ��ų���� �Ǵ�(TRUE : ��������) - ��ȯ�� ��ų����
		if (true == MainPlayerInfo_.SkillInfo[i].IsSelDead)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// IsPassive = TURE �϶� ���

		// �нú� Ÿ��
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].PassiveType));

		// ��ų������ ������ ������
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveLifePerLevel);

		// ��ų������ ���ʽ� ������ ������(��ü�� ���õ� ������ ����ü���� �ۼ�Ʈ : 100% ����)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveBonusLifePerLevel);

		// ��ų������ �̵��ӵ� ������(100% ����)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveVelocityPerLevel);

		// ��ų������ ������ ������
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveDamagePerLevel);

		// ��ų������ ���Ӽ� ���׷� ������(100% ����)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].PassiveResistAllPerLevel);

		// IsDebuff = TRUE �϶� ���

		// �ش� ��ų�� ���� ���Ͱ� �޴� �����ȿ�� Ÿ��
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].DebuffType));

		// �ش� ��ų������ �÷��̾ �޴� ����ȿ�� Ÿ��
		pFile.Write(static_cast<int>(MainPlayerInfo_.SkillInfo[i].BuffType));

		// ���ӽð�(1������) - 100% ����(�� / 100)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDuration);

		// ��ų������ ����� ���ӽð� ������ - 100% ����(�� / 100)
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDurationPerLevel);

		// ��ų������ ����� Ÿ���� ������ ������
		pFile.Write(MainPlayerInfo_.SkillInfo[i].DebuffDamagePerLevel);

		// ManaUse = TURE�϶� ���

		// �����Ҹ�
		pFile.Write(MainPlayerInfo_.SkillInfo[i].ManaUsage);

		// 

		// ��ų ������
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillDamage);

		// ��ų ���� �����̽ð�
		pFile.Write(MainPlayerInfo_.SkillInfo[i].SkillDelay);
	}

	// ============================== �÷��̾� ���������� ============================== //
	// ���� ���������� ����
	pFile.Write(MainPlayerInfo_.ItemInfoCnt);

	for (int i = 0; i < MainPlayerInfo_.ItemInfoCnt; ++i)
	{
		// ������ �⺻����

		// �����۸�(���)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemName_abbreviation);

		// �����۸�(���) - �κ���
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemName_abbreviation_Inven);

		// �������ڵ�
		pFile.Write(MainPlayerInfo_.ItemInfo[i].ItemCode);

		// ������Ÿ��
		pFile.Write(static_cast<int>(MainPlayerInfo_.ItemInfo[i].ItemType));

		// ������ ��������

		// ��������ġ(�κ��丮, �ϴܻ��¹�, â��, �Ǹ�â)
		pFile.Write(static_cast<int>(MainPlayerInfo_.ItemInfo[i].ItemLocType));

		// ������ â���� �����ϴ� ��ġ�� �ε���
		pFile.Write(MainPlayerInfo_.ItemInfo[i].StartPosition);

		// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� �ʺ�ĭ��
		pFile.Write(MainPlayerInfo_.ItemInfo[i].WidthSize);

		// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� ����ĭ��
		pFile.Write(MainPlayerInfo_.ItemInfo[i].HeightSize);

		// ������ ������
		if (true == MainPlayerInfo_.ItemInfo[i].IsDurability)
		{
			pFile.Write(1);
		}
		else
		{
			pFile.Write(0);
		}

		// �ִ� ������
		pFile.Write(MainPlayerInfo_.ItemInfo[i].MaxDurability);

		// ���� ������
		pFile.Write(MainPlayerInfo_.ItemInfo[i].CurDurability);

		// �ǰ�����Ȯ��
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Block);

		// �����۹���(�÷��̾� �̵��ӵ� ����)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Weight);

		// ������ ���(�Ǹ�â���� �Ǹ��ϴ� ���)
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Price);

		// ������ ������ �������ݷ�
		pFile.Write(MainPlayerInfo_.ItemInfo[i].PullDamage);

		// ������ ������ ��������
		pFile.Write(MainPlayerInfo_.ItemInfo[i].PullArmor);

		// ȸ����(���ǿ�) : �ۼ�Ʈ
		pFile.Write(MainPlayerInfo_.ItemInfo[i].Recovery);
	}

	pFile.Close();
}

void MainPlayerInfomation::LoadMainPlayerInfo(const std::string& _PlayerID)
{
	// ĳ���� ����ȭ�鿡�� �ؾ�����!!!!!
	// �ð� ���� �����Ұ�!!!!!

}
