#include "PreCompile.h"
#include "GameEngineString.h"

void GameEngineString::toupper(std::string& Text)
{
	// 문자열 전체 대문자로 변환
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);
}

void GameEngineString::tolower(std::string& Text)
{
	// 문자열 전체 소문자로 변환
	std::transform(Text.begin(), Text.end(), Text.begin(), ::tolower);
}

GameEngineString::GameEngineString() // default constructer 디폴트 생성자
{

}

GameEngineString::~GameEngineString() // default destructer 디폴트 소멸자
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}
