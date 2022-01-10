#pragma once
#include <GameEngineBase/GameEngineMath.h>

// �з� : ����(Vertex) ���̴�
// �뵵 : 
// ���� : ����(Vertex)�� ���޹޾� �̵�/ȸ��/ũ�⺯ȯ �� ����� ����
//            ��, ���� �������۰� �ƴ� �Է�������ܰ�(Input Assembler1)���� ������ ������ �������۸�
//            �̵�/ȸ��/ũ�⺯ȯ �� ����� �����ϵ��� �����Ѵ�. ��, �������� �ƹ��� ������ ��ġ���ʴ´�.
class GameEngineVertexShader
{
private:	// member Var

public:
	GameEngineVertexShader(); // default constructer ����Ʈ ������
	~GameEngineVertexShader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

