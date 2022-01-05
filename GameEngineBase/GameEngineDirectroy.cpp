#include "PreCompile.h"
#include "GameEngineDirectroy.h"
#include "GameEngineFile.h"

// Static Var

// Static Func

// constructer destructer
GameEngineDirectroy::GameEngineDirectroy()
{
	// std::string
	// 내부에 char* = new char[256]
	path_.resize(256);

	for (size_t i = 0; i < path_.size(); i++)
	{
		path_[i] = '\0';
	}

	// Standard Function 으로 변경예정
	GetCurrentDirectoryA(static_cast<DWORD>(path_.size()), &path_[0]);
	size_t ZeroCount = path_.find('\0');
	path_ = path_.substr(0, ZeroCount);
	path_ += "\\";
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
	// reverseFind
	size_t Count = path_.rfind("\\");
	if (std::string::npos == Count)
	{
		return path_;
	}

	//       5     10                
	// "aaaaa//bbbbb//ccccc"
	size_t StartCount = path_.rfind("\\", Count - 1);

	std::string Name = path_.substr(StartCount, Count);
	Name = Name.substr(1, Name.size() - 2);
	return Name;

}

bool GameEngineDirectroy::IsRoot()
{
	int Count = 0;

	for (size_t i = 0; i < path_.size(); i++)
	{
		if (path_[i] == '\\')
		{
			++Count;
		}
	}

	if (1 >= Count)
	{
		return true;
	}

	return false;
}

void GameEngineDirectroy::MoveParent() 
{
	size_t Count = path_.rfind("\\");
	if (std::string::npos == Count)
	{
		return;
	}

	// "aaaaa//bbbbb//ccccc//"
	// aaaaa//bbbbb//
	size_t StartCount = path_.rfind("\\", Count - 1);
	path_ = path_.substr(0, StartCount + 1);

}

bool GameEngineDirectroy::MoveParent(const std::string& _DirName)
{
	// 
	GameEngineDirectroy CheckDir = GameEngineDirectroy(*this);

	while (true)
	{
		if (_DirName == CheckDir.DirectroyName())
		{
			break;
		}

		CheckDir.MoveParent();

		if (true == CheckDir.IsRoot())
		{
			return false;
		}
	}

	this->path_ = CheckDir.path_;

	return true;
}


bool GameEngineDirectroy::MoveChild(const std::string& _DirName)
{
	if (0 == _DirName.size())
	{
		return false;
	}

	std::string CheckPath = _DirName;

	if (CheckPath[0] == '\\')
	{
		CheckPath = CheckPath.substr(1, _DirName.size());
	}

	if (CheckPath[CheckPath.size() - 1] == '\\')
	{
		CheckPath = CheckPath.substr(0, _DirName.size() - 1);
	}

	GameEngineDirectroy NewDir;
	NewDir.path_ = this->path_ + _DirName + "\\";

	if (false == NewDir.IsExist())
	{
		return false;
	}

	this->path_ += CheckPath + "\\";
	return true;
}

std::string GameEngineDirectroy::PathToPlusFileName(const std::string& _FileName)
{
	return path_ + _FileName;
}

GameEngineFile GameEngineDirectroy::PathToCreateFile(const std::string& _FileName) 
{
	GameEngineFile NewFile = GameEngineFile(PathToPlusFileName(_FileName), "wb");
	NewFile.Close();

	return NewFile;
}

GameEngineFile GameEngineDirectroy::PathToGetFile(const std::string& _FileName)
{
	return GameEngineFile(PathToPlusFileName(_FileName));
}