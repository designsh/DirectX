#pragma once
#include <GameEngineBase/GameEngineMath.h>

// �з� : ������ ���������� 
// �뵵 : 
// ���� : ������ ���������� ������ ����� �����ϰ� ȭ�鿡 ��ü�� ����ϱ� ���� ���ܰ踦 �����ϴ� ����� ����
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRenderingPipeLine
{
private:	// member Var
	std::vector<float4>							CopyVertex_;		// ������ Vertex Buffer
	GameEngineVertexBuffer*			VertexBuffer_;		// ���� Vertex Buffer
	GameEngineVertexShader*		VertexShader_;	// Vertex Shader

public:
	GameEngineRenderingPipeLine(); // default constructer ����Ʈ ������
	~GameEngineRenderingPipeLine(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:	// ���������������� �����غ�
	void SetInputAssembler1(GameEngineVertexBuffer* _Ptr);
	void SetVertexShader(GameEngineVertexShader* _Ptr);

public:	// ������ ���������������� ����
	void Rendering();
};

