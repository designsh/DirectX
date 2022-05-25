#include "PreCompile.h"
#include "EndingCredit.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"

EndingCredit::EndingCredit() :
	EndingCredit_(nullptr)
{
}

EndingCredit::~EndingCredit()
{
}

void EndingCredit::Start()
{
	float4 HarfScreenSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	EndingCredit_ = CreateTransformComponent<GameEngineUIRenderer>();
	EndingCredit_->SetImage("MessageView_Panel.png");
	EndingCredit_->SetAlpha(0.f);
	EndingCredit_->TextSetting("diablo", "THE END", 50, FW1_CENTER | FW1_VCENTER, float4(1.f, 0.9f, 0.7f));
	EndingCredit_->GetTransform()->SetLocalPosition(float4(0.f, HarfScreenSize.y - 30.f));
}

void EndingCredit::Update(float _DeltaTime)
{
}
