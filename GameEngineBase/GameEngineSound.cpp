#include "PreCompile.h"
#include "GameEngineDebug.h"
#include "GameEnginePath.h"
#include "GameEngineSound.h"
#include "GameEngineSoundFile.h"
#include "GameEngineSoundPlayer.h"

// Static Var
GameEngineSound* GameEngineSound::Inst = new GameEngineSound();	// Singleton Class Pointer

// Static Func

// constructer destructer
GameEngineSound::GameEngineSound() :
	soundSystem_(nullptr)
{
}

GameEngineSound::~GameEngineSound()
{
	// Sound Player ������� �޸� ����
	std::list<GameEngineSoundPlayer*>::iterator SoundPlayerStartIter = allSoundPlayer_.begin();
	std::list<GameEngineSoundPlayer*>::iterator SoundPlayerEndIter = allSoundPlayer_.end();
	for (; SoundPlayerStartIter != SoundPlayerEndIter; ++SoundPlayerStartIter)
	{
		if (nullptr != *SoundPlayerStartIter)
		{
			delete * SoundPlayerStartIter;
		}
	}
	allSoundPlayer_.clear();

	// Sound File ������� �޸� ����
	std::map<std::string, GameEngineSoundFile*>::iterator SoundFileStartIter = allLoadSound_.begin();
	std::map<std::string, GameEngineSoundFile*>::iterator SoundFileEndIter = allLoadSound_.end();
	for (; SoundFileStartIter != SoundFileEndIter; ++SoundFileStartIter)
	{
		if (nullptr != SoundFileStartIter->second)
		{
			delete SoundFileStartIter->second;
			SoundFileStartIter->second = nullptr;
		}
	}
	allLoadSound_.clear();

	// Sound System Pointer Release
	if (nullptr != soundSystem_)
	{
		soundSystem_->release();
		soundSystem_ = nullptr;
	}
}

GameEngineSound::GameEngineSound(GameEngineSound&& _other) noexcept
{
	soundSystem_ = _other.soundSystem_;
}

//member Func
GameEngineSoundFile* GameEngineSound::FindSound(const std::string& _name)
{
	std::map<std::string, GameEngineSoundFile*>::iterator FindIter = allLoadSound_.find(_name);
	if (FindIter == allLoadSound_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::Initialize()
{
	// �����ڵ忡�� NEW�� �� ���ɼ��� �ſ� �ٺ���.
	FMOD::System_Create(&soundSystem_);
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("sound system create Error");
		return;
	}

	// ���ÿ� 32�� �������� ���� ä���� �ǹ������� �� �𸣰� �ֽ��ϴ�.
	// 32ä���� ����Ҽ� �ִٴ� �ǹ��ε� �����Ե� �� �𸨴ϴ�.
	// FMOD_DEFAULT : �ѹ��� ����
	if (FMOD_OK != soundSystem_->init(32, FMOD_DEFAULT, nullptr))
	{
		GameEngineDebug::MsgBoxError("sound system init Error");
		return;
	}
}

void GameEngineSound::LoadSound(const std::string& _path)
{
	LoadSound(GameEnginePath::GetFileName(_path), _path);
}

void GameEngineSound::LoadSound(const std::string& _name, const std::string& _path)
{
	if (nullptr != FindSound(_name))
	{
		GameEngineDebug::MsgBoxError("Sound Load overlap error");
		return;
	}

	GameEngineSoundFile* newLoadSound = new GameEngineSoundFile();
	if (false == newLoadSound->Load(_path))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		delete newLoadSound;
		return;
	}

	allLoadSound_.insert(std::map<std::string, GameEngineSoundFile*>::value_type(_name, newLoadSound));
}

void GameEngineSound::PlaySoundOneShot(const std::string& _name)
{
	GameEngineSoundFile* SoundPtr = FindSound(_name);
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	soundSystem_->playSound(SoundPtr->sound_, nullptr, false, nullptr);
}

GameEngineSoundPlayer* GameEngineSound::CreateSoundPlayer()
{
	GameEngineSoundPlayer* NewSoundplayer = new GameEngineSoundPlayer();

	allSoundPlayer_.push_back(NewSoundplayer);

	return  NewSoundplayer;
}

void GameEngineSound::SoundUpdate()
{
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("SoundSystem Is null");
		return;
	}

	soundSystem_->update();
}
