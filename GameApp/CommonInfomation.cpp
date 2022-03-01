#include "PreCompile.h"
#include "CommonInfomation.h"

CommonInfomation::CommonInfomation() : 
	ID_{},
	JobName_("Necromancer"),
	JobType_(JobType::Necromancer),
	Level_(1),
	Exp_(0.f),
	Strength_(15),
	Dexterity_(25),
	Vitality_(15),
	Energy_(25)
{
}

CommonInfomation::~CommonInfomation()
{
}

void CommonInfomation::CreateCommonInfo()
{
}
