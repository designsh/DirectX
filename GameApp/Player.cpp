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
	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	Renderer->SetRenderingPipeLine("Color");
}

void Player::Update(float _DeltaTime)
{
}
