#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// �з� : 
// �뵵 : 
// ���� : ��������(Vertex Buffer)�� �ε�������(Index Buffer)�� ���� ȭ�鿡 �������Ϸ��� ��ü��
//			   ���(����)���� �����ϴ� ���� �޽�(Mesh)����Ѵ�.
//			   �ش� Ŭ������ �� �޽��� �����ϴ� Ŭ�����̴�.
class GameEngineMesh : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineIndexBuffer* IndexBuffer_;

public:
	GameEngineMesh(); // default constructer ����Ʈ ������
	~GameEngineMesh(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineMesh(const GameEngineMesh& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineMesh(GameEngineMesh&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineMesh& operator=(const GameEngineMesh& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineMesh& operator=(const GameEngineMesh&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

