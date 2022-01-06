#pragma once

// �з� : ���� ������
// �뵵 : 
// ���� : FMOD ����� üũ�ϸ� ���� �ε� �� �⺻ �������̽� ����
class GameEngineSoundFile;
class GameEngineSoundPlayer;
class GameEngineSound
{
public:
	friend GameEngineSoundFile;
	friend GameEngineSoundPlayer;

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

private:	// member Var
	FMOD::System* soundSystem_; // Fmod�� �������ִ� �������̽�(�ý��� ��ü)
	std::map<std::string, GameEngineSoundFile*> allLoadSound_;	// Sound File �������
	std::list<GameEngineSoundPlayer*> allSoundPlayer_;	// Sound Player List

private:		
	GameEngineSound(); // default constructer ����Ʈ ������
	~GameEngineSound(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSound(const GameEngineSound& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSound(GameEngineSound&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSound& operator=(const GameEngineSound& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSound& operator=(const GameEngineSound&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	GameEngineSoundFile* FindSound(const std::string& _name);

public:
	void Initialize();
	void LoadSound(const std::string& _path);
	void LoadSound(const std::string& _name, const std::string& _path);
	void PlaySoundOneShot(const std::string& _name);
	GameEngineSoundPlayer* CreateSoundPlayer();

public:
	void SoundUpdate();
};

