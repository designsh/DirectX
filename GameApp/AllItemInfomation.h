#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

#define ALL_ITEM_CNT 11

// �з� : ����
// �뵵 : ���������� ������
// ���� : ��� ������������ ����
class AllItemInfomation
{
private:
	static AllItemInfomation* Inst;

public:
	static AllItemInfomation& GetInst()
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
	std::vector<ItemList> AllItemList_;

private:
	bool ExcelZFlag_;

private:
	AllItemInfomation();
	~AllItemInfomation();

protected:		// delete constructer
	AllItemInfomation(const AllItemInfomation& _other) = delete;
	AllItemInfomation(AllItemInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllItemInfomation& operator=(const AllItemInfomation& _other) = delete;
	AllItemInfomation& operator=(const AllItemInfomation&& _other) = delete;

public:
	bool ItemInfoFind(const std::string& _ItemName, ItemList& _ItemInfo);

public:
	void CreateAllItemInfomation(bool _ExcelFile = false);
	void LoadItemExcelFile();
	void LoadItemBinaryFile();

public:
	void SaveItemBinaryFile();
};

