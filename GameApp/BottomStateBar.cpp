#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// 관련 액터
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "MainPlayer_LeftWeaponSkillButton.h"
#include "MainPlayer_RightWeaponSkillButton.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_MiniMenu.h"

BottomStateBar::BottomStateBar() :
	Panel_(nullptr),
	HP_(nullptr),
	MP_(nullptr),
	LWeaponSkill_(nullptr),
	RWeaponSkill_(nullptr),
	Stamina_(nullptr),
	MiniMenu_(nullptr)
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


	// 스태미나
	Stamina_ = GetLevel()->CreateActor<MainPlayer_Stamina>();

	// 물약칸


	// 미니메뉴관련
	MiniMenu_ = GetLevel()->CreateActor<MainPlayer_MiniMenu>();

}

void BottomStateBar::Update(float _DeltaTime)
{
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
