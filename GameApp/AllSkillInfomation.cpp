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
	// ��� Ŭ������ ��ų�� ��� �ε��Ͽ� ������ ����
	for (int i = 0; i < static_cast<int>(JobType::MAX); ++i)
	{
		std::vector<SkillList> SkillInfo = {};

		

		
	}
}
