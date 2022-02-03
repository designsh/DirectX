#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 렌더링 파이프라인 
// 용도 : 
// 설명 : 렌더링 파이프라인 순서별 기능을 제공하고 화면에 물체를 출력하기 위한 전단계를 관리하는 기능을 제공
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
// ======================================= InputAssembler 1 ======================================= //
private:
	GameEngineVertexBuffer*			VertexBuffer_;												// Vertex Buffer
	GameEngineVertexShader*		InputLayOutVertexShader_;					// Vertex Shader InputLayout

// ======================================== Vertex Shader ========================================= //
private:
	GameEngineVertexShader*		VertexShader_;											// Vertex Shader

// ======================================= InputAssembler 2 ======================================= //
private:
	GameEngineIndexBuffer*			IndexBuffer_;												// Index Buffer
	D3D11_PRIMITIVE_TOPOLOGY	Topology_;													// Topology(면생성 방법 : 점, 선, 삼각형, 다각형)

// ========================================== Rasterizer ========================================== //
private:
	GameEngineRasterizer*				Rasterizer_;													// Rasterizer

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

// ====================================== Rendering PipeLine 가동 준비단계 ====================================== //
public: // Assembler1 Setting
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);
	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

public: // Vertex Shader Setting
	void SetVertexShader(const std::string& _Name);

public: // Assembler2 Setting
	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);
	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology);

public: // Rasterizer Setting
	void SetRasterizer(const std::string& _Name);

// ======================================== Rendering PipeLine 가동 단계 ======================================== //
public:
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	void Rasteriazer();

public:
	void Rendering();
};

