#include "PreCompile.h"
#include "AllSkillInfomation.h"

#include <GameEngineBase/ExcelControl.h>

AllSkillInfomation* AllSkillInfomation::Inst = new AllSkillInfomation();

AllSkillInfomation::AllSkillInfomation() :
	ClassCount_(5),
	ExcelZFlag_(false)
{
}

AllSkillInfomation::~AllSkillInfomation()
{
}

bool AllSkillInfomation::ClassSkillFind(JobType _ClassType, std::vector<SkillList>& _ClassSkillList)
{
	// ��������� �����Ͱ� �־������ ��ȯ����
	if (true == AllSkillInfo_.empty())
	{
		GameEngineDebug::MsgBoxError("��ų������ ���� �ε��ؾ��մϴ�!!!!!");
		return false;
	}

	// �������(AllSkillInfo_)���� �ش� _ClassType�� ã�� ��� ��ų����� _ClassSkillList�� �����Ͽ� ��ȯ
	for (auto& Class : AllSkillInfo_)
	{
		// ������ Ŭ����(����)�� ��ų������ �����Ѵٸ� �ش� ���� ��� �����Ͽ� ��ȯ
		if (Class.ClassType == _ClassType)
		{
			_ClassSkillList = Class.SkillList;
		}
	}

	return true;
}

void AllSkillInfomation::CreateAllSkillInfomation(bool _ExcelFile)
{
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	if (true == _ExcelFile)
	{
		// ExcelDataFile ������ �ش� ������� ���̳ʸ� ���ϻ��� �ʿ�
		LoadSkillExcelFile();
		SaveSkillBinaryFile();
	}
	else
	{
		// ���������� �̰ɷ� �Ҳ���
		LoadSkillBinaryFile();
	}
}

