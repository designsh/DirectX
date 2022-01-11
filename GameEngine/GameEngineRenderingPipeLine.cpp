#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() :
	VertexBuffer_(nullptr),
	VertexShader_(nullptr)
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
	// Vertex Buffer 받아와서 보관단계
	VertexBuffer_ = _Ptr;
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Ptr)
{
	// VertexShader 받아와서 보관단계
	VertexShader_ = _Ptr;
}

void GameEngineRenderingPipeLine::Rendering()
{
	// Input Assembler1 가동단계
	// : 원본 Vertex Buffer를 복사한 복제본을 만들어낸다.
	CopyVertex_ = VertexBuffer_->GetVertexs();

	// Vertex Shader 가동단계
	// : 복제본 Vertex Buffer를 이용하여 이동/회전/크기변환 등 기능을 수행한다.
	//   이때 각 기능별 함수를 함수포인터를 이용하여 기능을 호출하여 복제본에 어떠한 
	//   변화를 반영한 뒤 변환된 Vertex Buffer를 받아와서 복제본 VertexBuffer에 저장한다.
	for (size_t i = 0; i < CopyVertex_.size(); ++i)
	{
		//CopyVertex_[i] = VertexShader_->VertexShaderFunction(CopyVertex_[i]);
	}



	// 
}
