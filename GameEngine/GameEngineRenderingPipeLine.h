#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 렌더링 파이프라인 
// 용도 : 
// 설명 : 렌더링 파이프라인 순서별 기능을 제공하고 화면에 물체를 출력하기 위한 전단계를 관리하는 기능을 제공
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineVertexBuffer*			VertexBuffer_;		// 원본 Vertex Buffer
	GameEngineVertexShader*		VertexShader_;	// Vertex Shader
	GameEngineIndexBuffer*			IndexBuffer_;		// Index Buffer
	GameEngineRasterizer*				Rasterizer_;			// 래스터라이저

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
	void SetMesh();
	void SetMaterial();

public:	// 렌더링파이프라인 가동준비
	void SetInputAssembler1(const std::string& _Name);
	void SetVertexShader(const std::string& _Name);
	void SetInputAssembler2(const std::string& _Name);
	void SetRasterizer(const std::string& _Name);

public:	// 실질적 렌더링파이프라인 가동
	void Rendering();
};

