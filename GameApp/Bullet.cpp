#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	Renderer->SetRenderingPipeLine("Color");
	Renderer->GetTransform()->SetLocalScaling({ 10.0f, 10.0f, 1.0f });
	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 1.0f, 1.0f));
}

void Bullet::Update(float _DeltaTime)
{
	GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 200.0f);
}