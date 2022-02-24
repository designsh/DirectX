#include "PreCompile.h"
#include "Monster.h"

#include "GameEngine/GameEngineImageRenderer.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}



void Monster::Start()
{
	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	Renderer->SetImage("Animation.png");
	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void Monster::Update(float _DeltaTime)
{

}