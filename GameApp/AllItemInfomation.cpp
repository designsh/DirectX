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
	// 모든 클래스의 스킬을 모두 로드하여 정보로 관리
	if (true == _ExcelFile)
	{
		// ExcelDataFile 수정시 해당 기능으로 바이너리 파일생성 필요
		LoadItemExcelFile();
		SaveItemBinaryFile();
	}
	else
	{
		// 실질적으로 이걸로 할꺼임
		LoadItemBinaryFile();
	}
}

void AllItemInfomation::LoadItemExcelFile()
{
	// 기존의 스킬정보를 들고있다면 클리어
	if (!AllItemList_.empty())
	{
		AllItemList_.clear();
	}

	// 게임 시작과 동시에 해당 함수가 호출되어 모든 클래스의 스킬정보를 생성한다.
	CExcelControl* ExcelFile = new CExcelControl();

	// 로드 파일 경로 편집
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\ItemInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// 실패시 -1 반환
	// 로드해야하는 시트는 한개
	if (1 == ExcelFile->Open(chFullPath))
	{
		// ItemInfo.xlsx 파일의 시트는 총 1개
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// 모든 컬럼과 로우를 검사하여 스킬정보로드
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < ALL_ITEM_CNT; ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // 컬럼 Z가 넘어가면 A1 식으로 컬럼진행이므로 체크한다.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// 실질적인 아이템목록 생성
			ItemList NewItemInfo = {};

			// ============================== 플레이어 아이템정보 ============================== //

			// 아이템이름 약어
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

			// 아이템이름 약어(인벤토리용)
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

			// 아이템코드
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

			// 아이템타입
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

			// 아이템 장착정보

			// 아이템위치(인벤토리, 하단상태바, 창고, 판매창)
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

			// 각각의 창에서 시작하는 위치의 인덱스
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

			// 아이템넓이 -> 이벤토리 or 창고 or 판매창에서 차지하는 너비칸수
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

			// 아이템높이 -> 이벤토리 or 창고 or 판매창에서 차지하는 높이칸수
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

			// 아이템 상세정보

			// 내구도 사용여부 판단(TRUE : 내구도사용)
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

			// 최대 내구도
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

			// 현재 내구도
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

			// 피격차단확률
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

			// 아이템무게(플레이어 이동속도 감소)
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

			// 아이템 비용(판매창에서 판매하는 비용)
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

			// 아이템 장착시 증가공격력
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

			// 아이템 장착시 증가방어력
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

			// 회복량(포션용) : 퍼센트
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

		// 파일 종료 및 권한 모두 릴리즈
		ExcelFile->Close();
	}

	// 컨트롤러 제거
	if (nullptr != ExcelFile)
	{
		delete ExcelFile;
		ExcelFile = nullptr;
	}
}

