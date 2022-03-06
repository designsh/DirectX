#pragma once
#include "MainPlayerInfomation.h"

// 분류 : 정보
// 용도 : 스킬정보 관리용
// 설명 : 모든 클래스의 스킬정보를 관리
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

