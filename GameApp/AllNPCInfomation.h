#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

enum class NPCClassType
{
	Akara,					// ��ȭ����
	Charsi,					// �������
	MAX,
};

enum class NPCType
{
	Normal,					// �Ϲ� NPC
	PotionShop,			// ������� NPC
	WeaponShop,		// ������� NPC
	Employer				// �뺴���� NPC
};

struct AllNPCInfo
{
	// ============================ NPC �⺻���� ============================ //
	std::string						Name;				// NPC ��
	NPCClassType				ClassType;			// NPC Ŭ���� Ÿ��
	NPCType						Type;					// NPC Ÿ��

	int									BuyMult;			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� ���ΰ���((����/1024*��))
	int									SellMult;			// NPC�� �÷��̾�� �����ǸŽ� ���ΰ���((����/1024*��))
	int									RepMult;			// NPC�� ������ ������ ����(floor(price/1024*value)) 
																		// -> �������� �������� ������ �޴´�.
	int									MaxBuy;			// NPC�� �÷��̾�κ��� ���Ǳ��Ž� �ִ밡��
};

// �з� : ����
// �뵵 : NPC���� ������
// ���� : ��� NPC������ ����
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

