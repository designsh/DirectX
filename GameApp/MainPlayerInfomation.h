#pragma once

// ����Ÿ��
enum class JobType
{
	None = -1,
	Necromancer = 0,		// ��ũ�θǼ�
	amazon,						// �Ƹ���
	Sorceress,						// �Ҽ�����
	barbarian,						// �ٹٸ���
	paladin							// �ȶ��
};

// ������Ÿ��
enum class ItemType
{
	Weapon,						// ����
	Shield,							// ���� 
	Helm,								// ����
	Armor,							// ����
	Gloves,							// �尩
	Belt,								// ��Ʈ
	Boots,							// �Ź�
	Ring,								// ����
	Amulet,							// �����
	Portion,							// ����
	Scroll,								// ��ũ��
	Etc,									// ��Ÿ
};

// ������ ��ġŸ��
enum class ItemLocType
{
	Inven_Weapon,			// �κ��丮 - ����ĭ
	Inven_Shield,				// �κ��丮 - ����ĭ
	Inven_Helm,					// �κ��丮 - ����ĭ
	Inven_Armor,				// �κ��丮 - ����ĭ
	Inven_Gloves,				// �κ��丮 - �尩ĭ
	Inven_Belt,					// �κ��丮 - ��Ʈĭ
	Inven_Boots,				// �κ��丮 - �Ź�ĭ
	Inven_LRing,				// �κ��丮 - ���� ����ĭ
	Inven_RRing,				// �κ��丮 - ������ ����ĭ
	Inven_Amulet,				// �κ��丮 - �����ĭ
	Inven_Bottom,			// �κ��丮 - �ϴ�ĭ
	BotStat_Portion1,		// �ϴܻ��¹� ���� ù��°ĭ
	BotStat_Portion2,		// �ϴܻ��¹� ���� �ι�°ĭ
	BotStat_Portion3,		// �ϴܻ��¹� ���� ����°ĭ
	BotStat_Portion4,		// �ϴܻ��¹� ���� �׹�°ĭ
	Storehouse_Bottom,	// â�� - �ϴ�ĭ
	BuySell_Weapon,		// �Ǹ�â - ������
	BuySell_Armor,			// �Ǹ�â - ����
	BuySell_Etc,					// �Ǹ�â - ��Ÿ��
};

// ��ųŸ��
enum class SkillType
{
	None,								// ���Ѿ���((Ex) FireBall))
	Range,							// ���Ÿ���
	H2H,								// �������ݸ�
	Both								// ���� or ���Ÿ�
};

// ����� Ÿ��(���ֽ�ų or ��ȯ����ų)
enum class SkillDebuffType
{
	Poisoned,						// �ߵ� : ȸ���� 50% ����
	Burning,						// ȭ�� : �ʴ� n������
	Bleeding,						// ���� : �ʴ� n������
	BlurredVision,				// �þ߰��� : �����þ߹ݰ� ����
	SpeedReduction,		// �ӷ°��� : �̵��ӵ� ����
};

// �нú� Ÿ��(��ȯ����ų)
enum class PassiveType
{
	SkeletonWarrior,			// �����ڷ� �����͸� : ��ȯ�� �����ڷз��� ������, ����, �������� ����
	Golem,							// �� �����͸� : ��ȯ�� �񷽷��� ������, �̵��ӵ�, ���ݵ���� ����
	SummonResist,			// ��ȯ������ : ��ȯ���� ��� �Ӽ� ���׷��� ����
};

struct ItemList
{
	// ============================== �÷��̾� ���������� ============================== //
	// ������ �⺻����
	std::wstring						ItemName;								// ������ �ѱ۸�
	int										ItemCode;									// �������ڵ�
	ItemType							ItemType;									// ������Ÿ��

	// ������ ��������
	ItemLocType						ItemLocType;							// ��������ġ(�κ��丮, �ϴܻ��¹�, â��, �Ǹ�â)
	int										StartPosition;							// ������ â���� �����ϴ� ��ġ�� �ε���
	int										WidthSize;								// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� �ʺ�ĭ��
	int										HeightSize;								// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� ����ĭ��
};

