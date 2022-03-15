#include "PreCompile.h"
#include "CreateCharacterBackDrop.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

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

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::BackDrop));
	BackDrop_->SetImage("CreateCharacter_BackDrop.png", WindowSize);
}

void CreateCharacterBackDrop::Update(float _DeltaTime)
{
}
