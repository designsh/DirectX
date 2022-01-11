#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() :
	VertexBuffer_(nullptr),
	VertexShader_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(GameEngineVertexBuffer* _Ptr)
{
	// Vertex Buffer �޾ƿͼ� �����ܰ�
	VertexBuffer_ = _Ptr;
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Ptr)
{
	// VertexShader �޾ƿͼ� �����ܰ�
	VertexShader_ = _Ptr;
}

void GameEngineRenderingPipeLine::Rendering()
{
	// Input Assembler1 �����ܰ�
	// : ���� Vertex Buffer�� ������ �������� ������.
	CopyVertex_ = VertexBuffer_->GetVertexs();

	// Vertex Shader �����ܰ�
	// : ������ Vertex Buffer�� �̿��Ͽ� �̵�/ȸ��/ũ�⺯ȯ �� ����� �����Ѵ�.
	//   �̶� �� ��ɺ� �Լ��� �Լ������͸� �̿��Ͽ� ����� ȣ���Ͽ� �������� ��� 
	//   ��ȭ�� �ݿ��� �� ��ȯ�� Vertex Buffer�� �޾ƿͼ� ������ VertexBuffer�� �����Ѵ�.
	for (size_t i = 0; i < CopyVertex_.size(); ++i)
	{
		//CopyVertex_[i] = VertexShader_->VertexShaderFunction(CopyVertex_[i]);
	}



	// 
}
