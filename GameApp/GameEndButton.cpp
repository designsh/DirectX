#include "PreCompile.h"
#include "GameEndButton.h"

#include <GameEngine/GameEngineUIRenderer.h>

GameEndButton::GameEndButton() :
	EndButton_(nullptr)
{
}

GameEndButton::~GameEndButton()
{
}

void GameEndButton::Start()
{
	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("LongButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	// 추후 버튼UI 만들면 변경예정
	EndButton_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	EndButton_->SetRenderingPipeLine("Texture");
	EndButton_->ShaderHelper.SettingTexture("Tex", "LongButton_Stay.png");
	EndButton_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	EndButton_->GetTransform()->SetLocalScaling(float4(430.f, 40.f));
	EndButton_->GetTransform()->SetLocalPosition(float4(0.f, -300.f));
}

void GameEndButton::Update(float _DeltaTime)
{
}
