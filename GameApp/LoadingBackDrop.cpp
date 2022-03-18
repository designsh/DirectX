#include "PreCompile.h"
#include "LoadingBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

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
	BackDrop_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(DepthZOrder::BackDrop)));
}

void LoadingBackDrop::Update(float _DeltaTime)
{
}