void AllSkillInfomation::LoadSkillExcelFile()
{
	// ������ ��ų������ ����ִٸ� Ŭ����
	if (!AllSkillInfo_.empty())
	{
		AllSkillInfo_.clear();
	}

	// ���� ���۰� ���ÿ� �ش� �Լ��� ȣ��Ǿ� ��� Ŭ������ ��ų������ �����Ѵ�.
	CExcelControl* ExcelFile = new CExcelControl();

	// �ε� ���� ��� ����
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\SkillInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// ���н� -1 ��ȯ
	if (1 == ExcelFile->Open(chFullPath))
	{
		// Ŭ���� ��� üũ�ϸ鼭 ��ų����� �о�´�.
		for (int i = 0; i < static_cast<int>(JobType::MAX); ++i)
		{
			// SkillInfo.xlsx ������ ��Ʈ�� �� 5��
			ExcelFile->SetVisible(false);
			ExcelFile->SetActiveSheet(i + 1);

			// ��ų���� ����
			AllSkillInfo NewAllSkill = {};

			// Ŭ���� ��Ī ����
			switch (static_cast<JobType>(i))
			{
				case JobType::Necromancer:
				{
					NewAllSkill.ClassName = "Necromancer";
					break;
				}
				case JobType::Amazon:
				{
					NewAllSkill.ClassName = "Amazon";
					break;
				}
				case JobType::Sorceress:
				{
					NewAllSkill.ClassName = "Sorceress";
					break;
				}
				case JobType::Barbarian:
				{
					NewAllSkill.ClassName = "Barbarian";
					break;
				}
				case JobType::Paladin:
				{
					NewAllSkill.ClassName = "Paladin";
					break;
				}
			}

			// Ŭ���� Ÿ�� ����
			NewAllSkill.ClassType = static_cast<JobType>(i);

			// ��� �÷��� �ο츦 �˻��Ͽ� ��ų�����ε�
			char ColRowName[MAX_PATH] = {};
			char RowNumber[MAX_PATH] = {};
			int RowNo = 1;
			for (int j = 0; j < 36; ++j)
			{
				memset(ColRowName, 0, sizeof(ColRowName));
				ColRowName[0] = 'A' + j;
				if (ExcelZFlag_) // �÷� Z�� �Ѿ�� A1 ������ �÷������̹Ƿ� üũ�Ѵ�.
				{
					ColRowName[0] = 'A';
					ColRowName[1] = 'A' + (j - 26);
				}

				// �������� ��ų��� ����
				SkillList NewSkillInfo = {};

				// =============================== �÷��̾� ��ų���� =============================== //
				// ��ų��
				memset(RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillName[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillName);
				NewSkillInfo.SkillName = pSkillName;
				++RowNo;

				// ��ų�ڵ�
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillID[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillID);
				int SkillIDInt = 0;
				sscanf_s(pSkillID, "%d", &SkillIDInt);
				NewSkillInfo.SkillCode = SkillIDInt;
				++RowNo;

				// ��ųŸ��
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillType[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillType);
				int SkillTypeInt = 0;
				sscanf_s(pSkillType, "%d", &SkillTypeInt);
				NewSkillInfo.SkillType = (SkillType)SkillTypeInt;
				++RowNo;

				// �÷��̾� ��ųâ�� ���� ������ No
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillPageNo[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillPageNo);
				int SkillPageNo = 0;
				sscanf_s(pSkillPageNo, "%d", &SkillPageNo);
				NewSkillInfo.SkillPage = SkillPageNo;
				++RowNo;

				// �÷��̾� ��ųâ�� ���� �������� Row
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillPageRow[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillPageRow);
				int SkillPageRow = 0;
				sscanf_s(pSkillPageRow, "%d", &SkillPageRow);
				NewSkillInfo.SkillRow = SkillPageRow;
				++RowNo;

				// �÷��̾� ��ųâ�� ���� �������� Column
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillPageColumn[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillPageColumn);
				int SkillPageColumn = 0;
				sscanf_s(pSkillPageColumn, "%d", &SkillPageColumn);
				NewSkillInfo.SkillColumn = SkillPageColumn;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(��ų����)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillLevel);
				int ReqSkillLevel = 0;
				sscanf_s(pReqSkillLevel, "%d", &ReqSkillLevel);
				NewSkillInfo.reqSkillLevel = ReqSkillLevel;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�1)
				memset(RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillName1[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillName1);
				NewSkillInfo.reqSkillName1 = pReqSkillName1;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�1)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillCode1[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillCode1);
				int ReqSkillCode1 = 0;
				sscanf_s(pReqSkillCode1, "%d", &ReqSkillCode1);
				NewSkillInfo.reqSkillCode1 = ReqSkillCode1;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�2)
				memset(RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillName2[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillName2);
				NewSkillInfo.reqSkillName2 = pReqSkillName2;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�2)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillCode2[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillCode2);
				int ReqSkillCode2 = 0;
				sscanf_s(pReqSkillCode2, "%d", &ReqSkillCode2);
				NewSkillInfo.reqSkillCode2 = ReqSkillCode2;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�3)
				memset(RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillName3[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillName3);
				NewSkillInfo.reqSkillName3 = pReqSkillName3;
				++RowNo;

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�3)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pReqSkillCode3[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pReqSkillCode3);
				int ReqSkillCode3 = 0;
				sscanf_s(pReqSkillCode3, "%d", &ReqSkillCode3);
				NewSkillInfo.reqSkillCode3 = ReqSkillCode3;
				++RowNo;

				// �ִ� ��ų����
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pMaxSkillLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pMaxSkillLevel);
				int MaxSkillLevel = 0;
				sscanf_s(pMaxSkillLevel, "%d", &MaxSkillLevel);
				NewSkillInfo.MaxSkillLevel = MaxSkillLevel;
				++RowNo;

				// ���� ��ų����
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pCurSkillLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pCurSkillLevel);
				int CurSkillLevel = 0;
				sscanf_s(pCurSkillLevel, "%d", &CurSkillLevel);
				NewSkillInfo.MaxSkillLevel = CurSkillLevel;
				++RowNo;

				// ��ų��밡�ɿ���(�ʱ⿡ 0����ų�� �Ϲݰ��ݸ� TRUE ����)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillActive[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillActive);
				int SkillActive = 0;
				sscanf_s(pSkillActive, "%d", &SkillActive);
				if (SkillActive == 1)
					NewSkillInfo.SkillActive = true;
				else
					NewSkillInfo.SkillActive = false;
				++RowNo;

				// ���� �������ִ� ��ų���� �Ǵ�(TURE : ���������)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pLineOfSight[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pLineOfSight);
				int LineOfSight = 0;
				sscanf_s(pLineOfSight, "%d", &LineOfSight);
				if (LineOfSight == 1)
					NewSkillInfo.LineOfSight = true;
				else
					NewSkillInfo.LineOfSight = false;
				++RowNo;

				// ��ų ������ �÷��̾ �ǰݻ��°� �Ǹ� �ش� ��ų������ ��ҵǴ��� �Ǵ�(TRUE : ��ҵ�)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pInterrupt[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pInterrupt);
				int Interrupt = 0;
				sscanf_s(pInterrupt, "%d", &Interrupt);
				if (Interrupt == 1)
					NewSkillInfo.Interrupt = true;
				else
					NewSkillInfo.Interrupt = false;
				++RowNo;

				// ���������� ��밡���� ��ų���� �Ǵ�(TRUE : ������ ��밡��)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pInTown[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pInTown);
				int InTown = 0;
				sscanf_s(pInTown, "%d", &InTown);
				if (InTown == 1)
					NewSkillInfo.InTown = true;
				else
					NewSkillInfo.InTown = false;
				++RowNo;

				// �ش� ��ų�� �нú� ��ų���� �Ǵ�(TRUE : �нú꽺ų�� �Ǵ�) - �÷��̾� ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pIsPassive[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pIsPassive);
				int IsPassive = 0;
				sscanf_s(pIsPassive, "%d", &IsPassive);
				if (IsPassive == 1)
					NewSkillInfo.IsPassive = true;
				else
					NewSkillInfo.IsPassive = false;
				++RowNo;

				// �ش� ��ų�� ����� ��ų���� �Ǵ�(TRUE : �������ų) - ���� �������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pIsDebuff[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pIsDebuff);
				int IsDebuff = 0;
				sscanf_s(pIsDebuff, "%d", &IsDebuff);
				if (IsDebuff == 1)
					NewSkillInfo.IsDebuff = true;
				else
					NewSkillInfo.IsDebuff = false;
				++RowNo;

				// �ش� ��ų ���� �����Ҹ𿩺� �Ǵ�(TRUE : �����Ҹ���)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pManaUse[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pManaUse);
				int ManaUse = 0;
				sscanf_s(pManaUse, "%d", &ManaUse);
				if (ManaUse == 1)
					NewSkillInfo.ManaUse = true;
				else
					NewSkillInfo.ManaUse = false;
				++RowNo;

				// ���ʹ��⿡ ���������� ��ų���� �Ǵ�(TRUE : ��밡��)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pLeftSkillUse[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pLeftSkillUse);
				int LeftSkillUse = 0;
				sscanf_s(pLeftSkillUse, "%d", &LeftSkillUse);
				if (LeftSkillUse == 1)
					NewSkillInfo.LeftSkillUse = true;
				else
					NewSkillInfo.LeftSkillUse = false;
				++RowNo;

				// �ش� ��ų�� ���� ��ü�� ���������� ��ų���� �Ǵ�(TRUE : ��������) - ��ȯ�� ��ų����
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pIsSelDead[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pIsSelDead);
				int IsSelDead = 0;
				sscanf_s(pIsSelDead, "%d", &IsSelDead);
				if (IsSelDead == 1)
					NewSkillInfo.IsSelDead = true;
				else
					NewSkillInfo.IsSelDead = false;
				++RowNo;

				// �нú� Ÿ��
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveType[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveType);
				int PassiveType = 0;
				sscanf_s(pPassiveType, "%d", &PassiveType);
				NewSkillInfo.PassiveType = (SkillPassiveType)PassiveType;
				++RowNo;

				// ��ų������ ������ ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveLifePerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveLifePerLevel);
				int PassiveLifePerLevel = 0;
				sscanf_s(pPassiveLifePerLevel, "%d", &PassiveLifePerLevel);
				NewSkillInfo.PassiveLifePerLevel = PassiveLifePerLevel;
				++RowNo;

				// ��ų������ ���ʽ� ������ ������(��ü�� ���õ� ������ ����ü���� �ۼ�Ʈ : 100% ����)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveBonusLifePerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveBonusLifePerLevel);
				int PassiveBonusLifePerLevel = 0;
				sscanf_s(pPassiveBonusLifePerLevel, "%d", &PassiveBonusLifePerLevel);
				NewSkillInfo.PassiveBonusLifePerLevel = PassiveBonusLifePerLevel;
				++RowNo;

				// ��ų������ �̵��ӵ� ������(100% ����)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveVelocityPerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveVelocityPerLevel);
				int PassiveVelocityPerLevel = 0;
				sscanf_s(pPassiveVelocityPerLevel, "%d", &PassiveVelocityPerLevel);
				NewSkillInfo.PassiveVelocityPerLevel = PassiveVelocityPerLevel;
				++RowNo;

				// ��ų������ ������ ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveDamagePerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveDamagePerLevel);
				int PassiveDamagePerLevel = 0;
				sscanf_s(pPassiveDamagePerLevel, "%d", &PassiveDamagePerLevel);
				NewSkillInfo.PassiveDamagePerLevel = PassiveDamagePerLevel;
				++RowNo;

				// ��ų������ ���Ӽ� ���׷� ������(100% ����)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pPassiveResistAllPerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pPassiveResistAllPerLevel);
				int PassiveResistAllPerLevel = 0;
				sscanf_s(pPassiveResistAllPerLevel, "%d", &PassiveResistAllPerLevel);
				NewSkillInfo.PassiveResistAllPerLevel = PassiveResistAllPerLevel;
				++RowNo;

				// �ش� ��ų�� ���� ���Ͱ� �޴� �����ȿ�� Ÿ��
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pDebuffType[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pDebuffType);
				int DebuffType = 0;
				sscanf_s(pDebuffType, "%d", &DebuffType);
				NewSkillInfo.DebuffType = (SkillDebuffType)DebuffType;
				++RowNo;

				// �ش� ��ų������ �÷��̾ �޴� ����ȿ�� Ÿ��
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pBuffType[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pBuffType);
				int BuffType = 0;
				sscanf_s(pBuffType, "%d", &BuffType);
				NewSkillInfo.BuffType = (SkillBuffType)BuffType;
				++RowNo;

				// ���ӽð�(1������) - 100% ����(�� / 100)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pDebuffDuration[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pDebuffDuration);
				int DebuffDuration = 0;
				sscanf_s(pDebuffDuration, "%d", &DebuffDuration);
				NewSkillInfo.DebuffDuration = DebuffDuration;
				++RowNo;

				// ��ų������ ����� ���ӽð� ������ - 100% ����(�� / 100)
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pDebuffDurationPerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pDebuffDurationPerLevel);
				int DebuffDurationPerLevel = 0;
				sscanf_s(pDebuffDurationPerLevel, "%d", &DebuffDurationPerLevel);
				NewSkillInfo.DebuffDurationPerLevel = DebuffDurationPerLevel;
				++RowNo;

				// ����� Ÿ���� ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pDebuffDamage[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pDebuffDamage);
				int DebuffDamage = 0;
				sscanf_s(pDebuffDamage, "%d", &DebuffDamage);
				NewSkillInfo.DebuffDamage = DebuffDamage;
				++RowNo;

				// ��ų������ ����� Ÿ���� ������ ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pDebuffDamagePerLevel[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pDebuffDamagePerLevel);
				int DebuffDamagePerLevel = 0;
				sscanf_s(pDebuffDamagePerLevel, "%d", &DebuffDamagePerLevel);
				NewSkillInfo.DebuffDamagePerLevel = DebuffDamagePerLevel;
				++RowNo;

				// �����Ҹ�
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pManaUsage[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pManaUsage);
				int ManaUsage = 0;
				sscanf_s(pManaUsage, "%d", &ManaUsage);
				NewSkillInfo.ManaUsage = ManaUsage;
				++RowNo;

				// ��ų ������
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillDamage[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillDamage);
				int SkillDamage = 0;
				sscanf_s(pSkillDamage, "%d", &SkillDamage);
				NewSkillInfo.SkillDamage = SkillDamage;
				++RowNo;

				// ��ų ���� �����̽ð�
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ExcelZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillDelay[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillDelay);
				int SkillDelay = 0;
				sscanf_s(pSkillDelay, "%d", &SkillDelay);
				NewSkillInfo.SkillDelay = SkillDelay;
				++RowNo;

				// ��ų���� �߰�
				NewAllSkill.SkillList.push_back(NewSkillInfo);

				if (RowNo > 39)
				{
					RowNo = 1;
				}

				if (ColRowName[0] == 'Z')
				{
					ExcelZFlag_ = true;
				}
			}

			// �ε�Ϸ��� ��Ʈ(Ŭ����)�� ��ų������ �������(������)�� ����
			AllSkillInfo_.push_back(NewAllSkill);

			ExcelZFlag_ = false;
		}

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

