#pragma once

// 분류 :
// 용도 :
// 설명 :
class GameEngineSoundFile;
class GameEngineSoundPlayer;
class GameEngineSound
{
private:
	static GameEngineSound* Inst;

public:
	static GameEngineSound& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	friend GameEngineSoundFile;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::System* soundSystem_; // Fmod가 제공해주는 인터페이스
	// 사운드파일하나하나가 아니라
	// fmod를 사용할수 있는지 확인해주고 사운드를 로드할수 있게 해주는 기본 인터페이스입니다.
	// 이녀석이 먼저 제대로 만들어질수 있는 환경이어야 사운드를 사용할수 있습니다.
	std::map<std::string, GameEngineSoundFile*> allLoadSound_;

	std::list<GameEngineSoundPlayer*> allSoundPlayer_;

private:
	GameEngineSoundFile* FindSound(const std::string& _name);

public:
	void Initialize();
	void LoadSound(const std::string& _name, const std::string& _path);
	void PlaySoundOneShot(const std::string& _name);
	GameEngineSoundPlayer* CreateSoundPlayer();

public:
	void SoundUpdate();

private:		
	GameEngineSound(); // default constructer 디폴트 생성자
	~GameEngineSound(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineSound(const GameEngineSound& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSound(GameEngineSound&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineSound& operator=(const GameEngineSound& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSound& operator=(const GameEngineSound&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

