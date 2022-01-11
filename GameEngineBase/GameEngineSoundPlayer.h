#pragma once
#include "GameEngineSound.h"
#include "GameEngineSoundManager.h"

// �з� : FMOD Sound System ����
// �뵵 :
// ���� : Sound Channel�� ��� Sound�� Control�ϴ� ����� ����
class GameEngineSoundPlayer
{
	friend GameEngineSoundManager;

private:	// member Var
	FMOD::Channel* playChannel_; // 
	int PlayCount;	// �ش� Channel�� ��� Sound �ݺ����Ƚ��

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
	bool IsPlay(); // ���� Channel�� ��� Sound�� ���
	void PlayCountReset(int _Count = -1); // ���� Channel�� ��� Sound�� �ݺ����Ƚ���� Setting
	void PlayOverLap(const std::string& _name, int _LoopCount = 1);	// ���ļ� ��� ������ ���尡 ����ǰ� �־ �׳� ����Ѵ�. OneShot.
	void PlayAlone(const std::string& _name, int _LoopCount = 1);	// ������ ���尡 ����� �����߸� ���� ���带 ����Ѵ�.
	void Stop();	// ���� ä�ο��� ������� Sound�� ����
};

