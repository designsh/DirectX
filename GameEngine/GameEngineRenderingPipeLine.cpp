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

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
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
	// Vertex Buffer 받아와서 보관단계
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);
	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	// VertexShader 받아와서 보관단계
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);
	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2(const std::string& _Name)
{
	// Index Buffer 받아와서 보관단계
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);
	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 인덱스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);
	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 래스터라이저를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::Rendering()
{
	// Input Assembler1 가동단계
	// : 원본 Vertex Buffer를 복사한 복제본을 만들어낸다.
	std::vector<float4> CopyVertex;
	CopyVertex = VertexBuffer_->GetVertexs();

	// Vertex Shader 가동단계
	// : 복제본 Vertex Buffer를 이용하여 이동/회전/크기변환 등 기능을 수행한다.
	//   이때 각 기능별 함수를 함수포인터를 이용하여 기능을 호출하여 복제본에 어떠한 
	//   변화를 반영한 뒤 변환된 Vertex Buffer를 받아와서 복제본 VertexBuffer에 저장한다.
	for (size_t i = 0; i < CopyVertex.size(); ++i)
	{
		CopyVertex[i] = VertexShader_->VertexShaderFunction(CopyVertex[i]);
	}

	// Input Assembler2 가동단계
	// : 인덱스 버퍼를 이용하여 면을생성
	std::vector<std::vector<float4>> TriVector;
	const std::vector<int>& Index = IndexBuffer_->Indexs_;

	// 삼각형 면의 개수만큼 resize
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

	// Rasterizer 가동단계
	for (size_t Tri = 0; Tri < TriVector.size(); ++Tri)
	{
		for (size_t i = 0; i < TriVector[Tri].size(); ++i)
		{
			Rasterizer_->RasterizerUpdate(TriVector[Tri][i]);
		}
	}

	// Pixel Shader 가동단계(블렌딩 단계)





	// 화면 렌더링
	for (size_t Tri = 0; Tri < TriVector.size(); Tri++)
	{

		POINT ArrTri[3] = {};

		ArrTri[0] = TriVector[Tri][0].GetWindowPoint();
		ArrTri[1] = TriVector[Tri][1].GetWindowPoint();
		ArrTri[2] = TriVector[Tri][2].GetWindowPoint();

		Polygon(GameEngineWindow::GetInst().GetWindowDC(), &ArrTri[0], 3);
	}

}
