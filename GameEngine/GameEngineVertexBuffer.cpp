#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() // default constructer 디폴트 생성자
{

}

GameEngineVertexBuffer::~GameEngineVertexBuffer() // default destructer 디폴트 소멸자
{

}

GameEngineVertexBuffer::GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

const std::vector<float4>& GameEngineVertexBuffer::GetVertexs()
{
    return Vertexs_;
}

