#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineVertexShaderManager
{
private:	// member Var

public:
	GameEngineVertexShaderManager(); // default constructer ����Ʈ ������
	~GameEngineVertexShaderManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShaderManager(const GameEngineVertexShaderManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

