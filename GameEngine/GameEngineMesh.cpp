#include "PreCompile.h"
#include "GameEngineMesh.h"

GameEngineMesh::GameEngineMesh() :
	VertexBuffer_(nullptr),
	IndexBuffer_(nullptr)
{

}

GameEngineMesh::~GameEngineMesh() // default destructer 디폴트 소멸자
{

}

GameEngineMesh::GameEngineMesh(GameEngineMesh&& _other) noexcept :
	VertexBuffer_(_other.VertexBuffer_),
	IndexBuffer_(_other.IndexBuffer_)
{

}

