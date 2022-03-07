#include "PreCompile.h"
#include "AllMonsterInfomation.h"

AllMonsterInfomation* AllMonsterInfomation::Inst = new AllMonsterInfomation();

AllMonsterInfomation::AllMonsterInfomation() :
	ExcelZFlag_(false)
{
}

AllMonsterInfomation::~AllMonsterInfomation()
{
}

bool AllMonsterInfomation::MonsterInfoFind(MonsterClassType _ClassType, AllMonsterInfo& _ClassMonsterInfo)
{
	int MonsterInfoSize = static_cast<int>(AllMonsterList_.size());
	for (int i = 0; i < MonsterInfoSize; ++i)
	{
		if (AllMonsterList_[i].ClassType == _ClassType)
		{
			_ClassMonsterInfo = AllMonsterList_[i];
			return true;
		}
	}

	return false;
}

void AllMonsterInfomation::CreateAllMonsterInfomation(bool _ExcelFile)
{
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	if (true == _ExcelFile)
	{
		// .dat ���� ������������ �ϴ°���(�׽�Ʈ��)
		LoadMonsterExcelFile();
	}
	else
	{
		// ���������� �̰ɷ� �Ҳ���
		LoadMonsterBinaryFile();
	}

	SaveMonsterBinaryFile();
}

