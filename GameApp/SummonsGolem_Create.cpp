#include "PreCompile.h"
#include "SummonsGolem.h"

#include "MainPlayerInfomation.h"

void SummonsGolem::InitGolem()
{
	// ���Ÿ���� �񷽰��� �ʱ�ȭ

	// �ؽ��� ����
	TextureCutting();

	// FSM ����
	CreateFSMState();

	// �浹ü ����
	CreateCollision();
}

void SummonsGolem::TextureCutting()
{
	// CLAY GOLEM


	// BLOOD GOLEM


	// IRON GOLEM


	// FIRE GOLEM

}

void SummonsGolem::CreateFSMState()
{
	// 
}

void SummonsGolem::CreateCollision()
{

}

void SummonsGolem::CreateGolemInfo()
{
	switch (GolemType_)
	{
		case GolemType::CLAY:
		{
			MainPlayerInfomation::GetInst().GetSkillInfo(75, GolemInfo_);
			break;
		}
		case GolemType::BLOOD:
		{
			MainPlayerInfomation::GetInst().GetSkillInfo(85, GolemInfo_);
			break;
		}
		case GolemType::IRON:
		{
			MainPlayerInfomation::GetInst().GetSkillInfo(90, GolemInfo_);
			break;
		}
		case GolemType::FIRE:
		{
			MainPlayerInfomation::GetInst().GetSkillInfo(94, GolemInfo_);
			break;
		}
	}
}

void SummonsGolem::CreateAnimation()
{
	switch (GolemType_)
	{
		case GolemType::CLAY:
		{

			break;
		}
		case GolemType::BLOOD:
		{

			break;
		}
		case GolemType::IRON:
		{

			break;
		}
		case GolemType::FIRE:
		{

			break;
		}
	}
}

void SummonsGolem::CreateAnimationEndFunction()
{

}
