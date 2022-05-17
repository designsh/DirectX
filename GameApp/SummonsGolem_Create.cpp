#include "PreCompile.h"
#include "SummonsGolem.h"

#include "MainPlayerInfomation.h"

void SummonsGolem::InitGolem()
{
	// 모든타입의 골렘관련 초기화

	// 텍스쳐 컷팅
	TextureCutting();

	// FSM 생성
	CreateFSMState();

	// 충돌체 생성
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
