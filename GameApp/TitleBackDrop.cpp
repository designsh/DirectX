#include "PreCompile.h"
#include "TitleBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

TitleBackDrop::TitleBackDrop() :
	BackDrop_(nullptr)
{
}

TitleBackDrop::~TitleBackDrop()
{
}

void TitleBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>();
	BackDrop_->SetImage("Title_BackDrop.png", WindowSize);
	BackDrop_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(DepthZOrder::BackDrop)));
}

void TitleBackDrop::Update(float _DeltaTime)
{
}
