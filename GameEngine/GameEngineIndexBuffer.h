#pragma once

// 분류 : 인덱스(Index) 버퍼
// 용도 : 
// 설명 : 인덱스버퍼를 관리하고 제공하는 클래스
class GameEngineIndexBuffer
{
private:	// member Var
	std::vector<int> Indexs_;

public:
	GameEngineIndexBuffer(); // default constructer 디폴트 생성자
	~GameEngineIndexBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

