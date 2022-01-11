#pragma once

// �з� : ���� ������
// �뵵 : 
// ���� : FMOD ����� üũ�ϸ� ���� �ε� �� �⺻ �������̽� ����
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
	FMOD::System* soundSystem_; // Fmod�� �������ִ� �������̽�(�ý��� ��ü)
	std::map<std::string, GameEngineSound*> allLoadSound_;	// Sound File �������
	std::list<GameEngineSoundPlayer*> allSoundPlayer_;	// Sound Player List

private:		
	GameEngineSoundManager(); // default constructer ����Ʈ ������
	~GameEngineSoundManager(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSoundManager(GameEngineSoundManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

