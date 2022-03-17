#pragma once

// �з� : ����
// �뵵 : ���ڿ����� ����
// ���� : ���ڿ� ��/�ҹ��� ��ȯ �� ���ڿ� ��� �ʿ��� ��� ����
class GameEngineString
{
public:
	static std::string toupper(const std::string& _Text);
	static std::string tolower(const std::string& _Text);

public:
	static void StringToWString(const std::string& _Text, std::wstring& _Out); // String -> WString Convert
	static void WStringToString(const std::wstring& _Text, std::string& _Out); // WString -> String Convert

private:
	GameEngineString(); // default constructer ����Ʈ ������
	virtual ~GameEngineString(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineString(const GameEngineString& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineString(GameEngineString&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineString& operator=(const GameEngineString& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineString& operator=(const GameEngineString&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
};

