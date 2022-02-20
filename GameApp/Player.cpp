#include "PreCompile.h"
#include "Player.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngineBase/GameEngineTime.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	}

	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->GetTransform()->SetLocalPosition({ 0.0f, 150.0f, 0.0f });
	}
}

void Player::Update(float _DeltaTime)
{
}