void AllMonsterInfomation::LoadMonsterExcelFile()
{
	// ������ ��ų������ ����ִٸ� Ŭ����
	if (!AllMonsterList_.empty())
	{
		AllMonsterList_.clear();
	}

	// ���� ���۰� ���ÿ� �ش� �Լ��� ȣ��Ǿ� ��� Ŭ������ ��ų������ �����Ѵ�.
	CExcelControl* ExcelFile = new CExcelControl();

	// �ε� ���� ��� ����
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\MonsterInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// ���н� -1 ��ȯ
	// �ε��ؾ��ϴ� ��Ʈ�� �Ѱ�
	if (1 == ExcelFile->Open(chFullPath))
	{
		// MonsterInfo.xlsx ������ ��Ʈ�� �� 1��
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// ��� �÷��� �ο츦 �˻��Ͽ� ��ų�����ε�
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < MONSTER_MAX; ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // �÷� Z�� �Ѿ�� A1 ������ �÷������̹Ƿ� üũ�Ѵ�.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// �������� ���͸�� ����
			AllMonsterInfo NewMonsterInfo = {};

			// ============================ ���� �⺻���� ============================ //

			// ���� ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pName[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pName);
			NewMonsterInfo.Name = pName;
			++RowNo;

			// ���� Ŭ���� Ÿ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pClassType[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pClassType);
			int ClassType = 0;
			sscanf_s(pClassType, "%d", &ClassType);
			NewMonsterInfo.ClassType = static_cast<MonsterClassType>(ClassType);
			++RowNo;

			// ���� Ÿ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pType[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pType);
			int Type = 0;
			sscanf_s(pType, "%d", &Type);
			NewMonsterInfo.Type = static_cast<MonsterType>(Type);
			++RowNo;

			// ���� ����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pLevel[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pLevel);
			int Level = 0;
			sscanf_s(pLevel, "%d", &Level);
			NewMonsterInfo.Level = Level;
			++RowNo;

			// ���� �̵��ӵ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pVelocity[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pVelocity);
			int Velocity = 0;
			sscanf_s(pVelocity, "%d", &Velocity);
			NewMonsterInfo.Velocity = Velocity;
			++RowNo;

			// ���� �ٱ���¿����� �̵��ӵ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pRunVelocity[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pRunVelocity);
			int RunVelocity = 0;
			sscanf_s(pRunVelocity, "%d", &RunVelocity);
			NewMonsterInfo.RunVelocity = RunVelocity;
			++RowNo;

			// �ѹ��� �����Ǵ� ������ �ּ� ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMinGrp[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMinGrp);
			int MinGrp = 0;
			sscanf_s(pMinGrp, "%d", &MinGrp);
			NewMonsterInfo.MinGrp = MinGrp;
			++RowNo;

			// �ѹ��� �����Ǵ� ������ �ִ� ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMaxGrp[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMaxGrp);
			int MaxGrp = 0;
			sscanf_s(pMaxGrp, "%d", &MaxGrp);
			NewMonsterInfo.MaxGrp = MaxGrp;
			++RowNo;

			// ���� ����� �÷��̾�� �ִ� ����ġ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropEXP[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropEXP);
			int DropEXP = 0;
			sscanf_s(pDropEXP, "%d", &DropEXP);
			NewMonsterInfo.DropEXP = DropEXP;
			++RowNo;

			// ���� ����� ������ �����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropItemPercent[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropItemPercent);
			int DropItemPercent = 0;
			sscanf_s(pDropItemPercent, "%d", &DropItemPercent);
			NewMonsterInfo.DropItemPercent = DropItemPercent;
			++RowNo;

			// ���� ����� ����Ǵ� ������ Ÿ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropItemType[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropItemType);
			int DropItemType = 0;
			sscanf_s(pDropItemType, "%d", &DropItemType);
			NewMonsterInfo.DropItemType = DropItemType;
			++RowNo;

			// ���� ����� ��� �����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropGoldPercent[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropGoldPercent);
			int DropGoldPercent = 0;
			sscanf_s(pDropGoldPercent, "%d", &DropGoldPercent);
			NewMonsterInfo.DropGoldPercent = DropGoldPercent;
			++RowNo;

			// ���� ����� ����Ǵ� �ּ� ��差
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropGoldMin[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropGoldMin);
			int DropGoldMin = 0;
			sscanf_s(pDropGoldMin, "%d", &DropGoldMin);
			NewMonsterInfo.DropGoldMin = DropGoldMin;
			++RowNo;

			// ���� ����� ����Ǵ� �ִ� ��差
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDropGoldMax[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDropGoldMax);
			int DropGoldMax = 0;
			sscanf_s(pDropGoldMax, "%d", &DropGoldMax);
			NewMonsterInfo.DropGoldMax = DropGoldMax;
			++RowNo;

			// ������ ����(�����) Flag
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsSpawn[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsSpawn);
			int IsSpawn = 0;
			sscanf_s(pIsSpawn, "%d", &IsSpawn);
			if (1 == IsSpawn)
			{
				NewMonsterInfo.IsSpawn = true;
			}
			else
			{
				NewMonsterInfo.IsSpawn = false;
			}
			++RowNo;

			// ���Ͱ� ���� �����ִ��� �Ǵ� Flag
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsDoorOpen[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsDoorOpen);
			int IsDoorOpen = 0;
			sscanf_s(pIsDoorOpen, "%d", &IsDoorOpen);
			if (1 == IsDoorOpen)
			{
				NewMonsterInfo.IsDoorOpen = true;
			}
			else
			{
				NewMonsterInfo.IsDoorOpen = false;
			}
			++RowNo;

			// ���� ���� ���԰��� �Ǵ� Flag
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsInTown[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsInTown);
			int IsInTown = 0;
			sscanf_s(pIsInTown, "%d", &IsInTown);
			if (1 == IsInTown)
			{
				NewMonsterInfo.IsInTown = true;
			}
			else
			{
				NewMonsterInfo.IsInTown = false;
			}
			++RowNo;

			// �ش� ���� ��ü�� Ư����ų ��밡�� Flag(Ex. �÷��̾� ��ȯ�� ��ų ��)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsCourpseSel[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsCourpseSel);
			int IsCourpseSel = 0;
			sscanf_s(pIsCourpseSel, "%d", &IsCourpseSel);
			if (1 == IsCourpseSel)
			{
				NewMonsterInfo.IsCourpseSel = true;
			}
			else
			{
				NewMonsterInfo.IsCourpseSel = false;
			}
			++RowNo;

			// ���Ͱ� �ٱⰡ �������� �Ǵ� Flag
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsRun[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsRun);
			int IsRun = 0;
			sscanf_s(pIsRun, "%d", &IsRun);
			if (1 == IsRun)
			{
				NewMonsterInfo.IsRun = true;
			}
			else
			{
				NewMonsterInfo.IsRun = false;
			}
			++RowNo;

			// ���� Ư�� ���ݰ��� ���� Flag
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsSpecialAttack[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsSpecialAttack);
			int IsSpecialAttack = 0;
			sscanf_s(pIsSpecialAttack, "%d", &IsSpecialAttack);
			if (1 == IsSpecialAttack)
			{
				NewMonsterInfo.IsSpecialAttack = true;
			}
			else
			{
				NewMonsterInfo.IsSpecialAttack = false;
			}
			++RowNo;

			// ============================ ���� ������ ============================ //

			// ���� �ּ� �����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMinHP[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMinHP);
			int MinHP = 0;
			sscanf_s(pMinHP, "%d", &MinHP);
			NewMonsterInfo.MinHP = MinHP;
			++RowNo;

			// ���� �ִ� �����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMaxHP[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMaxHP);
			int MaxHP = 0;
			sscanf_s(pMaxHP, "%d", &MaxHP);
			NewMonsterInfo.MaxHP = MaxHP;
			++RowNo;

			// ���� ����� ȸ����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pHPRegen[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pHPRegen);
			int HPRegen = 0;
			sscanf_s(pHPRegen, "%d", &HPRegen);
			NewMonsterInfo.HPRegen = HPRegen;
			++RowNo;

			// ���� ����
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pBlock[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pBlock);
			int Block = 0;
			sscanf_s(pBlock, "%d", &Block);
			NewMonsterInfo.Block = Block;
			++RowNo;

			// ���� �Ϲݰ��ݷ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDamage[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDamage);
			int Damage = 0;
			sscanf_s(pDamage, "%d", &Damage);
			NewMonsterInfo.Damage = Damage;
			++RowNo;

			// ���� Ư������ ��Ÿ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pSpeAtkCoolTime[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pSpeAtkCoolTime);
			int SpeAtkCoolTime = 0;
			sscanf_s(pSpeAtkCoolTime, "%d", &SpeAtkCoolTime);
			NewMonsterInfo.SpeAtkCoolTime = SpeAtkCoolTime;
			++RowNo;

			// ���� Ư�����ݷ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pSpeAtkDamage[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pSpeAtkDamage);
			int SpeAtkDamage = 0;
			sscanf_s(pSpeAtkDamage, "%d", &SpeAtkDamage);
			NewMonsterInfo.SpeAtkDamage = SpeAtkDamage;
			++RowNo;

			// �Ϲݰ��� ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pDamageResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pDamageResist);
			int DamageResist = 0;
			sscanf_s(pDamageResist, "%d", &DamageResist);
			NewMonsterInfo.DamageResist = DamageResist;
			++RowNo;

			// Ư������ ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pSpecialDamageResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pSpecialDamageResist);
			int SpecialDamageResist = 0;
			sscanf_s(pSpecialDamageResist, "%d", &SpecialDamageResist);
			NewMonsterInfo.SpecialDamageResist = SpecialDamageResist;
			++RowNo;

			// ȭ�� ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pFireResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pFireResist);
			int FireResist = 0;
			sscanf_s(pFireResist, "%d", &FireResist);
			NewMonsterInfo.FireResist = FireResist;
			++RowNo;

			// ����Ʈ�� ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pLightningResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pLightningResist);
			int LightningResist = 0;
			sscanf_s(pLightningResist, "%d", &LightningResist);
			NewMonsterInfo.LightningResist = LightningResist;
			++RowNo;

			// �ñ� ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pColdResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pColdResist);
			int ColdResist = 0;
			sscanf_s(pColdResist, "%d", &ColdResist);
			NewMonsterInfo.ColdResist = ColdResist;
			++RowNo;

			// �� ���׷�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pPosionResist[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pPosionResist);
			int PosionResist = 0;
			sscanf_s(pPosionResist, "%d", &PosionResist);
			NewMonsterInfo.PosionResist = PosionResist;
			++RowNo;

			AllMonsterList_.push_back(NewMonsterInfo);

			if (RowNo > 33)
			{
				RowNo = 1;
			}

			if (ColRowName[0] == 'Z')
			{
				ExcelZFlag_ = true;
			}
		}

		ExcelZFlag_ = false;

		// ���� ���� �� ���� ��� ������
		ExcelFile->Close();
	}

	// ��Ʈ�ѷ� ����
	if (nullptr != ExcelFile)
	{
		delete ExcelFile;
		ExcelFile = nullptr;
	}
}

