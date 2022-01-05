#pragma once
#include "GameEngineSound.h"
#include "GameEngineObjectNameBase.h"

// 분류 : FMOD Sound 객체관리
// 용도 : 
// 설명 : FMOD Sound 객체 생성 및 Sound File Load 기능제공(단, Sound 객체와 Sound File은 1:1로 대응된다.)
class GameEngineSoundPlayer;
class GameEngineSoundFile : public GameEngineObjectNameBase
{
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::Sound* sound_; // Sound 객체

private:		
	GameEngineSoundFile(); // default constructer 디폴트 생성자
	~GameEngineSoundFile(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineSoundFile(const GameEngineSoundFile& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSoundFile(GameEngineSoundFile&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineSoundFile& operator=(const GameEngineSoundFile& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSoundFile& operator=(const GameEngineSoundFile&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	bool Load(const std::string& _Path);
};

