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
	// 관리목록의 데이터가 있어야지만 반환가능
	if (true == AllSkillInfo_.empty())
	{
		GameEngineDebug::MsgBoxError("스킬정보를 먼저 로드해야합니다!!!!!");
		return false;
	}

	// 관리목록(AllSkillInfo_)에서 해당 _ClassType을 찾아 모든 스킬목록을 _ClassSkillList에 저장하여 반환
	for (auto& Class : AllSkillInfo_)
	{
		// 동일한 클래스(직업)의 스킬정보가 존재한다면 해당 정보 모두 저장하여 반환
		if (Class.ClassType == _ClassType)
		{
			_ClassSkillList = Class.SkillList;
		}
	}

	return true;
}

void AllSkillInfomation::CreateAllSkillInfomation()
{
	// 모든 클래스의 스킬을 모두 로드하여 정보로 관리
	LoadSkillExcelFile();

	// 관리용 스킬목록이 비어있지않다면 로드에 성공했으므로 
	// Excel이 깔려있지 않은 것을 고려하여 DataFile을 만들어준다
	// AllSkillInfo.dat 명칭 및 wb 형식으로 파일 생성하여 모든정보 저장
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
	// 게임 시작과 동시에 해당 함수가 호출되어 모든 클래스의 스킬정보를 생성한다.
	CExcelControl* ExcelFile = new CExcelControl();

	// 로드 파일 경로 편집
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\SkillInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// 실패시 -1 반환
	if (1 == ExcelFile->Open(chFullPath))
	{
		// 클래스 모두 체크하면서 스킬목록을 읽어온다.
		for (int i = 0; i < static_cast<int>(JobType::MAX); ++i)
		{
			// SkillInfo.xlsx 파일의 시트는 총 5개
			ExcelFile->SetVisible(false);
			ExcelFile->SetActiveSheet(i + 1);

			// 스킬정보 생성
			AllSkillInfo NewAllSkill = {};

			// 클래스 명칭 저장
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

			// 클래스 타입 저장
			NewAllSkill.ClassType = static_cast<JobType>(i);

			// 모든 컬럼과 로우를 검사하여 스킬정보로드
			char ColRowName[MAX_PATH] = {};
			char RowNumber[MAX_PATH] = {};
			int RowNo = 1;
			for (int j = 0; j < 36; ++j)
			{
				memset(ColRowName, 0, sizeof(ColRowName));
				ColRowName[0] = 'A' + j;
				if (ZFlag_) // 컬럼 Z가 넘어가면 A1 식으로 컬럼진행이므로 체크한다.
				{
					ColRowName[0] = 'A';
					ColRowName[1] = 'A' + (j - 26);
				}

				// 실질적인 스킬목록 생성
				SkillList NewSkillInfo = {};

				// =============================== 플레이어 스킬정보 =============================== //
				// 스킬명
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

				// 스킬코드
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

				// 스킬타입
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

				// 플레이어 스킬창의 속한 페이지 No
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

				// 플레이어 스킬창의 속한 페이지의 Row
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

				// 플레이어 스킬창의 속한 페이지의 Column
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

				// 해당 스킬 활성화 조건(스킬레벨)
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

				// 해당 스킬 활성화 조건(선행스킬이름1)
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

				// 해당 스킬 활성화 조건(선행스킬코드1)
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

				// 해당 스킬 활성화 조건(선행스킬이름2)
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

				// 해당 스킬 활성화 조건(선행스킬코드2)
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

				// 해당 스킬 활성화 조건(선행스킬이름3)
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

				// 해당 스킬 활성화 조건(선행스킬코드3)
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

				// 최대 스킬레벨
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

				// 현재 스킬레벨
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

				// 스킬사용가능여부(초기에 0번스킬인 일반공격만 TRUE 상태)
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

				// 벽을 넘을수있는 스킬인지 판단(TURE : 벽통과가능)
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

				// 스킬 시전중 플레이어가 피격상태가 되면 해당 스킬시전이 취소되는지 판단(TRUE : 취소됨)
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

				// 마을내에서 사용가능한 스킬인지 판단(TRUE : 마을내 사용가능)
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

				// 해당 스킬이 패시브 스킬인지 판단(TRUE : 패시브스킬로 판단) - 플레이어 버프용
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

				// 해당 스킬이 디버프 스킬인지 판단(TRUE : 디버프스킬) - 몬스터 디버프용
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

				// 해당 스킬 사용시 마나소모여부 판단(TRUE : 마나소모함)
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

				// 왼쪽무기에 장착가능한 스킬인지 판단(TRUE : 사용가능)
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

				// 해당 스킬이 몬스터 시체에 시전가능한 스킬인지 판단(TRUE : 시전가능) - 소환수 스킬전용
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

				// 패시브 타입
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

				// 스킬레벨당 라이프 증가량
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

				// 스킬레벨당 보너스 라이프 증가량(시체로 선택된 몬스터의 본래체력의 퍼센트 : 100% 기준)
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

				// 스킬레벨당 이동속도 증가량(100% 기준)
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

				// 스킬레벨당 데미지 증가량
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

				// 스킬레벨당 모든속성 저항력 증가량(100% 기준)
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

				// 해당 스킬을 맞은 몬스터가 받는 디버프효과 타입
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

				// 해당 스킬시전시 플레이어가 받는 버프효과 타입
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

				// 지속시간(1레벨값) - 100% 기준(값 / 100)
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

				// 스킬레벨당 디버프 지속시간 증가량 - 100% 기준(값 / 100)
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

				// 디버프 타입의 데미지
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

				// 스킬레벨당 디버프 타입의 데미지 증가량
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

				// 마나소모량
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

				// 스킬 데미지
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

				// 스킬 시전 딜레이시간
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

				// 스킬정보 추가
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

			// 로드완료한 시트(클래스)의 스킬정보를 멤버변수(관리용)에 저장
			AllSkillInfo_.push_back(NewAllSkill);

			ZFlag_ = false;
		}

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
