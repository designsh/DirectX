#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 정점(Vertex) 셰이더
// 용도 : 
// 설명 : 정점(Vertex)를 전달받아 이동/회전/크기변환 등 기능을 제공
//            단, 원본 정점버퍼가 아닌 입력조립기단계(Input Assembler1)에서 복사한 복제본 정점버퍼를
//            이동/회전/크기변환 등 기능을 수행하도록 설정한다. 즉, 원본에는 아무런 영향을 끼치지않는다.
class GameEngineVertexShader
{
private:	// member Var

public:
	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

