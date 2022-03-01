#include "PreCompile.h"
#include "SelectCharacterBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

SelectCharacterBackDrop::SelectCharacterBackDrop() :
	BackDrop_(nullptr)
{
}

SelectCharacterBackDrop::~SelectCharacterBackDrop()
{
}

void SelectCharacterBackDrop::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("CreateCharacter_BackDrop.png", WindowSize);
}

void SelectCharacterBackDrop::Update(float _DeltaTime)
{

}
