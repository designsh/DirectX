#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"

GameEngineImageRenderer::GameEngineImageRenderer()
{
}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, const float4& _RenderSize)
{
	ShaderHelper.SettingTexture("Tex", _ImageName);

	// 크기지정을 해주지않았다면 이미지크기대로 크기를 설정하고,
	if (true == _RenderSize.IsZero())
	{
		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
		if (nullptr != FindTexture)
		{
			float4 ImageSize = FindTexture->GetImageSize();
			GetTransform()->SetLocalScaling(float4(ImageSize));
		}
	}
	else // 크기를 지정했다면 해당 크기로 셰이더크기정보를 셋팅
	{
		GetTransform()->SetLocalScaling(float4(_RenderSize));
	}
}