void AllMonsterInfomation::LoadMonsterBinaryFile()
{
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// ��� ����
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllMonsterInfo.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// �������� ������ ���� ó���� ���������Ƿ� �������� ���� Read
	int MonsterCnt = 0;
	pFile.Read(MonsterCnt);
	AllMonsterList_.resize(MonsterCnt);

	for (int i = 0; i < MonsterCnt; ++i)
	{
		// ============================ ���� �⺻���� ============================ //
		// ���� ��
		std::string Name = "";
		pFile.Read(Name);
		AllMonsterList_[i].Name = Name;

		// ���� Ŭ���� Ÿ��
		int ClassType = 0;
		pFile.Read(ClassType);
		AllMonsterList_[i].ClassType = static_cast<MonsterClassType>(ClassType);

		// ���� Ÿ��
		int Type = 0;
		pFile.Read(Type);
		AllMonsterList_[i].Type = static_cast<MonsterType>(Type);

		// ���� ����
		int Level = 0;
		pFile.Read(Level);
		AllMonsterList_[i].Level = Level;

		// ���� �̵��ӵ�
		int Velocity = 0;
		pFile.Read(Velocity);
		AllMonsterList_[i].Velocity = Velocity;

		// ���� �ٱ���¿����� �̵��ӵ�
		int RunVelocity = 0;
		pFile.Read(RunVelocity);
		AllMonsterList_[i].RunVelocity = RunVelocity;

		// �ѹ��� �����Ǵ� ������ �ּ� ��
		int MinGrp = 0;
		pFile.Read(MinGrp);
		AllMonsterList_[i].MinGrp = MinGrp;

		// �ѹ��� �����Ǵ� ������ �ִ� ��
		int MaxGrp = 0;
		pFile.Read(MaxGrp);
		AllMonsterList_[i].MaxGrp = MaxGrp;

		// ���� ����� �÷��̾�� �ִ� ����ġ��
		int DropEXP = 0;
		pFile.Read(DropEXP);
		AllMonsterList_[i].DropEXP = DropEXP;

		// ���� ����� ������ �����
		int DropItemPercent = 0;
		pFile.Read(DropItemPercent);
		AllMonsterList_[i].DropItemPercent = DropItemPercent;

		// ���� ����� ����Ǵ� ������ Ÿ��
		int DropItemType = 0;
		pFile.Read(DropItemType);
		AllMonsterList_[i].DropItemType = DropItemType;

		// ���� ����� ��� �����
		int DropGoldPercent = 0;
		pFile.Read(DropGoldPercent);
		AllMonsterList_[i].DropGoldPercent = DropGoldPercent;

		// ���� ����� ����Ǵ� �ּ� ��差
		int DropGoldMin = 0;
		pFile.Read(DropGoldMin);
		AllMonsterList_[i].DropGoldMin = DropGoldMin;

		// ���� ����� ����Ǵ� �ִ� ��差
		int DropGoldMax = 0;
		pFile.Read(DropGoldMax);
		AllMonsterList_[i].DropGoldMax = DropGoldMax;

		// ������ ����(�����) Flag
		int IsSpawn = 0;
		pFile.Read(IsSpawn);
		if (1 == IsSpawn)
		{
			AllMonsterList_[i].IsSpawn = true;
		}
		else
		{
			AllMonsterList_[i].IsSpawn = false;
		}

		// ���Ͱ� ���� �����ִ��� �Ǵ� Flag
		int IsDoorOpen = 0;
		pFile.Read(IsDoorOpen);
		if (1 == IsDoorOpen)
		{
			AllMonsterList_[i].IsDoorOpen = true;
		}
		else
		{
			AllMonsterList_[i].IsDoorOpen = false;
		}

		// ���� ���� ���԰��� �Ǵ� Flag
		int IsInTown = 0;
		pFile.Read(IsInTown);
		if (1 == IsInTown)
		{
			AllMonsterList_[i].IsInTown = true;
		}
		else
		{
			AllMonsterList_[i].IsInTown = false;
		}

		// �ش� ���� ��ü�� Ư����ų ��밡�� Flag(Ex. �÷��̾� ��ȯ�� ��ų ��)
		int IsCourpseSel = 0;
		pFile.Read(IsCourpseSel);
		if (1 == IsCourpseSel)
		{
			AllMonsterList_[i].IsCourpseSel = true;
		}
		else
		{
			AllMonsterList_[i].IsCourpseSel = false;
		}

		// ���Ͱ� �ٱⰡ �������� �Ǵ� Flag
		int IsRun = 0;
		pFile.Read(IsRun);
		if (1 == IsRun)
		{
			AllMonsterList_[i].IsRun = true;
		}
		else
		{
			AllMonsterList_[i].IsRun = false;
		}

		// ���� Ư�� ���ݰ��� ���� Flag
		int IsSpecialAttack = 0;
		pFile.Read(IsSpecialAttack);
		if (1 == IsSpecialAttack)
		{
			AllMonsterList_[i].IsSpecialAttack = true;
		}
		else
		{
			AllMonsterList_[i].IsSpecialAttack = false;
		}

		// ============================ ���� ������ ============================ //
		// ���� �ּ� �����
		int MinHP = 0;
		pFile.Read(MinHP);
		AllMonsterList_[i].MinHP = MinHP;

		// ���� �ִ� �����
		int MaxHP = 0;
		pFile.Read(MaxHP);
		AllMonsterList_[i].MaxHP = MaxHP;

		// ���� ����� ȸ����
		int HPRegen = 0;
		pFile.Read(HPRegen);
		AllMonsterList_[i].HPRegen = HPRegen;

		// ���� ����
		int Block = 0;
		pFile.Read(Block);
		AllMonsterList_[i].Block = Block;

		// ���� �Ϲݰ��ݷ�
		int Damage = 0;
		pFile.Read(Damage);
		AllMonsterList_[i].Damage = Damage;

		// ���� Ư������ ��Ÿ��
		int SpeAtkCoolTime = 0;
		pFile.Read(SpeAtkCoolTime);
		AllMonsterList_[i].SpeAtkCoolTime = SpeAtkCoolTime;

		// ���� Ư�����ݷ�
		int SpeAtkDamage = 0;
		pFile.Read(SpeAtkDamage);
		AllMonsterList_[i].SpeAtkDamage = SpeAtkDamage;

		// �Ϲݰ��� ���׷�
		int DamageResist = 0;
		pFile.Read(DamageResist);
		AllMonsterList_[i].DamageResist = DamageResist;

		// Ư������ ���׷�
		int SpecialDamageResist = 0;
		pFile.Read(SpecialDamageResist);
		AllMonsterList_[i].SpecialDamageResist = SpecialDamageResist;

		// ȭ�� ���׷�
		int FireResist = 0;
		pFile.Read(FireResist);
		AllMonsterList_[i].FireResist = FireResist;

		// ����Ʈ�� ���׷�
		int LightningResist = 0;
		pFile.Read(LightningResist);
		AllMonsterList_[i].LightningResist = LightningResist;

		// �ñ� ���׷�
		int ColdResist = 0;
		pFile.Read(ColdResist);
		AllMonsterList_[i].ColdResist = ColdResist;

		// �� ���׷�
		int PosionResist = 0;
		pFile.Read(PosionResist);
		AllMonsterList_[i].PosionResist = PosionResist;
	}

	pFile.Close();
}

