#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

// Static Var

// Static Func

// constructer destructer
GameEngineDirectory::GameEngineDirectory()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	path_ = _Path;
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _other) noexcept 
	: GameEnginePath(_other)
{
}

//member Func
std::string GameEngineDirectory::DirectoryName() 
{
	return path_.filename().string();
}

bool GameEngineDirectory::IsRoot()
{
	return path_.root_directory() == path_;
}

void GameEngineDirectory::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectory::MoveParent(const std::string& _DirName)
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

bool GameEngineDirectory::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);
	if (false == IsExist())
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 경로로 이동했습니다.");
		return false;
	}

	return true;
}

std::string GameEngineDirectory::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);

	return NewPath.string();
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _filter, bool _AllDirectory)
{
	// 인자로 수신한 확장자명을 검사 후 '.' + '확장자명'으로 변환
	// Ex) _filter = mp3 -> _filter = .mp3 로 편집
	std::string Filter = "";
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}
	Filter += _filter;

	// 모든 확장자는 대문자로 변경하여 아래에서 비교검사
	GameEngineString::toupper(Filter);

	// 현재 경로의 최종 디렉터리의 모든 파일 확장자 비교 및 관리목록에 추가
	std::vector<GameEngineFile> vecReturnFile;

	// 하위 디렉터리를 모두 검사할지 안할지 결정하여 관리목록을 생성
	if (true == _AllDirectory)
	{
		// 현재 경로의 최종 디렉터리내 하위 디렉터리가 존재한다면 하위 디렉터리를 모두 검사
		std::filesystem::recursive_directory_iterator AllDirIter = std::filesystem::recursive_directory_iterator(path_);
		for (const std::filesystem::directory_entry& File : AllDirIter)
		{
			std::string Ext = File.path().extension().string();
			GameEngineString::toupper(Ext);
			if (_filter != "*" && Filter != Ext)
			{
				continue;
			}

			// 디렉터리 제외
			if (true == File.is_directory())
			{
				continue;
			}

			vecReturnFile.push_back(GameEngineFile(File.path()));
		}
	}
	else
	{
		// 현재 경로의 최종디렉터리내의 모든파일만 가져오며, 하위 디렉터리는 무시
		std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);
		for (const std::filesystem::directory_entry& File : DirIter)
		{
			std::string Ext = File.path().extension().string();
			GameEngineString::toupper(Ext);
			if (_filter != "*" && Filter != Ext)
			{
				continue;
			}

			// 디렉터리 제외
			if (true == File.is_directory())
			{
				continue;
			}

			vecReturnFile.push_back(GameEngineFile(File.path()));
		}
	}
	
	return vecReturnFile;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetAllDirectory(const std::string& _filter)
{
	std::string Filter = _filter;
	GameEngineString::toupper(Filter);

	std::vector<GameEngineDirectory> Return;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	for (const std::filesystem::directory_entry& File : DirIter)
	{
		if (true != File.is_directory())
		{
			continue;
		}

		if (std::string::npos == File.path().string().find(Filter))
		{
			continue;
		}

		Return.push_back(GameEngineDirectory(File.path().string()));
	}

	return Return;
}

std::vector<GameEngineDirectory> GameEngineDirectory::GetAllDirectoryRecursive(const std::string& _filter)
{
	std::string Filter = _filter;
	GameEngineString::toupper(Filter);

	// 현재 시작하는 디렉터리 추가 후 모든디렉터리를 순환해서 디렉터리 탐색
	std::vector<GameEngineDirectory> Return;
	Return.push_back(GameEngineDirectory(GetFullPath()));

	std::filesystem::recursive_directory_iterator DirIter = std::filesystem::recursive_directory_iterator(path_);

	for (const std::filesystem::directory_entry& File : DirIter)
	{
		if (false == File.is_directory())
		{
			continue;
		}

		if (std::string::npos == File.path().string().find(Filter))
		{
			continue;
		}

		Return.push_back(GameEngineDirectory(File.path().string()));
	}

	return Return;
}

bool GameEngineDirectory::CheckSameFileName(const std::string& _Name, const std::string& _Filter)
{
	std::string FileName = _Name;
	FileName += _Filter;

	// 동일한 이름이 있으며 TRUE, 없으면 FALSE
	for (auto& AllFileName : std::filesystem::recursive_directory_iterator(path_))
	{
		if (AllFileName.path().filename() == FileName)
		{
			return true;
		}
	}

	return false;
}
