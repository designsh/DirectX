#pragma once
#include "GameEngineSound.h"
#include "GameEngineObjectNameBase.h"

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundPlayer;
class GameEngineSoundFile : public GameEngineObjectNameBase
{
	friend GameEngineSound;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::Sound* sound_;

public:
	bool Load(const std::string& _Path);


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
};

