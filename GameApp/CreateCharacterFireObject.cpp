#include "PreCompile.h"
#include "CreateCharacterFireObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

CreateCharacterFireObject::CreateCharacterFireObject() :
	FireAnimation_(nullptr)
{
}

CreateCharacterFireObject::~CreateCharacterFireObject()
{
}

void CreateCharacterFireObject::Start()
{
	GameEngineTexture* Loading = GameEngineTextureManager::GetInst().Find("CreateCharacter_Fire.png");
	Loading->Cut(30, 1);

	FireAnimation_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	FireAnimation_->CreateAnimation("CreateCharacter_Fire.png", "FireAnimation", 0, 29, 0.1f);
	FireAnimation_->GetTransform()->SetLocalScaling(float4(150.f, 176.f, 1.f));
	FireAnimation_->GetTransform()->SetLocalPosition(float4(0.f, -100.f));
	FireAnimation_->SetChangeAnimation("FireAnimation");
}

void CreateCharacterFireObject::Update(float _DeltaTime)
{
}
