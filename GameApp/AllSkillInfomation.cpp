#include "PreCompile.h"
#include "AllSkillInfomation.h"

#include <GameEngineBase/ExcelControl.h>

AllSkillInfomation* AllSkillInfomation::Inst = new AllSkillInfomation();

AllSkillInfomation::AllSkillInfomation() :
	ZFlag_(false)
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

void AllSkillInfomation::CreateAllSkillInfomation()
{
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	LoadSkillExcelFile();

	// ������ ��ų����� ��������ʴٸ� �ε忡 ���������Ƿ� 
	// Excel�� ������� ���� ���� ����Ͽ� DataFile�� ������ش�
	// AllSkillInfo.dat ��Ī �� wb �������� ���� �����Ͽ� ������� ����
	if (!AllSkillInfo_.empty())
	{
		GameEngineDirectory DataFileDir;
		DataFileDir.MoveParent("DirectX");
		DataFileDir.MoveChild("Resources");
		DataFileDir.MoveChild("DataFile");






		int a = 0;
	}
}

void AllSkillInfomation::LoadSkillExcelFile()
{
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
				if (ZFlag_) // �÷� Z�� �Ѿ�� A1 ������ �÷������̹Ƿ� üũ�Ѵ�.
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
					memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
				else
					memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
				strcat_s(ColRowName, RowNumber);

				char pSkillPageRow[MAX_PATH] = {};
				ExcelFile->GetData(ColRowName, pSkillPageRow);
				int SkillPageRow = 0;
				sscanf_s(pSkillPageRow, "%d", &SkillPageRow);
				NewSkillInfo.SkillPage = SkillPageRow;
				++RowNo;

				// �÷��̾� ��ųâ�� ���� �������� Column
				memset(&RowNumber, 0, sizeof(RowNumber));
				strcpy_s(RowNumber, std::to_string(RowNo).c_str());
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
				if (ZFlag_)
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
					ZFlag_ = true;
				}
			}

			// �ε�Ϸ��� ��Ʈ(Ŭ����)�� ��ų������ �������(������)�� ����
			AllSkillInfo_.push_back(NewAllSkill);

			ZFlag_ = false;
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
