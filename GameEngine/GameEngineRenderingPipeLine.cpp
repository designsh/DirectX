#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"

#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() :
	VertexBuffer_(nullptr),
	VertexShader_(nullptr),
	IndexBuffer_(nullptr),
	Rasterizer_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept :
	VertexBuffer_(_other.VertexBuffer_),
	VertexShader_(_other.VertexShader_),
	IndexBuffer_(_other.IndexBuffer_),
	Rasterizer_(_other.Rasterizer_)
{

}

void GameEngineRenderingPipeLine::SetMesh()
{
	// SetInputAssembler1();
	// SetInputAssembler2();

}

void GameEngineRenderingPipeLine::SetMaterial()
{
	// 

}

void GameEngineRenderingPipeLine::SetInputAssembler1(const std::string& _Name)
{
	// Vertex Buffer �޾ƿͼ� �����ܰ�
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);
	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	// VertexShader �޾ƿͼ� �����ܰ�
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);
	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2(const std::string& _Name)
{
	// Index Buffer �޾ƿͼ� �����ܰ�
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);
	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ε��� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);
	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �����Ͷ������� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::Rendering()
{
}
