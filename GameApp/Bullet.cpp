#include "PreCompile.h"
#include "Bullet.h"
#include <GameEngine/GameEngineRenderer.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}



void Bullet::Start()
{
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 1.0f, 1.0f));
	}
}

void Bullet::Update(float _DeltaTime)
{
	GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 200.0f);
}