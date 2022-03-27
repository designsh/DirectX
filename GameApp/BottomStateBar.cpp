#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer_CurrentHP.h"

BottomStateBar::BottomStateBar() :
	Panel_(nullptr)
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



	// ���ʹ��� Ȱ��ȭ ��ų��ư(�⺻���� ���� �ƹ��͵� ����)


	
	
	// ���ʹ��� Ȱ��ȭ ��ų��ư(�����÷��̾��� ��ų���� �����Ͽ� Ȱ��ȭ�� ��ų��ư ����)



	// ���� ����ġ




	// ���¹̳� Ȱ��/��Ȱ�� ��ư




	// ���¹̳� ProgressBar




	// ����ĭ ���þ���



	// �̴ϸ޴�����

}

void BottomStateBar::Update(float _DeltaTime)
{
}

void BottomStateBar::InitBottomStateBar()
{
	// ���� HP
	

	// ���� MP
	

	// ���� ���׹̳�
	

	// ���� Ȱ��ȭ ���� ��ų��ư
	

	// ���� Ȱ��ȭ ������ ��ų��ư
	

	// ���� �������� ����
	

	// ���� ����ġ


}

void BottomStateBar::InitCurrentHP()
{
}

void BottomStateBar::InitCurrentMP()
{
}

void BottomStateBar::InitCurrentStamina()
{
}

void BottomStateBar::InitLeftSkillBtn()
{
}

void BottomStateBar::InitRightSkillBtn()
{
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
	HP_->SetImageCutting(_Damage);
}

void BottomStateBar::ConsumptionMP(float _MP)
{
	// �÷��̾��� ���� ����

}