void AllMonsterInfomation::SaveMonsterBinaryFile()
{
	if (!AllMonsterList_.empty())
	{
		GameEngineDirectory DataFileDir;
		DataFileDir.MoveParent("DirectX");
		DataFileDir.MoveChild("Resources");
		DataFileDir.MoveChild("DataFile");

		// ��� ����
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllMonsterInfo.dat";

		// ���� ����
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// ���� ���� ����
		int AllMonsterCnt = static_cast<int>(AllMonsterList_.size());
		pFile.Write(AllMonsterCnt);

		for (int i = 0; i < AllMonsterCnt; ++i)
		{
			// ============================ ���� �⺻���� ============================ //
			// ���� ��
			pFile.Write(AllMonsterList_[i].Name);

			// ���� Ŭ���� Ÿ��
			pFile.Write(static_cast<int>(AllMonsterList_[i].ClassType));

			// ���� Ÿ��
			pFile.Write(static_cast<int>(AllMonsterList_[i].Type));

			// ���� ����
			pFile.Write(AllMonsterList_[i].Level);

			// ���� �̵��ӵ�
			pFile.Write(AllMonsterList_[i].Velocity);

			// ���� �ٱ���¿����� �̵��ӵ�
			pFile.Write(AllMonsterList_[i].RunVelocity);

			// �ѹ��� �����Ǵ� ������ �ּ� ��
			pFile.Write(AllMonsterList_[i].MinGrp);

			// �ѹ��� �����Ǵ� ������ �ִ� ��
			pFile.Write(AllMonsterList_[i].MaxGrp);

			// ���� ����� �÷��̾�� �ִ� ����ġ��
			pFile.Write(AllMonsterList_[i].DropEXP);

			// ���� ����� ������ �����
			pFile.Write(AllMonsterList_[i].DropItemPercent);

			// ���� ����� ����Ǵ� ������ Ÿ��
			pFile.Write(AllMonsterList_[i].DropItemType);

			// ���� ����� ��� �����
			pFile.Write(AllMonsterList_[i].DropGoldPercent);

			// ���� ����� ����Ǵ� �ּ� ��差
			pFile.Write(AllMonsterList_[i].DropGoldMin);

			// ���� ����� ����Ǵ� �ִ� ��差
			pFile.Write(AllMonsterList_[i].DropGoldMax);

			// ������ ����(�����) Flag
			if (true == AllMonsterList_[i].IsSpawn)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ���Ͱ� ���� �����ִ��� �Ǵ� Flag
			if (true == AllMonsterList_[i].IsDoorOpen)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ���� ���� ���԰��� �Ǵ� Flag
			if (true == AllMonsterList_[i].IsInTown)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// �ش� ���� ��ü�� Ư����ų ��밡�� Flag(Ex. �÷��̾� ��ȯ�� ��ų ��)
			if (true == AllMonsterList_[i].IsCourpseSel)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ���Ͱ� �ٱⰡ �������� �Ǵ� Flag
			if (true == AllMonsterList_[i].IsRun)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ���� Ư�� ���ݰ��� ���� Flag
			if (true == AllMonsterList_[i].IsSpecialAttack)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ============================ ���� ������ ============================ //
			// ���� �ּ� �����
			pFile.Write(AllMonsterList_[i].MinHP);

			// ���� �ִ� �����
			pFile.Write(AllMonsterList_[i].MaxHP);

			// ���� ����� ȸ����
			pFile.Write(AllMonsterList_[i].HPRegen);

			// ���� ����
			pFile.Write(AllMonsterList_[i].Block);

			// ���� �Ϲݰ��ݷ�
			pFile.Write(AllMonsterList_[i].Damage);

			// ���� Ư������ ��Ÿ��
			pFile.Write(AllMonsterList_[i].SpeAtkCoolTime);

			// ���� Ư�����ݷ�
			pFile.Write(AllMonsterList_[i].SpeAtkDamage);

			// �Ϲݰ��� ���׷�
			pFile.Write(AllMonsterList_[i].DamageResist);

			// Ư������ ���׷�
			pFile.Write(AllMonsterList_[i].SpecialDamageResist);

			// ȭ�� ���׷�
			pFile.Write(AllMonsterList_[i].FireResist);

			// ����Ʈ�� ���׷�
			pFile.Write(AllMonsterList_[i].LightningResist);

			// �ñ� ���׷�
			pFile.Write(AllMonsterList_[i].ColdResist);

			// �� ���׷�
			pFile.Write(AllMonsterList_[i].PosionResist);
		}

		pFile.Close();
	}
}
