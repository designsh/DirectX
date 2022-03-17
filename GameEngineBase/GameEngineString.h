#pragma once

// 분류 : 헬퍼
// 용도 : 문자열관련 헬퍼
// 설명 : 문자열 대/소문자 변환 및 문자열 제어에 필요한 기능 제공
class GameEngineString
{
public:
	static std::string toupper(const std::string& _Text);
	static std::string tolower(const std::string& _Text);

public:
	static void StringToWString(const std::string& _Text, std::wstring& _Out); // String -> WString Convert
	static void WStringToString(const std::wstring& _Text, std::string& _Out); // WString -> String Convert

private:
	GameEngineString(); // default constructer 디폴트 생성자
	virtual ~GameEngineString(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineString(const GameEngineString& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineString(GameEngineString&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineString& operator=(const GameEngineString& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineString& operator=(const GameEngineString&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
};

