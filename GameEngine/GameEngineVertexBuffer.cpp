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