struct SkillList
{
	// =============================== �÷��̾� ��ų���� =============================== //
	// �÷��̾� ��ų �⺻����
	std::wstring						SkillName;									// ��ų �ѱ۸�
	int										SkillCode;									// ��ų�ڵ�
	SkillType							SkillType;									// ��ųŸ��

	int										SkillPage;									// �÷��̾� ��ųâ�� ���� ������ No
	int										SkillRow;									// �÷��̾� ��ųâ�� ���� �������� Row
	int										SkillColumn;								// �÷��̾� ��ųâ�� ���� �������� Column

	int										reqSkillName1;						// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�)
	int										reqSkillCode1;							// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�)
	int										reqSkillLevel1;							// �ش� ��ų Ȱ��ȭ ����(���ེų����)
	int										reqSkillName2;						// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�)
	int										reqSkillCode2;							// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�)
	int										reqSkillLevel2;							// �ش� ��ų Ȱ��ȭ ����(���ེų����)
	int										reqSkillName3;						// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�)
	int										reqSkillCode3;							// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�)
	int										reqSkillLevel3;							// �ش� ��ų Ȱ��ȭ ����(���ེų����)

	int										MaxSkillLevel;							// �ִ� ��ų����
	int										CurSkillLevel;							// ���� ��ų����

	// �÷��̾� ��ų ������(�Ǵܿ� Flag)
	bool									SkillActive;								// ��ų��밡�ɿ���(�ʱ⿡ 0����ų�� �Ϲݰ��ݸ� TRUE ����)
	bool									LineOfSight;								// ���� �������ִ� ��ų���� �Ǵ�(TURE : ���������)
	bool									Interrupt;									// ��ų ������ �÷��̾ �ǰݻ��°� �Ǹ� �ش� ��ų������ ��ҵǴ��� �Ǵ�(TRUE : ��ҵ�)
	bool									InTown;										// ���������� ��밡���� ��ų���� �Ǵ�(TRUE : ������ ��밡��)
	bool									IsPassive;									// �ش� ��ų�� �нú� ��ų���� �Ǵ�(TRUE : �нú꽺ų�� �Ǵ�) - �÷��̾� ������
	bool									IsDebuff;									// �ش� ��ų�� ����� ��ų���� �Ǵ�(TRUE : �������ų) - ���� �������
	bool									ManaUse;									// �ش� ��ų ���� �����Ҹ𿩺� �Ǵ�(TRUE : �����Ҹ���)
	bool									LeftSkillUse;								// ���ʹ��⿡ ���������� ��ų���� �Ǵ�(TRUE : ��밡��)
	bool									IsSummons;								// �ش� ��ų�� ���� ��ü�� ���������� ��ų���� �Ǵ�(TRUE : ��������) - ��ȯ�� ��ų����

	// IsPassive = TURE �϶� ���
	PassiveType						PassiveType;								// �нú� Ÿ��
	int										PassiveLifePerLevel;				// ��ų������ ������ ������
	int										PassiveDefensePerLevel;		// ��ų������ ���� ������
	int										PassiveVelocityPerLevel;		// ��ų������ �̵��ӵ� ������
	int										PassiveDamagePerLevel;		// ��ų������ ������ ������

	// IsDebuff = TRUE �϶� ���
	SkillDebuffType				DebuffType;								// �ش� ��ų�� ���� ���Ͱ� �޴� �����ȿ�� Ÿ��
	int										DebuffDuration;						// ����� ���ӽð�
	int										MinDebuffDamage;				// ����� Ÿ���� ȭ��, �ߵ�, ������ ��� ���Ϳ��� ������ �ּҵ�����
	int										MaxDebuffDamage;				// ����� Ÿ���� ȭ��, �ߵ�, ������ ��� ���Ϳ��� ������ �ִ뵥����

	// ManaUse = TURE�϶� ���
	int										ManaUsage;							// �����Ҹ�

