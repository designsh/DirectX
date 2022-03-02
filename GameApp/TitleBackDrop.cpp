#include "PreCompile.h"
#include "TitleBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

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

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("Title_BackDrop.png", WindowSize);
}

void TitleBackDrop::Update(float _DeltaTime)
{
}