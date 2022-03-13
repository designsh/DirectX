#include "PreCompile.h"
#include "GameStartButton.h"

#include <GameEngine/GameEngineUIRenderer.h>

GameStartButton::GameStartButton() :
	StartButton_(nullptr)
{
}

GameStartButton::~GameStartButton()
{
}

void GameStartButton::Start()
{
	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("LongButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();
	
	// 추후 버튼UI 만들면 변경예정
	StartButton_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	StartButton_->SetRenderingPipeLine("Texture");
	StartButton_->ShaderHelper.SettingTexture("Tex", "LongButton_Stay.png");
	StartButton_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	StartButton_->GetTransform()->SetLocalScaling(float4(430.f, 40.f));
}

void GameStartButton::Update(float _DeltaTime)
{
}
