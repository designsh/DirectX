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
	// Input Assembler1 �����ܰ�
	// : ���� Vertex Buffer�� ������ �������� ������.
	std::vector<float4> CopyVertex;
	CopyVertex = VertexBuffer_->GetVertexs();

	// Vertex Shader �����ܰ�
	// : ������ Vertex Buffer�� �̿��Ͽ� �̵�/ȸ��/ũ�⺯ȯ �� ����� �����Ѵ�.
	//   �̶� �� ��ɺ� �Լ��� �Լ������͸� �̿��Ͽ� ����� ȣ���Ͽ� �������� ��� 
	//   ��ȭ�� �ݿ��� �� ��ȯ�� Vertex Buffer�� �޾ƿͼ� ������ VertexBuffer�� �����Ѵ�.
	for (size_t i = 0; i < CopyVertex.size(); ++i)
	{
		CopyVertex[i] = VertexShader_->VertexShaderFunction(CopyVertex[i]);
	}

	// Input Assembler2 �����ܰ�
	// : �ε��� ���۸� �̿��Ͽ� ��������
	std::vector<std::vector<float4>> TriVector;
	const std::vector<int>& Index = IndexBuffer_->Indexs_;

	// �ﰢ�� ���� ������ŭ resize
	TriVector.resize(Index.size() / 3);

	for (size_t TriCount = 0; TriCount < Index.size() / 3; TriCount++)
	{
		TriVector[TriCount].resize(3);

		int CurIndex0 = Index[(TriCount * 3) + 0];
		int CurIndex1 = Index[(TriCount * 3) + 1];
		int CurIndex2 = Index[(TriCount * 3) + 2];

		TriVector[TriCount][0] = CopyVertex[CurIndex0];
		TriVector[TriCount][1] = CopyVertex[CurIndex1];
		TriVector[TriCount][2] = CopyVertex[CurIndex2];
	}

	// Rasterizer �����ܰ�
	for (size_t Tri = 0; Tri < TriVector.size(); ++Tri)
	{
		for (size_t i = 0; i < TriVector[Tri].size(); ++i)
		{
			Rasterizer_->RasterizerUpdate(TriVector[Tri][i]);
		}
	}

	// Pixel Shader �����ܰ�(���� �ܰ�)





	// ȭ�� ������
	for (size_t Tri = 0; Tri < TriVector.size(); Tri++)
	{

		POINT ArrTri[3] = {};

		ArrTri[0] = TriVector[Tri][0].GetWindowPoint();
		ArrTri[1] = TriVector[Tri][1].GetWindowPoint();
		ArrTri[2] = TriVector[Tri][2].GetWindowPoint();

		Polygon(GameEngineWindow::GetInst().GetWindowDC(), &ArrTri[0], 3);
	}

}
