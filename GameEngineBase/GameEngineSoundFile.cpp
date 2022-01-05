#include "PreCompile.h"
#include "GameEngineSoundFile.h"
#include "GameEngineDebug.h"


// Static Var
// Static Func

// constructer destructer
GameEngineSoundFile::GameEngineSoundFile()
	:sound_(nullptr)
{
}

GameEngineSoundFile::~GameEngineSoundFile()
{
}

GameEngineSoundFile::GameEngineSoundFile(GameEngineSoundFile&& _other) noexcept
	:sound_(_other.sound_)
{
}

//member Func

bool GameEngineSoundFile::Load(const std::string& _Path) 
{
	if (FMOD_RESULT::FMOD_OK != 
		GameEngineSound::GetInst().soundSystem_->createSound(
			_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound_))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		return false;
	}

	if (nullptr == sound_)
	{
		GameEngineDebug::MsgBoxError("Sound Pointer nullptr Error");
		return false;
	}

	return true;
}