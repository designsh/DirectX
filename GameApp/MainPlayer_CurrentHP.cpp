#include "PreCompile.h"
#include "MainPlayer_CurrentHP.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>
#include <GameEngine/GameEngineWindow.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

MainPlayer_CurrentHP::MainPlayer_CurrentHP() :
	HPRenderer_(nullptr)
{
}

MainPlayer_CurrentHP::~MainPlayer_CurrentHP()
{
}

void MainPlayer_CurrentHP::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	HPRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	HPRenderer_->SetImage("HP.png");
	HPRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::BottomToTop));
	HPRenderer_->GetTransform()->SetLocalPosition(float4(68.f - ScreenHarfSize.x, 52.f - ScreenHarfSize.y));

	if (false == GameEngineInput::GetInst().IsKey("TESTKEY"))
	{
		GameEngineInput::GetInst().CreateKey("TESTKEY", VK_END);
	}

	if (false == GameEngineInput::GetInst().IsKey("TESTKEY2"))
	{
		GameEngineInput::GetInst().CreateKey("TESTKEY2", VK_HOME);
	}
}

void MainPlayer_CurrentHP::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("TESTKEY"))
	{
		HPRenderer_->SetPercent(test);
		test -= 0.1f;
		if (test <= 0.0f)
		{
			test = 0.0f;
		}
	}

	if (true == GameEngineInput::GetInst().Down("TESTKEY2"))
	{
		HPRenderer_->SetPercent(test);
		test += 0.1f;
		if (test >= 1.0f)
		{
			test = 1.0f;
		}
	}
}

void MainPlayer_CurrentHP::HPConsumption(float _Damage)
{
	// 플레이어의 현재 체력에 영향을 받아 이미지를 컷팅하여 렌더링
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 현재 플레이어의 체력감소(데이터)
		GlobalValue::CurPlayer->DelCurrentHP(static_cast<int>(_Damage));

		// 현재 HP Circle의 퍼센트를 계산

	}
}
