#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// 관련 액터
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "MainPlayer_WeaponSkillButton.h"
#include "MainPlayer_LeftWeaponSkillButton.h"
#include "MainPlayer_RightWeaponSkillButton.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_LevelUpActiveButton.h"
#include "MainPlayer_CurExpProgressBar.h"
#include "MainPlayer_QuickSlot.h"

BottomStateBar::BottomStateBar() :
	Panel_(nullptr),
	PanelCol_(nullptr),
	HP_(nullptr),
	MP_(nullptr),
	LWeaponSkill_(nullptr),
	RWeaponSkill_(nullptr),
	Stamina_(nullptr),
	MiniMenu_(nullptr),
	AddStatPointButton_(nullptr),
	AddSkillPointButton_(nullptr),
	CurExpProgressBar_(nullptr),
	QuickSlot_(nullptr)
{
}

BottomStateBar::~BottomStateBar()
{
}

void BottomStateBar::Start()
{
	GameEngineTexture* BottomStateBarImage = GameEngineTextureManager::GetInst().Find("Player_BottomStatBar_UI.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageSize = BottomStateBarImage->GetTextureSize();
	float4 ImageHarfSize = ImageSize.halffloat4();

	// 하단상태바 틀
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI10));
	Panel_->SetImage("Player_BottomStatBar_UI.png", float4(WindowSize.x, ImageSize.y));
	Panel_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));

	// 플레이어 이동불가처리를 위한 충돌체 생성
	PanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	PanelCol_->SetName("Player_BottomStateBar");
	PanelCol_->GetTransform()->SetLocalScaling(Panel_->GetTransform()->GetLocalScaling());
	PanelCol_->GetTransform()->SetLocalPosition(Panel_->GetTransform()->GetLocalPosition());

	// ====================================================== 관련 액터 생성 ====================================================== //

	// HP Bar
	HP_ = GetLevel()->CreateActor<MainPlayer_CurrentHP>();
	
	// MP Bar
	MP_ = GetLevel()->CreateActor<MainPlayer_CurrentMP>();

	// 왼쪽무기 활성화 스킬버튼(기본공격 제외 아무것도 안함)
	LWeaponSkill_ = GetLevel()->CreateActor<MainPlayer_LeftWeaponSkillButton>();
	
	// 오른쪽무기 활성화 스킬버튼(메인플레이어의 스킬정보 공유하여 활성화된 스킬버튼 생성)
	RWeaponSkill_ = GetLevel()->CreateActor<MainPlayer_RightWeaponSkillButton>();

	// 현재 경험치
	CurExpProgressBar_ = GetLevel()->CreateActor<MainPlayer_CurExpProgressBar>();

	// 레벨업 활성화버튼(스탯포인트)
	AddStatPointButton_ = GetLevel()->CreateActor<MainPlayer_LevelUpActiveButton>();
	AddStatPointButton_->SetLevelUpActiveButtonInfo(LevelUpPointType::STAT, float4(220.f - WindowHarfSize.x, 24.f - WindowHarfSize.y));

	// 레벨업 활성화버튼(스킬포인트)
	AddSkillPointButton_ = GetLevel()->CreateActor<MainPlayer_LevelUpActiveButton>();
	AddSkillPointButton_->SetLevelUpActiveButtonInfo(LevelUpPointType::SKILL, float4(WindowHarfSize.x - 223.f, 24.f - WindowHarfSize.y));

	// 스태미나
	Stamina_ = GetLevel()->CreateActor<MainPlayer_Stamina>();

	// 퀵슬롯
	QuickSlot_ = GetLevel()->CreateActor<MainPlayer_QuickSlot>();

	// 미니메뉴관련
	MiniMenu_ = GetLevel()->CreateActor<MainPlayer_MiniMenu>();
}

void BottomStateBar::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(PanelCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

}

void BottomStateBar::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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
	else if (std::string::npos != _NextLevel->GetName().find("EndingLevel"))
	{
		return;
	}

	// 하단상태바가 들고있는 모든 액터 레벨넘김
	
	// HP
	if (nullptr != HP_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, HP_);
	}

	// MP
	if (nullptr != MP_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, MP_);
	}

	// 활성화스킬버튼(좌/우)
	if (nullptr != LWeaponSkill_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, LWeaponSkill_);
	}
	if (nullptr != RWeaponSkill_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, RWeaponSkill_);
	}

	// 스태미나
	if (nullptr != Stamina_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, Stamina_);
	}

	// 미니메뉴
	if (nullptr != MiniMenu_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, MiniMenu_);
	}

	// 레벨업시 활성화되는 버튼
	if (nullptr != AddStatPointButton_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, AddStatPointButton_);
	}
	if (nullptr != AddSkillPointButton_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, AddSkillPointButton_);
	}

	// 현재 경험치
	if (nullptr != CurExpProgressBar_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, CurExpProgressBar_);
	}

	// 퀵슬롯
	if (nullptr != QuickSlot_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, QuickSlot_);
	}
}

void BottomStateBar::InitBottomStateBar()
{
	// 현재 HP
	InitCurrentHP();

	// 현재 MP
	InitCurrentMP();

	// 현재 스테미나
	InitCurrentStamina();

	// 현재 활성화 왼쪽 스킬버튼
	InitLeftSkillBtn();
	
	// 현재 활성화 오른쪽 스킬버튼
	InitRightSkillBtn();

	// 현재 물약장착 상태
	InitLiquidMedicine();

	// 현재 경험치
	InitEXP();
}

void BottomStateBar::InitCurrentHP()
{
}

void BottomStateBar::InitCurrentMP()
{
}

void BottomStateBar::InitCurrentStamina()
{
	// 스태미나 소모량 셋팅
	Stamina_->InitStaminaDrain();
}

void BottomStateBar::InitLeftSkillBtn()
{
	LWeaponSkill_->InitLWeaponSkillList();
}

void BottomStateBar::InitRightSkillBtn()
{
	RWeaponSkill_->InitRWeaponSkillList();
}

void BottomStateBar::InitLiquidMedicine()
{
}

void BottomStateBar::InitEXP()
{
}

void BottomStateBar::ConsumptionHP(float _Damage)
{
	// 플레이어의 체력 감소
	HP_->HPConsumption(_Damage);
}

void BottomStateBar::ConsumptionMP(float _MP)
{
	// 플레이어의 마나 감소
	MP_->MPConsumption(_MP);
}
