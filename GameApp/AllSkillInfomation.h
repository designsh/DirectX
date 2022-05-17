#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

struct AllSkillInfo
{
	std::string							ClassName;			// Ŭ������(������) : ����
	JobType								ClassType;			// Ŭ����(���� Ÿ��)
	std::vector<SkillList>				SkillList;			// Ŭ������ ��ų���
};

// �з� : ����
// �뵵 : ��ų���� ������
// ���� : ��� Ŭ������ ��ų������ ����
class AllSkillInfomation
{
private:
	static AllSkillInfomation* Inst;

public:
	static AllSkillInfomation& GetInst()
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
	std::vector<AllSkillInfo> AllSkillInfo_;
	int ClassCount_;
	bool ExcelZFlag_;
	
private:
	AllSkillInfomation();
	~AllSkillInfomation();

protected:		// delete constructer
	AllSkillInfomation(const AllSkillInfomation& _other) = delete;
	AllSkillInfomation(AllSkillInfomation&& _other) noexcept = delete;

private:		//delete operator
	AllSkillInfomation& operator=(const AllSkillInfomation& _other) = delete;
	AllSkillInfomation& operator=(const AllSkillInfomation&& _other) = delete;

public:
	bool ClassSkillFind(JobType _ClassType, std::vector<SkillList>& _ClassSkillList);

public:
	void CreateAllSkillInfomation(bool _ExcelFile = false);
	void LoadSkillExcelFile();
	void LoadSkillBinaryFile();

public:
	void SaveSkillBinaryFile();
	
};

