#include "PreCompile.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineSoundFile.h"
#include "GameEngineDebug.h"

// Static Var

// Static Func

// constructer destructer
GameEngineSoundPlayer::GameEngineSoundPlayer() :
	playChannel_(nullptr),
	PlayCount(-1)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept : 
	playChannel_(_other.playChannel_),
	PlayCount(_other.PlayCount)
{
}

//member Func
bool GameEngineSoundPlayer::IsPlay() 
{
	bool Check = false;
	playChannel_->isPlaying(&Check);

	return Check;
}

void GameEngineSoundPlayer::PlayCountReset(int _Count) 
{
	PlayCount = _Count;
}

void GameEngineSoundPlayer::PlayOverLap(const std::string& _name, int _LoopCount)
{
	GameEngineSoundFile* SoundPtr = GameEngineSound::GetInst().FindSound(_name);
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSound::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
	
}

void GameEngineSoundPlayer::PlayAlone(const std::string& _name, int _LoopCount /*= 1*/) 
{
	GameEngineSoundFile* SoundPtr = GameEngineSound::GetInst().FindSound(_name);
	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (true == IsPlay())
	{
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSound::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
}

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	playChannel_->stop();
	playChannel_ = nullptr;
}