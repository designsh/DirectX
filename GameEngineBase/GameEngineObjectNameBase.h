#pragma once
#include "GameEngineObjectBase.h"

// 분류 : 
// 용도 : 
// 설명 : 
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
	GameEngineObjectNameBase(); // default constructer 디폴트 생성자
	~GameEngineObjectNameBase(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineObjectNameBase(const GameEngineObjectNameBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineObjectNameBase(GameEngineObjectNameBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineObjectNameBase& operator=(const GameEngineObjectNameBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

