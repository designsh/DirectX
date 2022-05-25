#include "PreCompile.h"
#include "EndingBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

EndingBackDrop::EndingBackDrop() :
	BackDrop_(nullptr)
{
}

EndingBackDrop::~EndingBackDrop()
{
}

void EndingBackDrop::Start()
{
	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>();
	BackDrop_->SetImage("EndingLevel_BackDrop.png");
}

void EndingBackDrop::Update(float _DeltaTime)
{
}