void AllSkillInfomation::LoadSkillBinaryFile()
{
	// ������ ��ų������ ����ִٸ� Ŭ����
	if (!AllSkillInfo_.empty())
	{
		AllSkillInfo_.clear();
	}

	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// ��� ����
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllSkillInfo.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	AllSkillInfo_.resize(ClassCount_);

	for (int i = 0; i < ClassCount_; ++i)
	{
		// Ŭ������(������) : ����
		std::string ReadClassName = "";
		pFile.Read(ReadClassName);
		AllSkillInfo_[i].ClassName = ReadClassName;

		// Ŭ����(���� Ÿ��)
		int ReadJobType = 0;
		pFile.Read(ReadJobType);
		AllSkillInfo_[i].ClassType = static_cast<JobType>(ReadJobType);

		// Ŭ������ ��ų���
		int ReadSkillInfoCnt = 0;
		pFile.Read(ReadSkillInfoCnt);

		AllSkillInfo_[i].SkillList.resize(ReadSkillInfoCnt);

		// ��ų ����
		for (int j = 0; j < ReadSkillInfoCnt; ++j)
		{
			// �÷��̾� ��ų �⺻����

			// ��ų �����
			std::string ReadSkillName = "";
			pFile.Read(ReadSkillName);
			AllSkillInfo_[i].SkillList[j].SkillName = ReadSkillName;

			// ��ų�ڵ�
			int ReadSkillCode = 0;
			pFile.Read(ReadSkillCode);
			AllSkillInfo_[i].SkillList[j].SkillCode = ReadSkillCode;

			// ��ųŸ��
			int ReadSkillType = 0;
			pFile.Read(ReadSkillType);
			AllSkillInfo_[i].SkillList[j].SkillType = static_cast<SkillType>(ReadSkillType);

			// �÷��̾� ��ųâ�� ���� ������ No
			int ReadSkillPage = 0;
			pFile.Read(ReadSkillPage);
			AllSkillInfo_[i].SkillList[j].SkillPage = ReadSkillPage;

			// �÷��̾� ��ųâ�� ���� �������� Row
			int ReadSkillRow = 0;
			pFile.Read(ReadSkillRow);
			AllSkillInfo_[i].SkillList[j].SkillRow = ReadSkillRow;

			// �÷��̾� ��ųâ�� ���� �������� Column
			int ReadSkillColumn = 0;
			pFile.Read(ReadSkillColumn);
			AllSkillInfo_[i].SkillList[j].SkillColumn = ReadSkillColumn;

			// �ش� ��ų Ȱ��ȭ ����(��ų����)
			int ReadreqSkillLevel = 0;
			pFile.Read(ReadreqSkillLevel);
			AllSkillInfo_[i].SkillList[j].reqSkillLevel = ReadreqSkillLevel;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�1)
			std::string ReadreqSkillName1 = "";
			pFile.Read(ReadreqSkillName1);
			AllSkillInfo_[i].SkillList[j].reqSkillName1 = ReadreqSkillName1;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�1)
			int ReadreqSkillCode1 = 0;
			pFile.Read(ReadreqSkillCode1);
			AllSkillInfo_[i].SkillList[j].reqSkillCode1 = ReadreqSkillCode1;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�2)
			std::string ReadreqSkillName2 = "";
			pFile.Read(ReadreqSkillName2);
			AllSkillInfo_[i].SkillList[j].reqSkillName2 = ReadreqSkillName2;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�2)
			int ReadreqSkillCode2 = 0;
			pFile.Read(ReadreqSkillCode2);
			AllSkillInfo_[i].SkillList[j].reqSkillCode2 = ReadreqSkillCode2;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�3)
			std::string ReadreqSkillName3 = "";
			pFile.Read(ReadreqSkillName3);
			AllSkillInfo_[i].SkillList[j].reqSkillName3 = ReadreqSkillName3;

			// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�3)
			int ReadreqSkillCode3 = 0;
			pFile.Read(ReadreqSkillCode3);
			AllSkillInfo_[i].SkillList[j].reqSkillCode3 = ReadreqSkillCode3;

			// �ִ� ��ų����
			int ReadMaxSkillLevel = 0;
			pFile.Read(ReadMaxSkillLevel);
			AllSkillInfo_[i].SkillList[j].MaxSkillLevel = ReadMaxSkillLevel;

			// ���� ��ų����
			int ReadCurSkillLevel = 0;
			pFile.Read(ReadCurSkillLevel);
			AllSkillInfo_[i].SkillList[j].CurSkillLevel = ReadCurSkillLevel;

			// �÷��̾� ��ų ������(�Ǵܿ� Flag)

			// ��ų��밡�ɿ���(�ʱ⿡ 0����ų�� �Ϲݰ��ݸ� TRUE ����)
			int ReadSkillActive = 0;
			pFile.Read(ReadSkillActive);
			if (1 == ReadSkillActive)
			{
				AllSkillInfo_[i].SkillList[j].SkillActive = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].SkillActive = false;
			}

			// ���� �������ִ� ��ų���� �Ǵ�(TURE : ���������)
			int ReadLineOfSight = 0;
			pFile.Read(ReadLineOfSight);
			if (1 == ReadLineOfSight)
			{
				AllSkillInfo_[i].SkillList[j].LineOfSight = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].LineOfSight = false;
			}

			// ��ų ������ �÷��̾ �ǰݻ��°� �Ǹ� �ش� ��ų������ ��ҵǴ��� �Ǵ�(TRUE : ��ҵ�)
			int ReadInterrupt = 0;
			pFile.Read(ReadInterrupt);
			if (1 == ReadInterrupt)
			{
				AllSkillInfo_[i].SkillList[j].Interrupt = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].Interrupt = false;
			}

			// ���������� ��밡���� ��ų���� �Ǵ�(TRUE : ������ ��밡��)
			int ReadInTown = 0;
			pFile.Read(ReadInTown);
			if (1 == ReadInTown)
			{
				AllSkillInfo_[i].SkillList[j].InTown = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].InTown = false;
			}

			// �ش� ��ų�� �нú� ��ų���� �Ǵ�(TRUE : �нú꽺ų�� �Ǵ�) - �÷��̾� ������
			int ReadIsPassive = 0;
			pFile.Read(ReadIsPassive);
			if (1 == ReadIsPassive)
			{
				AllSkillInfo_[i].SkillList[j].IsPassive = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].IsPassive = false;
			}

			// �ش� ��ų�� ����� ��ų���� �Ǵ�(TRUE : �������ų) - ���� �������
			int ReadIsDebuff = 0;
			pFile.Read(ReadIsDebuff);
			if (1 == ReadIsDebuff)
			{
				AllSkillInfo_[i].SkillList[j].IsDebuff = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].IsDebuff = false;
			}

			// �ش� ��ų ���� �����Ҹ𿩺� �Ǵ�(TRUE : �����Ҹ���)
			int ReadManaUse = 0;
			pFile.Read(ReadManaUse);
			if (1 == ReadManaUse)
			{
				AllSkillInfo_[i].SkillList[j].ManaUse = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].ManaUse = false;
			}

			// ���ʹ��⿡ ���������� ��ų���� �Ǵ�(TRUE : ��밡��)
			int ReadLeftSkillUse = 0;
			pFile.Read(ReadLeftSkillUse);
			if (1 == ReadLeftSkillUse)
			{
				AllSkillInfo_[i].SkillList[j].LeftSkillUse = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].LeftSkillUse = false;
			}

			// �ش� ��ų�� ���� ��ü�� ���������� ��ų���� �Ǵ�(TRUE : ��������) - ��ȯ�� ��ų����
			int ReadIsSelDead = 0;
			pFile.Read(ReadIsSelDead);
			if (1 == ReadIsSelDead)
			{
				AllSkillInfo_[i].SkillList[j].IsSelDead = true;
			}
			else
			{
				AllSkillInfo_[i].SkillList[j].IsSelDead = false;
			}

			// IsPassive = TURE �϶� ���

			// �нú� Ÿ��
			int ReadPassiveType = 0;
			pFile.Read(ReadPassiveType);
			AllSkillInfo_[i].SkillList[j].PassiveType = static_cast<SkillPassiveType>(ReadPassiveType);

			// ��ų������ ������ ������
			int ReadPassiveLifePerLevel = 0;
			pFile.Read(ReadPassiveLifePerLevel);
			AllSkillInfo_[i].SkillList[j].PassiveLifePerLevel = ReadPassiveLifePerLevel;

			// ��ų������ ���ʽ� ������ ������(��ü�� ���õ� ������ ����ü���� �ۼ�Ʈ : 100% ����)
			int ReadPassiveBonusLifePerLevel = 0;
			pFile.Read(ReadPassiveBonusLifePerLevel);
			AllSkillInfo_[i].SkillList[j].PassiveBonusLifePerLevel = ReadPassiveBonusLifePerLevel;

			// ��ų������ �̵��ӵ� ������(100% ����)
			int ReadPassiveVelocityPerLevel = 0;
			pFile.Read(ReadPassiveVelocityPerLevel);
			AllSkillInfo_[i].SkillList[j].PassiveVelocityPerLevel = ReadPassiveVelocityPerLevel;

			// ��ų������ ������ ������
			int ReadPassiveDamagePerLevel = 0;
			pFile.Read(ReadPassiveDamagePerLevel);
			AllSkillInfo_[i].SkillList[j].PassiveDamagePerLevel = ReadPassiveDamagePerLevel;

			// ��ų������ ���Ӽ� ���׷� ������(100% ����)
			int ReadPassiveResistAllPerLevel = 0;
			pFile.Read(ReadPassiveResistAllPerLevel);
			AllSkillInfo_[i].SkillList[j].PassiveResistAllPerLevel = ReadPassiveResistAllPerLevel;

			// IsDebuff = TRUE �϶� ���

			// �ش� ��ų�� ���� ���Ͱ� �޴� �����ȿ�� Ÿ��
			int ReadDebuffType = 0;
			pFile.Read(ReadDebuffType);
			AllSkillInfo_[i].SkillList[j].DebuffType = static_cast<SkillDebuffType>(ReadDebuffType);

			// �ش� ��ų������ �÷��̾ �޴� ����ȿ�� Ÿ��
			int ReadBuffType = 0;
			pFile.Read(ReadDebuffType);
			AllSkillInfo_[i].SkillList[j].BuffType = static_cast<SkillBuffType>(ReadBuffType);

			// ���ӽð�(1������) - 100% ����(�� / 100)
			int ReadDebuffDuration = 0;
			pFile.Read(ReadDebuffDuration);
			AllSkillInfo_[i].SkillList[j].DebuffDuration = ReadDebuffDuration;

			// ��ų������ ����� ���ӽð� ������ - 100% ����(�� / 100)
			int ReadDebuffDurationPerLevel = 0;
			pFile.Read(ReadDebuffDurationPerLevel);
			AllSkillInfo_[i].SkillList[j].DebuffDurationPerLevel = ReadDebuffDurationPerLevel;

			// ��ų������ ����� Ÿ���� ������ ������
			int ReadDebuffDamagePerLevel = 0;
			pFile.Read(ReadDebuffDamagePerLevel);
			AllSkillInfo_[i].SkillList[j].DebuffDamagePerLevel = ReadDebuffDamagePerLevel;

			// ManaUse = TURE�϶� ���

			// �����Ҹ�
			int ReadManaUsage = 0;
			pFile.Read(ReadManaUsage);
			AllSkillInfo_[i].SkillList[j].ManaUsage = ReadManaUsage;

			// 

			// ��ų ������
			int ReadSkillDamage = 0;
			pFile.Read(ReadSkillDamage);
			AllSkillInfo_[i].SkillList[j].SkillDamage = ReadSkillDamage;

			// ��ų ���� �����̽ð�
			int ReadSkillDelay = 0;
			pFile.Read(ReadSkillDelay);
			AllSkillInfo_[i].SkillList[j].SkillDelay = ReadSkillDelay;
		}
	}

	pFile.Close();
}

