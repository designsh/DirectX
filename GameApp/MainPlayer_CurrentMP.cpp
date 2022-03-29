#include "PreCompile.h"
#include "MainPlayer_CurrentMP.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>
#include <GameEngine/GameEngineWindow.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

MainPlayer_CurrentMP::MainPlayer_CurrentMP() :
	MPRenderer_(nullptr)
{
}

MainPlayer_CurrentMP::~MainPlayer_CurrentMP()
{
}

void MainPlayer_CurrentMP::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	MPRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	MPRenderer_->SetImage("MP.png");
	MPRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::TopToBottom));
	MPRenderer_->GetTransform()->SetLocalPosition(float4(ScreenHarfSize.x - 68.f, 52.f - ScreenHarfSize.y));
}

void MainPlayer_CurrentMP::Update(float _DeltaTime)
{
}

void MainPlayer_CurrentMP::MPConsumption(float _Damage)
{
	// �÷��̾��� ���� ü�¿� ������ �޾� �̹����� �����Ͽ� ������
	if (nullptr != GlobalValue::CurPlayer)
	{
		// ���� �÷��̾��� ü�°���(������)
		GlobalValue::CurPlayer->DelCurrentMP(static_cast<int>(_Damage));

		// ���� MP Circle�� �ۼ�Ʈ�� ���
		//MPRenderer_->SetParent();
	}
}
