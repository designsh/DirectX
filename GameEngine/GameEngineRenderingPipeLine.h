#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : ������ ���������� 
// �뵵 : 
// ���� : ������ ���������� ������ ����� �����ϰ� ȭ�鿡 ��ü�� ����ϱ� ���� ���ܰ踦 �����ϴ� ����� ����
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
	D3D11_PRIMITIVE_TOPOLOGY	Topology_;													// Topology(����� ��� : ��, ��, �ﰢ��, �ٰ���)

// ========================================== Rasterizer ========================================== //
private:
	GameEngineRasterizer*				Rasterizer_;													// Rasterizer

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
	void SetMesh();
	void SetMaterial();

// ====================================== Rendering PipeLine ���� �غ�ܰ� ====================================== //
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

// ======================================== Rendering PipeLine ���� �ܰ� ======================================== //
public:
	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	void Rasteriazer();

public:
	void Rendering();
};

