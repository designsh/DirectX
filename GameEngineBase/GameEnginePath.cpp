#include "PreCompile.h"
#include "GameEnginePath.h"

// Static Var

// Static Func

// constructer destructer
GameEnginePath::GameEnginePath()
	: path_("")
{
}

GameEnginePath::~GameEnginePath()
{
}


GameEnginePath::GameEnginePath(const GameEnginePath& _other) 
	: path_(_other.path_)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _other) noexcept
{
}

//member Func
bool GameEnginePath::IsExist()
{
	if (0 == _access(path_.c_str(), 0))
	{
		return true;
	}

	return false;
}