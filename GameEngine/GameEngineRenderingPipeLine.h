#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineDevice.h>
#include "GameEngineShaderResHelper.h"

// �з� : ������ ���������� 
// �뵵 : 
// ���� : ������ ���������� ������ ����� �����ϰ� ȭ�鿡 ��ü�� ����ϱ� ���� ���ܰ踦 �����ϴ� ����� ����
class GameEngineShader;
class GameEngineDepthStencil;
class GameEngineConstantBuffer;
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineBlend;
class GameEngineRenderTarget;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
	// ======================================= InputAssembler 1 ======================================= //
private:
	GameEngineVertexBuffer* VertexBuffer_;												// Vertex Buffer(IA1)
	GameEngineVertexShader* InputLayOutVertexShader_;					// Vertex Shader InputLayout

// ======================================== Vertex Shader ========================================= //
private:
	GameEngineVertexShader* VertexShader_;											// Vertex Shader(VS)

// ======================================= InputAssembler 2 ======================================= //
private:
	GameEngineIndexBuffer* IndexBuffer_;												// Index Buffer(IA2)
	D3D11_PRIMITIVE_TOPOLOGY	Topology_;													// Topology(����� ��� : ��, ��, �ﰢ��, �ٰ���)

// ========================================== Rasterizer ========================================== //
private:
	GameEngineRasterizer* Rasterizer_;													// Rasterizer(RS)

// ========================================= Pixel Shader ========================================= //
private:
	GameEnginePixelShader* PixelShader_;												// Pixel Shader(PS)

// ======================================== Ouput Merger ======================================== //
private:
	GameEngineBlend* Blend_;															// Blend(OM)
	GameEngineRenderTarget* RenderTarget_;											// Render Target(OM)
	GameEngineDepthStencil* DepthStencil_;												// DepthStencil(OM)

public:
	GameEngineRenderingPipeLine(); // default constructer ����Ʈ ������
	~GameEngineRenderingPipeLine(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	inline GameEnginePixelShader* GetPixelShader() const
	{
		return PixelShader_;
	}

	inline GameEngineVertexShader* GetVertexShader() const
	{
		return VertexShader_;
	}

	// ======================================== Rendering PipeLine �غ�ܰ� ======================================== //
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

public: // Pixel Shader Setting
	void SetPixelShader(const std::string& _Name);

public: // Output Merger Setting
	void SetOutputMergerBlend(const std::string& _Name);
	void SetOutputMergerDepthStencil(const std::string& _Name);

	// ======================================= Rendering PipeLine ���� �غ�ܰ� ======================================= //
public: // RenderingPipeLine Setting
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	void Rasteriazer();
	void PixelShader();
	void OutputMerger();

public: // RenderingPipeLine Setting
	void RenderingPipeLineSetting();

	// ========================================= Rendering PipeLine �����ܰ� ========================================= //
public:
	void Rendering();

	// ======================================== Rendering PipeLine �ʱ�ȭ�ܰ� ======================================== //
public:
	void Reset();
};

