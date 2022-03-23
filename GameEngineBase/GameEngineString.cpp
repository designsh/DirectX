#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

std::string GameEngineString::toupper(const std::string& _Text)
{
	std::string Text = _Text;

	// 문자열 전체 대문자로 변환
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);

	return Text;
}

std::string GameEngineString::tolower(const std::string& _Text)
{
	std::string Text = _Text;

	// 문자열 전체 소문자로 변환
	std::transform(Text.begin(), Text.end(), Text.begin(), ::tolower);

	return Text;
}

void GameEngineString::StringToWString(const std::string& _Text, std::wstring& _Out)
{
	// _Text를 wstring으로 변환했을때의 크기를 얻어온다.
	// Return Value : 변환한 문자열의 길이를 반환(0이면 실패)
	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);
	if (ConvertLength == 0)
	{
		GameEngineDebug::MsgBoxError("String To WString Convert Error");
		return;
	}

	// 위에서 추출한 크기로 _Out의 크기를 리사이즈한다.
	_Out.resize(ConvertLength);

	int CurOutStringLen = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], ConvertLength);
	if (CurOutStringLen == 0)
	{
		GameEngineDebug::MsgBoxError("String To WString Convert Error");
		return;
	}
}

void GameEngineString::WStringToString(const std::wstring& _Text, std::string& _Out)
{
	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);
	if (ConvertLength == 0)
	{
		GameEngineDebug::MsgBoxError("WString To String Convert Error");
		return;
	}

	_Out.resize(ConvertLength);

	int CurOutStringLen = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], ConvertLength, nullptr, nullptr);
	if (CurOutStringLen == 0)
	{
		GameEngineDebug::MsgBoxError("WString To String Convert Error");
		return;
	}
}

std::wstring GameEngineString::StringToWStringReturn(const std::string& _Text)
{
	// 인자 수신받은 문자열이 비어있다면
	if (true == _Text.empty())
	{
		return L"";
	}

	std::wstring Return;

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (ConvertLength == 0)
	{
		GameEngineDebug::MsgBoxError("String To WString Convert Error");
		return L"";
	}

	Return.resize(ConvertLength);

	int CurOutStringLen = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], ConvertLength);
	if (CurOutStringLen == 0)
	{
		GameEngineDebug::MsgBoxError("String To WString Convert Error");
		return L"";
	}

	return Return;
}

std::string GameEngineString::WStringToStringReturn(const std::wstring& _Text)
{	
	// 인자 수신받은 문자열이 비어있다면
	if (true == _Text.empty())
	{
		return "";
	}

	std::string Return;

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);
	if (ConvertLength == 0)
	{
		GameEngineDebug::MsgBoxError("WString To String Convert Error");
		return "";
	}

	Return.resize(ConvertLength);

	int CurOutStringLen = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], ConvertLength, nullptr, nullptr);
	if (CurOutStringLen == 0)
	{
		GameEngineDebug::MsgBoxError("WString To String Convert Error");
		return "";
	}

	return Return;
}

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept
{
}
