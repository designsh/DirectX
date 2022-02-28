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
	BackDrop_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BackDrop_->SetImage("CreateCharactor_BackDrop.png", float4(1280.f, 720.f));
}

void CreateCharactorBackDrop::Update(float _DeltaTime)
{
}
