#include "PreCompile.h"
#include "GameEngineProgressBarRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineWindow.h"
#include "GameEngineRenderTarget.h"

GameEngineProgressBarRenderer::GameEngineProgressBarRenderer() :
	ProgressBarData_{},
	ColorTint_(float4::WHITE)
{
}

GameEngineProgressBarRenderer::~GameEngineProgressBarRenderer()
{
}

void GameEngineProgressBarRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);

	SetRenderingPipeLine("ProgressBarUI");
	ShaderHelper.SettingConstantBufferLink("ProgressBarCBuffer", ProgressBarData_);
}

void GameEngineProgressBarRenderer::Render()
{
	GameEngineRenderer::Render();


}

void GameEngineProgressBarRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);
}

void GameEngineProgressBarRenderer::SetProgressBarDirect(int _ProgressBarDir)
{
	ProgressBarData_.PregressDirect = _ProgressBarDir;
}

void GameEngineProgressBarRenderer::SetPercent(float _Percent)
{
	ProgressBarData_.Percent = _Percent;
}

void GameEngineProgressBarRenderer::SetColor(float4 _Color)
{
	ColorTint_ = _Color;
}
