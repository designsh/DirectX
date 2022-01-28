#pragma once

// 분류 : 디버거
// 용도 : 메모리관리 메세지 출력 로그
// 설명 : 모든 디버깅 관련 기능은 여기에 모아놓는다.
class GameEngineDebug
{ 
private:	// member Var

public:
	static void LeakCheckOn();
	static void MsgBoxError(const std::string& _Ptr);
	static void MsgBox(const std::string& _Ptr);
	static void AssertFalse();
	static void OutPutDebugString(const std::string& _Text);

protected:	
	GameEngineDebug(); // default constructer 디폴트 생성자
	~GameEngineDebug(); // default destructer 디폴트 소멸자

protected:	// delete constructer
	GameEngineDebug(const GameEngineDebug& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineDebug(GameEngineDebug&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:	//delete operator
	GameEngineDebug& operator=(const GameEngineDebug& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDebug& operator=(const GameEngineDebug&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:	//member Func
};

