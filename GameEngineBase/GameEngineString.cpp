#include "PreCompile.h"
#include "GameEngineString.h"

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

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{

}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}
