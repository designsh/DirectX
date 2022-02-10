#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"

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
	RenderTarget_(nullptr)
{
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
	RenderTarget_(_other.RenderTarget_)
{
}

// ====================================== Rendering PipeLine ���� �غ�ܰ� ====================================== //
void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� VertexBuffer�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
{
	InputLayOutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayOutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� InputLayout�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� Vertex Shader�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� Index Buffer�� �����Ϸ��� �߽��ϴ�.");
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
		GameEngineDebug::MsgBoxError("�������� �ʴ� Rasterizer�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader_ = GameEnginePixelShaderManager::GetInst().Find(_Name);

	if (nullptr == PixelShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� Pixel Shader�� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMerger(const std::string& _Name)
{
	//RenderTarget_ = GameEngineRenderTarget::GetInst().Find(_Name);
	
	//if (nullptr == RenderTarget_)
	//{
	//	GameEngineDebug::MsgBoxError("�������� �ʴ� Render Target�� �����Ϸ��� �߽��ϴ�.");
	//	return;
	//}
}

// ======================================== Rendering PipeLine ���� �ܰ� ======================================== //
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

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	Rasteriazer();
	PixelShader();
}

void GameEngineRenderingPipeLine::Rendering()
{
	// ���������������� ������ ����
	RenderingPipeLineSetting();

	// ���������������� ����
	// ù��° ���� : �������� �ε����� ��
	// �ι�° ���� : �ε��� ���ۿ��� GPU�� ���� ù ��° �ε����� ��ġ
	// ����° ���� : ���� ���ۿ��� ������ �б� ���� �� �ε����� �߰��� ��
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer_->GetIndexCount(), 0, 0);
}

// ============================================== ���̴� ���� ���� ============================================= //
void GameEngineRenderingPipeLine::ResourcesCheck()
{
	ShaderResourcesCheck(VertexShader_);
	ShaderResourcesCheck(PixelShader_);
}

void GameEngineRenderingPipeLine::ShaderResourcesCheck(GameEngineShader* _Shader)
{
	for (auto& Constbuffer : _Shader->GetConstanceBuffer())
	{
		GameEngineConstantBufferSetting* NewSettingData = new GameEngineConstantBufferSetting();
	}
}
