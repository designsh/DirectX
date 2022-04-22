#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// ���� ����
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "MainPlayer_WeaponSkillButton.h"
#include "MainPlayer_LeftWeaponSkillButton.h"
#include "MainPlayer_RightWeaponSkillButton.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_LevelUpActiveButton.h"
#include "MainPlayer_CurExpProgressBar.h"

BottomStateBar::BottomStateBar() :
	Panel_(nullptr),
	HP_(nullptr),
	MP_(nullptr),
	LWeaponSkill_(nullptr),
	RWeaponSkill_(nullptr),
	Stamina_(nullptr),
	MiniMenu_(nullptr),
	AddStatPointButton_(nullptr),
	AddSkillPointButton_(nullptr),
	CurExpProgressBar_(nullptr)
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

	// �ϴܻ��¹� Ʋ
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI10));
	Panel_->SetImage("Player_BottomStatBar_UI.png", float4(WindowSize.x, ImageSize.y));
	Panel_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));

	// ====================================================== ���� ���� ���� ====================================================== //

	// HP Bar
	HP_ = GetLevel()->CreateActor<MainPlayer_CurrentHP>();
	
	// MP Bar
	MP_ = GetLevel()->CreateActor<MainPlayer_CurrentMP>();

	// ���ʹ��� Ȱ��ȭ ��ų��ư(�⺻���� ���� �ƹ��͵� ����)
	LWeaponSkill_ = GetLevel()->CreateActor<MainPlayer_LeftWeaponSkillButton>();
	
	// �����ʹ��� Ȱ��ȭ ��ų��ư(�����÷��̾��� ��ų���� �����Ͽ� Ȱ��ȭ�� ��ų��ư ����)
	RWeaponSkill_ = GetLevel()->CreateActor<MainPlayer_RightWeaponSkillButton>();

	// ���� ����ġ
	CurExpProgressBar_ = GetLevel()->CreateActor<MainPlayer_CurExpProgressBar>();

	// ������ Ȱ��ȭ��ư(��������Ʈ)
	AddStatPointButton_ = GetLevel()->CreateActor<MainPlayer_LevelUpActiveButton>();
	AddStatPointButton_->SetLevelUpActiveButtonInfo(LevelUpPointType::STAT, float4(220.f - WindowHarfSize.x, 24.f - WindowHarfSize.y));

	// ������ Ȱ��ȭ��ư(��ų����Ʈ)
	AddSkillPointButton_ = GetLevel()->CreateActor<MainPlayer_LevelUpActiveButton>();
	AddSkillPointButton_->SetLevelUpActiveButtonInfo(LevelUpPointType::SKILL, float4(WindowHarfSize.x - 223.f, 24.f - WindowHarfSize.y));

	// ���¹̳�
	Stamina_ = GetLevel()->CreateActor<MainPlayer_Stamina>();

	// ����ĭ


	// �̴ϸ޴�����
	MiniMenu_ = GetLevel()->CreateActor<MainPlayer_MiniMenu>();

}

void BottomStateBar::Update(float _DeltaTime)
{
}

void BottomStateBar::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// �ϴܻ��¹ٰ� ����ִ� ��� ���� �����ѱ�

	//// HP/MP
	//MainPlayer_CurrentHP* HP_;
	//MainPlayer_CurrentMP* MP_;

	//// Ȱ��ȭ��ų��ư(��/��)
	//MainPlayer_LeftWeaponSkillButton* LWeaponSkill_;
	//MainPlayer_RightWeaponSkillButton* RWeaponSkill_;

	//// ���¹̳�
	//MainPlayer_Stamina* Stamina_;

	//// �̴ϸ޴�
	//MainPlayer_MiniMenu* MiniMenu_;

	//// �������� Ȱ��ȭ�Ǵ� ��ư
	//MainPlayer_LevelUpActiveButton* AddStatPointButton_;
	//MainPlayer_LevelUpActiveButton* AddSkillPointButton_;

	//// ���� ����ġ
	//MainPlayer_CurExpProgressBar* CurExpProgressBar_;




	//GetLevel()->SetLevelActorMove(_NextLevel, this);
	//_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0F, -100.0F));

}

void BottomStateBar::InitBottomStateBar()
{
	// ���� HP
	InitCurrentHP();

	// ���� MP
	InitCurrentMP();

	// ���� ���׹̳�
	InitCurrentStamina();

	// ���� Ȱ��ȭ ���� ��ų��ư
	InitLeftSkillBtn();
	
	// ���� Ȱ��ȭ ������ ��ų��ư
	InitRightSkillBtn();

	// ���� �������� ����
	InitLiquidMedicine();

	// ���� ����ġ
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
	// ���¹̳� �Ҹ� ����
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
	// �÷��̾��� ü�� ����
	HP_->HPConsumption(_Damage);
}

void BottomStateBar::ConsumptionMP(float _MP)
{
	// �÷��̾��� ���� ����
	MP_->MPConsumption(_MP);
}
