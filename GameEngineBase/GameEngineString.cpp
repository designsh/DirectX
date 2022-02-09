#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

void GameEngineString::toupper(std::string& Text)
{
	// ���ڿ� ��ü �빮�ڷ� ��ȯ
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);
}

void GameEngineString::tolower(std::string& Text)
{
	// ���ڿ� ��ü �ҹ��ڷ� ��ȯ
	std::transform(Text.begin(), Text.end(), Text.begin(), ::tolower);
}

void GameEngineString::StringToWString(const std::string& _Text, std::wstring& _Out)
{
	// _Text�� wstring���� ��ȯ�������� ũ�⸦ ���´�.
	// Return Value : ��ȯ�� ���ڿ��� ���̸� ��ȯ(0�̸� ����)
	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);
	if (ConvertLength == 0)
	{
		GameEngineDebug::MsgBoxError("String To WString Convert Error");
		return;
	}

	// ������ ������ ũ��� _Out�� ũ�⸦ ���������Ѵ�.
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
	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr );
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

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{
}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{
}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{
}
