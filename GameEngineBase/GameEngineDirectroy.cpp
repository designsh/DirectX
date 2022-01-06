#include "PreCompile.h"
#include "GameEngineDirectroy.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

// Static Var

// Static Func

// constructer destructer
GameEngineDirectroy::GameEngineDirectroy()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectroy::GameEngineDirectroy(const GameEngineDirectroy& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectroy::~GameEngineDirectroy()
{
}

GameEngineDirectroy::GameEngineDirectroy(GameEngineDirectroy&& _other) noexcept
{
}

//member Func
std::string GameEngineDirectroy::DirectroyName() 
{
	return path_.filename().string();
}

bool GameEngineDirectroy::IsRoot()
{
	return path_.root_directory() == path_;
}

void GameEngineDirectroy::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectroy::MoveParent(const std::string& _DirName)
{
	while (false == IsRoot())
	{
		if (path_.filename().string() == _DirName)
		{
			return true;
		}

		MoveParent();
	}

	return false;
}

bool GameEngineDirectroy::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);
	if (false == IsExist())
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ��η� �̵��߽��ϴ�.");
		return false;
	}

	return true;
}

std::string GameEngineDirectroy::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);

	return NewPath.string();
}

std::vector<GameEngineFile> GameEngineDirectroy::GetAllFile(const std::string& _filter, bool _AllDirectory)
{
	// ���ڷ� ������ Ȯ���ڸ��� �˻� �� '.' + 'Ȯ���ڸ�'���� ��ȯ
	// Ex) _filter = mp3 -> _filter = .mp3 �� ����
	std::string Filter = "";
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}
	Filter += _filter;

	// ��� Ȯ���ڴ� �빮�ڷ� �����Ͽ� �Ʒ����� �񱳰˻�
	GameEngineString::toupper(Filter);

	// ���� ����� ���� ���͸��� ��� ���� Ȯ���� �� �� ������Ͽ� �߰�
	std::vector<GameEngineFile> vecReturnFile;

	// ���� ���͸��� ��� �˻����� ������ �����Ͽ� ��������� ����
	if (true == _AllDirectory)
	{
		// ���� ����� ���� ���͸��� ���� ���͸��� �����Ѵٸ� ���� ���͸��� ��� �˻�
		std::filesystem::recursive_directory_iterator AllDirIter = std::filesystem::recursive_directory_iterator(path_);
		for (const std::filesystem::directory_entry& File : AllDirIter)
		{
			std::string Ext = File.path().extension().string();
			GameEngineString::toupper(Ext);
			if (_filter != "*" && Filter != Ext)
			{
				continue;
			}

			vecReturnFile.push_back(GameEngineFile(File.path()));
		}
	}
	else
	{
		// ���� ����� �������͸����� ������ϸ� ��������, ���� ���͸��� ����
		std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);
		for (const std::filesystem::directory_entry& File : DirIter)
		{
			std::string Ext = File.path().extension().string();
			GameEngineString::toupper(Ext);
			if (_filter != "*" && Filter != Ext)
			{
				continue;
			}

			vecReturnFile.push_back(GameEngineFile(File.path()));
		}
	}
	
	return vecReturnFile;
}
