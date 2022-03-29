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
	// 스태미나 소모량 계산
	CalculationStaminaConsumption(_DeltaTime);
}

void MainPlayer_StaminaProgressBar::CalculationStaminaConsumption(float _DeltaTime)
{
	// 메인플레이어가 존재할때
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 메인플레이어가 뛰기상태이면 스태미나 소모량 계산
		if (true == GlobalValue::CurPlayer->GetIsRun())
		{









		}
		else // 메인플레이어가 걷기상태이면 회복량 계산
		{







		}
	}
}
