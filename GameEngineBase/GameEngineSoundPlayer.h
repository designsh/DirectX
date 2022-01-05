#pragma once
#include "GameEngineSoundFile.h"
#include "GameEngineSound.h"

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundPlayer
{
	friend GameEngineSound;

private:	// member Var
	GameEngineSound* playSoundFile_;
	FMOD::Channel* playChannel_; // 
	int PlayCount;

private:		
	GameEngineSoundPlayer(); // default constructer ����Ʈ ������
	~GameEngineSoundPlayer(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	bool IsPlay();

	void PlayCountReset(int _Count = -1);

	// ���ļ� ��� ������ ���尡 ����ǰ� �־ �׳� ����Ѵ�. OneShot.
	void PlayOverLap(const std::string& _name, int _LoopCount = 1);

	// ������ ���尡 ����� �����߸� ���� ���带 ����Ѵ�.
	void PlayAlone(const std::string& _name, int _LoopCount = 1);

	void Stop();
};

