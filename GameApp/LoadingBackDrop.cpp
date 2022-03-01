#include "PreCompile.h"
#include "LoadingBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

LoadingBackDrop::LoadingBackDrop() :
	BackDrop_(nullptr)
{
}

LoadingBackDrop::~LoadingBackDrop()
{
}

void LoadingBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("LoadingBackDrop.png", WindowSize);
}

void LoadingBackDrop::Update(float _DeltaTime)
{
}
