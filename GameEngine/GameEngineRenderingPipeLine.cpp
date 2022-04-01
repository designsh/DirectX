#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineBlendManager.h"
#include "GameEngineDepthStencilManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"

#include "GameEngineConstantBuffer.h"

#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() :
	VertexBuffer_(nullptr),
	InputLayOutVertexShader_(nullptr),
	VertexShader_(nullptr),
	IndexBuffer_(nullptr),
	Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	Rasterizer_(nullptr),
	PixelShader_(nullptr),
	Blend_(nullptr),
	RenderTarget_(nullptr),
	DepthStencil_(nullptr)
{
	SetOutputMergerBlend("EngineAlphaBlend");
	SetRasterizer("EngineBaseRasterizer");
	SetOutputMergerDepthStencil("BaseDepthOn");
	SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept :
	VertexBuffer_(_other.VertexBuffer_),
	InputLayOutVertexShader_(_other.InputLayOutVertexShader_),
	VertexShader_(_other.VertexShader_),
	IndexBuffer_(_other.IndexBuffer_),
	Topology_(_other.Topology_),
	Rasterizer_(_other.Rasterizer_),
	PixelShader_(_other.PixelShader_),
	Blend_(_other.Blend_),
	RenderTarget_(_other.RenderTarget_),
	DepthStencil_(_other.DepthStencil_)
{
}

// ====================================== Rendering PipeLine 가동 준비단계 ====================================== //
void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 VertexBuffer를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
{
	InputLayOutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayOutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 InputLayout을 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 Vertex Shader를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 Index Buffer를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	Topology_ = _Topology;
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);

	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 Rasterizer를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader_ = GameEnginePixelShaderManager::GetInst().Find(_Name);

	if (nullptr == PixelShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 Pixel Shader를 세팅을 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend_ = GameEngineBlendManager::GetInst().Find(_Name);
	if (nullptr == Blend_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 블랜드를 세팅을 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil_ = GameEngineDepthStencilManager::GetInst().Find(_Name);
	if (nullptr == DepthStencil_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 깊이 세팅을 세팅하려고 했습니다.");
		return;
	}
}

// ======================================== Rendering PipeLine 가동 단계 ======================================== //
void GameEngineRenderingPipeLine::InputAssembler1()
{
	VertexBuffer_->Setting();
	InputLayOutVertexShader_->InputLayOutSetting();
}

void GameEngineRenderingPipeLine::VertexShader()
{
	VertexShader_->Setting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	IndexBuffer_->Setting();
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology_);
}

void GameEngineRenderingPipeLine::Rasteriazer()
{
	Rasterizer_->Setting();							// Rasterizer Setting
	Rasterizer_->SettingViewPort();			// Viewport Setting
	Rasterizer_->SettingScissor();				// Scissor Setting
}

void GameEngineRenderingPipeLine::PixelShader()
{
	PixelShader_->Setting();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	Blend_->Setting();
	DepthStencil_->Setting();
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	Rasteriazer();
	PixelShader();
	OutputMerger();
}

void GameEngineRenderingPipeLine::Rendering()
{
	// 렌더링파이프라인 가동전 셋팅
	RenderingPipeLineSetting();

	// 렌더링파이프라인 가동
	// 첫번째 인자 : 렌더링할 인덱스의 수
	// 두번째 인자 : 인덱스 버퍼에서 GPU가 읽은 첫 번째 인덱스의 위치
	// 세번째 인자 : 정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer_->GetIndexCount(), 0, 0);
	// GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer_->GetIndexCount(), 0, 0, 1000);
}

void GameEngineRenderingPipeLine::Reset()
{
	// 블렌드 셋팅 초기화
	Blend_->Reset();

	// DepthStencil 셋팅 초기화
	DepthStencil_->Reset();
}