	// 
	int										SkillDamage;							// ��ų ������
	int										SkillDelay;									// ��ų ���� �����̽ð�
};

struct MainPlayerInfo
{
	// =============================== �÷��̾� �⺻���� =============================== //
	// �÷��̾� �⺻����(����)
	std::string							ID;												// ĳ���� ������ �Է��� ID
	JobType								JobType;									// ĳ���� ������ ������ ����
	std::wstring						JobName;									// ������ ������ �ѱ۸�
	int										Level;											// ���� ����(������ 1���� ����)
	float									Exp;											// ���� ����ġ(������ 0.f ����)

	// �÷��̾� ���� ��ų����(����)
	int										LeftStartSkill;							// ĳ���� ������ SkillCode 0�� (�Ϲݰ���) ���� - LeftWeaponSkill(���� - ������)
	int										RightStartSkill;							// ĳ���� ������ SkillCode 0�� (�Ϲݰ���) ���� - RightWeaponSkill

	// ������ �� ����Ʈ
	int										SkillPointsPerLevelUp;			// �������� ��ų����Ʈ(���� - 3����Ʈ)
	int										StatPointsPerLevelUp;			// �������� ��������Ʈ(���� - 5����Ʈ)

	// �÷��̾� ������(JobType�� ���� �ٸ�)
	int										Strength;									// ��
	int										Dexterity;									// ��ø
	int										Vitality;										// �����
	int										Energy;										// ������

	int										MinDamage;							// ���ݵ�����(�ּ�)
	int										MaxDamage;							// ���ݵ�����(�ִ�)
	int										AttackRating;							// ���ݵ��
	int										Defense;									// ���
	int										Stamina;									// ���¹̳�
	int										Life;											// ������
	int										Mana;										// ����
	int										FireResistance;							// ���̾� ���׷�
	int										ColdResistance;						// �ݵ� ���׷�
	int										LightningResistance;				// ����Ʈ�� ���׷�
	int										PoisonResistance;					// ������ ���׷�

	int										WalkVelocity;							// �ȱ� �ӵ�
	int										RunVelocity;								// �ٱ� �ӵ�
	int										RunStaminaDrain;					// �ٱ����(���¹̳��Ҹ�Ȱ��ȭ)�϶��� ���¹̳� �Ҹ�

	// �÷��̾� ��ų����(JobType�� ���� �ٸ�)
	std::vector<SkillList>		SkillInfo;									// ��ų����

	// �÷��̾� ����������(�ʱ� ������ : �⺻����, ��Ż��ũ��, �����۰�����ũ�� ����)
	std::vector<ItemList>		ItemInfo;									// ��������������
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
	MainPlayerInfo MainPlayerInfo_;	// (�÷��̾� ID.txt ������ ����)

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
	const MainPlayerInfo* GetMainPlayerInfo();

public: // CreateMainPlayerInfo : ĳ���ͻ���ȭ�鿡�� �����Ͽ� �ش� ���� ���Ϸ� ������ �� ����
	void CreateMainPlayerInfo(const std::string& _PlayerID, JobType _JobType);					// �����÷��̾� ���� �ʱ����
	MainPlayerInfo InformationByClass(JobType _JobType);															// Ŭ������ �������� ����
	std::vector<SkillList> NecromancerSkillInfo();																				// ��ũ�θǼ� ��ų���� ����
	std::vector<SkillList> AmazonSkillInfo();																						// �Ƹ��� ��ų���� ����
	std::vector<SkillList> SorceressSkillInfo();																						// �Ҽ����� ��ų���� ����
	std::vector<SkillList> BarbarianSkillInfo();																					// �ٹٸ��� ��ų���� ����
	std::vector<SkillList> PaladinSkillInfo();																							// �ȶ�� ��ų���� ����

public: // MainPlayerInfo Save & Load
	void SaveMainPlayerInfo(const std::string& _PlayerID);
	void LoadMainPlayerInfo(const std::string& _PlayerID);
};
