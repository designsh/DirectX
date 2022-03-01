#include "PreCompile.h"
#include "CreateCharacterBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

CreateCharacterBackDrop::CreateCharacterBackDrop() :
	BackDrop_(nullptr)
{
}

CreateCharacterBackDrop::~CreateCharacterBackDrop()
{
}

void CreateCharacterBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("CreateCharacter_BackDrop.png", WindowSize);
}

void CreateCharacterBackDrop::Update(float _DeltaTime)
{
}
