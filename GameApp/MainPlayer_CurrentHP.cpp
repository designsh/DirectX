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
}

void MainPlayer_CurrentHP::Update(float _DeltaTime)
{
}

void MainPlayer_CurrentHP::HPConsumption(float _Damage)
{
	// �÷��̾��� ���� ü�¿� ������ �޾� �̹����� �����Ͽ� ������
	if (nullptr != GlobalValue::CurPlayer)
	{
		// ���� �÷��̾��� ü�°���(������)
		GlobalValue::CurPlayer->DelCurrentHP(static_cast<int>(_Damage));

		// ���� HP Circle�� �ۼ�Ʈ�� ���
		
		//HPRenderer_->SetParent();
	}
}
