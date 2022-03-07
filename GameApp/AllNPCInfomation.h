#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

enum class NPCClassType
{
	Akara,					// 잡화상인
	Charsi,					// 무기상인
	MAX,
};

enum class NPCType
{
	Normal,					// 일반 NPC
	PotionShop,			// 물약상점 NPC
	WeaponShop,		// 무기상점 NPC
	Employer				// 용병상인 NPC
};

struct AllNPCInfo
{
	// ============================ NPC 기본정보 ============================ //
	std::string						Name;				// NPC 명
	NPCClassType				ClassType;			// NPC 클래스 타입
	NPCType						Type;					// NPC 타입

	int									BuyMult;			// NPC가 플레이어로부터 물건구매시 할인가격((가격/1024*값))
	int									SellMult;			// NPC가 플레이어에게 물건판매시 할인가격((가격/1024*값))
	int									RepMult;			// NPC가 아이템 수리시 가격(floor(price/1024*value)) 
																		// -> 아이템의 내구도의 영향을 받는다.
	int									MaxBuy;			// NPC가 플레이어로부터 물건구매시 최대가격
};

// 분류 : 정보
// 용도 : NPC정보 관리용
// 설명 : 모든 NPC정보를 관리
class AllNPCInfomation
{
private:
	static AllNPCInfomation* Inst;

public:
	static AllNPCInfomation& GetInst()
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
	std::vector<AllNPCInfo> AllNPCList_;

private:
	bool ExcelZFlag_;

private:
	AllNPCInfomation();
	~AllNPCInfomation();

protected:		// delete constructer
	AllNPCInfomation(const AllNPCInfomation& _other) = delete;
	AllNPCInfomation(AllNPCInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllNPCInfomation& operator=(const AllNPCInfomation& _other) = delete;
	AllNPCInfomation& operator=(const AllNPCInfomation&& _other) = delete;

public:
	bool NPCInfoFind(NPCClassType _ClassType, AllNPCInfo& _ClassNPCInfo);

public:
	void CreateAllNPCInfomation(bool _ExcelFile = false);
	void LoadNPCExcelFile();
	void LoadNPCBinaryFile();

public:
	void SaveNPCBinaryFile();
};

