#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer 디폴트 생성자
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(GameEngineVertexBuffer* _Ptr)
{
	// Vertex Buffer에서 관리중인 원본 정점버퍼를 복제
	CopyVertex_ = _Ptr->GetVertexs();
}

void GameEngineRenderingPipeLine::OutPutMerge()
{
	// 출력전 백버퍼에 픽셀(정점)정보들을 기록하며, 블랜딩 작업처리

}

