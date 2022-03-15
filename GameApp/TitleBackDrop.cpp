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

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::BackDrop));
	BackDrop_->SetImage("Title_BackDrop.png", WindowSize);
}

void TitleBackDrop::Update(float _DeltaTime)
{
}
