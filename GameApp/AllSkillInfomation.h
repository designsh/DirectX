#pragma once
#include "MainPlayerInfomation.h"

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
	std::map<JobType, std::vector<SkillList*>> AllSkillList_;

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
	void CreateAllSkillInfomation();
};

