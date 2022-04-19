#pragma once
#include "GameEngineObjectBase.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineObjectNameBase : public GameEngineObjectBase
{
private:	// member Var
	std::string name_;

public:
	std::string GetName()
	{
		return name_;
	}

	void SetName(const std::string& _name)
	{
		name_ = _name;
	}

public:
	GameEngineObjectNameBase(); // default constructer ����Ʈ ������
	~GameEngineObjectNameBase(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineObjectNameBase(const GameEngineObjectNameBase& _other); // default Copy constructer ����Ʈ ���������
	GameEngineObjectNameBase(GameEngineObjectNameBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

