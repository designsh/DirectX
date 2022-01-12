#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() // default constructer ����Ʈ ������
{

}

GameEngineVertexBuffer::~GameEngineVertexBuffer() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineVertexBuffer::GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

const std::vector<float4>& GameEngineVertexBuffer::GetVertexs()
{
    return Vertexs_;
}

void GameEngineVertexBuffer::Create(const std::vector<float4>& _Vertexs)
{
	for (const float4& Data : _Vertexs)
	{
		Vertexs_.push_back(Data);
	}
}

