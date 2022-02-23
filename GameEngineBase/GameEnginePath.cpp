#include "PreCompile.h"
#include "GameEnginePath.h"

// Static Var

// Static Func

std::string GameEnginePath::GetFileName(std::string _Path)
{
	std::filesystem::path NewPath = _Path;

	return NewPath.filename().string();
}

// constructer destructer
GameEnginePath::GameEnginePath() :
	path_("")
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _path) :
	path_(_path)
{
}

GameEnginePath::~GameEnginePath()
{
}


GameEnginePath::GameEnginePath(const GameEnginePath& _other) :
	path_(_other.path_)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept
{
}

//member Func
bool GameEnginePath::IsExist()
{
	return std::filesystem::exists(path_);
}

std::string GameEnginePath::GetFullPath()
{
	return path_.string();
}

std::string GameEnginePath::GetFileName()
{
	return path_.filename().string();
}

std::string GameEnginePath::GetFileNameWithOutExtension()
{
	// path_.stem() : 확장자를 제외한 파일명을 추출
	return std::string(path_.stem().string());
}

std::string GameEnginePath::GetExtension()
{
	return path_.extension().string();
}
