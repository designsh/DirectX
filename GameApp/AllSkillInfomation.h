#pragma once
#include "MainPlayerInfomation.h"
#include <GameEngineBase/ExcelControl.h>

struct AllSkillInfo
{
	std::string							ClassName;			// 클래스명(직업명) : 영어
	JobType								ClassType;			// 클래스(직업 타입)
	std::vector<SkillList>				SkillList;			// 클래스별 스킬목록
};

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

