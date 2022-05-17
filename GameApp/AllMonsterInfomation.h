#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

// 몬스터 클래스
enum class MonsterClassType
{
	SpikeFiend,					// 
	Zombie,						// 
	Fallen,						// 
	Tainted,					// 
	Andariel,					// 
	Diablo,						// 
	MAX,
};

// 몬스터 타입
enum class MonsterType
{
	Normal,						// 일반몬스터
	Boss,						// 보스몬스터
};

struct AllMonsterInfo
{
	// ============================ 몬스터 기본정보 ============================ //
	std::string								Name;								// 몬스터 명
	MonsterClassType						ClassType;							// 몬스터 클래스 타입
	MonsterType								Type;								// 몬스터 타입
	
	int										Level;								// 몬스터 레벨
	int										Velocity;							// 몬스터 이동속도
	int										RunVelocity;						// 몬스터 뛰기상태에서의 이동속도
	int										MinGrp;								// 한번에 스폰되는 몬스터의 최소 수
	int										MaxGrp;								// 한번에 스폰되는 몬스터의 최대 수

	int										DropEXP;							// 몬스터 사망시 플레이어에게 주는 경험치량
	int										DropItemPercent;					// 몬스터 사망시 아이템 드랍률
	int										DropItemType;						// 몬스터 사망시 드랍되는 아이템 타입
	int										DropGoldPercent;					// 몬스터 사망시 골드 드랍률
	int										DropGoldMin;						// 몬스터 사망시 드랍되는 최소 골드량
	int										DropGoldMax;						// 몬스터 사망시 드랍되는 최대 골드량

	bool									IsSpawn;							// 무작위 스폰(재생성) Flag
	bool									IsDoorOpen;							// 몬스터가 문을 열수있는지 판단 Flag
	bool									IsInTown;							// 몬스터 마을 진입가능 판단 Flag
	bool									IsCourpseSel;						// 해당 몬스터 시체에 특정스킬 사용가능 Flag(Ex. 플레이어 소환수 스킬 등)
	bool									IsRun;								// 몬스터가 뛰기가 가능한지 판단 Flag
	bool									IsSpecialAttack;					// 몬스터 특수 공격가능 여부 Flag

	// ============================ 몬스터 상세정보 ============================ //
	int										MinHP;								// 몬스터 최소 생명력
	int										MaxHP;								// 몬스터 최대 생명력
	int										HPRegen;							// 몬스터 생명력 회복량
	int										Block;								// 몬스터 방어력
	int										Damage;								// 몬스터 일반공격력

	int										SpeAtkCoolTime;						// 몬스터 특수공격 쿨타임
	int										SpeAtkDamage;						// 몬스터 특수공격력

	int										DamageResist;						// 일반공격 저항력
	int										SpecialDamageResist;				// 특수공격 저항력
	int										FireResist;							// 화염 저항력
	int										LightningResist;					// 라이트닝 저항력
	int										ColdResist;							// 냉기 저항력
	int										PosionResist;						// 독 저항력
};

// 분류 : 정보
// 용도 : 몬스터정보 관리용
// 설명 : 모든 몬스터정보를 관리
class AllMonsterInfomation
{
private:
	static AllMonsterInfomation* Inst;

public:
	static AllMonsterInfomation& GetInst()
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
	std::vector<AllMonsterInfo> AllMonsterList_;

private:
	bool ExcelZFlag_;

private:
	AllMonsterInfomation();
	~AllMonsterInfomation();

protected:		// delete constructer
	AllMonsterInfomation(const AllMonsterInfomation& _other) = delete;
	AllMonsterInfomation(AllMonsterInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllMonsterInfomation& operator=(const AllMonsterInfomation& _other) = delete;
	AllMonsterInfomation& operator=(const AllMonsterInfomation&& _other) = delete;

public:
	bool MonsterInfoFind(MonsterClassType _ClassType, AllMonsterInfo& _ClassMonsterInfo);

public:
	void CreateAllMonsterInfomation(bool _ExcelFile = false);
	void LoadMonsterExcelFile();
	void LoadMonsterBinaryFile();

public:
	void SaveMonsterBinaryFile();
};

