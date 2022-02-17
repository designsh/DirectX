#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"

GameEngineRenderer::GameEngineRenderer() :
	PipeLine_(nullptr)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	GetLevel()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Render()
{
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
		if (true == PipeLine_->ShaderHelper.IsConstantBuffer("TransformData"))
		{
			PipeLine_->ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
		}
	}
}
