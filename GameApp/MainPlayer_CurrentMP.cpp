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
	// 플레이어의 현재 체력에 영향을 받아 이미지를 컷팅하여 렌더링
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 현재 플레이어의 체력감소(데이터)
		GlobalValue::CurPlayer->DelCurrentMP(static_cast<int>(_Damage));

		// 현재 MP Circle의 퍼센트를 계산
		//MPRenderer_->SetParent();
	}
}
