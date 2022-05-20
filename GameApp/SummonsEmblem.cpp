#include "PreCompile.h"
#include "SummonsEmblem.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "SummonsGolem.h"
#include "SketelonWarrior.h"
#include "SketelonWizard.h"

SummonsEmblem::SummonsEmblem() :
	GolemEmblem_(nullptr),
	SketelonWarriorEmblem_(nullptr),
	SketelonWizardEmblem_(nullptr),
	WarriorCnt_(0),
	WizardCnt_(0),
	CurGolemType_(GolemType::NONE)
{
}

SummonsEmblem::~SummonsEmblem()
{
}

void SummonsEmblem::Start()
{
}

void SummonsEmblem::Update(float _DeltaTime)
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 현재 소환된 골렘이 존재하지않을경우 해당 렌더러 Off


		// 현재 소환된 전사형 스켈텔론이 존재하지않을경우 해당 렌더러 Off


		// 현재 소환된 마법사형 스켈텔론이 존재하지않을경우 해당 렌더러 Off

	}
}

void SummonsEmblem::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}

	// 이동???
}

void SummonsEmblem::GolemEmblemUpdate(GolemType _SpawnGolemType)
{
	if (nullptr == GolemEmblem_)
	{
		float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

		// 최초 스폰으로 렌더러 생성
		GolemEmblem_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
		GolemEmblem_->GetTransform()->SetLocalScaling(float4(46.f, 41.f));
		GolemEmblem_->GetTransform()->SetLocalPosition(float4(30.f - ScreenHarfSize.x, ScreenHarfSize.y - 30.f));
		GolemEmblem_->SetAlpha(0.7f);
		GolemEmblem_->On();
	}

	// 표시 이미지만 변경
	switch (_SpawnGolemType)
	{
		case GolemType::CLAY:
		{
			GolemEmblem_->SetImage("ClayGolem.png");
			break;
		}
		case GolemType::BLOOD:
		{
			GolemEmblem_->SetImage("BloodGolem.png");
			break;
		}
		case GolemType::IRON:
		{
			GolemEmblem_->SetImage("IronGolem.png");
			break;
		}
		case GolemType::FIRE:
		{
			GolemEmblem_->SetImage("FireGolem.png");
			break;
		}
	}
}

void SummonsEmblem::SketelonWarriorUpdate(int _CurCount)
{
	WarriorCnt_ = _CurCount;

	// 최초 스켈텔론(전사형) 스폰
	if (nullptr == SketelonWarriorEmblem_)
	{
		float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

		// 최초 스폰으로 렌더러 생성
		SketelonWarriorEmblem_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
		SketelonWarriorEmblem_->SetImage("Skeleton_Warrior.png");
		SketelonWarriorEmblem_->SetAlpha(0.7f);
		SketelonWarriorEmblem_->GetTransform()->SetLocalScaling(float4(46.f, 41.f));
		SketelonWarriorEmblem_->GetTransform()->SetLocalPosition(float4(90.f - ScreenHarfSize.x, ScreenHarfSize.y - 30.f));
		SketelonWarriorEmblem_->TextSetting("diablo", std::to_string(WarriorCnt_), 10, FW1_RIGHT | FW1_VCENTER, float4::WHITE, float4(23.f, 19.f));
		SketelonWarriorEmblem_->On();
	}

	SketelonWarriorEmblem_->SetPrintText(std::to_string(WarriorCnt_));
}

void SummonsEmblem::SketelonWizardUpdate(int _CurCount)
{
	WizardCnt_ = _CurCount;

	// 최초 스켈텔론(마법사형) 스폰
	if (nullptr == SketelonWizardEmblem_)
	{
		float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

		// 최초 스폰으로 렌더러 생성
		SketelonWizardEmblem_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
		SketelonWizardEmblem_->SetImage("Skeleton_Wizard.png");
		SketelonWizardEmblem_->SetAlpha(0.7f);
		SketelonWizardEmblem_->GetTransform()->SetLocalScaling(float4(46.f, 41.f));
		SketelonWizardEmblem_->GetTransform()->SetLocalPosition(float4(150.f - ScreenHarfSize.x, ScreenHarfSize.y - 30.f));
		SketelonWizardEmblem_->TextSetting("diablo", std::to_string(WizardCnt_), 10, FW1_RIGHT | FW1_VCENTER, float4::WHITE, float4(23.f, 19.f));
		SketelonWizardEmblem_->On();
	}

	SketelonWizardEmblem_->SetPrintText(std::to_string(WizardCnt_));
}
