#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineVertexShaderManager
{
private:	// member Var

public:
	GameEngineVertexShaderManager(); // default constructer 디폴트 생성자
	~GameEngineVertexShaderManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShaderManager(const GameEngineVertexShaderManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

