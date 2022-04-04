#include "PreCompile.h"
#include "AllItemInfomation.h"

AllItemInfomation* AllItemInfomation::Inst = new AllItemInfomation();

AllItemInfomation::AllItemInfomation() :
	ExcelZFlag_(false)
{
}

AllItemInfomation::~AllItemInfomation()
{
}

bool AllItemInfomation::ItemInfoFind(const std::string& _ItemName, ItemList& _ItemInfo)
{
	int ItemListSize = static_cast<int>(AllItemList_.size());
	for (int i = 0; i < ItemListSize; ++i)
	{
		if (AllItemList_[i].ItemName_abbreviation == _ItemName)
		{
			_ItemInfo = AllItemList_[i];
			return true;
		}
	}

	return false;
}

void AllItemInfomation::CreateAllItemInfomation(bool _ExcelFile)
{
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	if (true == _ExcelFile)
	{
		// ExcelDataFile ������ �ش� ������� ���̳ʸ� ���ϻ��� �ʿ�
		LoadItemExcelFile();
		SaveItemBinaryFile();
	}
	else
	{
		// ���������� �̰ɷ� �Ҳ���
		LoadItemBinaryFile();
	}
}

void AllItemInfomation::LoadItemExcelFile()
{
	// ������ ��ų������ ����ִٸ� Ŭ����
	if (!AllItemList_.empty())
	{
		AllItemList_.clear();
	}

	// ���� ���۰� ���ÿ� �ش� �Լ��� ȣ��Ǿ� ��� Ŭ������ ��ų������ �����Ѵ�.
	CExcelControl* ExcelFile = new CExcelControl();

	// �ε� ���� ��� ����
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\ItemInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// ���н� -1 ��ȯ
	// �ε��ؾ��ϴ� ��Ʈ�� �Ѱ�
	if (1 == ExcelFile->Open(chFullPath))
	{
		// ItemInfo.xlsx ������ ��Ʈ�� �� 1��
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// ��� �÷��� �ο츦 �˻��Ͽ� ��ų�����ε�
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < ALL_ITEM_CNT; ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // �÷� Z�� �Ѿ�� A1 ������ �÷������̹Ƿ� üũ�Ѵ�.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// �������� �����۸�� ����
			ItemList NewItemInfo = {};

			// ============================== �÷��̾� ���������� ============================== //

			// �������̸� ���
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pItemNameEng[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pItemNameEng);
			NewItemInfo.ItemName_abbreviation = pItemNameEng;
			++RowNo;

			// �������̸� ���(�κ��丮��)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pSItemNameInven[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pSItemNameInven);
			std::string sSItemNameInven = pSItemNameInven;
			NewItemInfo.ItemName_abbreviation_Inven = sSItemNameInven;
			++RowNo;

			// �������ڵ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pItemCode[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pItemCode);
			int ItemCode = 0;
			sscanf_s(pItemCode, "%d", &ItemCode);
			NewItemInfo.ItemCode = ItemCode;
			++RowNo;

			// ������Ÿ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pItemType[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pItemType);
			int intItemType = 0;
			sscanf_s(pItemType, "%d", &intItemType);
			NewItemInfo.ItemType = static_cast<ItemType>(intItemType);
			++RowNo;

			// ������ ��������

			// ��������ġ(�κ��丮, �ϴܻ��¹�, â��, �Ǹ�â)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pItemLocType[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pItemLocType);
			int intItemLocType = 0;
			sscanf_s(pItemLocType, "%d", &intItemLocType);
			NewItemInfo.ItemLocType = static_cast<ItemLocType>(intItemLocType);
			++RowNo;

			// ������ â���� �����ϴ� ��ġ�� �ε���
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pStartPosition[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pStartPosition);
			int StartPosition = 0;
			sscanf_s(pStartPosition, "%d", &StartPosition);
			NewItemInfo.StartPosition = StartPosition;
			++RowNo;

			// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� �ʺ�ĭ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pWidthSize[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pWidthSize);
			int WidthSize = 0;
			sscanf_s(pWidthSize, "%d", &WidthSize);
			NewItemInfo.WidthSize = WidthSize;
			++RowNo;

			// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� ����ĭ��
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pHeightSize[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pHeightSize);
			int HeightSize = 0;
			sscanf_s(pHeightSize, "%d", &HeightSize);
			NewItemInfo.HeightSize = HeightSize;
			++RowNo;

			// ������ ������

			// ������ ��뿩�� �Ǵ�(TRUE : ���������)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pIsDurability[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pIsDurability);
			int IsDurability = 0;
			sscanf_s(pIsDurability, "%d", &IsDurability);
			if (1 == IsDurability)
			{
				NewItemInfo.IsDurability = true;
			}
			else
			{
				NewItemInfo.IsDurability = false;
			}
			++RowNo;

			// �ִ� ������
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pMaxDurability[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pMaxDurability);
			int MaxDurability = 0;
			sscanf_s(pMaxDurability, "%d", &MaxDurability);
			NewItemInfo.MaxDurability = MaxDurability;
			++RowNo;

			// ���� ������
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pCurDurability[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pCurDurability);
			int CurDurability = 0;
			sscanf_s(pCurDurability, "%d", &CurDurability);
			NewItemInfo.CurDurability = CurDurability;
			++RowNo;

			// �ǰ�����Ȯ��
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
			NewItemInfo.Block = Block;
			++RowNo;

			// �����۹���(�÷��̾� �̵��ӵ� ����)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pWeight[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pWeight);
			int Weight = 0;
			sscanf_s(pWeight, "%d", &Weight);
			NewItemInfo.Weight = Weight;
			++RowNo;

			// ������ ���(�Ǹ�â���� �Ǹ��ϴ� ���)
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pPrice[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pPrice);
			int Price = 0;
			sscanf_s(pPrice, "%d", &Price);
			NewItemInfo.Price = Price;
			++RowNo;

			// ������ ������ �������ݷ�
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pPullDamage[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pPullDamage);
			int PullDamage = 0;
			sscanf_s(pPullDamage, "%d", &PullDamage);
			NewItemInfo.PullDamage = PullDamage;
			++RowNo;

			// ������ ������ ��������
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pPullArmor[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pPullArmor);
			int PullArmor = 0;
			sscanf_s(pPullArmor, "%d", &PullArmor);
			NewItemInfo.PullArmor = PullArmor;
			++RowNo;

			// ȸ����(���ǿ�) : �ۼ�Ʈ
			memset(RowNumber, 0, sizeof(RowNumber));
			strcpy_s(RowNumber, std::to_string(RowNo).c_str());
			if (ExcelZFlag_)
				memset(&ColRowName[2], 0, sizeof(ColRowName) - 2);
			else
				memset(&ColRowName[1], 0, sizeof(ColRowName) - 1);
			strcat_s(ColRowName, RowNumber);

			char pRecovery[MAX_PATH] = {};
			ExcelFile->GetData(ColRowName, pRecovery);
			int Recovery = 0;
			sscanf_s(pRecovery, "%d", &Recovery);
			NewItemInfo.Recovery = Recovery;
			++RowNo;

			AllItemList_.push_back(NewItemInfo);

			if (RowNo > 17)
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

void AllItemInfomation::LoadItemBinaryFile()
{
	// ������ ��ų������ ����ִٸ� Ŭ����
	if (!AllItemList_.empty())
	{
		AllItemList_.clear();
	}

	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// ��� ����
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllItemInfo.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// ������ ������ ���� ó���� ���������Ƿ� ������ ���� Read
	int ItemCnt = 0;
	pFile.Read(ItemCnt);
	AllItemList_.resize(ItemCnt);

	for (int i = 0; i < ItemCnt; ++i)
	{
		// ============================== �÷��̾� ���������� ============================== //
		// �����۸�(���)
		std::string ReadItemName_Eng = "";
		pFile.Read(ReadItemName_Eng);
		AllItemList_[i].ItemName_abbreviation = ReadItemName_Eng;

		// �����۸�(���)-�κ��丮��
		std::string ReadItemNameInven = "";
		pFile.Read(ReadItemNameInven);
		AllItemList_[i].ItemName_abbreviation_Inven = ReadItemNameInven;

		// �������ڵ�
		int ReadItemCode = 0;
		pFile.Read(ReadItemCode);
		AllItemList_[i].ItemCode = ReadItemCode;

		// ������Ÿ��
		int ReadItemType = 0;
		pFile.Read(ReadItemType);
		AllItemList_[i].ItemType = static_cast<ItemType>(ReadItemType);

		// ������ ��������

		// ��������ġ(�κ��丮, �ϴܻ��¹�, â��, �Ǹ�â)
		int ReadItemLocType = 0;
		pFile.Read(ReadItemLocType);
		AllItemList_[i].ItemLocType = static_cast<ItemLocType>(ReadItemLocType);

		// ������ â���� �����ϴ� ��ġ�� �ε���
		int ReadStartPosition = 0;
		pFile.Read(ReadStartPosition);
		AllItemList_[i].StartPosition = ReadStartPosition;

		// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� �ʺ�ĭ��
		int ReadWidthSize = 0;
		pFile.Read(ReadWidthSize);
		AllItemList_[i].WidthSize = ReadWidthSize;

		// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� ����ĭ��
		int ReadHeightSize = 0;
		pFile.Read(ReadHeightSize);
		AllItemList_[i].HeightSize = ReadHeightSize;

		// ������ ������

		// ������ ��뿩�� �Ǵ�(TRUE : ���������)
		int ReadIsDurability = 0;
		pFile.Read(ReadIsDurability);
		if (1 == ReadIsDurability)
		{
			AllItemList_[i].HeightSize = true;
		}
		else
		{
			AllItemList_[i].HeightSize = false;
		}

		// �ִ� ������
		int ReadMaxDurability = 0;
		pFile.Read(ReadMaxDurability);
		AllItemList_[i].MaxDurability = ReadMaxDurability;

		// ���� ������
		int ReadCurDurability = 0;
		pFile.Read(ReadCurDurability);
		AllItemList_[i].CurDurability = ReadCurDurability;

		// �ǰ�����Ȯ��
		int ReadBlock = 0;
		pFile.Read(ReadBlock);
		AllItemList_[i].Block = ReadBlock;

		// �����۹���(�÷��̾� �̵��ӵ� ����)
		int ReadWeight = 0;
		pFile.Read(ReadWeight);
		AllItemList_[i].Weight = ReadWeight;

		// ������ ���(�Ǹ�â���� �Ǹ��ϴ� ���)
		int ReadPrice = 0;
		pFile.Read(ReadPrice);
		AllItemList_[i].Price = ReadPrice;

		// ������ ������ �������ݷ�
		int ReadPullDamage = 0;
		pFile.Read(ReadPullDamage);
		AllItemList_[i].PullDamage = ReadPullDamage;

		// ������ ������ ��������
		int ReadPullArmor = 0;
		pFile.Read(ReadPullArmor);
		AllItemList_[i].PullArmor = ReadPullArmor;

		// ȸ����(���ǿ�) : �ۼ�Ʈ
		int ReadRecovery = 0;
		pFile.Read(ReadRecovery);
		AllItemList_[i].Recovery = ReadRecovery;
	}

	pFile.Close();
}

void AllItemInfomation::SaveItemBinaryFile()
{
	if (!AllItemList_.empty())
	{
		GameEngineDirectory DataFileDir;
		DataFileDir.MoveParent("DirectX");
		DataFileDir.MoveChild("Resources");
		DataFileDir.MoveChild("DataFile");

		// ��� ����
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllItemInfo.dat";

		// ���� ����
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// ������ ���� ����
		int AllItemCnt = static_cast<int>(AllItemList_.size());
		pFile.Write(AllItemCnt);

		for (int i = 0; i < AllItemCnt; ++i)
		{
			// ============================== �÷��̾� ���������� ============================== //
			// �����۸�(���)
			pFile.Write(AllItemList_[i].ItemName_abbreviation);

			// �����۸�(���)-�κ���
			pFile.Write(AllItemList_[i].ItemName_abbreviation_Inven);

			// �������ڵ�
			pFile.Write(AllItemList_[i].ItemCode);

			// ������Ÿ��
			pFile.Write(static_cast<int>(AllItemList_[i].ItemType));

			// ������ ��������

			// ��������ġ(�κ��丮, �ϴܻ��¹�, â��, �Ǹ�â)
			pFile.Write(static_cast<int>(AllItemList_[i].ItemLocType));

			// ������ â���� �����ϴ� ��ġ�� �ε���
			pFile.Write(AllItemList_[i].StartPosition);

			// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� �ʺ�ĭ��
			pFile.Write(AllItemList_[i].WidthSize);

			// �����۳��� -> �̺��丮 or â�� or �Ǹ�â���� �����ϴ� ����ĭ��
			pFile.Write(AllItemList_[i].HeightSize);

			// ������ ������

			// ������ ��뿩�� �Ǵ�(TRUE : ���������)
			if (true == AllItemList_[i].IsDurability)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// �ִ� ������
			pFile.Write(AllItemList_[i].MaxDurability);

			// ���� ������
			pFile.Write(AllItemList_[i].CurDurability);

			// �ǰ�����Ȯ��
			pFile.Write(AllItemList_[i].Block);

			// �����۹���(�÷��̾� �̵��ӵ� ����)
			pFile.Write(AllItemList_[i].Weight);

			// ������ ���(�Ǹ�â���� �Ǹ��ϴ� ���)
			pFile.Write(AllItemList_[i].Price);

			// ������ ������ �������ݷ�
			pFile.Write(AllItemList_[i].PullDamage);

			// ������ ������ ��������
			pFile.Write(AllItemList_[i].PullArmor);

			// ȸ����(���ǿ�) : �ۼ�Ʈ
			pFile.Write(AllItemList_[i].Recovery);
		}

		pFile.Close();
	}
}
