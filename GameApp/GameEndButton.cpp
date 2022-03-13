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

	// ���� ��ưUI ����� ���濹��
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
