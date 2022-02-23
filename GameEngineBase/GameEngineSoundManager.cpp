#include "PreCompile.h"
#include "GameEngineDebug.h"
#include "GameEnginePath.h"
#include "GameEngineSoundManager.h"
#include "GameEngineSound.h"
#include "GameEngineSoundPlayer.h"

// Static Var
GameEngineSoundManager* GameEngineSoundManager::Inst = new GameEngineSoundManager();	// Singleton Class Pointer

// Static Func

// constructer destructer
GameEngineSoundManager::GameEngineSoundManager() :
	soundSystem_(nullptr)
{
}

GameEngineSoundManager::~GameEngineSoundManager()
{
	// Sound Player 관리목록 메모리 제거
	std::list<GameEngineSoundPlayer*>::iterator SoundPlayerStartIter = allSoundPlayer_.begin();
	std::list<GameEngineSoundPlayer*>::iterator SoundPlayerEndIter = allSoundPlayer_.end();
	for (; SoundPlayerStartIter != SoundPlayerEndIter; ++SoundPlayerStartIter)
	{
		if (nullptr != *SoundPlayerStartIter)
		{
			delete *SoundPlayerStartIter;
		}
	}
	allSoundPlayer_.clear();

	// Sound File 관리목록 메모리 제거
	std::map<std::string, GameEngineSound*>::iterator SoundFileStartIter = allLoadSound_.begin();
	std::map<std::string, GameEngineSound*>::iterator SoundFileEndIter = allLoadSound_.end();
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

GameEngineSoundManager::GameEngineSoundManager(GameEngineSoundManager&& _other) noexcept
{
	soundSystem_ = _other.soundSystem_;
}

//member Func
GameEngineSound* GameEngineSoundManager::FindSound(const std::string& _name)
{
	std::map<std::string, GameEngineSound*>::iterator FindIter = allLoadSound_.find(_name);
	if (FindIter == allLoadSound_.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSoundManager::Initialize()
{
	// 내부코드에서 NEW를 할 가능성이 매우 다분해.
	FMOD::System_Create(&soundSystem_);
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("sound system create Error");
		return;
	}

	// 동시에 32개 개수인지 사운드 채널의 의미인지를 잘 모르고 있습니다.
	// 32채널을 재생할수 있다는 의미인데 선생님도 잘 모릅니다.
	// FMOD_DEFAULT : 한번만 실행
	if (FMOD_OK != soundSystem_->init(32, FMOD_DEFAULT, nullptr))
	{
		GameEngineDebug::MsgBoxError("sound system init Error");
		return;
	}
}

void GameEngineSoundManager::Load(const std::string& _path)
{
	Load(GameEnginePath::GetFileName(_path), _path);
}

void GameEngineSoundManager::Load(const std::string& _name, const std::string& _path)
{
	if (nullptr != FindSound(_name))
	{
		GameEngineDebug::MsgBoxError("Sound Load overlap error");
		return;
	}

	GameEngineSound* newLoadSound = new GameEngineSound();
	if (false == newLoadSound->Load(_path))
	{
		GameEngineDebug::MsgBoxError("Sound Load Error");
		delete newLoadSound;
		return;
	}

	allLoadSound_.insert(std::map<std::string, GameEngineSound*>::value_type(_name, newLoadSound));
}

void GameEngineSoundManager::PlaySoundOneShot(const std::string& _name)
{
	GameEngineSound* SoundPtr = FindSound(_name);
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	soundSystem_->playSound(SoundPtr->sound_, nullptr, false, nullptr);
}

GameEngineSoundPlayer* GameEngineSoundManager::CreateSoundPlayer()
{
	GameEngineSoundPlayer* NewSoundplayer = new GameEngineSoundPlayer();

	allSoundPlayer_.push_back(NewSoundplayer);

	return  NewSoundplayer;
}

void GameEngineSoundManager::SoundUpdate()
{
	if (nullptr == soundSystem_)
	{
		GameEngineDebug::MsgBoxError("SoundSystem Is null");
		return;
	}

	soundSystem_->update();
}
