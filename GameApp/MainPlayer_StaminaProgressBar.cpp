#include "PreCompile.h"
#include "MainPlayer_StaminaProgressBar.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>

#include "MainPlayer.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer_StaminaProgressBar::MainPlayer_StaminaProgressBar() :
	StaminaRenderer_(nullptr)
{
}

MainPlayer_StaminaProgressBar::~MainPlayer_StaminaProgressBar()
{
}

void MainPlayer_StaminaProgressBar::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	StaminaRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	StaminaRenderer_->SetImage("StaminaBar.png");
	StaminaRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	StaminaRenderer_->GetTransform()->SetLocalPosition(float4(-77.f, 18.f - ScreenHarfSize.y));

	//StaminaRenderer_->SetResultColor(float4());
}

void MainPlayer_StaminaProgressBar::Update(float _DeltaTime)
{
	// ���¹̳� �Ҹ� ���
	CalculationStaminaConsumption(_DeltaTime);
}

void MainPlayer_StaminaProgressBar::CalculationStaminaConsumption(float _DeltaTime)
{
	// �����÷��̾ �����Ҷ�
	if (nullptr != GlobalValue::CurPlayer)
	{
		// �����÷��̾ �ٱ�����̸� ���¹̳� �Ҹ� ���
		if (true == GlobalValue::CurPlayer->GetIsRun())
		{









		}
		else // �����÷��̾ �ȱ�����̸� ȸ���� ���
		{







		}
	}
}
