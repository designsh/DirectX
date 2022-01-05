#pragma once
#include "GameEngineSoundFile.h"
#include "GameEngineSound.h"

// 분류 :
// 용도 :
// 설명 :
class GameEngineSoundPlayer
{
	friend GameEngineSound;

private:	// member Var
	GameEngineSound* playSoundFile_;
	FMOD::Channel* playChannel_; // 
	int PlayCount;

private:		
	GameEngineSoundPlayer(); // default constructer 디폴트 생성자
	~GameEngineSoundPlayer(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	bool IsPlay();

	void PlayCountReset(int _Count = -1);

	// 겹쳐서 재생 기존의 사운드가 재생되고 있어도 그냥 재생한다. OneShot.
	void PlayOverLap(const std::string& _name, int _LoopCount = 1);

	// 기존의 사운드가 재생이 끝나야만 다음 사운드를 재생한다.
	void PlayAlone(const std::string& _name, int _LoopCount = 1);

	void Stop();
};

