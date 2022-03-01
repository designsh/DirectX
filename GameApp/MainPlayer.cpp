#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineRenderer.h>

MainPlayer::MainPlayer() :
	PlayerInfomation_(nullptr),
	PlayerImageRenderer_(nullptr)
{
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::Start()
{
	// 임시테스트용
	PlayerImageRenderer_ = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	PlayerImageRenderer_->SetRenderingPipeLine("Color");
	PlayerImageRenderer_->GetTransform()->SetLocalScaling(float4(100.f, 100.f, 1.f));
	PlayerImageRenderer_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.f, 1.f, 1.f));
}

void MainPlayer::Update(float _DeltaTime)
{
}

