#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// ���� ����
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


	// ���¹̳�
	Stamina_ = GetLevel()->CreateActor<MainPlayer_Stamina>();

	// ����ĭ


	// �̴ϸ޴�����
	MiniMenu_ = GetLevel()->CreateActor<MainPlayer_MiniMenu>();

}

void BottomStateBar::Update(float _DeltaTime)
{
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
