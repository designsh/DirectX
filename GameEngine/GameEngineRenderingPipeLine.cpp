#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
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
	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
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

	// �����Ͷ�����


	// Input Assembler2 �����ܰ�
	// : �ε��� ���۸� �̿��Ͽ� ȭ�鿡 ������
	const std::vector<int>& Index = IndexBuffer_->Indexs_;
	POINT ArrTri[3];
	for (size_t TriCount = 0; TriCount < Index.size() / 3; TriCount++)
	{
		for (size_t i = 0; i < 3; i++)
		{
			int CurIndex = Index[(TriCount * 3) + i];

			ArrTri[i] = CopyVertex[CurIndex].GetWindowPoint();
		}

		Polygon(GameEngineWindow::GetInst().GetWindowDC(), &ArrTri[0], 3);
	}
}