void AllSkillInfomation::SaveSkillBinaryFile()
{
	// ������ ��ų����� ��������ʴٸ� �ε忡 ���������Ƿ� 
	// Excel�� ������� ���� ���� ����Ͽ� DataFile�� ������ش�
	// AllSkillInfo.dat ��Ī �� wb �������� ���� �����Ͽ� ������� ����
	if (!AllSkillInfo_.empty())
	{
		GameEngineDirectory DataFileDir;
		DataFileDir.MoveParent("DirectX");
		DataFileDir.MoveChild("Resources");
		DataFileDir.MoveChild("DataFile");

		// ��� ����
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllSkillInfo.dat";

		// ���� ����
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		for (int i = 0; i < ClassCount_; ++i)
		{
			// Ŭ������(������) : ����
			pFile.Write(AllSkillInfo_[i].ClassName);

			// Ŭ����(���� Ÿ��)
			pFile.Write(static_cast<int>(AllSkillInfo_[i].ClassType));

			// Ŭ������ ��ų���
			int SkillInfoSize = static_cast<int>(AllSkillInfo_[i].SkillList.size());

			// ��ų ��� ���� ����
			pFile.Write(SkillInfoSize);

			// ��ų ����
			for (int j = 0; j < SkillInfoSize; ++j)
			{
				// �÷��̾� ��ų �⺻����

				// ��ų �����
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillName);

				// ��ų�ڵ�
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillCode);

				// ��ųŸ��
				pFile.Write(static_cast<int>(AllSkillInfo_[i].SkillList[j].SkillType));

				// �÷��̾� ��ųâ�� ���� ������ No
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillPage);

				// �÷��̾� ��ųâ�� ���� �������� Row
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillRow);

				// �÷��̾� ��ųâ�� ���� �������� Column
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillColumn);

				// �ش� ��ų Ȱ��ȭ ����(��ų����)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillLevel);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�1)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillName1);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�1)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillCode1);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�2)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillName2);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�2)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillCode2);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�̸�3)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillName3);

				// �ش� ��ų Ȱ��ȭ ����(���ེų�ڵ�3)
				pFile.Write(AllSkillInfo_[i].SkillList[j].reqSkillCode3);

				// �ִ� ��ų����
				pFile.Write(AllSkillInfo_[i].SkillList[j].MaxSkillLevel);

				// ���� ��ų����
				pFile.Write(AllSkillInfo_[i].SkillList[j].CurSkillLevel);

				// �÷��̾� ��ų ������(�Ǵܿ� Flag)

				// ��ų��밡�ɿ���(�ʱ⿡ 0����ų�� �Ϲݰ��ݸ� TRUE ����)
				if (true == AllSkillInfo_[i].SkillList[j].SkillActive)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// ���� �������ִ� ��ų���� �Ǵ�(TURE : ���������)
				if (true == AllSkillInfo_[i].SkillList[j].LineOfSight)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// ��ų ������ �÷��̾ �ǰݻ��°� �Ǹ� �ش� ��ų������ ��ҵǴ��� �Ǵ�(TRUE : ��ҵ�)
				if (true == AllSkillInfo_[i].SkillList[j].Interrupt)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// ���������� ��밡���� ��ų���� �Ǵ�(TRUE : ������ ��밡��)
				if (true == AllSkillInfo_[i].SkillList[j].InTown)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// �ش� ��ų�� �нú� ��ų���� �Ǵ�(TRUE : �нú꽺ų�� �Ǵ�) - �÷��̾� ������
				if (true == AllSkillInfo_[i].SkillList[j].IsPassive)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// �ش� ��ų�� ����� ��ų���� �Ǵ�(TRUE : �������ų) - ���� �������
				if (true == AllSkillInfo_[i].SkillList[j].IsDebuff)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// �ش� ��ų ���� �����Ҹ𿩺� �Ǵ�(TRUE : �����Ҹ���)
				if (true == AllSkillInfo_[i].SkillList[j].ManaUse)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// ���ʹ��⿡ ���������� ��ų���� �Ǵ�(TRUE : ��밡��)
				if (true == AllSkillInfo_[i].SkillList[j].LeftSkillUse)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// �ش� ��ų�� ���� ��ü�� ���������� ��ų���� �Ǵ�(TRUE : ��������) - ��ȯ�� ��ų����
				if (true == AllSkillInfo_[i].SkillList[j].IsSelDead)
				{
					pFile.Write(1);
				}
				else
				{
					pFile.Write(0);
				}

				// IsPassive = TURE �϶� ���

				// �нú� Ÿ��
				pFile.Write(static_cast<int>(AllSkillInfo_[i].SkillList[j].PassiveType));

				// ��ų������ ������ ������
				pFile.Write(AllSkillInfo_[i].SkillList[j].PassiveLifePerLevel);

				// ��ų������ ���ʽ� ������ ������(��ü�� ���õ� ������ ����ü���� �ۼ�Ʈ : 100% ����)
				pFile.Write(AllSkillInfo_[i].SkillList[j].PassiveBonusLifePerLevel);

				// ��ų������ �̵��ӵ� ������(100% ����)
				pFile.Write(AllSkillInfo_[i].SkillList[j].PassiveVelocityPerLevel);

				// ��ų������ ������ ������
				pFile.Write(AllSkillInfo_[i].SkillList[j].PassiveDamagePerLevel);

				// ��ų������ ���Ӽ� ���׷� ������(100% ����)
				pFile.Write(AllSkillInfo_[i].SkillList[j].PassiveResistAllPerLevel);

				// IsDebuff = TRUE �϶� ���

				// �ش� ��ų�� ���� ���Ͱ� �޴� �����ȿ�� Ÿ��
				pFile.Write(static_cast<int>(AllSkillInfo_[i].SkillList[j].DebuffType));

				// �ش� ��ų������ �÷��̾ �޴� ����ȿ�� Ÿ��
				pFile.Write(static_cast<int>(AllSkillInfo_[i].SkillList[j].BuffType));

				// ���ӽð�(1������) - 100% ����(�� / 100)
				pFile.Write(AllSkillInfo_[i].SkillList[j].DebuffDuration);

				// ��ų������ ����� ���ӽð� ������ - 100% ����(�� / 100)
				pFile.Write(AllSkillInfo_[i].SkillList[j].DebuffDurationPerLevel);

				// ��ų������ ����� Ÿ���� ������ ������
				pFile.Write(AllSkillInfo_[i].SkillList[j].DebuffDamagePerLevel);

				// ManaUse = TURE�϶� ���

				// �����Ҹ�
				pFile.Write(AllSkillInfo_[i].SkillList[j].ManaUsage);

				// 

				// ��ų ������
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillDamage);

				// ��ų ���� �����̽ð�
				pFile.Write(AllSkillInfo_[i].SkillList[j].SkillDelay);
			}
		}

		pFile.Close();
	}
}
