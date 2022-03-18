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

	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>();
	BackDrop_->SetImage("CreateCharacter_BackDrop.png", WindowSize);
	BackDrop_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, static_cast<float>(DepthZOrder::BackDrop)));
}

void CreateCharacterBackDrop::Update(float _DeltaTime)
{
}
