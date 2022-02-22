#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Monster.h"
#include "Bullet.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}



void Monster::Start()
{
	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	Renderer->SetRenderingPipeLine("Color");
	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 0.0f, 0.0f));
}

void Monster::Update(float _DeltaTime)
{

}