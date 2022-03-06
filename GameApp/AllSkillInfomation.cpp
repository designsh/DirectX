#include "PreCompile.h"
#include "AllSkillInfomation.h"

AllSkillInfomation* AllSkillInfomation::Inst = new AllSkillInfomation();

AllSkillInfomation::AllSkillInfomation() 
{
}

AllSkillInfomation::~AllSkillInfomation()
{
}

void AllSkillInfomation::CreateAllSkillInfomation()
{
	// 모든 클래스의 스킬을 모두 로드하여 정보로 관리
	for (int i = 0; i < static_cast<int>(JobType::MAX); ++i)
	{
		std::vector<SkillList> SkillInfo = {};

		

		
	}
}
