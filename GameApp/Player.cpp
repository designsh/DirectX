#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"

#include <GameEngine/GameEngineImageRenderer.h>

Player::Player() :
	PlayerImageRenderer(nullptr)
{
}

Player::~Player()
{
}

void Player::Start()
{
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("Char.png");
		//PlayerImageRenderer->SetImage("Char.png", float4(100.f, 100.f, 1.f));
	}

	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
		Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	}

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst().CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst().CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst().CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
		GameEngineInput::GetInst().CreateKey("RotZ-", 'E');
		GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
	}
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Down("Fire"))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		NewBullet->Release(10.0f);
	}

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}
