#pragma once

// �з� : �ε���(Index) ����
// �뵵 : 
// ���� : �ε������۸� �����ϰ� �����ϴ� Ŭ����
class GameEngineIndexBuffer
{
private:	// member Var
	std::vector<int> Indexs_;

public:
	GameEngineIndexBuffer(); // default constructer ����Ʈ ������
	~GameEngineIndexBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

