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
	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("Title_BackDrop.png", float4(1280.f, 720.f));
}

void TitleBackDrop::Update(float _DeltaTime)
{
}
