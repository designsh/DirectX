#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

GameEngineRenderer::GameEngineRenderer() :
	PipeLine_(nullptr),
	ShaderHelper()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	GetLevel()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Update()
{
}

void GameEngineRenderer::Render()
{
	ShaderHelper.Setting();
	PipeLine_->Rendering();
}

void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Value);
	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 파이프라인 입니다!");
	}
	else
	{
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetVertexShader());
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetPixelShader());
		if (true == ShaderHelper.IsConstantBuffer("TransformData"))
		{
			ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
		}
	}
}
