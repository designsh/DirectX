#include "PreCompile.h"
#include "MainPlayer_CurExpProgressBar.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

MainPlayer_CurExpProgressBar::MainPlayer_CurExpProgressBar() :
	ExpRenderer_(nullptr),
	Reflection_(false),
	CurEXP_(0)
{
}

MainPlayer_CurExpProgressBar::~MainPlayer_CurExpProgressBar()
{
}

void MainPlayer_CurExpProgressBar::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	ExpRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	ExpRenderer_->SetImage("MainPlayer_CurEXP.png");
	ExpRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	ExpRenderer_->GetTransform()->SetLocalPosition(float4(-85.f, 38.f - ScreenHarfSize.y));
	ExpRenderer_->SetPercent(0.0f);
}

void MainPlayer_CurExpProgressBar::Update(float _DeltaTime)
{
	// ���� �÷��̾ �����Ҷ� ���� �÷��̾��� ����ġ�� �ݿ�
	if (nullptr != GlobalValue::CurPlayer)
	{
		if (false == Reflection_)
		{
			// ������ ���������ʾ����� �÷��̾��� �������ġ�� ��������ġ�� �ٸ��ٸ� ����ġ�ٸ� �����ϰ�,
			// ���� Flag On
			if (GlobalValue::CurPlayer->GetCurrentEXP() != GlobalValue::CurPlayer->GetPrevEXP())
			{
				float ExpBarPercent = static_cast<float>(GlobalValue::CurPlayer->GetCurrentEXP());
				ExpBarPercent *= 0.01f;
				ExpRenderer_->SetPercent(ExpBarPercent);

				Reflection_ = true;
			}
		}
	}
}
