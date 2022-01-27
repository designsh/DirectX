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

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
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
	// Vertex Buffer 받아와서 보관단계
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);
	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	// VertexShader 받아와서 보관단계
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);
	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2(const std::string& _Name)
{
	// Index Buffer 받아와서 보관단계
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);
	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 인덱스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);
	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 래스터라이저를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::Rendering()
{
}
