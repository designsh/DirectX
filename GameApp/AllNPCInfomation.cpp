#include "PreCompile.h"
#include "AllNPCInfomation.h"

AllNPCInfomation* AllNPCInfomation::Inst = new AllNPCInfomation();

AllNPCInfomation::AllNPCInfomation() :
	ExcelZFlag_(false)
{
}

AllNPCInfomation::~AllNPCInfomation()
{
}

bool AllNPCInfomation::NPCInfoFind(NPCClassType _ClassType, AllNPCInfo& _ClassNPCInfo)
{
	int NPCInfoSize = static_cast<int>(AllNPCList_.size());
	for (int i = 0; i < NPCInfoSize; ++i)
	{
		if (AllNPCList_[i].ClassType == _ClassType)
		{
			_ClassNPCInfo = AllNPCList_[i];
			return true;
		}
	}

	return false;
}

void AllNPCInfomation::CreateAllNPCInfomation(bool _ExcelFile)
{
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	if (true == _ExcelFile)
	{
		// ExcelDataFile ������ �ش� ������� ���̳ʸ� ���ϻ��� �ʿ�
		LoadNPCExcelFile();
		SaveNPCBinaryFile();
	}
	else
	{
		// ���������� �̰ɷ� �Ҳ���
		LoadNPCBinaryFile();
	}
}

void AllNPCInfomation::LoadNPCExcelFile()
{
	// ������ NPC������ ����ִٸ� Ŭ����
	if (!AllNPCList_.empty())
	{
		AllNPCList_.clear();
	}

	// ���� ���۰� ���ÿ� �ش� �Լ��� ȣ��Ǿ� ��� Ŭ������ NPC������ �����Ѵ�.
	CExcelControl* ExcelFile = new CExcelControl();

	// �ε� ���� ��� ����
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\NPCInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// ���н� -1 ��ȯ
	// �ε��ؾ��ϴ� ��Ʈ�� �Ѱ�
	if (1 == ExcelFile->Open(chFullPath))
	{
		// NPCInfo.xlsx ������ ��Ʈ�� �� 1��
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// ��� �÷��� �ο츦 �˻��Ͽ� ���������ε�
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < static_cast<int>(NPCClassType::MAX); ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // �÷� Z�� �Ѿ�� A1 ������ �÷������̹Ƿ� üũ�Ѵ�.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// �������� NPC��� ����
			AllNPCInfo NewNPCInfo = {};

			// ============================ NPC �⺻���� ============================ //

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
			NewNPCInfo.Name = pName;
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
			NewNPCInfo.ClassType = static_cast<NPCClassType>(ClassType);
			++RowNo;

			// NPC Ÿ��
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
			NewNPCInfo.Type = static_cast<NPCType>(Type);
			++RowNo;

			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� ���ΰ���((����/1024*��))
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pBuyMult[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pBuyMult);
			int BuyMult = 0;
			sscanf_s(pBuyMult, "%d", &BuyMult);
			NewNPCInfo.BuyMult = BuyMult;
			++RowNo;

			// NPC�� �÷��̾�� �����ǸŽ� ���ΰ���((����/1024*��))
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pSellMult[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pSellMult);
			int SellMult = 0;
			sscanf_s(pSellMult, "%d", &SellMult);
			NewNPCInfo.SellMult = SellMult;
			++RowNo;

			// NPC�� ������ ������ ����(floor(price/1024*value)) -> �������� �������� ������ �޴´�.
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pRepMult[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pRepMult);
			int RepMult = 0;
			sscanf_s(pRepMult, "%d", &RepMult);
			NewNPCInfo.RepMult = RepMult;
			++RowNo;

			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� �ִ밡��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMaxBuy[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMaxBuy);
			int MaxBuy = 0;
			sscanf_s(pMaxBuy, "%d", &MaxBuy);
			NewNPCInfo.MaxBuy = MaxBuy;
			++RowNo;

			AllNPCList_.push_back(NewNPCInfo);

			if (RowNo > 7)
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

void AllNPCInfomation::LoadNPCBinaryFile()
{
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// ��� ����
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllNPCInfo.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// NPC���� ������ ���� ó���� ���������Ƿ� NPC���� ���� Read
	int NPCCnt = 0;
	pFile.Read(NPCCnt);
	AllNPCList_.resize(NPCCnt);

	for (int i = 0; i < NPCCnt; ++i)
	{
		// ============================ NPC �⺻���� ============================ //

		// NPC ��
		std::string Name = "";
		pFile.Read(Name);
		AllNPCList_[i].Name = Name;

		// NPC Ŭ���� Ÿ��
		int ClassType = 0;
		pFile.Read(ClassType);
		AllNPCList_[i].ClassType = static_cast<NPCClassType>(ClassType);

		// NPC Ÿ��
		int Type = 0;
		pFile.Read(Type);
		AllNPCList_[i].Type = static_cast<NPCType>(Type);

		// NPC�� �÷��̾�κ��� ���Ǳ��Ž� ���ΰ���((����/1024*��))
		int BuyMult = 0;
		pFile.Read(BuyMult);
		AllNPCList_[i].BuyMult = BuyMult;

		// NPC�� �÷��̾�� �����ǸŽ� ���ΰ���((����/1024*��))
		int SellMult = 0;
		pFile.Read(SellMult);
		AllNPCList_[i].SellMult = SellMult;

		// NPC�� ������ ������ ����(floor(price/1024*value)) -> �������� �������� ������ �޴´�.
		int RepMult = 0;
		pFile.Read(RepMult);
		AllNPCList_[i].RepMult = RepMult;

		// NPC�� �÷��̾�κ��� ���Ǳ��Ž� �ִ밡��		
		int MaxBuy = 0;
		pFile.Read(MaxBuy);
		AllNPCList_[i].MaxBuy = MaxBuy;
	}

	pFile.Close();
}

void AllNPCInfomation::SaveNPCBinaryFile()
{
	if (!AllNPCList_.empty())
	{
		GameEngineDirectory DataFileDir;
		DataFileDir.MoveParent("DirectX");
		DataFileDir.MoveChild("Resources");
		DataFileDir.MoveChild("DataFile");

		// ��� ����
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllNPCInfo.dat";

		// ���� ����
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// NPC���� ���� ����
		int AllNPCCnt = static_cast<int>(AllNPCList_.size());
		pFile.Write(AllNPCCnt);

		for (int i = 0; i < AllNPCCnt; ++i)
		{
			// ============================ NPC �⺻���� ============================ //
			// NPC ��
			pFile.Write(AllNPCList_[i].Name);

			// NPC Ŭ���� Ÿ��
			pFile.Write(static_cast<int>(AllNPCList_[i].ClassType));

			// NPC Ÿ��
			pFile.Write(static_cast<int>(AllNPCList_[i].Type));

			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� ���ΰ���((����/1024*��))
			pFile.Write(AllNPCList_[i].BuyMult);

			// NPC�� �÷��̾�� �����ǸŽ� ���ΰ���((����/1024*��))
			pFile.Write(AllNPCList_[i].SellMult);

			// NPC�� ������ ������ ����(floor(price/1024*value)) -> �������� �������� ������ �޴´�.
			pFile.Write(AllNPCList_[i].RepMult);

			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� �ִ밡��		
			pFile.Write(AllNPCList_[i].MaxBuy);
		}

		pFile.Close();
	}
}
