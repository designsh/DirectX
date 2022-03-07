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
	// 모든 클래스의 스킬을 모두 로드하여 정보로 관리
	if (true == _ExcelFile)
	{
		// ExcelDataFile 수정시 해당 기능으로 바이너리 파일생성 필요
		LoadNPCExcelFile();
		SaveNPCBinaryFile();
	}
	else
	{
		// 실질적으로 이걸로 할꺼임
		LoadNPCBinaryFile();
	}
}

void AllNPCInfomation::LoadNPCExcelFile()
{
	// 기존의 NPC정보를 들고있다면 클리어
	if (!AllNPCList_.empty())
	{
		AllNPCList_.clear();
	}

	// 게임 시작과 동시에 해당 함수가 호출되어 모든 클래스의 NPC정보를 생성한다.
	CExcelControl* ExcelFile = new CExcelControl();

	// 로드 파일 경로 편집
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\NPCInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// 실패시 -1 반환
	// 로드해야하는 시트는 한개
	if (1 == ExcelFile->Open(chFullPath))
	{
		// NPCInfo.xlsx 파일의 시트는 총 1개
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// 모든 컬럼과 로우를 검사하여 몬스터정보로드
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < static_cast<int>(NPCClassType::MAX); ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // 컬럼 Z가 넘어가면 A1 식으로 컬럼진행이므로 체크한다.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// 실질적인 NPC목록 생성
			AllNPCInfo NewNPCInfo = {};

			// ============================ NPC 기본정보 ============================ //

			// 몬스터 명
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

			// 몬스터 클래스 타입
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

			// NPC 타입
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

			// NPC가 플레이어로부터 물건구매시 할인가격((가격/1024*값))
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

			// NPC가 플레이어에게 물건판매시 할인가격((가격/1024*값))
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

			// NPC가 아이템 수리시 가격(floor(price/1024*value)) -> 아이템의 내구도의 영향을 받는다.
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

			// NPC가 플레이어로부터 물건구매시 최대가격
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

void AllNPCInfomation::LoadNPCBinaryFile()
{
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// 경로 편집
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllNPCInfo.dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// NPC정보 개수를 제일 처음에 저장했으므로 NPC정보 개수 Read
	int NPCCnt = 0;
	pFile.Read(NPCCnt);
	AllNPCList_.resize(NPCCnt);

	for (int i = 0; i < NPCCnt; ++i)
	{
		// ============================ NPC 기본정보 ============================ //

		// NPC 명
		std::string Name = "";
		pFile.Read(Name);
		AllNPCList_[i].Name = Name;

		// NPC 클래스 타입
		int ClassType = 0;
		pFile.Read(ClassType);
		AllNPCList_[i].ClassType = static_cast<NPCClassType>(ClassType);

		// NPC 타입
		int Type = 0;
		pFile.Read(Type);
		AllNPCList_[i].Type = static_cast<NPCType>(Type);

		// NPC가 플레이어로부터 물건구매시 할인가격((가격/1024*값))
		int BuyMult = 0;
		pFile.Read(BuyMult);
		AllNPCList_[i].BuyMult = BuyMult;

		// NPC가 플레이어에게 물건판매시 할인가격((가격/1024*값))
		int SellMult = 0;
		pFile.Read(SellMult);
		AllNPCList_[i].SellMult = SellMult;

		// NPC가 아이템 수리시 가격(floor(price/1024*value)) -> 아이템의 내구도의 영향을 받는다.
		int RepMult = 0;
		pFile.Read(RepMult);
		AllNPCList_[i].RepMult = RepMult;

		// NPC가 플레이어로부터 물건구매시 최대가격		
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

		// 경로 편집
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllNPCInfo.dat";

		// 파일 열기
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// NPC정보 갯수 저장
		int AllNPCCnt = static_cast<int>(AllNPCList_.size());
		pFile.Write(AllNPCCnt);

		for (int i = 0; i < AllNPCCnt; ++i)
		{
			// ============================ NPC 기본정보 ============================ //
			// NPC 명
			pFile.Write(AllNPCList_[i].Name);

			// NPC 클래스 타입
			pFile.Write(static_cast<int>(AllNPCList_[i].ClassType));

			// NPC 타입
			pFile.Write(static_cast<int>(AllNPCList_[i].Type));

			// NPC가 플레이어로부터 물건구매시 할인가격((가격/1024*값))
			pFile.Write(AllNPCList_[i].BuyMult);

			// NPC가 플레이어에게 물건판매시 할인가격((가격/1024*값))
			pFile.Write(AllNPCList_[i].SellMult);

			// NPC가 아이템 수리시 가격(floor(price/1024*value)) -> 아이템의 내구도의 영향을 받는다.
			pFile.Write(AllNPCList_[i].RepMult);

			// NPC가 플레이어로부터 물건구매시 최대가격		
			pFile.Write(AllNPCList_[i].MaxBuy);
		}

		pFile.Close();
	}
}