void AllItemInfomation::LoadItemBinaryFile()
{
	// 기존의 스킬정보를 들고있다면 클리어
	if (!AllItemList_.empty())
	{
		AllItemList_.clear();
	}

	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// 경로 편집
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllItemInfo.dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// 아이템 개수를 제일 처음에 저장했으므로 아이템 개수 Read
	int ItemCnt = 0;
	pFile.Read(ItemCnt);
	AllItemList_.resize(ItemCnt);

	for (int i = 0; i < ItemCnt; ++i)
	{
		// ============================== 플레이어 아이템정보 ============================== //
		// 아이템명(약어)
		std::string ReadItemName_Eng = "";
		pFile.Read(ReadItemName_Eng);
		AllItemList_[i].ItemName_abbreviation = ReadItemName_Eng;

		// 아이템명(약어)-인벤토리용
		std::string ReadItemNameInven = "";
		pFile.Read(ReadItemNameInven);
		AllItemList_[i].ItemName_abbreviation_Inven = ReadItemNameInven;

		// 아이템코드
		int ReadItemCode = 0;
		pFile.Read(ReadItemCode);
		AllItemList_[i].ItemCode = ReadItemCode;

		// 아이템타입
		int ReadItemType = 0;
		pFile.Read(ReadItemType);
		AllItemList_[i].ItemType = static_cast<ItemType>(ReadItemType);

		// 아이템 장착정보

		// 아이템위치(인벤토리, 하단상태바, 창고, 판매창)
		int ReadItemLocType = 0;
		pFile.Read(ReadItemLocType);
		AllItemList_[i].ItemLocType = static_cast<ItemLocType>(ReadItemLocType);

		// 각각의 창에서 시작하는 위치의 인덱스
		int ReadStartPosition = 0;
		pFile.Read(ReadStartPosition);
		AllItemList_[i].StartPosition = ReadStartPosition;

		// 아이템넓이 -> 이벤토리 or 창고 or 판매창에서 차지하는 너비칸수
		int ReadWidthSize = 0;
		pFile.Read(ReadWidthSize);
		AllItemList_[i].WidthSize = ReadWidthSize;

		// 아이템높이 -> 이벤토리 or 창고 or 판매창에서 차지하는 높이칸수
		int ReadHeightSize = 0;
		pFile.Read(ReadHeightSize);
		AllItemList_[i].HeightSize = ReadHeightSize;

		// 아이템 상세정보

		// 내구도 사용여부 판단(TRUE : 내구도사용)
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

		// 최대 내구도
		int ReadMaxDurability = 0;
		pFile.Read(ReadMaxDurability);
		AllItemList_[i].MaxDurability = ReadMaxDurability;

		// 현재 내구도
		int ReadCurDurability = 0;
		pFile.Read(ReadCurDurability);
		AllItemList_[i].CurDurability = ReadCurDurability;

		// 피격차단확률
		int ReadBlock = 0;
		pFile.Read(ReadBlock);
		AllItemList_[i].Block = ReadBlock;

		// 아이템무게(플레이어 이동속도 감소)
		int ReadWeight = 0;
		pFile.Read(ReadWeight);
		AllItemList_[i].Weight = ReadWeight;

		// 아이템 비용(판매창에서 판매하는 비용)
		int ReadPrice = 0;
		pFile.Read(ReadPrice);
		AllItemList_[i].Price = ReadPrice;

		// 아이템 장착시 증가공격력
		int ReadPullDamage = 0;
		pFile.Read(ReadPullDamage);
		AllItemList_[i].PullDamage = ReadPullDamage;

		// 아이템 장착시 증가방어력
		int ReadPullArmor = 0;
		pFile.Read(ReadPullArmor);
		AllItemList_[i].PullArmor = ReadPullArmor;

		// 회복량(포션용) : 퍼센트
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

		// 경로 편집
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllItemInfo.dat";

		// 파일 열기
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// 아이템 갯수 저장
		int AllItemCnt = static_cast<int>(AllItemList_.size());
		pFile.Write(AllItemCnt);

		for (int i = 0; i < AllItemCnt; ++i)
		{
			// ============================== 플레이어 아이템정보 ============================== //
			// 아이템명(약어)
			pFile.Write(AllItemList_[i].ItemName_abbreviation);

			// 아이템명(약어)-인벤용
			pFile.Write(AllItemList_[i].ItemName_abbreviation_Inven);

			// 아이템코드
			pFile.Write(AllItemList_[i].ItemCode);

			// 아이템타입
			pFile.Write(static_cast<int>(AllItemList_[i].ItemType));

			// 아이템 장착정보

			// 아이템위치(인벤토리, 하단상태바, 창고, 판매창)
			pFile.Write(static_cast<int>(AllItemList_[i].ItemLocType));

			// 각각의 창에서 시작하는 위치의 인덱스
			pFile.Write(AllItemList_[i].StartPosition);

			// 아이템넓이 -> 이벤토리 or 창고 or 판매창에서 차지하는 너비칸수
			pFile.Write(AllItemList_[i].WidthSize);

			// 아이템높이 -> 이벤토리 or 창고 or 판매창에서 차지하는 높이칸수
			pFile.Write(AllItemList_[i].HeightSize);

			// 아이템 상세정보

			// 내구도 사용여부 판단(TRUE : 내구도사용)
			if (true == AllItemList_[i].IsDurability)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 최대 내구도
			pFile.Write(AllItemList_[i].MaxDurability);

			// 현재 내구도
			pFile.Write(AllItemList_[i].CurDurability);

			// 피격차단확률
			pFile.Write(AllItemList_[i].Block);

			// 아이템무게(플레이어 이동속도 감소)
			pFile.Write(AllItemList_[i].Weight);

			// 아이템 비용(판매창에서 판매하는 비용)
			pFile.Write(AllItemList_[i].Price);

			// 아이템 장착시 증가공격력
			pFile.Write(AllItemList_[i].PullDamage);

			// 아이템 장착시 증가방어력
			pFile.Write(AllItemList_[i].PullArmor);

			// 회복량(포션용) : 퍼센트
			pFile.Write(AllItemList_[i].Recovery);
		}

		pFile.Close();
	}
}
