#pragma once
#include "GameEngineSound.h"
#include "GameEngineObjectNameBase.h"

// �з� : FMOD Sound ��ü����
// �뵵 : 
// ���� : FMOD Sound ��ü ���� �� Sound File Load �������(��, Sound ��ü�� Sound File�� 1:1�� �����ȴ�.)
class GameEngineSoundPlayer;
class GameEngineSoundFile : public GameEngineObjectNameBase
{
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::Sound* sound_; // Sound ��ü

private:		
	GameEngineSoundFile(); // default constructer ����Ʈ ������
	~GameEngineSoundFile(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSoundFile(const GameEngineSoundFile& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSoundFile(GameEngineSoundFile&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSoundFile& operator=(const GameEngineSoundFile& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSoundFile& operator=(const GameEngineSoundFile&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	bool Load(const std::string& _Path);
};

