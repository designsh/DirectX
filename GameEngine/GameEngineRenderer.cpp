#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "CameraComponent.h"

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
	GetLevel()->GetMainCamera()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Update()
{
}

void GameEngineRenderer::Render()
{
	ShaderHelper.Setting();
	PipeLine_->Rendering();
	ShaderHelper.ReSet();
	PipeLine_->Reset();
}

void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Value);
	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���������� �Դϴ�!");
	}
	else
	{
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetPixelShader());
		ShaderHelper.ShaderResourcesCheck(PipeLine_->GetVertexShader());
		
		if (true == ShaderHelper.IsConstantBuffer("TransformData"))
		{
			ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
		}
	}
}