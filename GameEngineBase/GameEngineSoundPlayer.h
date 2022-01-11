#pragma once
#include "GameEngineSound.h"
#include "GameEngineSoundManager.h"

// 분류 : FMOD Sound System 조작
// 용도 :
// 설명 : Sound Channel에 담긴 Sound를 Control하는 기능을 제공
class GameEngineSoundPlayer
{
	friend GameEngineSoundManager;

private:	// member Var
	FMOD::Channel* playChannel_; // 
	int PlayCount;	// 해당 Channel에 담긴 Sound 반복재생횟수

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
	bool IsPlay(); // 현재 Channel에 담긴 Sound를 재생
	void PlayCountReset(int _Count = -1); // 현재 Channel에 담긴 Sound의 반복재생횟수를 Setting
	void PlayOverLap(const std::string& _name, int _LoopCount = 1);	// 겹쳐서 재생 기존의 사운드가 재생되고 있어도 그냥 재생한다. OneShot.
	void PlayAlone(const std::string& _name, int _LoopCount = 1);	// 기존의 사운드가 재생이 끝나야만 다음 사운드를 재생한다.
	void Stop();	// 현재 채널에서 재생중인 Sound를 정지
};

