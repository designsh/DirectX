#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer ����Ʈ ������
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
	// Vertex Buffer���� �������� ���� �������۸� ����
	CopyVertex_ = _Ptr->GetVertexs();
}

void GameEngineRenderingPipeLine::OutPutMerge()
{
	// ����� ����ۿ� �ȼ�(����)�������� ����ϸ�, ���� �۾�ó��

}

