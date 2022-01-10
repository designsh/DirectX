#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 렌더링 파이프라인 
// 용도 : 
// 설명 : 렌더링 파이프라인 순서별 기능을 제공하고 화면에 물체를 출력하기 위한 전단계를 관리하는 기능을 제공
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRenderingPipeLine
{
private:	// member Var
	std::vector<float4> CopyVertex_; // 정점버퍼(Vertex Buffer)로부터 복제한 정점정보집합체

public:
	GameEngineRenderingPipeLine(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLine(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	// 렌더링파이프라인에서의 입력조립기단계(원본 정점버퍼를 복제하는 기능수행)
	void SetInputAssembler1(GameEngineVertexBuffer* _Ptr);

	// 렌더링파이프라인에서의 정점셰이더단계(복제한 정점버퍼를 이용하여 이동/회전/크기변환 등 기능 수행)
	//void SetVertexShader(GameEngineVertexShader* _Ptr);

	// 렌더링파이프라인에서의 출력병합기단계(후면버퍼(Back Buffer)에 기록하며 혼합(블랜딩) 등 화면출력을 위한 마지막단계 기능 수행)
	void OutPutMerge();
};

