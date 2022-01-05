#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// �з� : ���� �ھ�
// �뵵 : 
// ���� : ���� ������ �ʿ��� �⺻������ �����ϸ�, �ش� Ŭ������ ��ӹ޴� ��ü�� �ݵ�� �ʱ�ȭ/���ҽ��ε�/���ӷ���/����������
//           �����ϵ��� ����
class GameEngineCore : public GameEngineObjectBase
{
private:	// member Var

public:
	template<typename UserGameType>
	static void Start()
	{
		UserGameType NewUserGame;

		NewUserGame.Initialize();
		NewUserGame.ResourcesLoad();

		// Game Loop
		while (NewUserGame.IsOn())
		{
			NewUserGame.GameLoop();
		}

		NewUserGame.Release();
	}

protected:
	GameEngineCore(); // default constructer ����Ʈ ������
	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void EngineDestory();

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;
};

