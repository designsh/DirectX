#include "PreCompile.h"
#include "GameEngineImageRenderer.h"

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

void GameEngineImageRenderer::SetImage(const std::string& _ImageName)
{
	ShaderHelper.SettingTexture("Tex", _ImageName);
}
