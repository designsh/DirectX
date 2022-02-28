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

	// ũ�������� �������ʾҴٸ� �̹���ũ���� ũ�⸦ �����ϰ�,
	if (true == _RenderSize.IsZero())
	{
		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
		if (nullptr != FindTexture)
		{
			float4 ImageSize = FindTexture->GetImageSize();
			GetTransform()->SetLocalScaling(float4(ImageSize));
		}
	}
	else // ũ�⸦ �����ߴٸ� �ش� ũ��� ���̴�ũ�������� ����
	{
		GetTransform()->SetLocalScaling(float4(_RenderSize));
	}
}
