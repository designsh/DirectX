#pragma once
#include <GameEngineBase/GameEngineMath.h>

// �з� : ������ ���������� 
// �뵵 : 
// ���� : ������ ���������� ������ ����� �����ϰ� ȭ�鿡 ��ü�� ����ϱ� ���� ���ܰ踦 �����ϴ� ����� ����
class GameEngineIndexBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineVertexBuffer*			VertexBuffer_;		// ���� Vertex Buffer
	GameEngineVertexShader*		VertexShader_;	// Vertex Shader
	GameEngineIndexBuffer*			IndexBuffer_;		// Index Buffer
	GameEngineRasterizer*				Rasterizer_;			// �����Ͷ�����

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

public:	// ���������������� �����غ�
	void SetInputAssembler1(const std::string& _Name);
	void SetVertexShader(const std::string& _Name);
	void SetInputAssembler2(const std::string& _Name);
	void SetRasterizer(const std::string& _Name);

public:	// ������ ���������������� ����
	void Rendering();
};

