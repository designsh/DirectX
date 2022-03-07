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
	// 모든 클래스의 스킬을 모두 로드하여 정보로 관리
	if (true == _ExcelFile)
	{
		// .dat 파일 만들어놓으려고 하는거임(테스트용)
		LoadMonsterExcelFile();
	}
	else
	{
		// 실질적으로 이걸로 할꺼임
		LoadMonsterBinaryFile();
	}

	SaveMonsterBinaryFile();
}

void AllMonsterInfomation::LoadMonsterExcelFile()
{
	// 기존의 스킬정보를 들고있다면 클리어
	if (!AllMonsterList_.empty())
	{
		AllMonsterList_.clear();
	}

	// 게임 시작과 동시에 해당 함수가 호출되어 모든 클래스의 스킬정보를 생성한다.
	CExcelControl* ExcelFile = new CExcelControl();

	// 로드 파일 경로 편집
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\MonsterInfo.xlsx";
	const char* chFullPath = nullptr;
	chFullPath = FullPath.c_str();

	// 실패시 -1 반환
	// 로드해야하는 시트는 한개
	if (1 == ExcelFile->Open(chFullPath))
	{
		// MonsterInfo.xlsx 파일의 시트는 총 1개
		ExcelFile->SetVisible(false);
		ExcelFile->SetActiveSheet(1);

		// 모든 컬럼과 로우를 검사하여 스킬정보로드
		char ColRowName[MAX_PATH] = {};
		char RowNumber[MAX_PATH] = {};
		int RowNo = 1;
		for (int j = 0; j < MONSTER_MAX; ++j)
		{
			memset(ColRowName, 0, sizeof(ColRowName));
			ColRowName[0] = 'A' + j;
			if (ExcelZFlag_) // 컬럼 Z가 넘어가면 A1 식으로 컬럼진행이므로 체크한다.
			{
				ColRowName[0] = 'A';
				ColRowName[1] = 'A' + (j - 26);
			}

			// 실질적인 몬스터목록 생성
			AllMonsterInfo NewMonsterInfo = {};

			// ============================ 몬스터 기본정보 ============================ //

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
			NewMonsterInfo.Name = pName;
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
			NewMonsterInfo.ClassType = static_cast<MonsterClassType>(ClassType);
			++RowNo;

			// 몬스터 타입
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

			// 몬스터 레벨
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

			// 몬스터 이동속도
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

			// 몬스터 뛰기상태에서의 이동속도
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

			// 한번에 스폰되는 몬스터의 최소 수
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

			// 한번에 스폰되는 몬스터의 최대 수
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

			// 몬스터 사망시 플레이어에게 주는 경험치량
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

			// 몬스터 사망시 아이템 드랍률
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

			// 몬스터 사망시 드랍되는 아이템 타입
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

			// 몬스터 사망시 골드 드랍률
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

			// 몬스터 사망시 드랍되는 최소 골드량
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

			// 몬스터 사망시 드랍되는 최대 골드량
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

			// 무작위 스폰(재생성) Flag
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

			// 몬스터가 문을 열수있는지 판단 Flag
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

			// 몬스터 마을 진입가능 판단 Flag
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

			// 해당 몬스터 시체에 특정스킬 사용가능 Flag(Ex. 플레이어 소환수 스킬 등)
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

			// 몬스터가 뛰기가 가능한지 판단 Flag
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

			// 몬스터 특수 공격가능 여부 Flag
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

			// ============================ 몬스터 상세정보 ============================ //

			// 몬스터 최소 생명력
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

			// 몬스터 최대 생명력
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

			// 몬스터 생명력 회복량
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

			// 몬스터 방어력
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

			// 몬스터 일반공격력
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

			// 몬스터 특수공격 쿨타임
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

			// 몬스터 특수공격력
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

			// 일반공격 저항력
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

			// 특수공격 저항력
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

			// 화염 저항력
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

			// 라이트닝 저항력
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

			// 냉기 저항력
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

			// 독 저항력
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

void AllMonsterInfomation::LoadMonsterBinaryFile()
{
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("DataFile");

	// 경로 편집
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "AllMonsterInfo.dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// 몬스터정보 개수를 제일 처음에 저장했으므로 몬스터정보 개수 Read
	int MonsterCnt = 0;
	pFile.Read(MonsterCnt);
	AllMonsterList_.resize(MonsterCnt);

	for (int i = 0; i < MonsterCnt; ++i)
	{
		// ============================ 몬스터 기본정보 ============================ //
		// 몬스터 명
		std::string Name = "";
		pFile.Read(Name);
		AllMonsterList_[i].Name = Name;

		// 몬스터 클래스 타입
		int ClassType = 0;
		pFile.Read(ClassType);
		AllMonsterList_[i].ClassType = static_cast<MonsterClassType>(ClassType);

		// 몬스터 타입
		int Type = 0;
		pFile.Read(Type);
		AllMonsterList_[i].Type = static_cast<MonsterType>(Type);

		// 몬스터 레벨
		int Level = 0;
		pFile.Read(Level);
		AllMonsterList_[i].Level = Level;

		// 몬스터 이동속도
		int Velocity = 0;
		pFile.Read(Velocity);
		AllMonsterList_[i].Velocity = Velocity;

		// 몬스터 뛰기상태에서의 이동속도
		int RunVelocity = 0;
		pFile.Read(RunVelocity);
		AllMonsterList_[i].RunVelocity = RunVelocity;

		// 한번에 스폰되는 몬스터의 최소 수
		int MinGrp = 0;
		pFile.Read(MinGrp);
		AllMonsterList_[i].MinGrp = MinGrp;

		// 한번에 스폰되는 몬스터의 최대 수
		int MaxGrp = 0;
		pFile.Read(MaxGrp);
		AllMonsterList_[i].MaxGrp = MaxGrp;

		// 몬스터 사망시 플레이어에게 주는 경험치량
		int DropEXP = 0;
		pFile.Read(DropEXP);
		AllMonsterList_[i].DropEXP = DropEXP;

		// 몬스터 사망시 아이템 드랍률
		int DropItemPercent = 0;
		pFile.Read(DropItemPercent);
		AllMonsterList_[i].DropItemPercent = DropItemPercent;

		// 몬스터 사망시 드랍되는 아이템 타입
		int DropItemType = 0;
		pFile.Read(DropItemType);
		AllMonsterList_[i].DropItemType = DropItemType;

		// 몬스터 사망시 골드 드랍률
		int DropGoldPercent = 0;
		pFile.Read(DropGoldPercent);
		AllMonsterList_[i].DropGoldPercent = DropGoldPercent;

		// 몬스터 사망시 드랍되는 최소 골드량
		int DropGoldMin = 0;
		pFile.Read(DropGoldMin);
		AllMonsterList_[i].DropGoldMin = DropGoldMin;

		// 몬스터 사망시 드랍되는 최대 골드량
		int DropGoldMax = 0;
		pFile.Read(DropGoldMax);
		AllMonsterList_[i].DropGoldMax = DropGoldMax;

		// 무작위 스폰(재생성) Flag
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

		// 몬스터가 문을 열수있는지 판단 Flag
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

		// 몬스터 마을 진입가능 판단 Flag
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

		// 해당 몬스터 시체에 특정스킬 사용가능 Flag(Ex. 플레이어 소환수 스킬 등)
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

		// 몬스터가 뛰기가 가능한지 판단 Flag
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

		// 몬스터 특수 공격가능 여부 Flag
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

		// ============================ 몬스터 상세정보 ============================ //
		// 몬스터 최소 생명력
		int MinHP = 0;
		pFile.Read(MinHP);
		AllMonsterList_[i].MinHP = MinHP;

		// 몬스터 최대 생명력
		int MaxHP = 0;
		pFile.Read(MaxHP);
		AllMonsterList_[i].MaxHP = MaxHP;

		// 몬스터 생명력 회복량
		int HPRegen = 0;
		pFile.Read(HPRegen);
		AllMonsterList_[i].HPRegen = HPRegen;

		// 몬스터 방어력
		int Block = 0;
		pFile.Read(Block);
		AllMonsterList_[i].Block = Block;

		// 몬스터 일반공격력
		int Damage = 0;
		pFile.Read(Damage);
		AllMonsterList_[i].Damage = Damage;

		// 몬스터 특수공격 쿨타임
		int SpeAtkCoolTime = 0;
		pFile.Read(SpeAtkCoolTime);
		AllMonsterList_[i].SpeAtkCoolTime = SpeAtkCoolTime;

		// 몬스터 특수공격력
		int SpeAtkDamage = 0;
		pFile.Read(SpeAtkDamage);
		AllMonsterList_[i].SpeAtkDamage = SpeAtkDamage;

		// 일반공격 저항력
		int DamageResist = 0;
		pFile.Read(DamageResist);
		AllMonsterList_[i].DamageResist = DamageResist;

		// 특수공격 저항력
		int SpecialDamageResist = 0;
		pFile.Read(SpecialDamageResist);
		AllMonsterList_[i].SpecialDamageResist = SpecialDamageResist;

		// 화염 저항력
		int FireResist = 0;
		pFile.Read(FireResist);
		AllMonsterList_[i].FireResist = FireResist;

		// 라이트닝 저항력
		int LightningResist = 0;
		pFile.Read(LightningResist);
		AllMonsterList_[i].LightningResist = LightningResist;

		// 냉기 저항력
		int ColdResist = 0;
		pFile.Read(ColdResist);
		AllMonsterList_[i].ColdResist = ColdResist;

		// 독 저항력
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

		// 경로 편집
		std::string FullPath = DataFileDir.GetFullPath();
		FullPath += "\\";
		FullPath += "AllMonsterInfo.dat";

		// 파일 열기
		GameEngineFile pFile = GameEngineFile(FullPath, "wb");

		// 몬스터 갯수 저장
		int AllMonsterCnt = static_cast<int>(AllMonsterList_.size());
		pFile.Write(AllMonsterCnt);

		for (int i = 0; i < AllMonsterCnt; ++i)
		{
			// ============================ 몬스터 기본정보 ============================ //
			// 몬스터 명
			pFile.Write(AllMonsterList_[i].Name);

			// 몬스터 클래스 타입
			pFile.Write(static_cast<int>(AllMonsterList_[i].ClassType));

			// 몬스터 타입
			pFile.Write(static_cast<int>(AllMonsterList_[i].Type));

			// 몬스터 레벨
			pFile.Write(AllMonsterList_[i].Level);

			// 몬스터 이동속도
			pFile.Write(AllMonsterList_[i].Velocity);

			// 몬스터 뛰기상태에서의 이동속도
			pFile.Write(AllMonsterList_[i].RunVelocity);

			// 한번에 스폰되는 몬스터의 최소 수
			pFile.Write(AllMonsterList_[i].MinGrp);

			// 한번에 스폰되는 몬스터의 최대 수
			pFile.Write(AllMonsterList_[i].MaxGrp);

			// 몬스터 사망시 플레이어에게 주는 경험치량
			pFile.Write(AllMonsterList_[i].DropEXP);

			// 몬스터 사망시 아이템 드랍률
			pFile.Write(AllMonsterList_[i].DropItemPercent);

			// 몬스터 사망시 드랍되는 아이템 타입
			pFile.Write(AllMonsterList_[i].DropItemType);

			// 몬스터 사망시 골드 드랍률
			pFile.Write(AllMonsterList_[i].DropGoldPercent);

			// 몬스터 사망시 드랍되는 최소 골드량
			pFile.Write(AllMonsterList_[i].DropGoldMin);

			// 몬스터 사망시 드랍되는 최대 골드량
			pFile.Write(AllMonsterList_[i].DropGoldMax);

			// 무작위 스폰(재생성) Flag
			if (true == AllMonsterList_[i].IsSpawn)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 몬스터가 문을 열수있는지 판단 Flag
			if (true == AllMonsterList_[i].IsDoorOpen)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 몬스터 마을 진입가능 판단 Flag
			if (true == AllMonsterList_[i].IsInTown)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 해당 몬스터 시체에 특정스킬 사용가능 Flag(Ex. 플레이어 소환수 스킬 등)
			if (true == AllMonsterList_[i].IsCourpseSel)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 몬스터가 뛰기가 가능한지 판단 Flag
			if (true == AllMonsterList_[i].IsRun)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// 몬스터 특수 공격가능 여부 Flag
			if (true == AllMonsterList_[i].IsSpecialAttack)
			{
				pFile.Write(1);
			}
			else
			{
				pFile.Write(0);
			}

			// ============================ 몬스터 상세정보 ============================ //
			// 몬스터 최소 생명력
			pFile.Write(AllMonsterList_[i].MinHP);

			// 몬스터 최대 생명력
			pFile.Write(AllMonsterList_[i].MaxHP);

			// 몬스터 생명력 회복량
			pFile.Write(AllMonsterList_[i].HPRegen);

			// 몬스터 방어력
			pFile.Write(AllMonsterList_[i].Block);

			// 몬스터 일반공격력
			pFile.Write(AllMonsterList_[i].Damage);

			// 몬스터 특수공격 쿨타임
			pFile.Write(AllMonsterList_[i].SpeAtkCoolTime);

			// 몬스터 특수공격력
			pFile.Write(AllMonsterList_[i].SpeAtkDamage);

			// 일반공격 저항력
			pFile.Write(AllMonsterList_[i].DamageResist);

			// 특수공격 저항력
			pFile.Write(AllMonsterList_[i].SpecialDamageResist);

			// 화염 저항력
			pFile.Write(AllMonsterList_[i].FireResist);

			// 라이트닝 저항력
			pFile.Write(AllMonsterList_[i].LightningResist);

			// 냉기 저항력
			pFile.Write(AllMonsterList_[i].ColdResist);

			// 독 저항력
			pFile.Write(AllMonsterList_[i].PosionResist);
		}

		pFile.Close();
	}
}
