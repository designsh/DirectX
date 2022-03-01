#include "PreCompile.h"
#include "CreateCharactorBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

CreateCharactorBackDrop::CreateCharactorBackDrop() :
	BackDrop_(nullptr)
{
}

CreateCharactorBackDrop::~CreateCharactorBackDrop()
{
}

void CreateCharactorBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("CreateCharacter_BackDrop.png", WindowSize);
}

void CreateCharactorBackDrop::Update(float _DeltaTime)
{
}
