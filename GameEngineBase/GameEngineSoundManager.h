#pragma once

// 분류 : 사운드 관리자
// 용도 : 
// 설명 : FMOD 사용을 체크하며 사운드 로드 및 기본 인터페이스 제공
class GameEngineSound;
class GameEngineSoundPlayer;
class GameEngineSoundManager
{
public:
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

private:
	static GameEngineSoundManager* Inst;

public:
	static GameEngineSoundManager& GetInst()
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

private:	// member Var
	FMOD::System* soundSystem_; // Fmod가 제공해주는 인터페이스(시스템 객체)
	std::map<std::string, GameEngineSound*> allLoadSound_;	// Sound File 관리목록
	std::list<GameEngineSoundPlayer*> allSoundPlayer_;	// Sound Player List

private:		
	GameEngineSoundManager(); // default constructer 디폴트 생성자
	~GameEngineSoundManager(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSoundManager(GameEngineSoundManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	GameEngineSound* FindSound(const std::string& _name);

public:
	void Initialize();
	void LoadSound(const std::string& _path);
	void LoadSound(const std::string& _name, const std::string& _path);
	void PlaySoundOneShot(const std::string& _name);
	GameEngineSoundPlayer* CreateSoundPlayer();

public:
	void SoundUpdate();
};

